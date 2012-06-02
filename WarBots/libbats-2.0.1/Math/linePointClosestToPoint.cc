#include "math.ih"

/**
  *  Calculates the nearest point on a line to
  *  another point.
  *
  *  @param l0 the start point of the line.
  *  @param lVect the not normalized line vector.
  *  @param point the other point.
  */
Vector3d Math::linePointClosestToPoint(Vector3d const &l0,
				 Vector3d const &lVect,
				 Vector3d const &point)
{
  Vector3d v = lVect.normalized();
  
  Vector3d s = calcPerpend(v);

  // There probably is a more efficient formula.
  double u = ((s[0]/s[1])*(l0.y() - point.y()) + (point.x() - l0.x()))/(v[0] - (s[0]/s[1])*v[1]);

  
  // When no perpendicular line is posible within the segment, use
  // the closest endpoint.
  if (u > lVect.norm()) {
    if ((l0 - point).norm() < ((l0 + lVect) - point).norm())
      return l0;
    else
      return l0+lVect;
  }

  return l0 + v*u;
}

