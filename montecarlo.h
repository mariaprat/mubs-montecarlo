#ifndef MONTECARLO_H_
#define MONTECARLO_H_

#include "utilities-complex.h"

#include <vector>

using NumericVector = std::vector<long double>;
using NumericMatrix = std::vector<NumericVector>;
using NumericMatrices = std::vector<NumericMatrix>;
using NumericMatrixOfMatrices = std::vector<NumericMatrices>;

struct Results {
    int n;
    int d;
    long double min_epsilon;
    long double initial_epsilon;
    long double acceptation_rate;
    long double n_attempts;
    long double min_beta;
    long double max_beta;
    long double num_beta;
    ComplexMatrices initial_states;
    long double time_beta_finite;
    long double time_beta_infinite;
    NumericVector beta_values;
    NumericVector mean_values;
    long double result;
    long double existence_result;
    ComplexMatrices best_states;
    NumericMatrixOfMatrices pairwise_scalar_products;
};

/* Finds a local maximum of the CHSH function for d and a given number of mubs n
 * The parameters of the optimization can be tuned.
 */
Results optimize(int n, int d,
    long double epsilon,
    long double min_epsilon,
    long double acceptation_rate,
    long double n_attempts,
    long double min_beta,
    long double max_beta,
    long double num_beta,
    long double repetitions_beta_infinite);

#endif
