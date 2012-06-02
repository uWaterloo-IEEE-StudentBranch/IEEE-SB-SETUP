#include "humanoidagent.ih"

void HumanoidAgent::startUp()
{
  SConf::initialize();
  if (d_confFile != "")
    SConf::getInstance().setFile(d_confFile);

  SAgentSocketComm::initialize();
  SCochlea::initialize();
  SWorldModel::initialize();

  SAgentSocketComm::getInstance().initSocket(d_host, d_port);
  SWorldModel::getInstance().setTeamName(d_teamName);
  SCochlea::getInstance().setTeamName(d_teamName);

  SAgentModel::initialize();
  SBehaviorFactory::initialize();
  SCerebellum::initialize();
  
  // Before messages can be parsed, the parser should be initialized.
  Parser::initialize();
  
  AgentModel& am = SAgentModel::getInstance();
  am.setUnum(d_unum);
  
  //  WorldModel& wm = SWorldModel::getInstance();
  SAgentSocketComm::getInstance().connect();

  rf<Predicate> scene = new Predicate("scene");
  scene->pushLeaf("rsg/agent/" + am.getRSG());
    
  _debugLevel4(*scene);
  SAgentSocketComm::getInstance().send(scene);

  SClock::initialize<RC3DClock>();
  
  // Set blokcing mode.
  //  d_comm.setBlocking(true);
}
