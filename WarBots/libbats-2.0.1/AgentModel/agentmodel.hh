/*
 *  Little Green BATS (2008), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	November 1, 2008
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef _BATS_AGENTMODEL_HH_
#define _BATS_AGENTMODEL_HH_

#include <vector>
#include <map>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "../Distribution/NormalDistribution/normaldistribution.hh"
#include "../RefAble/refable.hh"
#include "../Ref/rf.hh"
#include "../Singleton/singleton.hh"
#include "../Types/types.hh"
#include "../Math/math.hh"

namespace bats
{
  class XMLNode;
  
  /**
   *  The AgentModel
   */
  class AgentModel
  {
  public:
    
    struct Joint;
    
    /**
     * Body part information
     */
    struct BodyPart : public RefAble
    {
      virtual ~BodyPart() {}
      
      /// Name of body part
      std::string name;
      
      /// Transformation matrix of body part
      Eigen::Transform3d transform;

      // Needed when having fixed sized Eigen member
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };

    /**
     * Limb information
     */
    struct Limb : public BodyPart
    {
      /// Weight of limb
      double weight;
      
      /// Weight of limb divided by the robot's total weight
      double relativeWeight;
      
      /// Dimensions of limb
      Eigen::Vector3d size;
      
      /// List of joints attached to this limb
      std::vector<rf<Joint> > joints;

      // Needed when having fixed sized Eigen member
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };
    
    /**
     * Joint information
     */
    struct Joint : public BodyPart
    {
      Joint()
      {
        angle = new NormalDistribution(1);
      }
      
      /// Axis of joint in local coordinate system
      Eigen::Vector3d axis;
      
      /// Name of joint's angle perceptor as used by server
      std::string perceptor;
      
      /// Name of joint's motor as used by server
      std::string effector;
      
      /// This joint's identifier
      Types::Joint id;
      
      /// This joint's type
      Types::JointType type;
      
      /// The index (0, 1) of this joint if it is part of a universal joint
      unsigned ujindex;

      /// Joint angle
      rf<NormalDistribution> angle;
      
      /// Body part connected by this joint
      rf<BodyPart> bodyPart;
      
      /// Anchor points of joint on body parts, relative to their center
      std::pair<Eigen::Vector3d, Eigen::Vector3d> anchors;
      
      /// @returns the joint's axis direction vector in the global coordinate system
      Eigen::Vector3d getAxisVec() const
      {
        return transform * axis;
      }

      // Needed when having fixed sized Eigen member
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };

     /**
      *  Directions the agent could be falling in
      */
    enum FallDirection
    {
      NOT_FALLING = 0,
      FALL_TO_FRONT,
      FALL_TO_BACK,
      FALL_TO_LEFT,
      FALL_TO_RIGHT
    };
  
  
    AgentModel();
    virtual ~AgentModel() {}
    
    /**
     * Initialize the agent's body description.
     *
     * This method uses Conf to acquire the model data.
     */
    void initBody();

    /**
     * Update the model of the agent.
     */
    void update();

    /**
     * Update the posture of a body
     * 
     * @param toros The torso (root node) of the body to update. When 0 (default), the AgentModel's internal body will be used
     * @param updateJoints If set to true, the joint angles in the body will be updated with values from the Cochlea
     */
    void updatePosture(rf<BodyPart> torso = 0, bool updateJoints = true);

    /**
     * @returns the name of the Ruby Scene Graph (rsg) file that the simulator uses for this agent.
     */
    std::string getRSG() const;
    
    /**
     * Set the uniform number of this agent. Only use before initializing the body description.
     */
    void setUnum(unsigned int const unum);
    /**
     * @returns the uniform number of this agent. This number is updated when a number is requested from and given by the simulator.
     */
    unsigned getUnum() const;
    
    /**
     * @returns the player class of this agent as defined in the configuration file
     */
    std::string getPlayerClass() const;
    
    /**
     * Inverse of getJointName
     * @returns the translation of a joint name into a Types::Joint enumeration value, Types::NJOINTS when joint does not exist.
     */
    Types::Joint getJointID(std::string const& joint) const;
    
    /**
     * Inverse of getJointID
     * @returns the translation of a Types::Joint enumeration value into a string.
     */
    std::string getJointName(Types::Joint const id) const;
    
    /**
     * @returns the information of joint @a joint
     */
    rf<Joint> getJoint(Types::Joint joint) const;

    /**
     * @returns the information of body part @a part
     */
    rf<Limb> getBodyPart(Types::BodyPart part) const;

    /**
     * @returns the force vector measured by the Force Resistance Perceptor (FRP) of the food on side @a side
     */
    Eigen::Vector3d getFootForce(Types::Side side) const;
    
    /**
     * @returns the center where the force measured by the Force Resistance Perceptor (FRP) of the food on side @a side acts upon.
     */
    Eigen::Vector3d getFootForceCenter(Types::Side side) const;
    
    /**
     * @returns the gyroscopic sensor measurement
     */
    Eigen::Vector3d getGyro() const;
    
    /**
     * @returns the gyroscopic sensor measurement from the previous step
     */
    Eigen::Vector3d getOldGyro() const;
    
    /**
     * @returns the accelerometer sensor measurement
     */
    Eigen::Vector3d getAcc() const;

    /**
     * @returns the location of the Center Of Mass (COM) of the robot, relative to the center of its torso.
     */
    Eigen::Vector3d getCOM() const;
    
    /**
     *  @returns true when the agent lies on its belly.
     */
    bool onMyBelly() const;

    /**
     *  @returns true when the agent lies on its back.
     */
    bool onMyBack() const;

    /**
     *  @returns true when the agent stands on its feet.
     */ 
    bool onMyFeet() const;

    /**
     *  @returns true when the agent lies on one of its sides.
     */
    bool onMySide() const;

    /** See whether the agent is down or not
     * @param check Whether you want to check if the agent is down or if he is standing
     */
    bool isDown(bool check = true) const;
    
    /**
     * @returns FallDirection (enum) in which direction the agent is falling
     */
    FallDirection getDirectionOfFall()
    {
      return d_fallDirection;
    }
    
    rf<BodyPart> getBodyCopy();
    
    // Needed when having fixed sized Eigen member
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:

    std::string d_rsg;
    unsigned d_unum;
    std::string d_playerClass;
    
    rf<BodyPart> d_torso;
    double d_weight;
    Eigen::Vector3d d_COM;
    
    Eigen::Vector3d d_footForceCenters[2];
    Eigen::Vector3d d_footForces[2];
    
    Eigen::Vector3d d_gyro;
    Eigen::Vector3d d_oldGyro;
    
    Eigen::Vector3d d_acc;
    
    FallDirection d_fallDirection;

    std::map<std::string, Types::Joint> d_jointNameMap;
    std::map<Types::Joint, rf<Joint> > d_joints;
    
    std::map<std::string, Types::BodyPart> d_limbNameMap;
    std::map<Types::BodyPart, rf<Limb> > d_limbs;
    

    // The modeled maximum kicking distance of the agent.
    rf<NormalDistribution> d_kickMaxDistance;

    // The modeled maximum kicking speed of the agent.
    rf<NormalDistribution> d_kickMaxSpeed;

    /** Recursive method to traverse XML to initialize body model
     *
     * @param node Current body part configuration node
     * @param playerClass The agent's player class
     * @param joint Joint current body part should be connected to
     * @returns Mass accumulated by this body part and recursive calls
     */
    double initBody(XMLNode& node, std::string playerClass, rf<Joint> joint);
    
    void updateCOM();
    void checkDirectionOfFall();

    rf<BodyPart> getBodyPartCopy(rf<BodyPart> part);
  };

  typedef Singleton<AgentModel> SAgentModel;
  
  // Inline method implementations
  
  inline std::string AgentModel::getRSG() const
  {
    return d_rsg;
  }
  
  inline unsigned AgentModel::getUnum() const
  {
    return d_unum;
  }

  inline std::string AgentModel::getPlayerClass() const
  {
    return d_playerClass;
  }

  inline Types::Joint AgentModel::getJointID(std::string const& joint) const
  {
    std::map<std::string, Types::Joint>::const_iterator j = d_jointNameMap.find(joint);
    if (j == d_jointNameMap.end())
      return Types::NJOINTS;
    else
      return j->second;
  }
  
  inline rf<AgentModel::Joint> AgentModel::getJoint(Types::Joint joint) const
  {
    return d_joints.find(joint)->second;
  }

  inline rf<AgentModel::Limb> AgentModel::getBodyPart(Types::BodyPart part) const
  {
    return d_limbs.find(part)->second;
  }

  inline Eigen::Vector3d AgentModel::getFootForce(Types::Side side) const
  {
    return d_footForces[side];
  }

  inline Eigen::Vector3d AgentModel::getFootForceCenter(Types::Side side) const
  {
    return d_footForceCenters[side];
  }

  inline Eigen::Vector3d AgentModel::getGyro() const
  {
    return d_gyro;
  }
  
  inline Eigen::Vector3d AgentModel::getOldGyro() const
  {
    return d_oldGyro;
  }

  inline Eigen::Vector3d AgentModel::getAcc() const
  {
    return d_acc;
  }
  
  inline Eigen::Vector3d AgentModel::getCOM() const
  {
    return d_COM;
  }
  
}

#endif
