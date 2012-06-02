#include "kalmanlocalizer.ih"

Matrix3d KalmanLocalizer::cutLocMat(MatrixXd const& locvel) const
{
  Matrix3d loc = locvel.corner<3,3>(TopLeft);
  return loc;
}

