#include "kalmanlocalizer.ih"

KalmanLocalizer::KalmanLocalizer()
{
  WorldModel& wm = SWorldModel::getInstance();
  double fieldLength = wm.getFieldLength();
  double fieldWidth = wm.getFieldWidth();
  double goalWidth = wm.getGoalWidth();
  
  
  double halfFieldLength = fieldLength / 2;
  double halfFieldWidth = fieldWidth / 2;
  double halfGoalWidth = goalWidth / 2;
  
  d_globalTransform = AngleAxisd(-.5 * M_PI, Vector3d::UnitZ());
  d_globalRotation = Transform3d(d_globalTransform.rotation());;
  
  d_globalTranslation = Transform3d(MatrixXd::Identity(4,4));
  d_localTransform = Transform3d(MatrixXd::Identity(4,4));

  
  AgentModel& am = SAgentModel::getInstance();

  for (unsigned i = 0; i < Types::NOBJECTS; ++i)
  {
    /*
    d_locationsRaw[i] = new NormalDistribution(3);
    d_locationsLocal[i] = new NormalDistribution(3);
    d_locationsGlobal[i] = new NormalDistribution(3);

    d_velocitiesLocal[i] = new NormalDistribution(3);
    d_velocitiesGlobal[i] = new NormalDistribution(3);
    */
    if (i >= Types::PLAYER1 && i <= Types::OPPONENT11)
    {
      rf<PlayerInfo> info = new PlayerInfo();
      info->locLArmLocal = Vector3d(0,0,0);
      info->locRArmLocal = Vector3d(0,0,0);
      info->locLFootLocal = Vector3d(0,0,0);
      info->locRFootLocal = Vector3d(0,0,0);

      info->locLArmGlobal = Vector3d(0,0,0);
      info->locRArmGlobal = Vector3d(0,0,0);
      info->locLFootGlobal = Vector3d(0,0,0);
      info->locRFootGlobal = Vector3d(0,0,0);
      d_objectInfos[i] = info;
    }
    else
      d_objectInfos[i] = new ObjectInfo();

    d_objectInfos[i]->alive = false;
    d_locationsVelocitiesRaw[i] = new NormalDistribution(6);
    d_objectInfos[i]->locVelLocal = new NormalDistribution(6);
    d_objectInfos[i]->locVelGlobal = new NormalDistribution(6);
  }
  
  Matrix3d s = Matrix3d::Identity();
  s = s * 30;
  
  Matrix3d i = Matrix3d::Identity();
  
  d_objectInfos[Types::FLAG1US]->locVelGlobal->init(joinLocVelVec(Vector3d(-halfFieldLength, halfFieldWidth, 0), Vector3d(0,0,0)), MatrixXd::Identity(6, 6));
  d_objectInfos[Types::FLAG2US]->locVelGlobal->init(joinLocVelVec(Vector3d(-halfFieldLength, -halfFieldWidth, 0), Vector3d(0,0,0)), MatrixXd::Identity(6, 6));
  d_objectInfos[Types::FLAG1THEM]->locVelGlobal->init(joinLocVelVec(Vector3d(halfFieldLength, halfFieldWidth, 0), Vector3d(0,0,0)), MatrixXd::Identity(6, 6));
  d_objectInfos[Types::FLAG2THEM]->locVelGlobal->init(joinLocVelVec(Vector3d(halfFieldLength, -halfFieldWidth, 0), Vector3d(0,0,0)), MatrixXd::Identity(6, 6));
  
  d_objectInfos[Types::GOAL1US]->locVelGlobal->init(joinLocVelVec(Vector3d(-halfFieldLength, halfGoalWidth, .8), Vector3d(0,0,0)), MatrixXd::Identity(6, 6));
  d_objectInfos[Types::GOAL2US]->locVelGlobal->init(joinLocVelVec(Vector3d(-halfFieldLength, -halfGoalWidth, .8), Vector3d(0,0,0)), MatrixXd::Identity(6, 6));
  d_objectInfos[Types::GOAL1THEM]->locVelGlobal->init(joinLocVelVec(Vector3d(halfFieldLength, halfGoalWidth, .8), Vector3d(0,0,0)), MatrixXd::Identity(6, 6));
  d_objectInfos[Types::GOAL2THEM]->locVelGlobal->init(joinLocVelVec(Vector3d(halfFieldLength, -halfGoalWidth, .8), Vector3d(0,0,0)), MatrixXd::Identity(6, 6));

  d_forwardPairs.push_back(LandmarkPair(Types::FLAG2US, Types::FLAG1US));
  d_forwardPairs.push_back(LandmarkPair(Types::GOAL2US, Types::GOAL1US));
  d_forwardPairs.push_back(LandmarkPair(Types::FLAG2THEM, Types::FLAG1THEM));
  d_forwardPairs.push_back(LandmarkPair(Types::GOAL2THEM, Types::GOAL1THEM));

  d_rightPairs.push_back(LandmarkPair(Types::FLAG1US, Types::FLAG1THEM));
  d_rightPairs.push_back(LandmarkPair(Types::FLAG2US, Types::FLAG2THEM));
  d_rightPairs.push_back(LandmarkPair(Types::GOAL1US, Types::GOAL1THEM));
  d_rightPairs.push_back(LandmarkPair(Types::GOAL2US, Types::GOAL2THEM));

  d_rightCrossProductPairs.push_back(LandmarkPairPair(LandmarkPair(Types::FLAG1US, Types::GOAL1US), LandmarkPair(Types::FLAG1US, Types::GOAL2US)));
  d_rightCrossProductPairs.push_back(LandmarkPairPair(LandmarkPair(Types::FLAG1US, Types::GOAL1US), LandmarkPair(Types::FLAG1US, Types::FLAG2US)));
  d_rightCrossProductPairs.push_back(LandmarkPairPair(LandmarkPair(Types::FLAG1US, Types::GOAL2US), LandmarkPair(Types::FLAG1US, Types::FLAG2US)));
  d_rightCrossProductPairs.push_back(LandmarkPairPair(LandmarkPair(Types::GOAL1US, Types::GOAL2US), LandmarkPair(Types::GOAL1US, Types::FLAG2US)));

  d_rightCrossProductPairs.push_back(LandmarkPairPair(LandmarkPair(Types::FLAG1THEM, Types::GOAL1THEM), LandmarkPair(Types::FLAG1THEM, Types::GOAL2THEM)));
  d_rightCrossProductPairs.push_back(LandmarkPairPair(LandmarkPair(Types::FLAG1THEM, Types::GOAL1THEM), LandmarkPair(Types::FLAG1THEM, Types::FLAG2THEM)));
  d_rightCrossProductPairs.push_back(LandmarkPairPair(LandmarkPair(Types::FLAG1THEM, Types::GOAL2THEM), LandmarkPair(Types::FLAG1THEM, Types::FLAG2THEM)));
  d_rightCrossProductPairs.push_back(LandmarkPairPair(LandmarkPair(Types::GOAL1THEM, Types::GOAL2THEM), LandmarkPair(Types::GOAL1THEM, Types::FLAG2THEM)));
}

