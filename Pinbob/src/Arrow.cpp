#include "Arrow.h"

Arrow::Arrow() : arrowType(1), startTime(0), duration(0){}
<<<<<<< HEAD

Arrow::Arrow(unsigned char arrowType) : startTime(0), duration(0){
	this->arrowType = arrowType;
}

Arrow::Arrow(unsigned char arrowType,
		unsigned int startTime, unsigned int duration){
	this->arrowType = arrowType;
	this->startTime = startTime;
	this->duration = duration;
}

unsigned char Arrow::getArrowType(){
	return arrowType;
}

unsigned int Arrow::getStartTime(){
	return startTime;
}

unsigned int Arrow::getDuration(){
	return duration;
}

void Arrow::setArrowType(unsigned char arrowType){
	this->arrowType = arrowType;
}

void Arrow::setStartTime(unsigned int startTime){
	this->startTime = startTime;
}

=======

Arrow::Arrow(unsigned char arrowType) : startTime(0), duration(0){
	this->arrowType = arrowType;
}
	
Arrow::Arrow(unsigned char arrowType, 
		unsigned int startTime, unsigned int duration){
	this->arrowType = arrowType;
	this->startTime = startTime;
	this->duration = duration;
}

unsigned char Arrow::getArrowType(){
	return arrowType;
}

unsigned int Arrow::getStartTime(){
	return startTime;
}

unsigned int Arrow::getDuration(){
	return duration;
}

void Arrow::setArrowType(unsigned char arrowType){
	this->arrowType = arrowType;
}

void Arrow::setStartTime(unsigned int startTime){
	this->startTime = startTime;
}

>>>>>>> ce36d6621c9e95b98b03f5e1e538ea2d7440a360
void Arrow::setDuration(unsigned int duration){
	this->duration = duration;
}

