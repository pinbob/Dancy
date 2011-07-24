/*
 * menu.cpp
 *
 *  Created on: Jul 22, 2011
 *      Author: ovilia
 */

#include "Menu.h"

Menu::Menu() : curContent(0), contentAmt(0){}

Menu::Menu(int contentAmt, string* imagePath){
	if (contentAmt <= 0)
		return;
	this->curContent = 0;
	this->contentAmt = contentAmt;
	this->imagePath = new string[contentAmt];
	for (int i = 0; i < this->contentAmt; ++i){
		this->imagePath[i] = imagePath[i];
	}
}

Menu::~Menu(){
	if (contentAmt > 0){
		delete []imagePath;
	}
}

int Menu::getContentAmt(){
	return contentAmt;
}

int Menu::getCurContent(){
	return curContent;
}

string Menu::getPathAt(int index){
	return imagePath[index];
}

void Menu::setCurContent(int index){
	curContent = index;
}

void Menu::setPathAt(int index, string path){
	imagePath[index] = path;
}
