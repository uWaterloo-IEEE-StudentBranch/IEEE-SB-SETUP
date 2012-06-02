#include "agentmodel.ih"

rf<AgentModel::BodyPart> AgentModel::getBodyCopy()
{
  return getBodyPartCopy(d_torso);
}

