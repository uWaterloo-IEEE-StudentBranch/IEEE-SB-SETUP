#include "worldmodel.ih"

WorldModel::WorldModel()
  :
  d_time(0),
  d_teamName(""),
  d_gameTime(0),
  d_prevGameTime(0),
  d_timeStep(0.04),
  d_playMode(Types::UNKNOWN),
  d_lastPlayMode(Types::UNKNOWN),
  d_team(Types::UNKNOWN_SIDE),
  d_scoreUs(0),
  d_scoreThem(0),
  d_firstTime(-1),
  d_numMsgReceived(0),
  d_ballRadius(0.042)
{
  Conf& conf = SConf::getInstance();
  d_fieldLength = conf.getParam("fieldlength", 18.0);
  d_fieldWidth = conf.getParam("fieldwidth", 12.0);
  d_goalWidth = conf.getParam("goalwidth", 2.1);
  d_halfTimeRestart = conf.getParam("halftimerestart", 1) == 1;
}

