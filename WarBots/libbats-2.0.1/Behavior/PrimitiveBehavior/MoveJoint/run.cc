#include "movejoint.hh"
#include "../../../Action/RC3DAction/rc3daction.hh"

using namespace bats;
using namespace std;

bool MoveJoint::run()
{
  rf<StateVarNode> speedNode = rf_cast<StateVarNode>(d_goal->findDeep("Speed"));

  if (!speedNode)
  {
    return false;
  }
    
  double speed = speedNode->getVar().second.mean();

  d_action = new MoveJointAction(d_joint, speed);
  
  addToActionCommandBehaviors();
  
  return true;
}
