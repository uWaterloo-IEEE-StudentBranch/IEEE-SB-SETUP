#include "kalmanlocalizer.ih"

void KalmanLocalizer::updateGlobalRotation()
{
  Cochlea& cochlea = SCochlea::getInstance();
  AgentModel& am = SAgentModel::getInstance();

  Vector3d oldGyro = am.getOldGyro();
  Vector3d gyro = am.getGyro();
  double dt = cochlea.getDt(Cochlea::iTorsoGyro);
  //cout << oldGyro << endl;
  //cout << gyro << endl;
  
  Vector3d avgGyro = d_globalRotation * ((oldGyro + gyro) / 2.0);
  Vector3d rotation = avgGyro * dt;
  //cerr << "rotation: " << endl << rotation << endl;
  d_globalRotation = Math::makeRotation(rotation) * d_globalRotation;
  //cerr << "rotation matrix: " << endl << d_globalRotation.matrix() << endl;
  
}

