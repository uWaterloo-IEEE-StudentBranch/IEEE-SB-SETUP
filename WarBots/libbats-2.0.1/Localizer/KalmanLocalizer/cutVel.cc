#include "kalmanlocalizer.ih"

Matrix3d KalmanLocalizer::cutVelMat(MatrixXd const& locvel) const
{
  Matrix3d vel = locvel.corner<3,3>(BottomRight);
  return vel;
}

