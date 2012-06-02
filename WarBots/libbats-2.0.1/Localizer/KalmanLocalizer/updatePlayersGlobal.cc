#include "kalmanlocalizer.ih"

void KalmanLocalizer::updatePlayersGlobal()
{
  VectorXd myLocvel = d_objectInfos[Types::SELF]->locVelGlobal->getMu();
  MatrixXd mySigma = d_objectInfos[Types::SELF]->locVelGlobal->getSigma();

  for (unsigned p = Types::PLAYER1; p <= Types::OPPONENT11; ++p)
  {
    rf<PlayerInfo> info = rf_static_cast<PlayerInfo>(d_objectInfos[p]);
    
    VectorXd oldLocVel = info->locVelGlobal->getMu();
    /*
     * Predict
     */
    MatrixXd F = MatrixXd::Identity(6,6);
    
    double dt = 0.02;
    // x_{t+1} = x_t + dt * v_t
    // v_{t+1} = v_t
    for (unsigned i = 0; i < 3; ++i)
      F(i, i+3) = dt;

    // Assume no control
    // TODO: make this smarter
    MatrixXd B = MatrixXd::Zero(6,3);
    
    // Assume player is decelerating
    // TODO: make this smarter
    Vector3d oldVel = cutVelVec(oldLocVel);
    Vector3d u = -oldVel;
    
    for (unsigned i = 0; i < 3; ++i)
    {
      B(i, i) = dt * dt / 2;
      B(i+3, i) = dt;
    }

    // Slight process noise to overcome lack of control data
    // TODO: tweak this
    MatrixXd Q = MatrixXd::Identity(6, 6) * 0.0001;
    
    info->locVelGlobal->predict(F, B, u, Q);

    /*
     * Update
     */
    if (d_newVisionData)
    {
      Transform3d globalRotationTrans = Transform3d(d_globalRotation.matrix().transpose());
      if (info->visible)
      {
        VectorXd meas = d_locationsVelocitiesRaw[p]->getMu();
        MatrixXd sigma = d_locationsVelocitiesRaw[p]->getSigma();

        VectorXd globalMeas = joinLocVelVec(cutLocVec(myLocvel) + d_globalRotation * cutLocVec(meas), Vector3d(0,0,0));
        VectorXd vel = globalMeas - oldLocVel;
        globalMeas = joinLocVelVec(cutLocVec(globalMeas), cutLocVec(vel));

        MatrixXd globalSigma = joinLocVelMat(d_globalRotation.linear() * cutLocMat(sigma) * globalRotationTrans.linear(),
                                             d_globalRotation.linear() * cutVelMat(sigma) * globalRotationTrans.linear()) + mySigma;
        
        info->locVelGlobal->update(MatrixXd::Identity(6, 6), globalMeas, globalSigma);
      }
    
      if (info->lArmVisible)
      {
        info->locLArmGlobal = cutLocVec(myLocvel) + d_globalRotation * info->locLArmLocal;
        info->alive = true;
      }
      if (info->rArmVisible)
      {
        info->locRArmGlobal = cutLocVec(myLocvel) + d_globalRotation * info->locRArmLocal;
        info->alive = true;
      }
      if (info->lFootVisible)
      {
        info->locLFootGlobal = cutLocVec(myLocvel) + d_globalRotation * info->locLFootLocal;
        info->alive = true;
      }
      if (info->rFootVisible)
      {
        info->locRFootGlobal = cutLocVec(myLocvel) + d_globalRotation * info->locRFootLocal;
        info->alive = true;
      }
    }

    if (info->locVelGlobal->getSigma()(0, 0) > 1.0)
      info->alive = false;
  }
}

