#include "math.hpp"

#define PI 3.141592653589793

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

double findRotationTo(double startX, double startY, double endX, double endY){
	double angle = atan2f(
    ( endY - startY ),
    ( endX - startX )
  ) * (180 / PI);
  // convert counterclockwise to clockwise
  angle = -angle + 90;
	return angle;
}

double findDistanceTo(double startX, double startY, double endX, double endY){
	return sqrtf(
    pow ( ( endX - startX ), 2.0) +
    pow ( ( endY - startY ), 2.0)
  );
}

point findOffsetTarget(point start, point target, point offset, double extraDistance){
	double d = sqrt(
		pow ( offset.x, 2.0 ) +
		pow ( offset.y, 2.0 ) ) + extraDistance;
	double dt = atan2(offset.y, offset.x) - ( PI / 2.0 );
	double t = atan2( target.y - start.y, target.x - start.x ) + dt;
	point newTarget;
	newTarget.x = target.x + ( d * cos(t) );
	newTarget.y = target.y + ( d * sin(t) );
	return newTarget;
}
