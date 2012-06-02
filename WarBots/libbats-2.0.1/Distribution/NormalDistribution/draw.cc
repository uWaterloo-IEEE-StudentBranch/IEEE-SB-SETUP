#include "normaldistribution.ih"

VectorXd NormalDistribution::draw() const
{
  VectorXd z(d_size);
  for (unsigned i = 0; i < d_size; ++i)
    z(i) = Random::stdNorm();
    
  return d_mu + d_sigma.llt().matrixL() * z;
}

