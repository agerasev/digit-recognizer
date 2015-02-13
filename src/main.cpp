#include <iostream>

#include "misc.h"

#include "network.h"
#include "network_gd.h"

#include "reader.hpp"

static const uint HIDDEN = 30;
static const uint EPOCHS = 128;
static const uint SAMPLE = 25;
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
	
	for(uint epoch = 0; epoch < EPOCHS; ++epoch)
	{
		std::cout << "Epoch " << epoch << std::endl;
		
		/* Learning */
		GD_shuffle(train_set->size,(void**)train_set->images,SEED*(epoch + 1));
		for(uint i = 0; i < train_set->size; ++i)
		{
			real result[10] = {0.0};
			result[train_set->images[i]->digit] = 1.0;
			
			feedforward(net,train_set->images[i]->data);
			GD_computeError(net,buf,result);
			GD_addGradient(net,buf);
			
			if(!((i + 1)%SAMPLE))
			{
				GD_normalizeGradient(buf,SAMPLE);
				GD_performDescent(net,buf,RATE);
				GD_clearGradient(buf);
			}
		}
		
		/* Testing */
		uint score = 0;
		real cost = 0.0;
		for(uint i = 0; i < test_set->size; ++i)
		{
			feedforward(net,test_set->images[i]->data);
			
			real result[10] = {0.0};
			result[test_set->images[i]->digit] = 1.0;
			cost += GD_computeCost(net,result);
			
			real max = net->layer[net->depth]->activation[0];
			uint digit = 0;
			for(uint j = 1; j < 10; ++j)
			{
				if(net->layer[net->depth]->activation[j] > max)
				{
					max = net->layer[net->depth]->activation[j];
					digit = j;
				}
			}
			
			if(digit == test_set->images[i]->digit)
			{
				++score;
			}
		}
		std::cout << "Total score: " << score << " of " << test_set->size << std::endl;
		std::cout << "Average cost: " << cost/test_set->size << std::endl;
		
		std::cout << std::endl;
	}
	
	GD_destroyBuffer(buf);
	
	destroyConnection(net->connection[0]);
	destroyConnection(net->connection[1]);
	destroyLayer(net->layer[0]);
	destroyLayer(net->layer[1]);
	destroyLayer(net->layer[2]);
	destroyNetwork(net);
	
	destroyImageSet(test_set);
	destroyImageSet(train_set);
	
	return 0;
}
