/* TODO: Use BLAS */

#include "linalg.h"

#include <math.h>

real sqr(real a)
{
	return a*a;
}

void copy_array(const uint s, const real *in, real *out)
{
	uint i;
	for(i = 0; i < s; ++i)
	{
		out[i] = in[i];
	}
}

void sum_array(const uint s, const real *a, const real *b, real *out)
{
	uint i;
	for(i = 0; i < s; ++i)
	{
		out[i] = a[i] + b[i];
	}
}

void dif_array(const uint s, const real *a, const real *b, real *out)
{
	uint i;
	for(i = 0; i < s; ++i)
	{
		out[i] = a[i] - b[i];
	}
}

void product_array(const uint s, const real *a, const real *b, real *out)
{
	uint i;
	for(i = 0; i < s; ++i)
	{
		out[i] = a[i]*b[i];
	}
}

void product_array_scal(const uint s, const real *a, const real b, real *out)
{
	uint i;
	for(i = 0; i < s; ++i)
	{
		out[i] = a[i]*b;
	}
}

void zero_array(const uint s, real *a)
{
	uint i;
	for(i = 0; i < s; ++i)
	{
		a[i] = 0.0;
	}
}

void product_mat_vec(const uint sx, const uint sy, const real *mat, const real *in, real *out)
{
	uint ix, iy;
	for(iy = 0; iy < sy; ++iy)
	{
		const real *line = mat + sx*iy;
		real sum = 0.0;
		for(ix = 0; ix < sx; ++ix)
		{
			sum += line[ix]*in[ix];
		}
		out[iy] = sum;
	}
}

void product_mat_t_vec(const uint sx, const uint sy, const real *mat, const real *in, real *out)
{
	uint ix, iy;
	for(iy = 0; iy < sy; ++iy)
	{
		real sum = 0.0;
		for(ix = 0; ix < sx; ++ix)
		{
			sum += mat[ix*sy + iy]*in[ix];
		}
		out[iy] = sum;
	}
}

real product_dot(const uint s, const real *a, const real *b)
{
	uint i;
	real sum = 0.0;
	for(i = 0; i < s; ++i)
	{
		sum += a[i]*b[i];
	}
	return sum;
}

void product_tensor(const uint sx, const uint sy, const real *ax, const real *ay, real *out)
{
	uint ix, iy;
	for(iy = 0; iy < sy; ++iy)
	{
		for(ix = 0; ix < sx; ++ix)
		{
			out[iy*sx + ix] = ax[ix]*ay[iy];
		}
	}
}

void product_tensor_t(const uint sx, const uint sy, const real *ax, const real *ay, real *out)
{
	uint ix, iy;
	for(ix = 0; ix < sx; ++ix)
	{
		for(iy = 0; iy < sy; ++iy)
		{
			out[ix*sy + iy] = ax[ix]*ay[iy];
		}
	}
}

real sigma(real arg)
{
	return 1.0/(1.0 + exp(-arg));
}

real sigma_deriv(real arg)
{
	real ep = exp(-arg);
	return ep/sqr(1.0 + ep);
}

void sigma_vec(const uint s, const real *in, real *out)
{
	uint i;
	for(i = 0; i < s; ++i)
	{
		out[i] = sigma(in[i]);
	}
}

void sigma_deriv_vec(uint s, const real *in, real *out)
{
	uint i;
	for(i = 0; i < s; ++i)
	{
		out[i] = sigma_deriv(in[i]);
	}
}
