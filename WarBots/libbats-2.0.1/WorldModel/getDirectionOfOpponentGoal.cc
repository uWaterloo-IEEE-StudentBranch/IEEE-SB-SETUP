#include "worldmodel.ih"

Vector3d WorldModel::getDirectionOfOpponentGoal() const
{
  Localizer& loc = SLocalizer::getInstance();
  Vector3d goal = loc.getLocationLocal(Types::GOAL1THEM)->getMu();
  goal += loc.getLocationLocal(Types::GOAL2THEM)->getMu();
  goal /= 2;
  return Math::cartesianToPolar(goal);
}
