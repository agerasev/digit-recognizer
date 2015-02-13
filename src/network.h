#pragma once

#include "misc.h"

typedef struct Layer
{
	uint size;
	
	real *input;
	real *activation;
}
Layer;

typedef struct Connection
{
	uint input_size;
	uint output_size;
	
	real *weight;
	real *bias;
}
Connection;

typedef struct Network
{
	uint depth;
	
	Layer      **layer;
	Connection **connection;
}
Network;

#ifdef __cplusplus
extern "C" {
#endif

Layer *createLayer(uint size);
void destroyLayer(Layer *layer);

Connection *createConnection(uint input_size, uint output_size);
void destroyConnection(Connection *connection);

Network *createNetwork(uint depth);
void destroyNetwork(Network *network);

void feedforward(Network *network, const real *input);

#ifdef __cplusplus
}
#endif
