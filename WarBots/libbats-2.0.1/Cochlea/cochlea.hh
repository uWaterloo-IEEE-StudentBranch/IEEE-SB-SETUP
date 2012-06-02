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

#ifndef _BATS_COCHLEA_HH_
#define _BATS_COCHLEA_HH_

#include "../Ref/rf.hh"
#include "../SocketComm/AgentSocketComm/agentsocketcomm.hh"
#include "../Singleton/singleton.hh"
#include <vector>
#include <list>
#include <map>
#include <Eigen/Core>
#include "../Hashclasses/hashclasses.hh"
//#include "../PlayerInfo/playerinfo.hh"

namespace bats
{
  class Cochlea
  {
    friend class Singleton<Cochlea>;
    
  public:
    /**
     * Enumeration of all predicate types
     */
    enum InfoID {

      iNone = 0,
      
      iGameState,
      iUnum,
      iTeam,
      iGameTime,
      iPlayMode,
      
      iTime,         
      iNow,          ///< The current playing time.
      iStep,         ///< The time step (dt?)
      iVision,
      iVisionFlag1L, ///< First flag on the left side.
      iVisionFlag2L, ///< Second flag on the left side.
      iVisionFlag1R, ///< First flag on the right side.
      iVisionFlag2R, ///< Second flag on the right side.
      iVisionGoal1L, ///< First
      iVisionGoal2L, ///< 
      iVisionGoal1R, ///< 
      iVisionGoal2R, ///< 
      iVisionPlayer1,
      iVisionPlayer2,
      iVisionPlayer3,
      iVisionPlayer4,
      iVisionPlayer5,
      iVisionPlayer6,
      iVisionPlayer7,
      iVisionPlayer8,
      iVisionPlayer9,
      iVisionPlayer10,
      iVisionPlayer11,
      iVisionPlayerNone,
      iVisionOpponent1,
      iVisionOpponent2,
      iVisionOpponent3,
      iVisionOpponent4,
      iVisionOpponent5,
      iVisionOpponent6,
      iVisionOpponent7,
      iVisionOpponent8,
      iVisionOpponent9,
      iVisionOpponent10,
      iVisionOpponent11,
      iVisionOpponentNone,
      iVisionBall,   ///< Position of the ball.
      iUJ,
      iHJ,
      iHJT,
      iName,
      iAxis,
      iRate,
      iAxis1,
      iRate1,
      iAxis2,
      iRate2,

      iHeadJoint1,
      iHeadJoint2,
      
      iLLegJoint1,
      iLLegJoint2,
      iLLegJoint3,
      iLLegJoint4,
      iLLegJoint5,
      iLLegJoint6,

      iRLegJoint1,
      iRLegJoint2,
      iRLegJoint3,
      iRLegJoint4,
      iRLegJoint5,
      iRLegJoint6,

      iLArmJoint1,  ///< 
      iLArmJoint2,  ///< 
      iLArmJoint3,
      iLArmJoint4,

      iRArmJoint1,
      iRArmJoint2,
      iRArmJoint3,
      iRArmJoint4,

      iGyro,
      iTorsoGyro,
      iTouch,
      iFootLeft,
      iFootLeft2,  /// dummy
      iFootRight,
      iFootRight2,
      iVal,
      
      iForceResistancePerceptor,
      iContact,
      iForce,

      iHear,
      
      iP, /// Player vision info.

      iBody,
      iBodyHead,
      iBodyRLowerArm,
      iBodyLLowerArm,
      iBodyRFoot,
      iBodyLFoot,

      iRLowerArmPlayer1,
      iRLowerArmPlayer2,
      iRLowerArmPlayer3,
      iRLowerArmPlayer4,
      iRLowerArmPlayer5,
      iRLowerArmPlayer6,
      iRLowerArmPlayer7,
      iRLowerArmPlayer8,
      iRLowerArmPlayer9,
      iRLowerArmPlayer10,
      iRLowerArmPlayer11,
      
      iLLowerArmPlayer1,
      iLLowerArmPlayer2,
      iLLowerArmPlayer3,
      iLLowerArmPlayer4,
      iLLowerArmPlayer5,
      iLLowerArmPlayer6,
      iLLowerArmPlayer7,
      iLLowerArmPlayer8,
      iLLowerArmPlayer9,
      iLLowerArmPlayer10,
      iLLowerArmPlayer11,
      
      iRFootPlayer1,
      iRFootPlayer2,
      iRFootPlayer3,
      iRFootPlayer4,
      iRFootPlayer5,
      iRFootPlayer6,
      iRFootPlayer7,
      iRFootPlayer8,
      iRFootPlayer9,
      iRFootPlayer10,
      iRFootPlayer11,
      
      iLFootPlayer1,
      iLFootPlayer2,
      iLFootPlayer3,
      iLFootPlayer4,
      iLFootPlayer5,
      iLFootPlayer6,
      iLFootPlayer7,
      iLFootPlayer8,
      iLFootPlayer9,
      iLFootPlayer10,
      iLFootPlayer11,
      
      iRLowerArmOpponent1,
      iRLowerArmOpponent2,
      iRLowerArmOpponent3,
      iRLowerArmOpponent4,
      iRLowerArmOpponent5,
      iRLowerArmOpponent6,
      iRLowerArmOpponent7,
      iRLowerArmOpponent8,
      iRLowerArmOpponent9,
      iRLowerArmOpponent10,
      iRLowerArmOpponent11,
      
      iLLowerArmOpponent1,
      iLLowerArmOpponent2,
      iLLowerArmOpponent3,
      iLLowerArmOpponent4,
      iLLowerArmOpponent5,
      iLLowerArmOpponent6,
      iLLowerArmOpponent7,
      iLLowerArmOpponent8,
      iLLowerArmOpponent9,
      iLLowerArmOpponent10,
      iLLowerArmOpponent11,
      
      iRFootOpponent1,
      iRFootOpponent2,
      iRFootOpponent3,
      iRFootOpponent4,
      iRFootOpponent5,
      iRFootOpponent6,
      iRFootOpponent7,
      iRFootOpponent8,
      iRFootOpponent9,
      iRFootOpponent10,
      iRFootOpponent11,
      
      iLFootOpponent1,
      iLFootOpponent2,
      iLFootOpponent3,
      iLFootOpponent4,
      iLFootOpponent5,
      iLFootOpponent6,
      iLFootOpponent7,
      iLFootOpponent8,
      iLFootOpponent9,
      iLFootOpponent10,
      iLFootOpponent11,

      iAcc,
      iAccA,
      
      // Should always have the highest numeric value.
      iInfoID,
      
    };

    /**
     * Structure of an auditory message
     */
    struct HearMessage
    {
      double time;            /// Time at which message is received
      double angle;           /// Angle relative to torso of the direction the message came from
      std::string message;    /// Message content
      
      HearMessage(double t, double a, std::string const& m)
      : time(t), angle(a), message(m)
      {}
    };
    
  public:
    HearMessage getHearMessage() const { return d_hearMessage; }
    
    InfoID objectTypeToInfoID(Types::Object type)
    {
      if (d_objectTypesMap.find(type) != d_objectTypesMap.end())
        return d_objectTypesMap[type];
      else
        return iNone;
    }
    
    /**
     * @returns the translation of @a mode to a Types::PlayMode value
     */
    Types::PlayMode getPlayMode(std::string const& mode)
    {
      if (d_playModeMap.find(mode) != d_playModeMap.end())
        return d_playModeMap[mode];
      else
        return Types::UNKNOWN;
    }
    
    /**
     * Set the name of your own team, used to recognize team mates and opponents
     */
    void setTeamName(std::string const& teamName) { d_teamName = teamName; }
    
    std::string getOpponentName() const { return d_opponentName; }
    
    /**
     * Set translation. This is primarily used to map joint pereptor names to Cochlea's internal names.
     */
    void setTranslation(std::string const& from, std::string const& to) { d_infoMap[from] = d_infoMap[to]; }
    
    /**
     * @returns the translation of @a name to an InfoID value
     */
    InfoID translateInfo(std::string const &name);


    /**
     * Update values by integrating the latest predicate received by AgentSocketComm
     */
    void update();

    /**
     * @returns the value of the information with id @a id in the form of a 4-dimensional vector
     */	
    Eigen::Vector4d getInfo(InfoID id) const { return d_info[id]; }

    /**
     * @returns the time of the last measurement of this value
     */
    double getTimestamp(InfoID id) const { return d_timestamps[id]; }

    /**
     * @returns the time of the last measurement of this value
     */
    double getDelay(InfoID id) const { return d_timestamps[id] - d_info[iNow](0); }

    /**
     * @returns the time between the previous and the current measurement of this value
     */
    double getDt(InfoID id) const { return d_dt[id]; }
    
    // Needed when having fixed sized Eigen member
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
    FBB::StringHash<InfoID> d_infoMap;
    FBB::StringHash<Types::PlayMode> d_playModeMap;

    std::map<Types::Object, InfoID> d_objectTypesMap;
    
    Eigen::Vector4d d_info[iInfoID];
    double d_timestamps[iInfoID];
    double d_dt[iInfoID];
    
    HearMessage d_hearMessage;

    std::string d_teamName;
    std::string d_opponentName;
    
    //std::map<unsigned,PlayerInfo> d_players;
    //std::map<unsigned,PlayerInfo> d_opponents;

    Cochlea();
    
    Eigen::Vector4d parseVect(rf<Predicate> const &pred);

    Eigen::Vector4d parseScalar(rf<Predicate> const &pred);

    void integrate(rf<Predicate> const &pred);

    //PlayerInfo &getPlayerFromPid(unsigned pid);
    //PlayerInfo &getOpponentFromPid(unsigned pid);

    bool d_frpFix;

  };
  
  typedef Singleton<Cochlea> SCochlea;

/*
  inline Cochlea::player_iterator Cochlea::beginPlayers() const
  {
    return d_players.begin();
  }

  inline Cochlea::player_iterator Cochlea::endPlayers() const
  {
    return d_players.end();
  }

  inline Cochlea::player_iterator Cochlea::beginOpponents() const
  {
    return d_opponents.begin();
  }

  inline Cochlea::player_iterator Cochlea::endOpponents() const
  {
    return d_opponents.end();
  }  
*/

}

#endif

