################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tools/fileIO.c \
../src/tools/prettyPrint.c 

OBJS += \
./src/tools/fileIO.o \
./src/tools/prettyPrint.o 

C_DEPS += \
./src/tools/fileIO.d \
./src/tools/prettyPrint.d 


# Each subdirectory must supply rules for building sources it contributes
src/tools/%.o: ../src/tools/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/Users/s223852/bin/homebrew/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


