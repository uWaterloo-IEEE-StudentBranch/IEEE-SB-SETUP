#include "math.ih"


Vector3d Math::cartesianToPolar(Vector3d const &cartesian)
{
	Vector3d polar;
	
  // XY-angle
  polar.y() = (normalizeRad(atan2(cartesian.y(),cartesian.x()) - .5 * M_PI));

  double d = sqrt(cartesian.x() * cartesian.x() + cartesian.y() * cartesian.y());

  // Latitude-angle
  polar.z() = (normalizeRad(atan2(cartesian.z(), d)));
  
  // Distance
  polar.x() = (sqrt(d * d + cartesian.z() * cartesian.z()));
  
  return polar;
}

/*Vector3d Math::cartesianToPolar2(Vector3d const &cartesian)
{
	Vector3d polar;
	
	polar.x() = (cartesian.length());
	
	Vector3d xy(cartesian.x(), cartesian.y(), 0);
	polar.y() = (acos(cartesian.x() / xy.length()));
	if (cartesian.y() < 0)
		polar.y() = (-polar.y());
		
	Vector3d xz(cartesian.x(), 0, cartesian.z());
	polar.z() = (acos(cartesian.x() / xz.length()));
	if (cartesian.z() < 0)
		polar.z() = (-polar.z());
	
	return polar;
}*/
