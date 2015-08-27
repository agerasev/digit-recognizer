#include <iostream>

#include "misc.h"

#include "network.h"
#include "network_gd.h"
#include "print_gd.h"

#include "reader.hpp"

static const uint HIDDEN = 30;
static const uint EPOCHS = 16;
static const uint SAMPLE = 10;
static const real RATE = 1.0;

static const uint SEED = 0x87654321;

int main(int, char *[])
{
	ImageSet *test_set = createImageSet(
	    "case/t10k-labels.idx1-ubyte",
	    "case/t10k-images.idx3-ubyte"
	);
	
	/*
	ImageSet *train_set = createImageSet(
	    "case/train-labels.idx1-ubyte",
	    "case/train-images.idx3-ubyte"
	);
	*/
	
	ImageSet *train_set = test_set;
	
	if(test_set == nullptr || train_set == nullptr)
	{
		return 1;
	}
	
	Network *net = createNetwork(2);
	net->layer[0] = createLayer(test_set->size_x*test_set->size_y);
	net->layer[1] = createLayer(HIDDEN);
	net->layer[2] = createLayer(10);
	net->connection[0] = createConnection(net->layer[0]->size,net->layer[1]->size);
	net->connection[1] = createConnection(net->layer[1]->size,net->layer[2]->size);
	
	GD_randomize(net,SEED);
	
	GD_Buffer *buf = GD_createBuffer(net);
	GD_clearGradient(buf);
	
	/* Learning */
	real result[10] = {0.0};
	result[train_set->images[0]->digit] = 1.0;
	
	feedforward(net,train_set->images[0]->data);
	GD_computeError(net,buf,result);
	GD_addGradient(net,buf);
	
	// GD_printBuffer(net,buf); //

	GD_normalizeGradient(buf,1);
	GD_performDescent(net,buf,RATE);
	
	GD_printBuffer(net,buf); //
	
	GD_clearGradient(buf);
	
	GD_destroyBuffer(buf);
	
	destroyConnection(net->connection[0]);
	destroyConnection(net->connection[1]);
	destroyLayer(net->layer[0]);
	destroyLayer(net->layer[1]);
	destroyLayer(net->layer[2]);
	destroyNetwork(net);
	
	destroyImageSet(test_set);
	//destroyImageSet(train_set);
	
	return 0;
}
