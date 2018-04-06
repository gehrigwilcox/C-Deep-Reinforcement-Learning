/*
 * main.c
 *
 *  Created on: Mar 21, 2018
 *      Author: Gehrig Wilcox
 */


#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_vector_float.h>
#include <time.h>

#include "NeuralNetwork/neuralNet.h"
#include "tools/prettyPrint.h"


/*
 *
 *
 * #IFDEF _WIN32
 *
 * 		Windows 32 bit
 *
 * #ELIF _WIN64
 *
 * 		Windows 64 bit
 *
 * #ELIF defined(__unix__) || defined(__unix) || defined(unix)
 *
 * 		Unix Distro
 *
 * 		#IF defined(__APPLE__) && defined(__MACH__)
 *
 * 			MacOSX
 *
 * 		#ELIF __linux__
 *
 * 			Linux Distro
 *
 * 		#ELIF __FreeBSD__
 *
 * 			FreeBSD Distro
 *
 * 		#ENDIF
 *
 * #ENDIF
 */


int main(int argc, char* argv[]){


	init();

	//clearScreen();

	srand(time(NULL));


	gsl_vector_float *input;

	gsl_vector_float *ans;


	input = gsl_vector_float_calloc(2);

	gsl_vector_float_set(input, 0, (float)rand()/(float)RAND_MAX*9);
	gsl_vector_float_set(input, 1, (float)rand()/(float)RAND_MAX*9);

	printf("BEFORE TRAINING: \n%f + %f = ", gsl_vector_float_get(input, 0), gsl_vector_float_get(input, 1));

	run(input);

	printf("%f\n", gsl_vector_float_get(input, 0));


	gsl_vector_float_free(input);

	for(int i = 0; i < 150; i++){



		input = gsl_vector_float_calloc(2);

		ans = gsl_vector_float_calloc(1);



		gsl_vector_float_set(input, 0, (float)rand()/(float)RAND_MAX*9);

		gsl_vector_float_set(input, 1, (float)rand()/(float)RAND_MAX*9);

		gsl_vector_float_set(ans, 0,

				gsl_vector_float_get(input, 0) + gsl_vector_float_get(input, 1)

		);

		train(input, ans);

		gsl_vector_float_free(input);

		gsl_vector_float_free(ans);

	}


	input = gsl_vector_float_calloc(2);

	gsl_vector_float_set(input, 0, (float)rand()/(float)RAND_MAX*9);
	gsl_vector_float_set(input, 1, (float)rand()/(float)RAND_MAX*9);

	printf("AFTER TRAINING: \n%f + %f = ", gsl_vector_float_get(input, 0), gsl_vector_float_get(input, 1));

	run(input);

	printf("%f\n", gsl_vector_float_get(input, 0));





	cleanup();

}
