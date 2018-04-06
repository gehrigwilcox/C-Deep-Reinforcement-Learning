/*
 * neuralNet.h
 *
 *  Created on: Mar 21, 2018
 *      Author: Gehrig Wilcox
 */

#ifndef NEURALNET_H_
#define NEURALNET_H_


#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>



#define RELU_LEAK .000001


#define LEARNING_RATE .001


void init();

void cleanup();

void run(gsl_vector_float *input);

void train(gsl_vector_float *input, gsl_vector_float *targetValue);

void activationFunction(gsl_vector_float *in);

void findMSE(gsl_vector_float *output, gsl_vector_float *expected);

float individualMSE(float output, float expected);

float activationFunctionDerivative(float x);

void printNetworkWeights();


#endif /* NEURALNET_H_ */
