#include "behavior.ih"

void Behavior::createBehaviors(unsigned id)
{
  try {
    Conf& conf = SConf::getInstance();
  
    vector<XMLNode> players;
    string playerClass;
  
    conf.getRoot().findAll(players, "player");
    for (vector<XMLNode>::iterator iter = players.begin(); iter != players.end(); ++iter)
      if (static_cast<unsigned>(atoi(iter->getProp("id").c_str())) == id || atoi(iter->getProp("id").c_str()) == 0)
				playerClass = iter->getProp("class");
  
    string path = "/conf/player-class[@id='" + playerClass + "']/behaviors/behavior[@id='win']";
    XMLNodeSet set = conf.selectXPath(path);

    if (set.empty())
      throw runtime_error(string() + "createBehavior: '" + path + "' not found!");

    XMLNode win = set.front();
    s_win = buildTree(win, playerClass);

	// Iterate over all behaviors, and call 'constructed'
	for (map<string, rf<Behavior> >::iterator iter = s_behaviors.begin(); iter != s_behaviors.end(); ++iter)
		(iter->second)->constructed();
	
  } catch (BatsException *e) {
    BATS_CATCH_FRAME(e);
    throw;
  }
}
