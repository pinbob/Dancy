################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ArManager.cpp \
../src/Arrow.cpp \
../src/Score.cpp \
../src/irrAR.cpp \
../src/main.cpp \
../src/main2.cpp 

OBJS += \
./src/ArManager.o \
./src/Arrow.o \
./src/Score.o \
./src/irrAR.o \
./src/main.o \
./src/main2.o 

CPP_DEPS += \
./src/ArManager.d \
./src/Arrow.d \
./src/Score.d \
./src/irrAR.d \
./src/main.d \
./src/main2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTEST_ARMANAGER -D_DEBUG -I/home/yejiabin/Documents/irrlicht-1.7.2/include -I/home/yejiabin/Documents/ARToolKit/include -O0 -g3 -Wall -c -fmessage-length=0 -Wno-write-strings -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


