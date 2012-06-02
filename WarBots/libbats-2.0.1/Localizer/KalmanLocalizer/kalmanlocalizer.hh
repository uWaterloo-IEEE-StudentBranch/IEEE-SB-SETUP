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

#ifndef _BATS_KALMANLOCALIZER_HH_
#define _BATS_KALMANLOCALIZER_HH_

#include "../localizer.hh"
#include "../../Distribution/NormalDistribution/normaldistribution.hh"
#include "../../BatsEvent/batsevent.hh"
#include <map>
#include <vector>
#include <utility>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace bats
{
  class KalmanLocalizer : public Localizer
  {
      friend class Singleton<Localizer>;
      
      typedef std::pair<Types::Object, Types::Object> LandmarkPair;
      typedef std::pair<LandmarkPair, LandmarkPair> LandmarkPairPair;

      double d_lastRotationCheck;
      std::vector<LandmarkPair> d_forwardPairs;
      std::vector<LandmarkPair> d_rightPairs;
      std::vector<LandmarkPairPair> d_rightCrossProductPairs;
      
      Eigen::Transform3d d_globalRotation;
      Eigen::Transform3d d_globalTranslation;
      Eigen::Transform3d d_globalTransform;
      Eigen::Transform3d d_localTransform;
      
      bool d_newVisionData;
      
      /*
      bool d_visible[Types::NOBJECTS];
      bool d_alive[Types::NOBJECTS];
      */
      
      rf<NormalDistribution> d_locationsRaw[Types::NOBJECTS];
      //rf<NormalDistribution> d_locationsLocal[Types::NOBJECTS];
      //rf<NormalDistribution> d_locationsGlobal[Types::NOBJECTS];
      
      /*
      rf<NormalDistribution> d_velocitiesLocal[Types::NOBJECTS];
      rf<NormalDistribution> d_velocitiesGlobal[Types::NOBJECTS];
      */
      
      
      rf<NormalDistribution> d_locationsVelocitiesRaw[Types::NOBJECTS];
      //rf<NormalDistribution> d_locationsVelocitiesLocal[Types::NOBJECTS];
      //rf<NormalDistribution> d_locationsVelocitiesGlobal[Types::NOBJECTS];

      KalmanLocalizer();
      KalmanLocalizer(KalmanLocalizer const& other); //NI
      KalmanLocalizer& operator=(KalmanLocalizer const* other); //NI
      
      
      Eigen::Vector3d cutLocVec(Eigen::VectorXd const& locvel) const;
      Eigen::Vector3d cutVelVec(Eigen::VectorXd const& locvel) const;
      Eigen::VectorXd joinLocVelVec(Eigen::Vector3d const& loc, Eigen::Vector3d const& vel) const;
      
      Eigen::Matrix3d cutLocMat(Eigen::MatrixXd const& locvel) const;
      Eigen::Matrix3d cutVelMat(Eigen::MatrixXd const& locvel) const;
      Eigen::MatrixXd joinLocVelMat(Eigen::Matrix3d const& loc, Eigen::Matrix3d const& vel) const;
      
      
      void updateGlobalRotation();
      void checkGlobalRotation();
      
      void updateRaw();
      void updateSelfGlobal();
      void updateBallGlobal();
      void updatePlayersGlobal();
      void globalToLocal();
      //void cutDistributions();
      
    public:
      virtual void init();
      virtual void update();

      virtual rf<Distribution> getLocationLocal(Types::Object object)
      {
        rf<NormalDistribution> d = new NormalDistribution(3);
        d->init(d_objectInfos[object]->locVelLocal->getMu().start<3>(), d_objectInfos[object]->locVelLocal->getSigma().block<3,3>(0,0));
        return d;
      }
      
      virtual rf<Distribution> getVelocityLocal(Types::Object object)
      {
        rf<NormalDistribution> d = new NormalDistribution(3);
        d->init(d_objectInfos[object]->locVelLocal->getMu().end<3>(), d_objectInfos[object]->locVelLocal->getSigma().block<3,3>(3,3));
        return d;
      }

      virtual rf<Distribution> getLocationGlobal(Types::Object object)
      {
        rf<NormalDistribution> d = new NormalDistribution(3);
        d->init(d_objectInfos[object]->locVelGlobal->getMu().start<3>(), d_objectInfos[object]->locVelGlobal->getSigma().block<3,3>(0,0));
        return d;
      }

      virtual rf<Distribution> getVelocityGlobal(Types::Object object)
      {
        rf<NormalDistribution> d = new NormalDistribution(3);
        d->init(d_objectInfos[object]->locVelGlobal->getMu().end<3>(), d_objectInfos[object]->locVelGlobal->getSigma().block<3,3>(3,3));
        return d;
      }

      virtual Eigen::Transform3d getLocalTransformation() const { return d_localTransform; }

      virtual Eigen::Transform3d getGlobalTransformation() const { return d_globalTransform; }
      
      void onBeam(rf<BeamEvent> event);

      // Needed when having fixed sized Eigen member
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  };

  // Inline member implementations
  
  inline Eigen::Vector3d KalmanLocalizer::cutLocVec(Eigen::VectorXd const& locvel) const
  {
    return locvel.start<3>();
  }
  
  inline Eigen::Vector3d KalmanLocalizer::cutVelVec(Eigen::VectorXd const& locvel) const
  {
    return locvel.end<3>();
  }

}

#endif

