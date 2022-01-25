#include "utilities-complex.h"

#include <cmath>
#include <numeric>
#include <random>
#include <chrono>
#include <iostream>

void PrintVector(const ComplexVector &v) {
    for (int j = 0; j < int(v.size()); ++j) {
        if (j != 0) {
            std::cout << " ";
        }
        std::cout << v[j];
    }
    std::cout << '\n';
}

void PrintMatrix(const ComplexMatrix &v) {
    for (int i = 0; i < int(v.size()); ++i) {
        PrintVector(v[i]);
    }
}

void PrintSet(const ComplexMatrices &v) {
    for (int i = 0; i < int(v.size()); ++i) {
        std::cout << i + 1 << "-th matrix" << '\n';
        PrintMatrix(v[i]);
        std::cout << '\n';
    }
}

void PrintNiceSet(const ComplexMatrices &v) {
    for (int i = 0; i < int(v.size()); ++i) {
        PrintMatrix(v[i]);
        std::cout << '\n';
    }
}

long double RelativeError(long double theoretical_value, long double experimental_value) {
    long double result = theoretical_value - experimental_value;
    return std::abs(result)/theoretical_value;
}

void Replace(ComplexMatrices &v, int index, const ComplexMatrix &u) {
    for (int i = 0; i < int(v[index].size()); ++i) {
        for(int j = 0; j < int(v[index][i].size()); ++j) {
            v[index][i][j] = u[i][j];
        }
    }
}

Complex InnerProduct(const ComplexVector &u, const ComplexVector &v) {
    Complex result = Complex(0.0, 0.0);
    for (int i = 0; i < int(u.size()); ++i) {
        result += u[i]*std::conj(v[i]);
    }
    return result;
}

long double CalculateNorm(const ComplexVector &v) {
	return sqrtl(std::real(InnerProduct(v, v)));
}

void Normalise(ComplexVector &u) {
	long double norm = CalculateNorm(u);
	for (int j = 0; j < int(u.size()); ++j) {
		u[j] /= norm;
	}
}

void Normalise(ComplexMatrix &u) {
	for (int i = 0; i < int(u.size()); ++i) {
        Normalise(u[i]);
	}
}

void Mix(ComplexVector &a,
    ComplexVector &b, Complex k) {
    for (int i = 0; i < int(a.size()); ++i) {
        a[i] += k*b[i];
    }
}

void Orthonormalise(ComplexMatrix &u) {
    /* Gram-Schmidt */
    for (int i = 0; i < int(u.size()); ++i) {
        for (int j = 0; j < i; ++j) {
            Complex product = InnerProduct(u[i], u[j]);
            long double norm = std::norm(InnerProduct(u[j], u[j]));
            Mix(u[i], u[j], -product/(norm * norm));
	    }
        Normalise(u[i]);
    }
}

void Sum(const ComplexMatrix &u, const ComplexMatrix &du, ComplexMatrix &w) {
    for (int i = 0; i < int(u.size()); ++i) {
        for (int j = 0; j < int(u[i].size()); ++j) {
            w[i][j] = u[i][j] + du[i][j]; }
    }
}

ComplexMatrix GenerateRandomMUBs(int n, int d, long double mean, long double std_dev) {
	ComplexMatrix v(n, ComplexVector(d));
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937_64 generator(seed);
	std::normal_distribution<long double> distribution(mean, std_dev);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < d; ++j) {
            v[i][j] = Complex(distribution(generator), distribution(generator));
		}
	}
	return v;
}

long double CalculateT(const ComplexMatrix &u,
     const ComplexMatrix &v) {
    long double t = 0;
    for (int j = 0; j < int(u.size()); ++j) {
        for (int k = 0; k < int(v.size()); ++k) {
	        long double norm = std::norm(InnerProduct(u[j], v[k]));
            t += sqrtl(1 - norm);
        }
    }
    return t;
}

long double CalculateT(const ComplexMatrices &v) {
	long double t = 0;
	for (int i = 0; i < int(v.size()); ++i) {
		for (int j = i+1; j < int(v.size()); ++j) {
            t += CalculateT(v[i], v[j]);
		}
	}
	return t;
}

ComplexVector PairwiseScalarProducts(const ComplexMatrix &v) {
	ComplexVector u;
	for (int i = 0; i < int(v.size()); ++i) {
		for (int j = 0; j < int(v.size()); ++j) {
			u.push_back(InnerProduct(v[i], v[j]));
		}
	}
	return u;
}
