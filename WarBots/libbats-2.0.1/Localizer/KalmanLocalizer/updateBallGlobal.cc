#include "kalmanlocalizer.ih"

void KalmanLocalizer::updateBallGlobal()
{
  Cochlea& cochlea = SCochlea::getInstance();
  AgentModel& am = SAgentModel::getInstance();
  
  VectorXd oldLocVel = d_objectInfos[Types::BALL]->locVelGlobal->getMu();
  //cerr << "oldLoc:" << endl << oldLoc << endl;
  
  /*
   * Predict
   */
  MatrixXd F = MatrixXd::Identity(6, 6);
  
  double dt = 0.02;
  // x_{t+1} = x_t + dt * v_t
  // v_{t+1} = v_t
  for (unsigned i = 0; i < 3; ++i)
    F(i, i+3) = dt;
  //cerr << "F:" << endl << F << endl;
  
  // a = f/m = 0.01 * vel / 0.026
  double linearDrag = -0.01;
  double ballMass = 0.026;
  Vector3d a = cutVelVec(oldLocVel) * linearDrag / ballMass;
  //cerr << "a:" << endl << a << endl;
  
  // Assume no control
  // TODO: make this smarter by using friction
  MatrixXd B = MatrixXd::Zero(6,3);
  VectorXd u = a;
  for (unsigned i = 0; i < 3; ++i)
  {
    B(i, i) = dt * dt / 2;
    B(i+3, i) = dt;
  }
  //cerr << "B:" << endl << B << endl;

  // Slight process noise to overcome lack of control data
  // TODO: tweak this
  MatrixXd Q = MatrixXd::Identity(6, 6) * 0.0001;
  
  d_objectInfos[Types::BALL]->locVelGlobal->predict(F, B, u, Q);
  //cerr << "after predict: " << endl << d_locationsVelocitiesGlobal[Types::BALL]->getMu() << endl;

  /*
   * Update
   */
  if (d_newVisionData)
  {
    Transform3d globalRotationTrans = Transform3d(d_globalRotation.matrix().transpose());
    if (d_objectInfos[Types::BALL]->visible)
    {
      //cerr << "t: " << SWorldModel::getInstance().getTime() << endl;
      
      VectorXd meas = d_locationsVelocitiesRaw[Types::BALL]->getMu();
      //cerr << "meas:" << endl << meas << endl;
      
      MatrixXd sigma = d_locationsVelocitiesRaw[Types::BALL]->getSigma();
      //cerr << "sigma:" << endl << sigma << endl;

      VectorXd myLocvel = d_objectInfos[Types::SELF]->locVelGlobal->getMu();
      MatrixXd mySigma = d_objectInfos[Types::SELF]->locVelGlobal->getSigma();

      VectorXd globalMeas = joinLocVelVec(cutLocVec(myLocvel) + d_globalRotation * cutLocVec(meas), Vector3d(0,0,0));
      
      VectorXd vel = (globalMeas - oldLocVel) / cochlea.getDt(Cochlea::iVisionBall);
      globalMeas = joinLocVelVec(cutLocVec(globalMeas), cutLocVec(vel));

      //cerr << "globalMeas:" << endl << globalMeas << endl;

      MatrixXd globalSigma = joinLocVelMat(d_globalRotation.linear() * cutLocMat(sigma) * globalRotationTrans.linear(),
                                           d_globalRotation.linear() * cutVelMat(sigma) * globalRotationTrans.linear()) + mySigma;
      
      //cerr << "globalSigma:" << endl << globalSigma << endl;

      d_objectInfos[Types::BALL]->locVelGlobal->update(MatrixXd::Identity(6, 6), globalMeas, globalSigma);
    }
    // Only check being alive when we got vision info
    else
    {
      // If ball should be in field of view, it's dead
      Vector3d lookDir = Math::getForward(am.getBodyPart(Types::HEAD)->transform);
      Vector3d lookDirPolar = Math::cartesianToPolar(lookDir);
      Vector3d ballPos = d_objectInfos[Types::BALL]->locVelLocal->getMu().start<3>(); // This is estimation of lst step. Should move this to after globalToLocal perhaps?
      Vector3d headToBall = ballPos - am.getBodyPart(Types::HEAD)->transform.translation();
      Vector3d ballDirPolar = Math::cartesianToPolar(headToBall);
      Vector3d diff = ballDirPolar - lookDirPolar;
      if (diff[1] < 60.0 / 180.0 * M_PI || diff[2] < 60.0 / 180.0 * M_PI)
        d_objectInfos[Types::BALL]->locVelGlobal->setSigma(MatrixXd::Identity(6,6) * 30.0);
    }
  }  
  //cerr << "after update: " << endl << d_locationsVelocitiesGlobal[Types::BALL]->getMu() << endl;
}

