#include "debug.hpp"

void printEncoders(){
	printf("\n------\n");
	printf("left encoder =\t %.2lf\n", leftEncoder.get());
	printf("right encoder =\t %.2lf\n", rightEncoder.get());
	printf("back encoder =\t %.2lf\n", backEncoder.get());
}

void printOdom(){
	printf("\n------\n");
	printf("x =\t %.2lf\n", xPos);
	printf("y =\t %.2lf\n", yPos);
	printf("rot =\t %.2lf\n", rot);
}
