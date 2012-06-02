#include "kalmanlocalizer.ih"

void KalmanLocalizer::globalToLocal()
{
  Transform3d invGlobalTransform = Transform3d(d_globalTransform.inverse());

  Vector3d localUp = Math::getUp(invGlobalTransform);
  Vector3d localRight = localUp.cross(Vector3d::UnitX().cross(localUp)).normalized();
  Vector3d localForward = localUp.cross(Vector3d::UnitY().cross(localUp)).normalized();
  
  Transform3d invLocalTransform = Math::makeTransform(localRight, localForward, localUp);
  d_localTransform = invLocalTransform.inverse();
  
  //cerr << "local trans:" << endl << d_localTransform.matrix() << endl;
  //cerr << "global trans:" << endl << d_globalTransform.matrix() << endl;
   
  Transform3d globalToLocal = d_localTransform * invGlobalTransform;
  
  Transform3d globalToLocalRot = Transform3d(globalToLocal.linear());
  Transform3d globalToLocalRotTrans = Transform3d(globalToLocalRot.matrix().transpose());
  
  // Determine local coordinates
  for (unsigned o = 0; o < Types::NOBJECTS; ++o)
  {
    d_objectInfos[o]->locVelLocal->init(joinLocVelVec(globalToLocal * cutLocVec(d_objectInfos[o]->locVelGlobal->getMu()),
                                                      globalToLocalRot * cutVelVec(d_objectInfos[o]->locVelGlobal->getMu())),
                                        joinLocVelMat(globalToLocalRot.linear() * cutLocMat(d_objectInfos[o]->locVelGlobal->getSigma()) * globalToLocalRotTrans.linear(),
                                                      globalToLocalRot.linear() * cutVelMat(d_objectInfos[o]->locVelGlobal->getSigma()) * globalToLocalRotTrans.linear()));
                                                      
    if (o >= Types::PLAYER1 && o <= Types::OPPONENT11)
    {
      rf<PlayerInfo> info = rf_static_cast<PlayerInfo>(d_objectInfos[o]);
      info->locLArmLocal = globalToLocal * info->locLArmGlobal;
      info->locRArmLocal = globalToLocal * info->locRArmGlobal;
      info->locLFootLocal = globalToLocal * info->locLFootGlobal;
      info->locRFootLocal = globalToLocal * info->locRFootGlobal;
    }
  }

}

