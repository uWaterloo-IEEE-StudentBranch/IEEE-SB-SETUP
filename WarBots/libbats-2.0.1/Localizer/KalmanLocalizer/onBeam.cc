#include "kalmanlocalizer.ih"

void KalmanLocalizer::onBeam(rf<BeamEvent> event)
{
  //cout << "Beam! Resetting..." << endl;
  
  d_globalRotation = AngleAxisd(event->getWhere()[2] / 180.0 * M_PI -.5 * M_PI, Vector3d::UnitZ());

  AgentModel& am = SAgentModel::getInstance();
  unsigned me = Types::PLAYER1 + am.getUnum() - 1;
  
  Vector3d pos = event->getWhere();
  pos[2] = 0.35;
  
  MatrixXd s2 = MatrixXd::Identity(6, 6) * 30;
  VectorXd m = VectorXd::Zero(6);
  d_objectInfos[Types::SELF]->locVelGlobal->init(joinLocVelVec(pos, Vector3d(0,0,0)), s2);
  d_objectInfos[Types::BALL]->locVelGlobal->init(m, s2);
  for (unsigned p = Types::PLAYER1; p <= Types::OPPONENT11; ++p)
    d_objectInfos[p]->locVelGlobal->init(m, s2);
    
}

