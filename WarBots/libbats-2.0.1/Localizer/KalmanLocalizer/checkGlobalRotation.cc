#include "kalmanlocalizer.ih"

void KalmanLocalizer::checkGlobalRotation()
{
  if (!d_newVisionData)
    return;
    
  // Find forward (0,1,0)
  Vector3d forward(0, 0, 0);
  unsigned haveForward = 0;
  for(vector<LandmarkPair>::iterator iter = d_forwardPairs.begin(); iter != d_forwardPairs.end(); ++iter)
  {
    if (d_objectInfos[iter->first]->visible && d_objectInfos[iter->second]->visible)
    {
      forward = forward + (cutLocVec(d_locationsVelocitiesRaw[iter->second]->getMu()) - cutLocVec(d_locationsVelocitiesRaw[iter->first]->getMu())).normalized();
      ++haveForward;
    }
  }
  
  if (haveForward == 0)
    return;
  
  forward = forward / haveForward;
  
  Vector3d right(0, 0, 0);
  unsigned haveRight = 0;
  for(vector<LandmarkPair>::iterator iter = d_rightPairs.begin(); iter != d_rightPairs.end(); ++iter)
  {
    if (d_objectInfos[iter->first]->visible && d_objectInfos[iter->second]->visible)
    {
      right = right + (cutLocVec(d_locationsVelocitiesRaw[iter->second]->getMu()) - cutLocVec(d_locationsVelocitiesRaw[iter->first]->getMu())).normalized();
      ++haveRight;
    }
  }
  
  if (haveRight == 0)
  {
    // Check cross products
    for (vector<LandmarkPairPair>::iterator iter = d_rightCrossProductPairs.begin(); iter != d_rightCrossProductPairs.end(); ++iter)
    {
      if (d_objectInfos[iter->first.first]->visible && d_objectInfos[iter->first.second]->visible &&
          d_objectInfos[iter->second.first]->visible && d_objectInfos[iter->second.second]->visible)
      {
        Vector3d a = cutLocVec(d_locationsVelocitiesRaw[iter->first.second]->getMu()) - cutLocVec(d_locationsVelocitiesRaw[iter->first.first]->getMu());
        Vector3d b = cutLocVec(d_locationsVelocitiesRaw[iter->second.second]->getMu()) - cutLocVec(d_locationsVelocitiesRaw[iter->second.first]->getMu());
        right = right + a.cross(b).normalized();
        ++haveRight;
      }
    }
    if (haveRight == 0)
      return;
  }

  right = right / haveRight;
  
  Vector3d up = right.cross(forward);
  
  Transform3d invTransform = Math::makeTransform(right, forward, up);
  Transform3d transform(invTransform.inverse());
  
  // If both are the same, this should be the identity matrix
  Transform3d diff = d_globalRotation * invTransform;

  if (diff.matrix().diagonal().minCoeff() < 0.98)
    d_globalRotation = transform;
}

