#ifndef UTILITIES_COMPLEX_H_
#define UTILITIES_COMPLEX_H_

#include <vector>
#include <complex>

using Complex = std::complex<long double>;
using ComplexVector = std::vector<Complex>;
using ComplexMatrix = std::vector<std::vector<Complex>>;
using ComplexMatrices = std::vector<std::vector<std::vector<Complex>>>;
/* Arguments:
 *  v: vector
 * Prints a vector
 */
void PrintVector(const ComplexVector &v);

/* Arguments:
 *  v: matrix
 * Prints a matrix
 */
void PrintMatrix(const ComplexMatrix &v);

/* Arguments:
 *  v: set of matrices
 * Prints a set of matrices
 */
void PrintSet(const ComplexMatrices &v);

/* Arguments:
 *  v: set of matrices
 * Prints a set of matrices nicely
 */
void PrintNiceSet(const ComplexMatrices &v);

/* Returns the relative error */
long double RelativeError(long double theoretical_value, long double experimental_value);

/* Arguments:
 *  v:     m x n set of vectors
 *  index: index in the set v (in [0, m-1])
 *  u:     vector with n elements
 * Replaces the index-th vector of v with u
 */
void Replace(ComplexMatrices &v, int index, const ComplexMatrix &u);

/* Arguments:
 *  u:    vector with n elements
 *  v:    vector with n elements
 * Returns the inner product of u and v
 */
Complex InnerProduct(const ComplexVector &u, const ComplexVector &v);

/* Arguments:
 * 	v: vector
 * Returns the norm of the vector v
 */
long double CalculateNorm(const ComplexVector &v);

/* Arguments:
 * 	u: set of vector
 * Normalise a vector
 */
void Normalise(ComplexVector &u);

/* Arguments:
 * 	v: set of vectors
 * Normalises each one of the vectors in the set
 */
void Normalise(ComplexMatrix &v);

/* Arguments:
 *  u: matrix
 * Orthonormalises the set of vectors described by u
 */
void Orthonormalise(ComplexMatrix &u);

/* Arguments:
 *  u:  d x d matrix
 *  du: d x d matrix
 *  w:  d x d matrix
 * Sums u and du and saves it in w
 */
void Sum(const ComplexMatrix &u, const ComplexMatrix &du, ComplexMatrix &w);

/* Arguments:
 * 	n:       number of random vectors
 * 	d:       dimension of the vectors
 *  mean:    mean of the normal distribution
 *  std_dev: standard deviation of the normal distribution
 * Returns a set of n random d-dimensional vectors generated using a normal distribution
 */
ComplexMatrix GenerateRandomMUBs(int n, int d, long double mean = 0.0, long double std_dev = 1.0);

/* Arguments:
 *	u: state
 *  v: state
 * Returns the CHSH value of the pair of states u and v
 */
long double CalculateT(const ComplexMatrix &u, const ComplexMatrix &v);

/* Arguments:
 *	v: set of states
 * Returns the sum of the CHSH values of all pairwise combinations of states in v
 */
long double CalculateT(const ComplexMatrices &v);

/* Arguments:
 *	v: set of states
 * Returns the scalar products of all pairwise combinations of states in v
 */
ComplexVector PairwiseScalarProducts(const ComplexMatrix &v);

#endif
