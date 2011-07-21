/*
 * Arrow.h
 *
 *  Created on: Jul 19, 2011
 *      Author: yejiabin
 */

#ifndef ARROW_H
#define ARROW_H

class Arrow{
public:
	Arrow();
	Arrow(unsigned char arrowType);
	Arrow(unsigned char arrowType,
		unsigned int startTime, unsigned int duration);

	unsigned char getArrowType();
	unsigned int getStartTime();
	unsigned int getDuration();

	void setArrowType(unsigned char arrowType);
	void setStartTime(unsigned int startTime);
	void setDuration(unsigned int duration);

private:
	unsigned char arrowType;
	unsigned int startTime;
	unsigned int duration;
};

#endif
