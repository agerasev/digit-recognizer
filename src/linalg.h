#pragma once

#include "misc.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Copyes in[a] to out[s] */
void copy_array(const uint s, const real *in, real *out);

/** Sum of vectors 
 * out[s] = a[s] + b[s] */
void sum_array(const uint s, const real *a, const real *b, real *out);

/** Dif of vectors 
 * out[s] = a[s] - b[s] */
void dif_array(const uint s, const real *a, const real *b, real *out);

/** Hadamard product of vectors 
 * out[s] = a[s]*b[s] */
void product_array(const uint s, const real *a, const real *b, real *out);

/** Product of vector and scalar 
 * out[s] = a[s]*b */
void product_array_scal(const uint s, const real *a, const real b, real *out);

/** Fill array a[s] with zeros */
void zero_array(const uint s, real *a);

/** Matrix-vector product 
 * mat[sx][sy], in[sx], out[sy] */
void product_mat_vec(const uint sx, const uint sy, const real *mat, const real *in, real *out);

/** Transposed matrix-vector product 
 * mat[sy][sx], in[sx], out[sy] */
void product_mat_t_vec(const uint sx, const uint sy, const real *mat, const real *in, real *out);

/** Dot product of vectors 
 * a[s], b[s] */
real product_dot(const uint s, const real *a, const real *b);

/** Tensor product of vectors
 * ax[sx], ay[sy], out[sy][sx] */
void product_tensor(const uint sx, const uint sy, const real *ax, const real *ay, real *out);

/** Tensor product of vectors with transposed result
 * ax[sx], ay[sy], out[sx][sy] */
void product_tensor_t(const uint sx, const uint sy, const real *ax, const real *ay, real *out);

/** Sigmoid function and its derivative */
real sigma(real arg);
real sigma_deriv(real arg);

/** Vertor version of sigmoid function its derivative */
void sigma_vec(const uint s, const real *in, real *out);
void sigma_deriv_vec(uint s, const real *in, real *out);

#ifdef __cplusplus
}
#endif
