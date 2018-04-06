################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/QLearning/qLearner.c 

OBJS += \
./src/QLearning/qLearner.o 

C_DEPS += \
./src/QLearning/qLearner.d 


# Each subdirectory must supply rules for building sources it contributes
src/QLearning/%.o: ../src/QLearning/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/Users/s223852/bin/homebrew/include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


