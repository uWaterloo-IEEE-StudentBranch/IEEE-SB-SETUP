#include "kalmanlocalizer.ih"

void KalmanLocalizer::updateSelfGlobal()
{
  AgentModel& am = SAgentModel::getInstance();
  
  VectorXd oldLocVel = d_objectInfos[Types::SELF]->locVelGlobal->getMu();
  
  double dt = SClock::getInstance().getDt();

  Vector3d accLocal = am.getAcc();
  Vector3d accGlobal = d_globalRotation.linear() * accLocal;
  
  /*
   * Predict
   */
  
  // x_{t+1} = x_t + dt * v_t
  // v_{t+1} = v_t
  MatrixXd F = MatrixXd::Identity(6, 6);
  F.corner(TopRight, 3, 3).diagonal().setConstant(dt);

  // Assume no control
  // TODO: make this smarter by using actions of previous step
  MatrixXd B = MatrixXd::Zero(6,6);
  B.corner(BottomRight,3 ,3).diagonal().setConstant(dt);
  VectorXd u(6);
  u << 0,0,0,0,0,0;//accGlobal;

  // Slight process noise to overcome lack of control data
  // TODO: tweak this
  MatrixXd Q = VectorXd::Constant(6, 0.0001).asDiagonal();
  
  d_objectInfos[Types::SELF]->locVelGlobal->predict(F, B, u, Q);
  //cerr << "after predict: " << endl << d_locationsVelocitiesGlobal[Types::SELF]->getMu() << endl;
  
  /*
   * Update
   */
  if (d_newVisionData)
  {
    Transform3d globalRotationTrans(d_globalRotation.matrix().transpose());
    for (unsigned o = Types::FLAG1US; o <= Types::GOAL2THEM; o++)
    {
      if (d_objectInfos[o]->visible)
      {
        VectorXd loc = d_objectInfos[o]->locVelGlobal->getMu();
        //cerr << "landmark loc:" << endl << loc << endl;
        VectorXd meas = d_locationsVelocitiesRaw[o]->getMu();
        //cerr << "raw meas:" << endl << meas << endl;
        MatrixXd sigma = d_locationsVelocitiesRaw[o]->getSigma();

        VectorXd globalMeas = VectorXd::Zero(6);
        // Location part
        globalMeas.start<3>() = cutLocVec(loc) - d_globalRotation * cutLocVec(meas);
        // Velocity part
        globalMeas.end<3>() = (globalMeas - oldLocVel).start<3>();
        //cerr << "global meas:" << endl << globalMeas << endl;
        
        MatrixXd globalSigma = joinLocVelMat(d_globalRotation.linear() * cutLocMat(sigma) * globalRotationTrans.linear(),
                                             d_globalRotation.linear() * cutVelMat(sigma) * globalRotationTrans.linear());
        
        d_objectInfos[Types::SELF]->locVelGlobal->update(MatrixXd::Identity(6,6), globalMeas, globalSigma);
        //cerr << "after update: " << endl << d_locationsVelocitiesGlobal[Types::SELF]->getMu() << endl;
      }
    }
  }
  
  d_globalTranslation = Translation3d(cutLocVec(d_objectInfos[Types::SELF]->locVelGlobal->getMu()));
  d_globalTransform = d_globalTranslation * d_globalRotation;
  
  //cerr << "globalTransform:" << endl << d_globalTransform.matrix() << endl;
}

