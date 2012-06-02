#include "kalmanlocalizer.ih"

void KalmanLocalizer::update()
{
  updateGlobalRotation();
  
  updateRaw();

  checkGlobalRotation();

  updateSelfGlobal();

  updateBallGlobal();

  updatePlayersGlobal();

  globalToLocal();

  //cutDistributions();
}

