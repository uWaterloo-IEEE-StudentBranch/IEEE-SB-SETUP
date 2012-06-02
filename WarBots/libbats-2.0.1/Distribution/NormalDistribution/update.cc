#include "normaldistribution.ih"

void NormalDistribution::update(MatrixXd const& H, VectorXd const& z, MatrixXd const& R)
{
  MatrixXd Ht = H.transpose();

  _debugLevel4("H:" << endl << H);
  _debugLevel4("z:" << endl << z);
  _debugLevel4("R:" << endl << R);
  
  // Innovation
  VectorXd y = z - H * d_mu;
  _debugLevel4("y:" << endl << y);
  
  // Innovation covariance
  MatrixXd S = H * d_sigma * Ht + R;
  _debugLevel4("S:" << endl << S);
  
  MatrixXd Sinv = S.inverse();
  _debugLevel4("S^-1:" << endl << Sinv);
  
  // Kalman gain
  MatrixXd K = d_sigma * Ht * Sinv;
  _debugLevel4("K:" << endl << K);
  
  d_mu = d_mu + K * y;
  
  d_sigma = (d_I - K * H) * d_sigma;
}

