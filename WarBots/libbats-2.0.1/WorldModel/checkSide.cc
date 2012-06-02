#include "worldmodel.ih"

Types::Object WorldModel::checkSide(Types::Object object) const
{
  switch (object)
  {
    case Types::FLAG1L:
      return d_team == Types::LEFT ? Types::FLAG1US : Types::FLAG2THEM;
      
    case Types::FLAG2L:
      return d_team == Types::LEFT ? Types::FLAG2US : Types::FLAG1THEM;
      
    case Types::FLAG1R:
      return d_team == Types::LEFT ? Types::FLAG1THEM : Types::FLAG2US;
      
    case Types::FLAG2R:
      return d_team == Types::LEFT ? Types::FLAG2THEM : Types::FLAG1US;
      
    case Types::GOAL1L:
      return d_team == Types::LEFT ? Types::GOAL1US : Types::GOAL2THEM;
      
    case Types::GOAL2L:
      return d_team == Types::LEFT ? Types::GOAL2US : Types::GOAL1THEM;
      
    case Types::GOAL1R:
      return d_team == Types::LEFT ? Types::GOAL1THEM : Types::GOAL2US;
      
    case Types::GOAL2R:
      return d_team == Types::LEFT ? Types::GOAL2THEM : Types::GOAL1US;
    	
    default:
      return object;
  }
}

