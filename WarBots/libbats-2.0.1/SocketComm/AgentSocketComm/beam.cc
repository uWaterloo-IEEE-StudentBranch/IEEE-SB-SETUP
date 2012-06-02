#include "agentsocketcomm.ih"

void AgentSocketComm::beam(Vector3d const& pos)
{
  send(makeBeamMessage(pos));
  beam_signal(new BeamEvent(pos));
}

rf<Predicate> AgentSocketComm::makeBeamMessage(Vector3d const& pos)
{
  rf<Predicate> beamPred = new Predicate("beam");
  beamPred->pushLeafs(pos);
  return beamPred;
}

