#include "montecarlo.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>

void Print(std::ofstream &file, const int n) {
    file << n << '\n';
}

void Print(std::ofstream &file, const long double d) {
    file << d << '\n';
}

void Print (std::ofstream &file, const NumericVector &v) {
    for (int i = 0; i < int(v.size()); ++i) {
        file << v[i] << ' ';
    }
    file << '\n';
}

void Print (std::ofstream &file, const ComplexMatrices &m) {
    for (int i = 0; i < int(m.size()); ++i) {
        for (int j = 0; j < int(m[i].size()); ++j) {
            for (int k = 0; k < int(m[i][j].size()); ++k) {
                file << std::real(m[i][j][k]);
                long double imag = std::imag(m[i][j][k]);
        		if (imag >= 0.0) {
        		    file << '+';
                }
        	    file << imag << 'j' << ' ';
            }
            file << '\n';
        }
        file << '\n';
    }
    file << '\n';
}

void Print (std::ofstream &file, const NumericMatrixOfMatrices &m) {
    for (int i = 0; i < int(m.size()); ++i) {
        for (int j = 0; j < int(m[i].size()); ++j) {
            for (int k = 0; k < int(m[i][j].size()); ++k) {
                for (int l = 0; l < int(m[i][j][k].size()); ++l) {
                    file << m[i][j][k][l] << ' ';
                }
                file << '\n';
            }
            file << '\n';
        }
        file << '\n';
    }
    file << '\n';
}

void PrintResults(std::ofstream &file, const Results &results) {
    Print(file, results.n);
    Print(file, results.d);
    Print(file, results.min_epsilon);
    Print(file, results.initial_epsilon);
    Print(file, results.acceptation_rate);
    Print(file, results.n_attempts);
    Print(file, results.min_beta);
    Print(file, results.max_beta);
    Print(file, results.num_beta);
    Print(file, results.initial_states);
    Print(file, results.time_beta_finite);
    Print(file, results.time_beta_infinite);
    Print(file, results.beta_values);
    Print(file, results.mean_values);
    Print(file, results.result);
    Print(file, results.existence_result);
    Print(file, results.best_states);
    Print(file, results.pairwise_scalar_products);
}

void usage(const std::string &name) {
    std::cerr << "usage: " << '\n';
    std::cerr << "  " << name << " d n epsilon min_epsilon acceptation_rate";
    std::cerr << " n_attempts min_beta max_beta num_beta repetitions_beta_infinite results_filename" << '\n';
}

int main(int argc, char** argv) {
    if (argc != 12) {
        usage(std::string(argv[0]));
        return 1;
    }

    int d = std::stoi(argv[1]);
    int n = std::stoi(argv[2]);
    long double epsilon = std::stod(argv[3]);
    long double min_epsilon = std::stod(argv[4]);
    long double acceptation_rate = std::stod(argv[5]);
    long double n_attempts = std::stod(argv[6]);
    long double min_beta = std::stod(argv[7]);
    long double max_beta = std::stod(argv[8]);
    long double num_beta = std::stod(argv[9]);
    long double repetitions_beta_infinite = std::stod(argv[10]);
    std::string results_filename = argv[11];

    Results results = optimize(n, d, epsilon, min_epsilon, acceptation_rate, n_attempts, min_beta, max_beta, num_beta, repetitions_beta_infinite);
    std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10) << std::fixed;
    std::cout << "value obtained:  " << results.result << '\n';
    std::cout << "existence value: " << results.existence_result << '\n';
    std::cout << "time:            " << results.time_beta_finite + results.time_beta_infinite << 's' << '\n';

    std::ofstream file(results_filename, std::ofstream::out);
    file << std::setprecision(std::numeric_limits<long double>::max_digits10) << std::fixed;
    PrintResults(file, results);
    file.close();
}
