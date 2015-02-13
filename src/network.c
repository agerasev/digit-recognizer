#include "stdlib.h"

#include "network.h"

#include "linalg.h"

Layer *createLayer(uint size)
{
	Layer *layer = (Layer*) malloc(sizeof(Layer));
	layer->size = size;
	layer->input = (real*) malloc(sizeof(real)*size);
	layer->activation = (real*) malloc(sizeof(real)*size);
	return layer;
}

void destroyLayer(Layer *layer)
{
	free(layer->activation);
	free(layer->input);
	free(layer);
}

Connection *createConnection(uint input_size, uint output_size)
{
	Connection *con = (Connection*) malloc(sizeof(Connection));
	con->input_size = input_size;
	con->output_size = output_size;
	con->weight = (real*) malloc(sizeof(real)*input_size*output_size);
	con->bias = (real*) malloc(sizeof(real)*output_size);
	return con;
}

void destroyConnection(Connection *connection)
{
	free(connection->weight);
	free(connection->bias);
	free(connection);
}

Network *createNetwork(uint depth)
{
	Network *network = (Network*) malloc(sizeof(Network));
	network->depth = depth;
	network->layer = (Layer**) malloc(sizeof(Layer*)*(depth + 1));
	network->connection = (Connection**) malloc(sizeof(Connection*)*depth);
	return network;
}

void destroyNetwork(Network *network)
{
	free(network->connection);
	free(network->layer);
	free(network);
}

void feedforward(Network *network, const real *input)
{
	uint i;
	copy_array(
	    network->layer[0]->size,
	    input, 
	    network->layer[0]->activation
	);
	for(i = 0; i < network->depth; ++i)
	{
		product_mat_vec(
				network->connection[i]->input_size,
				network->connection[i]->output_size,
				network->connection[i]->weight,
				network->layer[i]->activation, 
				network->layer[i+1]->input
		);
		sum_array(
		    network->layer[i+1]->size,
		    network->layer[i+1]->input,
		    network->connection[i]->bias,
		    network->layer[i+1]->input
		);
		sigma_vec(
		    network->layer[i+1]->size,
		    network->layer[i+1]->input,
		    network->layer[i+1]->activation
		);
	}
}
