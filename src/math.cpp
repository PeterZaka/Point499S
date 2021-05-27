#include "math.hpp"

double posMod(double x, double y){
	double answer = fmod(x, y);
	if (answer < 0)
		return answer + y;
	return answer;
}

double findShortestRotation(double start, double rotation){
	double startNormal = posMod(start, 360);
	rotation = posMod(rotation, 360);
	double over = rotation + 360;
	double under = rotation - 360;

  double overDistance = abs(over - startNormal);
	double middleDistance = abs(rotation - startNormal);
	double underDistance = abs(under - startNormal);
	double bestDistance = std::min({
		overDistance,
		middleDistance,
		underDistance}
		);

	if (bestDistance == overDistance)
		return over - startNormal + start;
	else if (bestDistance == middleDistance)
		return rotation - startNormal + start;
	else
		return under - startNormal + start;
}
