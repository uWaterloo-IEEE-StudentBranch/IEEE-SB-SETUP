#include "behaviorfactory.ih"

rf<Behavior> BehaviorFactory::createBehavior(string const& key, string const& id, string const& playerClass)
{
  if (d_createFunctions.find(key) == d_createFunctions.end())
    throw runtime_error(string() + "createBehavior: no creation function registered for '" + key + "'!");
    
  return (d_createFunctions[key])(id, playerClass);
}

