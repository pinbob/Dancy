################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ASceneNode.cpp \
../src/ArManager.cpp \
../src/Arrow.cpp \
../src/ArrowFactory.cpp \
../src/ArrowPrototypeFactory.cpp \
../src/ConfigFileManager.cpp \
../src/DefaultGameLogic.cpp \
../src/GSTPlayer.cpp \
../src/GameEventReceiver.cpp \
../src/GameInfo.cpp \
../src/GameObject.cpp \
../src/GameOverState.cpp \
../src/HighScore.cpp \
../src/MenuFactory.cpp \
../src/MenuHandler.cpp \
../src/ModeScreen.cpp \
../src/NoteData.cpp \
../src/NoteTypes.cpp \
../src/NotesLoader.cpp \
../src/Score.cpp \
../src/SettingHandler.cpp \
../src/Song.cpp \
../src/SongCollection.cpp \
../src/SongListScreen.cpp \
../src/StateMachine.cpp \
../src/irrAR.cpp \
../src/main.cpp \
../src/main2.cpp \
../src/test.cpp \
../src/yatest.cpp 

OBJS += \
./src/ASceneNode.o \
./src/ArManager.o \
./src/Arrow.o \
./src/ArrowFactory.o \
./src/ArrowPrototypeFactory.o \
./src/ConfigFileManager.o \
./src/DefaultGameLogic.o \
./src/GSTPlayer.o \
./src/GameEventReceiver.o \
./src/GameInfo.o \
./src/GameObject.o \
./src/GameOverState.o \
./src/HighScore.o \
./src/MenuFactory.o \
./src/MenuHandler.o \
./src/ModeScreen.o \
./src/NoteData.o \
./src/NoteTypes.o \
./src/NotesLoader.o \
./src/Score.o \
./src/SettingHandler.o \
./src/Song.o \
./src/SongCollection.o \
./src/SongListScreen.o \
./src/StateMachine.o \
./src/irrAR.o \
./src/main.o \
./src/main2.o \
./src/test.o \
./src/yatest.o 

CPP_DEPS += \
./src/ASceneNode.d \
./src/ArManager.d \
./src/Arrow.d \
./src/ArrowFactory.d \
./src/ArrowPrototypeFactory.d \
./src/ConfigFileManager.d \
./src/DefaultGameLogic.d \
./src/GSTPlayer.d \
./src/GameEventReceiver.d \
./src/GameInfo.d \
./src/GameObject.d \
./src/GameOverState.d \
./src/HighScore.d \
./src/MenuFactory.d \
./src/MenuHandler.d \
./src/ModeScreen.d \
./src/NoteData.d \
./src/NoteTypes.d \
./src/NotesLoader.d \
./src/Score.d \
./src/SettingHandler.d \
./src/Song.d \
./src/SongCollection.d \
./src/SongListScreen.d \
./src/StateMachine.d \
./src/irrAR.d \
./src/main.d \
./src/main2.d \
./src/test.d \
./src/yatest.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTEST_ARMANAGER -DTEST_ALL -D_DEBUG -I/home/yejiabin/Documents/irrlicht-1.7.2/include -I/home/yejiabin/Downloads/irrKlang-1.3.0/include -I/home/yejiabin/Downloads/ARToolKit/include -O2 -g3 -Wall -c -fmessage-length=0 -Wno-write-strings `pkg-config --cflags --libs gstreamer-0.10` -pthread -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


