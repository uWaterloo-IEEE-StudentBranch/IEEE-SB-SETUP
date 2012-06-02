#include "beamto.ih"

void BeamTo::update()
{
  WorldModel& wm = SWorldModel::getInstance();
  Types::PlayMode pm = wm.getPlayMode();
  
  d_committed = pm == Types::UNKNOWN || pm == Types::BEFORE_KICKOFF || pm == Types::GOAL_US || pm == Types::GOAL_THEM;
}

