#include "normaldistribution.ih"

void NormalDistribution::predict(MatrixXd const& F, MatrixXd const& B, VectorXd const& u, MatrixXd const& Q)
{
  _debugLevel4("F:" << endl << F);
  _debugLevel4("B:" << endl << B);
  _debugLevel4("u:" << endl << u);
  _debugLevel4("Q:" << endl << Q);

  // x_k^- = F x_k-1 + B u_k-1
  // where u is the movement model
  // the movement model is 
  // All movement is accumulated in the movement model. so there is no extra movement: A = I and no translation is needed: B = 1, so:
  // x_k^- = x_k-1 + u_k-1
  d_mu = F * d_mu + B * u;
  
  // S_k^- = F P_k-1^+ F^T + Q_k-1 = P_k-1^+ + Q_k-1
  d_sigma = F * d_sigma * F.transpose() + Q;
  
}

