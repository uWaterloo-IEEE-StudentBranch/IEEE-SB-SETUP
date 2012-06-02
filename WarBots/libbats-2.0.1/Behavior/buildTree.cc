#include "behavior.ih"

#define _elseif(X) else if (b.getProp("type") == #X) \
    behavior = new X(b.getProp("id"), playerClass)

#define _elseif1(X) else if (b.getProp("type") == #X) \
    behavior = new X(b.getProp("id"))



rf<Behavior> Behavior::buildTree(XMLNode& b, string playerClass)
{
  Conf& conf = SConf::getInstance();

  // Make behavior of this node's type
  
  BehaviorFactory& bf = SBehaviorFactory::getInstance();
  rf<Behavior> behavior = bf.createBehavior(b.getProp("type"), b.getProp("id"), playerClass);
  

  if (!behavior)
    throw runtime_error(b.getProp("type") + ": unknown behavior type (trying to create behavior with id: " + b.getProp("id") + ")");

  behavior->setPlayerClass(playerClass);

  // Go through the slots
  for(XMLNode s = b.getChildren(); s; s = s.getNext())
  {
    if (s.getName() != "slot")
      continue;

    string index = s.getProp("index");
    unsigned step = atoi(index.substr(0, index.find("-")).c_str());
    unsigned slot = atoi(index.substr(index.find("-") + 1).c_str());


    for (XMLNode sb = s.getChildren(); sb; sb = sb.getNext())
      if (sb.getName() == "behavior")
      {

        string path = "/conf/player-class[@id='" + playerClass + "']/behaviors/behavior[@id='" + sb.getProp("refid") + "']";
        try{
          string commit = sb.getProp("commit");
          string scicc = sb.getProp("scicc");

          XMLNodeSet set = conf.selectXPath(path);
          if (set.size() > 1)
          {
            //_foreach(s, set)
            //  //cout << (*s).getContent() << endl;
            throw new BatsException(string() + "buildTree: '" + path + "' found multiple times.");
          }
          if (set.empty())
            throw new BatsException(string() + "buildTree: '" + path + "' not found.");

          XMLNode sb = set.front();
          rf<Behavior> subBehavior = buildTree(sb, playerClass);
          subBehavior->shouldCommit(commit == "1");
          subBehavior->shouldCommitIfChildrenCommitted(scicc == "1");
          behavior->addToSlot(subBehavior, step, slot);

        }
        catch(BatsException *e)
        {
            throw e;
        }
      }
  }
  //Check if we had already loaded the behavior
  /*
  if(s_behaviors.count(behavior->getId()) > 0)
  {
    cerr << "Double ID, behavior: " << behavior->getName() << "(" << behavior->getId() << ")" << " already in tree" << endl;
    //assert(false);
  }
  */
  s_behaviors[behavior->getId()] = behavior;

  return behavior;
}

