/*
 * neuralNet.c
 *
 *  Created on: Mar 21, 2018
 *      Author: Gehrig Wilcox
 */


#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "neuralNet.h"





// Input layer, hidden layers, output layer (how many nodes in each layer)
int layerSize[] = {2,2,1};

// Network is the number of spaces in between layers
gsl_matrix_float *network[sizeof(layerSize)/sizeof(layerSize[0]) - 1];

void init(){


	srand(time(NULL));

	//For every matrix in network
	for(int i = 0; i < sizeof(network)/sizeof(network[0]); i++){

		//make a new matrix that is the previous layer by the current layer (The layerSize array is shifted left one layer from the network array)
		//size 1 = how many outputs (rows)
		//size 2 = how many inputs (columns)
		network[i] = gsl_matrix_float_calloc(layerSize[i], layerSize[i+1]);


		//Fill matrix with random number between -1 and 1

		//for every row
		for(int j = 0; j < network[i]->size1; j++){
			//for every column
			for(int k = 0; k < network[i]->size2; k++){

				//Chose a random number between -1 and 1
				gsl_matrix_float_set(network[i], j, k,

						(float)rand()/(float)RAND_MAX*2-1

				);

			}
		}

	}

}

void cleanup(){

	//For every matrix in network
	for(int i = 0; i < sizeof(network)/sizeof(network[0]); i++){

		//Free
		gsl_matrix_float_free(network[i]);
	}

}

void run(gsl_vector_float *input){

	//For every matrix in network
	for(int i = 0; i < sizeof(network)/sizeof(network[0]); i++){


		gsl_vector_float *temp = gsl_vector_float_calloc(network[i]->size2);

		//Multiply the input vector by the network matrix and store it in input
		gsl_blas_sgemv(CblasTrans, 1.0, network[i], input, 0.0, temp);


		//Copy temp to input

		gsl_vector_float_free(input);

		input = gsl_vector_float_alloc(temp->size);

		gsl_vector_float_memcpy(input, temp);




		//apply activation function to input
		activationFunction(input);

	}

}

void train(gsl_vector_float *input, gsl_vector_float *targetValue){



	//Run the network normally to test the output
	//run(input);

	//make a vector for each layer in network
	gsl_vector_float *outputs[sizeof(network)/sizeof(network[0])+1];

	int outputsSize = sizeof(outputs)/sizeof(outputs[0]);

	outputs[0] = gsl_vector_float_alloc(input->size);
	{
		//copy input to outputs[0] to simplify recursive multiplication
		gsl_vector_float_memcpy(outputs[0], input);

		//for every vector in outputs
		//the -1 after sizeof(outputs[0]) is there because we are using outputs[i+1]
		for(int i = 0; i < sizeof(outputs)/sizeof(outputs[0]) - 1; i++){


			/*
				multiply each weight with the output of the previous layers corresponding node
				and then add them up (done through matrix and vector multiplication
				the output is then stored in outputs[i+1] which is then passed through
				the activation function
			*/

			outputs[i+1] = gsl_vector_float_alloc(network[i]->size2);

			gsl_blas_sgemv(CblasTrans, 1.0, network[i], outputs[i], 0.0, outputs[i+1]);

			activationFunction(outputs[i+1]);

		}

		gsl_vector_float *nodeErrors[sizeof(network)/sizeof(network[0])];


		int nodeErrorsSize = sizeof(nodeErrors)/sizeof(nodeErrors[0]);

		nodeErrors[nodeErrorsSize-1] = gsl_vector_float_alloc(outputs[outputsSize-1]->size);

		gsl_vector_float_memcpy(nodeErrors[nodeErrorsSize-1],outputs[outputsSize-1]);
		{

			findMSE(nodeErrors[nodeErrorsSize-1], targetValue);


			//iterate backwards through the network
			for(int i = nodeErrorsSize-2; i > -1; i--){

				//We transpose the matrix because we are going backwards


				gsl_matrix_float *transposed = gsl_matrix_float_alloc(network[i+1]->size2, network[i+1]->size1);

				gsl_matrix_float_transpose_memcpy(transposed, network[i+1]);


				nodeErrors[i] = gsl_vector_float_alloc(transposed->size2);

				//nodeErrors[i] = nodeErrors[i+1]*transposed;
				gsl_blas_sgemv(CblasTrans, 1.0, transposed, nodeErrors[i+1], 0.0, nodeErrors[i]);

				gsl_matrix_float_free(transposed);


			}

			//Adjust each weight by LEARNING_RATE * error * derivative of activation function at input

			//for each layer in network
			for(int i = 0; i < sizeof(network)/sizeof(network[0]); i++){
				//for each node in current layer
				for(int j = 0; j < network[i]->size2; j++){
					//for each weight connecting to each node in next layer
					for(int k = 0; k < network[i]->size1; k++){

						gsl_matrix_float_set(network[i], k, j,
								gsl_matrix_float_get(network[i], k, j) + LEARNING_RATE *
								gsl_vector_float_get(nodeErrors[i],j) *
								activationFunctionDerivative(gsl_vector_float_get(outputs[i],j))
								);

					}
				}
			}

		}

		//free nodeErrors
			for(int i = 0; i < nodeErrorsSize; i++){
				gsl_vector_float_free(nodeErrors[i]);
			}
	}

	//free outputs
	for(int i = 0; i < sizeof(outputs)/sizeof(outputs[0]); i++){
		gsl_vector_float_free(outputs[i]);
	}


	//TODO: Normalize network weights

	//printNetworkWeights();

}

void printNetworkWeights(){


	printf("BEGINNING NETWORK WEIGHTS\n");

	//for every layer
	for(int i = 0; i < sizeof(network)/sizeof(network[0]); i++){
		//for each node in current layer
		for(int j = 0; j < network[i]->size2; j++){
			//for each weight connecting each node in next layer
			for(int k = 0; k < network[i]->size1; k++){
				printf("%f ", gsl_matrix_float_get(network[i], k, j));
			}
			printf("\n");
		}
		printf("\n\n\n");
	}

	printf("DONE PRINTING NETWORK WEIGHTS\n");

}

void activationFunction(gsl_vector_float *in){

	/*
	 *
	 *  x > 0		x
	 *  x < 0		x * RELU_LEAK
	 *
	 *
	 */




	for(int i = 0; i < in->size; i++){

		float f = gsl_vector_float_get(in, i);

		//if num is greater than or equal to 0, multiply by one (aka do nothing)
		if(f < 0) gsl_vector_float_set(in, i, f * RELU_LEAK);


	}

}

void findMSE(gsl_vector_float *output, gsl_vector_float *expected){

	for(int i = 0; i < output->size; i++){

		/*
		 * For every number in output:
		 *
		 * 		num = pow(.5*(expected - output),2);
		 *
		 */

		gsl_vector_float_set(output, i,
				.5*pow(
						gsl_vector_float_get(expected,i) - gsl_vector_float_get(output,i),2));

	}

}

//Get the derivative of the activation function
float activationFunctionDerivative(float x){

	return x > 0 ? 1 : RELU_LEAK;

}
