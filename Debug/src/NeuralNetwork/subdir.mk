################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/NeuralNetwork/neuralNet.c 

OBJS += \
./src/NeuralNetwork/neuralNet.o 

C_DEPS += \
./src/NeuralNetwork/neuralNet.d 


# Each subdirectory must supply rules for building sources it contributes
src/NeuralNetwork/%.o: ../src/NeuralNetwork/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/Users/s223852/bin/homebrew/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


