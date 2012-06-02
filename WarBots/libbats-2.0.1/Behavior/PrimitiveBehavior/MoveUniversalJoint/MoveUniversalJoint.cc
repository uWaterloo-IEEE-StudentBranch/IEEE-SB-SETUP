#include "moveuniversaljoint.hh"
#include "../../../BatsException/batsexception.hh"

using namespace bats;

MoveUniversalJoint::MoveUniversalJoint(std::string const &id, std::string const &playerClass)
  : PrimitiveBehavior("MoveUniversalJoint", id, playerClass)
{

  XMLNodeSet params = getParams("/joint");
  
  if(!params || params.empty())
    throw new BatsException("MoveUniversalJoint behavior requires a joint parameter");
  else
  {
    XMLNode jointNode = params.front();
    d_joint = (Types::Joint)atoi(jointNode.getContent().c_str());
  }
  
  d_lastSpeeds[0] = 0;
  d_lastSpeeds[1] = 0;
}
