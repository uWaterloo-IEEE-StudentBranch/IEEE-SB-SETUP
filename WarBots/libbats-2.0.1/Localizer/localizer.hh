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

#ifndef _BATS_LOCALIZER_HH_
#define _BATS_LOCALIZER_HH_

#include <Eigen/Core>
#include <Eigen/LU>
#include <Eigen/Geometry>

#include "../Distribution/distribution.hh"
#include "../Types/types.hh"
#include "../Singleton/singleton.hh"

namespace bats
{
  struct ObjectInfo : RefAble
  {
    rf<Distribution> locVelLocal;
    rf<Distribution> locVelGlobal;
    bool alive;
    bool visible;
  };
  
  struct PlayerInfo : ObjectInfo
  {
    Eigen::Vector3d locLArmLocal;
    Eigen::Vector3d locRArmLocal;
    Eigen::Vector3d locLFootLocal;
    Eigen::Vector3d locRFootLocal;

    Eigen::Vector3d locLArmGlobal;
    Eigen::Vector3d locRArmGlobal;
    Eigen::Vector3d locLFootGlobal;
    Eigen::Vector3d locRFootGlobal;
    
    bool lArmVisible;
    bool rArmVisible;
    bool lFootVisible;
    bool rFootVisible;
  };
  /** The localizer interface

    Localization is done using a class with an interface compatible with this
    one. The specialized version (like SimpleLocalizer) should be placed in the
    Singleton of the Localizer type, which then returns the interface compatible
    specialized class.

    Example: SLocalizer::initialize<SimpleLocalizer>();

    Localizers (and other modules of the library) consider three coordinate
    frames:
    - Agent frame. The origin is at the center of the agent's torso. The
    positive x-axis points to his right (left shoulder to right shoulder), the
    positive y-axis to his front and the positive z-axis upwards (from center of
    torso to head). This is the frame used by AgentModel.
    - Local frame. The origin is at the center of the agent's torso. The
    positive x-axis points to his right, parallel to the field, the positive
    y-axis points to his front, parallel to the field and the positive z-axis
    points upwards, perpendicular to the field. So, this frame is sensitive to
    rotation in the plane parallel to the field, but not to rotation in a
    vertical plane. This frame is most useful for determining positions and
    directions relative to the agent.
    - Global frame. The origin is at the center of the field. The positive
    x-axis points from the origin to the opponent's goal, the positive y-axis to
    the left when facing the opponent's goal and the positive z-axis points
    upward, perpendicular to the field.
  */
  class Localizer
  {
    public:
      /** Called to initialize the Localizer */
      virtual void init() = 0;

      /** Called when an update needs to be done */
      virtual void update() = 0;

      rf<ObjectInfo> getObjectInfo(Types::Object object) const { return d_objectInfos[object]; }
      
      bool alive(Types::Object object) const { return d_objectInfos[object]->alive; }

      /** Return whether the  object is visible */
      bool visible(Types::Object object) const { return d_objectInfos[object]->visible; }

      rf<Distribution> getLocVelLocal(Types::Object object) const { return d_objectInfos[object]->locVelLocal; }
      
      rf<Distribution> getLocVelGlobal(Types::Object object) const { return d_objectInfos[object]->locVelGlobal; }
      
      /** Get the location estimate of an object in the local frame */
      virtual rf<Distribution> getLocationLocal(Types::Object object) = 0;
      /** Get the velocity estimate of an object in the local frame */
      virtual rf<Distribution> getVelocityLocal(Types::Object object) = 0;

      /** Get the location estimate of an object in the global frame */
      virtual rf<Distribution> getLocationGlobal(Types::Object object) = 0;
      /** Get the velocity estimate of an object in the global frame */
      virtual rf<Distribution> getVelocityGlobal(Types::Object object) = 0;


      /** Get the local transformation matrix
       *
       * This matrix describes the transformation from the local frame to the
         agent frame, i.e. the axes of the agent frame in terms of the local
         frame. Multiplication of a vector in the agent frame with this matrix
         results in the location of that vector with respect to the local frame.
       */
      virtual Eigen::Transform3d getLocalTransformation() const = 0;

      /** Get the global transformation matrix
       *
       * This matrix describes the transformation from the global frame to the
         agent frame, i.e. the axes of the agent frame in terms of the global
         frame. Multiplication of a vector in the agent frame with this matrix
         results in the location of that vector with respect to the global
         frame.
       */
      virtual Eigen::Transform3d getGlobalTransformation() const = 0;


      /*
        Function to tell the localizer that we know our position for sure,
        for example after we have beamed to somewhere.
      */
      virtual void setGlobalPosition(Eigen::Vector3d &position) { };

      Eigen::Vector3d localToGobal(Eigen::Vector3d const& loc) { return Eigen::Transform3d(getGlobalTransformation() * getLocalTransformation().inverse()) * loc; }

      Eigen::Vector3d globalToLocal(Eigen::Vector3d const& glob) { return Eigen::Transform3d(getLocalTransformation() * getGlobalTransformation().inverse()) * glob; }
    protected:
      rf<ObjectInfo> d_objectInfos[Types::NOBJECTS];
  };

  typedef Singleton<Localizer> SLocalizer;
}

#endif

