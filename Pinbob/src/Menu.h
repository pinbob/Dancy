/*
 * menu.h
 *
 *  Created on: Jul 22, 2011
 *      Author: ovilia
 */

#ifndef MENU_H_
#define MENU_H_

#include <string>
using namespace std;

class Menu{
public:
	Menu();
	Menu(int contentAmt, string* imagePath);
	~Menu();

	string getPathAt(int index);
	int getContentAmt();
	int getCurContent();

	void setPathAt(int index, string path);
	void setCurContent(int index);

private:
	string* imagePath;
	int contentAmt;
	int curContent;
};


#endif /* MENU_H_ */
