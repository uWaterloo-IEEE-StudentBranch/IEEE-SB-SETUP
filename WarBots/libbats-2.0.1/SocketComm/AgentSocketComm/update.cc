#include "agentsocketcomm.ih"

void AgentSocketComm::update()
{
  syn();
  send();
  //send();
  receive();
}

