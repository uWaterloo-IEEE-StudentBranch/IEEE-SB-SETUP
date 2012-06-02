#include "beamto.ih"

rf<Goal> BeamTo::generateGoal(unsigned step, unsigned slot)
{
  WorldModel& wm = SWorldModel::getInstance();
  
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  // See where the opponent's receiver is
  // We assume it's the one that is the most to the side
  double maxSideDist = 0;
  Vector3d opponentPos;
  
  /*
  for (WorldModel::player_iterator iter = wm.beginOpponents(); iter != wm.endOpponents(); ++iter)
  {
    Vector3d pos = iter->second.getWorldPosition();
    
    double dist = fabs(pos[1]);
    if (dist > maxSideDist)
    {
      opponentPos = pos;
      maxSideDist = dist;
    }
  }
  */
  if (wm.weGetKickOff())
  {
    Vector3d beamPos = d_posWeGetKickOff;
    /*
    if (d_coverOpponent && wm.getNumberOfOpponents() > 0)
    {
      if (beamPos[1] * opponentPos[1] > 0)
      {
        beamPos[1] = -beamPos[1];
        beamPos[2] = -beamPos[2];
      }
    }
    */
    con->addVar("", beamPos);
  }
  else
  {
	/*
    if (d_coverOpponent && wm.getNumberOfOpponents() > 0)
    {
      Vector3d beamPos;
      // Don't stand in the center circle
      if (fabs(opponentPos[1]) < 1.5)
      {
        beamPos = d_posTheyGetKickOff;
        beamPos[1] = opponentPos[1] < 0 ? -1 : 1;
      }
      else
      {
        beamPos = Vector3d(-1, opponentPos[1], 0);
      }
      con->addVar("", beamPos);
    }
    else
    */
      con->addVar("", d_posTheyGetKickOff);
  }

  return goal;
}
