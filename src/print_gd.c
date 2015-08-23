#include "print_gd.h"

#include <stdio.h>

void GD_printBuffer(const Network *network, GD_Buffer *buffer)
{
	int l, ix;
	for(l = 0; l < network->depth; ++l)
	{
		for(ix = 0; ix < network->layer[l]->size; ++ix)
		{
			printf("%f ", network->layer[l]->input[ix]);
		}
		printf("\n");
		for(ix = 0; ix < network->layer[l]->size; ++ix)
		{
			printf("%f ", network->layer[l]->activation[ix]);
		}
		printf("\n");
	}
}
