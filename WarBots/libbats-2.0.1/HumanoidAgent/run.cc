#include "humanoidagent.ih"

void HumanoidAgent::run()
{
  // Startup agent
  startUp();

  // Get our worldmodel and stuff
  Cochlea& cochlea = SCochlea::getInstance();
  WorldModel& wm = SWorldModel::getInstance();
  AgentSocketComm& comm = SAgentSocketComm::getInstance();
  AgentModel& am = SAgentModel::getInstance();
  Clock& clock = SClock::getInstance();

	// Get first message
	comm.update();
  cochlea.update();
  clock.update();
  wm.update();
	unsigned i(0);

	while(wm.getNumMsgReceived() < 2 && ++i < 200) /// \todo Tweak to a minimum possible number of messages before sending init is ok.
	{
    _debugLevel1("Hoi 0 - " << wm.getNumMsgReceived());
  	comm.update();
    cochlea.update();
    clock.update();
    wm.update();
  }

	//Send init
  comm.init(d_unum, d_teamName);

	//Wait for unum
	while(wm.getNumMsgReceived() < 10 && cochlea.getInfo(Cochlea::iUnum)[0] == 0)//Failsafe max messages
	{
    _debugLevel1("Hoi 1");
  	comm.update();
  	cochlea.update();
    clock.update();
    wm.update();
  }

  float unum = cochlea.getInfo(Cochlea::iUnum)[0];
  if (unum != 0)
  {
    _debugLevel1("Hoi 2");
    assert(unum > 0);
    am.setUnum(static_cast<unsigned int>(unum));
  }

  // At this point we should have a unum
  assert(am.getUnum());
  am.initBody();

  //Init behavior system (Localizer should be initialized in here)
  init();

  _debugLevel1("Hoi 4");


  Localizer& loc = SLocalizer::getInstance();
  loc.init();

 	am.update();
  loc.update();

  while(!s_die)
  {
    _debugLevel4("----------------------- New think cycle ------------------------");

  	comm.update();
    _debugLevel4("Comm updated");

  	cochlea.update();
    _debugLevel4("Cochlea updated");

    clock.update();
    _debugLevel4("Clock updated");

    wm.update();
    _debugLevel4("WorldModel updated");

  	am.update();
    _debugLevel4("AgentModel updated");

  	loc.update();
    _debugLevel4("Localizer updated");

    think_start_signal();
    think();
    think_end_signal();
  }

}
