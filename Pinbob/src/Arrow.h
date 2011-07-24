#ifndef ARROW_H
#define ARROW_H

<<<<<<< HEAD
#ifndef ARROW_H
#define ARROW_H

=======
>>>>>>> ce36d6621c9e95b98b03f5e1e538ea2d7440a360
class Arrow{
public:
	Arrow();
	Arrow(unsigned char arrowType);
<<<<<<< HEAD
	Arrow(unsigned char arrowType,
		unsigned int startTime, unsigned int duration);

	unsigned char getArrowType();
	unsigned int getStartTime();
	unsigned int getDuration();

=======
	Arrow(unsigned char arrowType, 
		unsigned int startTime, unsigned int duration);
		
	unsigned char getArrowType();
	unsigned int getStartTime();
	unsigned int getDuration();
	
>>>>>>> ce36d6621c9e95b98b03f5e1e538ea2d7440a360
	void setArrowType(unsigned char arrowType);
	void setStartTime(unsigned int startTime);
	void setDuration(unsigned int duration);

private:
	unsigned char arrowType;
	unsigned int startTime;
	unsigned int duration;
};

#endif
