#include "debug.hpp"

void printEncoders(){
	printf("\n------\n");
	printf("left encoder =\t %.2lf\n", leftEncoder.get());
	printf("right encoder =\t %.2lf\n", rightEncoder.get());
	printf("back encoder =\t %.2lf\n", backEncoder.get());
}

void printOdom(){
	OdomState odom = chassis->getState();
	printf("\n------\n");
	printf("x =\t %.2lf\t %.2lf\n", odom.x.convert(inch), xPos);
	printf("y =\t %.2lf\t %.2lf\n", odom.y.convert(inch), yPos);
	printf("rot =\t %.2lf\t %.2lf\n", odom.theta.convert(degree), rot);
}
