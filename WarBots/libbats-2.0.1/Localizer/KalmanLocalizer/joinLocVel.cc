#include "kalmanlocalizer.ih"

VectorXd KalmanLocalizer::joinLocVelVec(Vector3d const& loc, Vector3d const& vel) const
{
  VectorXd locVel(6);
  locVel.start<3>() = loc;
  locVel.end<3>() = vel;
  return locVel;
}


MatrixXd KalmanLocalizer::joinLocVelMat(Matrix3d const& loc, Matrix3d const& vel) const
{
  MatrixXd locVel(6,6);
  locVel.fill(0);
  locVel.corner<3,3>(TopLeft) = loc;
  locVel.corner<3,3>(BottomRight) = vel;

  return locVel;
}

