#include "simplelocalizer.ih"

SimpleLocalizer::SimpleLocalizer()
{
  for (unsigned i = 0; i < Types::NOBJECTS; ++i)
  {
    d_locationsRaw[i] = new NormalDistribution(3);
    d_locationsLocal[i] = new NormalDistribution(3);
    d_locationsGlobal[i] = new NormalDistribution(3);

    d_velocitiesLocal[i] = new NormalDistribution(3);
    d_velocitiesGlobal[i] = new NormalDistribution(3);
  }
}

