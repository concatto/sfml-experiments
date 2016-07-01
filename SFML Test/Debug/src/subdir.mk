################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SFML\ Test.cpp 

OBJS += \
./src/SFML\ Test.o 

CPP_DEPS += \
./src/SFML\ Test.d 


# Each subdirectory must supply rules for building sources it contributes
src/SFML\ Test.o: ../src/SFML\ Test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"src/SFML Test.d" -MT"src/SFML\ Test.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


