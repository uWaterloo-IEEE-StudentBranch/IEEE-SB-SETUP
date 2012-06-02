#include "agentmodel.ih"

void AgentModel::updatePosture(rf<BodyPart> torso, bool updateJoints)
{
  if (!torso)
    torso = d_torso;
    
  assert(torso);
  
  Cochlea& cochlea = SCochlea::getInstance();
  
  list<rf<BodyPart> > partQueue;

  torso->transform.setIdentity();

  partQueue.push_back(torso);
  
  while (!partQueue.empty())
  {
    rf<BodyPart> part = partQueue.front();
    partQueue.pop_front();
    
    if (rf<Limb> limb = rf_dynamic_cast<Limb>(part))
    {
      _debugLevel4(limb->name << " " << limb->transform.translation() << " " << limb->relativeWeight);
      for (vector<rf<Joint> >::iterator iter = limb->joints.begin(); iter != limb->joints.end(); ++iter)
      {
        rf<Joint> joint = *iter;
        _debugLevel4(joint->name << " " << joint->anchors.first);
        joint->transform = limb->transform *
                           Translation3d(joint->anchors.first);
        
        partQueue.push_back(joint);
      }
    }
    else
    {
      rf<Joint> joint = rf_dynamic_cast<Joint>(part);
      _debugLevel4(joint->name << " " << joint->transform.translation() << " " << cochlea.getInfo(cochlea.translateInfo(joint->name))[0]);
      double a = Math::degToRad(cochlea.getInfo(cochlea.translateInfo(joint->name))[0]);
      if (updateJoints)
        joint->angle->init(VectorXd::Constant(1,a), VectorXd::Constant(1,1.0));
      _debugLevel4(joint->name << " " << -joint->anchors.second);
      
      rf<BodyPart> part2 = joint->bodyPart;
      part2->transform = joint->transform *
                          AngleAxisd(joint->angle->getMu()(0), joint->axis) *
                          Translation3d(-joint->anchors.second);
      //_debugLevel4(part2->transform);
      partQueue.push_back(part2);
    }
  }
  
}
