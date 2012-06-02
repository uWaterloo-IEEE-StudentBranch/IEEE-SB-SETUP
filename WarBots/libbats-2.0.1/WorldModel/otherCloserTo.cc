#include "worldmodel.ih"

// TODO: reimplement standing check
unsigned WorldModel::otherCloserTo(Vector3d const& pos, bool standing, bool count, Types::Object ignore)
{
  Localizer& loc = SLocalizer::getInstance();

  double dist = pos.norm();
  unsigned cnt = 0;

  //cout << "ignoring: " << ignore << endl;

  for (Types::Object p = Types::PLAYER1; p <= Types::PLAYER11; p = (Types::Object)(p + 1))
  {
    if (p == ignore)
      continue;

    if (loc.alive(p))
    {
      Vector3d pPos = loc.getLocationLocal(p)->getMu();
      if (pPos.norm() < 0.01) // if it's not ourselves
          continue;
      //cerr << "oppPos: " << o << endl;
      pPos(2) = 0;
      double d = (pPos - pos).norm();
      if (d < dist)
      {
        ++cnt;
        if (!count)
          break;

      }
    }
  }

  return cnt;
}

unsigned WorldModel::otherCloserToBall(bool standing, bool count)
{
  Localizer& loc = SLocalizer::getInstance();

  return otherCloserTo(loc.getLocationLocal(Types::BALL)->getMu(), standing, count);
}

