#include "print_gd.h"

#include <stdio.h>

void GD_printBuffer(const Network *network, GD_Buffer *buffer)
{
	int l, ix, iy;
	
	for(l = 0; l < network->depth + 1; ++l)
	{
		//printf("%d: ", network->layer[l]->size);
		for(ix = 0; ix < network->layer[l]->size; ++ix)
		{
			printf("%f ", network->layer[l]->input[ix]);
		}
		printf("\n");
		
		//printf("%d: ", network->layer[l]->size);
		for(ix = 0; ix < network->layer[l]->size; ++ix)
		{
			printf("%f ", network->layer[l]->activation[ix]);
		}
		printf("\n");
		
		if(l < network->depth)
		{
			//printf("%d: ", network->connection[l]->output_size*network->connection[l]->input_size);
			for(iy = 0; iy < network->connection[l]->output_size; ++iy)
			{
				for(ix = 0; ix < network->connection[l]->input_size; ++ix)
				{
					printf("%f ", network->connection[l]->weight[iy*network->connection[l]->input_size + ix]);
				}
			}
			printf("\n");
			
			//printf("%d: ", network->connection[l]->output_size);
			for(iy = 0; iy < network->connection[l]->output_size; ++iy)
			{
				printf("%f ", network->connection[l]->bias[iy]);
			}
			printf("\n");
		}
	}
	
	for(l = 0; l < buffer->depth + 1; ++l)
	{
		//printf("%d: ", buffer->error[l].size);
		for(ix = 0; ix < buffer->error[l].size; ++ix)
		{
			printf("%f ", buffer->error[l].buffer[ix]);
		}
		printf("\n");
		
		//printf("%d: ", buffer->error[l].size);
		for(ix = 0; ix < buffer->error[l].size; ++ix)
		{
			printf("%f ", buffer->error[l].error[ix]);
		}
		printf("\n");
		
		if(l < buffer->depth)
		{
			//printf("%d: ", buffer->gradient[l].output_size*buffer->gradient[l].input_size);
			for(iy = 0; iy < buffer->gradient[l].output_size; ++iy)
			{
				for(ix = 0; ix < buffer->gradient[l].input_size; ++ix)
				{
					printf("%f ", buffer->gradient[l].grad_weight[iy*network->connection[l]->input_size + ix]);
				}
			}
			printf("\n");
			
			//printf("%d: ", buffer->gradient[l].output_size);
			for(iy = 0; iy < buffer->gradient[l].output_size; ++iy)
			{
				printf("%f ", buffer->gradient[l].grad_bias[iy]);
			}
			printf("\n");
		}
	}
}
