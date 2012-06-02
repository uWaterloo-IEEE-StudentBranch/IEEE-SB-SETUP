#include "rc3dclock.ih"

void RC3DClock::update()
{
  Cochlea& cochlea = SCochlea::getInstance();
  
  if (cochlea.getInfo(Cochlea::iNow)[0] != 0)
  {
    double newTime = cochlea.getInfo(Cochlea::iNow)[0];
    d_dt = newTime - d_time;
    d_time = newTime;
  }
}
