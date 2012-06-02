#include "kalmanlocalizer.ih"

// sigma_dist     0.0965f * dist / 100.0
// sigma_phi      0.1225f
// sigma_theta    0.1480f

void KalmanLocalizer::updateRaw()
{
  Cochlea& cochlea = SCochlea::getInstance();
  WorldModel& wm = SWorldModel::getInstance();
  AgentModel& am = SAgentModel::getInstance();
  
  Transform3d invHeadTransform = am.getBodyPart(Types::HEAD)->transform;
  Transform3d invHeadRotation(invHeadTransform.linear());
  
  d_newVisionData = SCochlea::getInstance().getTimestamp(Cochlea::iVision) == SClock::getInstance().getTime();
  
  // No sense in updating if there is no vision data
  if (!d_newVisionData)
    return;
    
  for (unsigned oID = 0; oID < Types::NOBJECTS; ++oID)
  {
    if (oID >= Types::PLAYER1 && oID <= Types::OPPONENT11)
    {
      rf<PlayerInfo> info = rf_static_cast<PlayerInfo>(d_objectInfos[oID]);
      info->lArmVisible = false;
      info->rArmVisible = false;
      info->lFootVisible = false;
      info->rFootVisible = false;
    }
    d_objectInfos[oID]->visible = false;
  }
  
  for (unsigned oID = Types::BALL; oID <= Types::GOAL2R; ++oID)
  {
    // Ignore your own limbs
    if (oID == Types::PLAYER1 + SAgentModel::getInstance().getUnum() - 1)
      continue;
      
    // Update raw positions of body parts of players
    // TODO: also filter noise
    if (oID >= Types::PLAYER1 && oID <= Types::OPPONENT11)
    {
      rf<PlayerInfo> info = rf_static_cast<PlayerInfo>(d_objectInfos[oID]);
      Vector3d locPolar;
      
      bool opp = oID >= Types::OPPONENT1;
      int pIdx = opp ? oID - Types::OPPONENT1 : oID - Types::PLAYER1;
      
      Cochlea::InfoID iIDlarm = (Cochlea::InfoID)((opp ? Cochlea::iLLowerArmOpponent1 : Cochlea::iLLowerArmPlayer1) + pIdx);
      Cochlea::InfoID iIDrarm = (Cochlea::InfoID)((opp ? Cochlea::iRLowerArmOpponent1 : Cochlea::iRLowerArmPlayer1) + pIdx);
      Cochlea::InfoID iIDlfoot = (Cochlea::InfoID)((opp ? Cochlea::iLFootOpponent1 : Cochlea::iLFootPlayer1) + pIdx);
      Cochlea::InfoID iIDrfoot = (Cochlea::InfoID)((opp ? Cochlea::iRFootOpponent1 : Cochlea::iRFootPlayer1) + pIdx);

      if (wm.getTime() - cochlea.getTimestamp(iIDlarm) < 0.005)
      {
        info->lArmVisible = true;
        locPolar = cochlea.getInfo(iIDlarm).start<3>();
        info->locLArmLocal = invHeadTransform * Math::polarToCartesian(locPolar);
      }

      if (wm.getTime() - cochlea.getTimestamp(iIDrarm) < 0.005)
      {
        info->rArmVisible = true;
        locPolar = cochlea.getInfo(iIDrarm).start<3>();
        info->locRArmLocal = invHeadTransform * Math::polarToCartesian(locPolar);
      }

      if (wm.getTime() - cochlea.getTimestamp(iIDlfoot) < 0.005)
      {
        info->lFootVisible = true;
        locPolar = cochlea.getInfo(iIDlfoot).start<3>();
        info->locLFootLocal = invHeadTransform * Math::polarToCartesian(locPolar);
      }

      if (wm.getTime() - cochlea.getTimestamp(iIDrfoot) < 0.005)
      {
        info->rFootVisible = true;
        locPolar = cochlea.getInfo(iIDrfoot).start<3>();
        info->locRFootLocal = invHeadTransform * Math::polarToCartesian(locPolar);
      }
    }
    
    // Update raw position of object
    Cochlea::InfoID iID = cochlea.objectTypeToInfoID((Types::Object)oID);
    if (wm.getTime() - cochlea.getTimestamp(iID) < 0.005)
    {
      unsigned oID2 = wm.checkSide((Types::Object)oID);
      
      d_objectInfos[oID2]->alive = d_objectInfos[oID2]->visible = d_objectInfos[oID]->visible = true;
      Vector3d locPolar = cochlea.getInfo(iID).start<3>();
      double dt = cochlea.getDt(iID);
      Vector3d locPolarWithNoise = locPolar + Vector3d(0.1225/ 180.0 * M_PI, 0.1480 / 180.0 * M_PI, 0.0965 * locPolar[2] / 100.0);
      VectorXd locVel(6);
      locVel.start<3>() = invHeadTransform * Math::polarToCartesian(locPolar);
      Vector3d locWithNoise = invHeadTransform * Math::polarToCartesian(locPolarWithNoise);
      VectorXd oldLocVel = d_locationsVelocitiesRaw[oID]->getMu();
      locVel.end<3>() = cutLocVec(locVel - oldLocVel) / dt;
      
      MatrixXd locVelSigma = MatrixXd::Zero(6,6);
      double s = (locWithNoise - locVel.start<3>()).norm();
      locVelSigma.diagonal().setConstant(s);

      locVelSigma.block<3,3>(3,3) = locVelSigma.block<3,3>(0,0) + d_locationsVelocitiesRaw[oID]->getSigma().block<3,3>(0,0);
      d_locationsVelocitiesRaw[oID]->init(locVel, locVelSigma);
      if (oID != oID2)
        d_locationsVelocitiesRaw[oID2]->init(locVel, locVelSigma);
    }
  }
}

