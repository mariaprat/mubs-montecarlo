#include "montecarlo.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <random>
#include <cmath>
#include <string>
#include <limits>

int n_choose_2(int n) {
    return n*(n-1)/2;
}

void run_attempts(
    Results &results,
    int n,
    int d,
    bool &continue_iterating,
    ComplexMatrices &v,
    ComplexMatrices &best_v,
    long double &best_t, long double &epsilon, long double min_epsilon,
    long double acceptation_rate, long double n_attempts,
    bool beta_infinite,
    long double beta = -1.0) {

    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 generator(seed);

    long double mean_t = CalculateT(v);

    if (continue_iterating) {
        long double n_accepted = 0;

        for (long double attempt = 1; continue_iterating and attempt <= n_attempts; ++attempt) {
            /* we choose one of the n matrices randomly and rotate it by some random amount */
            int m = generator()%n;
            ComplexMatrix u = v[m];
            ComplexMatrix du = GenerateRandomMUBs(d, d, 0.0, epsilon);
            ComplexMatrix w(d, ComplexVector(d));
            Sum(u, du, w);
            Orthonormalise(w);

            long double old_t = CalculateT(v);
            v[m] = w;
            long double new_t = CalculateT(v);
            v[m] = u;
            long double deltaT = new_t - old_t;

            /* Metropolis rule */

            bool accepted = (deltaT > 0.0);

            if (not accepted and not beta_infinite) {
                accepted = ((long double)(generator() - generator.min())/(long double)(generator.max()) < exp(beta*deltaT));
            }

            if (accepted) {
                ++n_accepted;
                v[m] = w;
            }

            if (new_t > best_t) {
                best_t = new_t;
                best_v = v;
            }

            mean_t = (mean_t*attempt + new_t)/(attempt + 1.0);
        }

        long double ratio = n_accepted/n_attempts;
        if (ratio < 0.8 * acceptation_rate) {
            epsilon *= 0.8;
        } else if (ratio > 1.2 * acceptation_rate) {
            epsilon *= 1.2;
        }

        if (epsilon <= min_epsilon) {
	    std::cout << "MIN EPSILON REACHED\n";
            continue_iterating = false;
        }
    }

    results.beta_values.push_back(beta);
    results.mean_values.push_back(mean_t);
}

Results optimize(int n, int d, long double epsilon,
    long double min_epsilon, long double acceptation_rate,
    long double n_attempts, long double min_beta, long double max_beta,
    long double num_beta, long double repetitions_beta_infinite) {

    Results results;

    results.n = n;
    results.d = d;
    results.min_epsilon = min_epsilon;
    results.initial_epsilon = epsilon;
    results.acceptation_rate = acceptation_rate;
    results.n_attempts = n_attempts;
    results.min_beta = min_beta;
    results.max_beta = max_beta;
    results.num_beta = num_beta;

    long double step = (max_beta - min_beta)/(num_beta - 1);

    long double best_t = 0.0;
    ComplexMatrices best_v(n);
    ComplexMatrices v(n);

    for (int i = 0; i < n; ++i) {
        v[i] = GenerateRandomMUBs(d, d);
        Orthonormalise(v[i]);
    }

    results.initial_states = v;

    auto start_beta_finite = std::chrono::high_resolution_clock::now();

    bool continue_iterating = true;

    for (long double beta = min_beta; continue_iterating and beta <= max_beta + step/2; beta += step) {
        std::cerr << "beta: " << beta << '\n';
        run_attempts(results, n, d, continue_iterating, v, best_v, best_t, epsilon, min_epsilon, acceptation_rate, n_attempts, false, beta);
    }

    auto end_beta_finite = std::chrono::high_resolution_clock::now();

    results.time_beta_finite = std::chrono::duration<double>(end_beta_finite - start_beta_finite).count();

    auto start_beta_infinite = std::chrono::high_resolution_clock::now();

    continue_iterating = true;

    std::cerr << "starting beta infinite iterations...\n";
    // we run some attemps of a move with beta = infinite
    while (repetitions_beta_infinite--) {
        run_attempts(results, n, d, continue_iterating, best_v, best_v, best_t, epsilon, min_epsilon, acceptation_rate, n_attempts, true);
        if ((long long)(repetitions_beta_infinite)%5 == 0) {
            std::cerr << repetitions_beta_infinite << " iterations left\n";
        }
    }

    auto end_beta_infinite = std::chrono::high_resolution_clock::now();

    results.time_beta_infinite = std::chrono::duration<double>(end_beta_infinite - start_beta_infinite).count();

    results.result = best_t;
    results.existence_result = n_choose_2(n) * d * sqrtl(d * (d - 1));
    results.best_states = best_v;

    NumericMatrixOfMatrices &r = results.pairwise_scalar_products;
    r = NumericMatrixOfMatrices(n, NumericMatrices(n, NumericMatrix(d, NumericVector(d))));
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            for (int k = 0; k < d; ++k) {
                for (int l = 0; l < d; ++l) {
                    // choose two states
                    r[i][j][k][l] = std::norm(InnerProduct(best_v[i][k], best_v[j][l]));
                    if (i != j) {
                        r[j][i][k][l] = r[i][j][k][l];
                    }
                }
            }
        }
    }

    return results;
}
