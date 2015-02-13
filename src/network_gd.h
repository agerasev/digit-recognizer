#pragma once

#include "misc.h"

#include "network.h"

typedef struct GD_Error
{
	uint size;
	
	real *error;
	real *buffer;
}
GD_Error;

typedef struct GD_Gradient
{
	uint input_size;
	uint output_size;
	
	real *grad_weight;
	real *grad_bias;
	real *buffer;
}
GD_Gradient;

typedef struct GD_Buffer
{
	uint depth;
	
	GD_Error    *error;
	GD_Gradient *gradient;
}
GD_Buffer;

#ifdef __cplusplus
extern "C" {
#endif

void GD_randomize(Network *network, uint seed);
void GD_shuffle(uint length, void **array, uint seed);

GD_Buffer *GD_createBuffer(const Network *network);
void GD_destroyBuffer(GD_Buffer *buffer);

real GD_computeCost(const Network *network, const real *result);
void GD_computeError(const Network *network, GD_Buffer *buffer, const real *result);

void GD_addGradient(const Network *network, GD_Buffer *buffer);
void GD_normalizeGradient(GD_Buffer *buffer, uint sample_length);
void GD_clearGradient(GD_Buffer *buffer);

void GD_performDescent(Network *network, GD_Buffer *buffer, const real rate);

#ifdef __cplusplus
}
#endif

