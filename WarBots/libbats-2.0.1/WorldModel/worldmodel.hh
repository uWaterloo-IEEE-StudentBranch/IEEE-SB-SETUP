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

#ifndef __INC_BATS_WORLDMODEL_HH_
#define __INC_BATS_WORLDMODEL_HH_

//#include <iostream>


#include <map>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "../Predicate/predicate.hh"
#include "../Ref/rf.hh"
#include "../SocketComm/AgentSocketComm/agentsocketcomm.hh"
#include "../Hashclasses/hashclasses.hh"
#include "../Distribution/NormalDistribution/normaldistribution.hh"
#include "../Singleton/singleton.hh"
//#include "../PlayerInfo/playerinfo.hh"
#include "../Localizer/localizer.hh"

namespace bats {

  /**
   *  The WorldModel
   */
  class WorldModel {

    friend class Singleton<WorldModel>;

  public:

    /**
     *  @returns the current simulation time.
     */
    float getTime() const;

    /**
     *  Sets the team name, which is used later on to identify which player
     *  is our and which player is theirs.
     */
    void setTeamName(std::string const &name);

    /**
     *  @returns our team name.
     */
    std::string getTeamName() const;

    /**
     * @returns the side of the field our team is playing on.
     */
    Types::Side getSide() const;

    /** Check if an object is on our or on their side
     *
     * @returns the US/THEM type corresponding to @object.
     */
    Types::Object checkSide(Types::Object object) const;

    /**
     *  @returns the gamestate
     */
    Types::PlayMode getPlayMode() const;

    /**
     * @returns the gamestate of last timestep
     */
    Types::PlayMode getLastPlayMode() const;

    /**
     * @returns whether our team has scored this timestep
     */
    bool weJustScored() const;

    /**
     * @returns whether the opponent has scored this timestep
     */
    bool theyJustScored() const;

    /**
     *  @returns the current game time.
     */
    double getGameTime() const;

    /**
     *  @returns the game time of the previous step.
     */
    double getPrevGameTime() const;

    /**
     *  @returns the amount of time between the previous and the current game time.
     */
    double getTimeStep() const;

    /**
     * /TODO Move to a better place
     * @returns the direction of the center of the opponent's goal in polar coordinates
     */
    Eigen::Vector3d getDirectionOfOpponentGoal() const;

    /**
     * @returns he first time recieved by the server ever
     */
    double getFirstTime() const;

    /**
     * Update the world model. This updates the AgentSocketComm, reads all messages and integrates them into the model.
     */
    void update();

    /**
     *  @returns the number of messages received by the agent.
     */
    unsigned getNumMsgReceived() const;

    /**
     * @returns the radius of the ball in meters
     */
    double getBallRadius() const;

    /**
     * @returns the length of the field
     */
    double getFieldLength() const;

    /**
     * @returns the width of the field
     */
    double getFieldWidth() const;

    /**
     * @returns the width of the goal
     */
    double getGoalWidth() const;

    /**
     * @returns the number of players in our team
     */
    size_t getNumberOfPlayers() const;

    /**
     * @returns the number of players in the opponent's team
     */
    size_t getNumberOfOpponents() const;

    /**
     * @return whether we get to take the next kick off. Only usable in Types::BEFORE_KICKOFF and Types::GOAL_US/GOAL_THEM
     */
    bool weGetKickOff() const;

    /**
     * @returns whether other team mates are closer to the ball than this agent. If @a standing is true (default), only standing agents are considered. If @a count is false (default), the method returns directly after the first team mate closer to the ball is encountered, otherwise it returns the total number of team mates closer by.
     */
    unsigned otherCloserToBall(bool standing = true, bool count = false);

    /**
     * @returns whether other team mates are closer to the given point than this agent. If @a standing is true (default), only standing agents are considered. If @a count is false (default), the method returns directly after the first team mate closer to the given point is encountered, otherwise it returns the total number of team mates closer by.
     */
    unsigned otherCloserTo(Eigen::Vector3d const& pos, bool standing = true, bool count = false, Types::Object ignore = Types::NOBJECTS);

    /**
     * @returns our score
     */
    unsigned getOurScore() const;

    /**
     * @returns the opponents score
     */
    unsigned getTheirScore() const;
/*
    typedef std::map<unsigned,PlayerInfo>::const_iterator player_iterator;

    player_iterator beginPlayers() const;
    player_iterator endPlayers() const;

    player_iterator beginOpponents() const;
    player_iterator endOpponents() const;
*/

    // Needed when having fixed sized Eigen member
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:

    WorldModel(WorldModel const &); // NI
    WorldModel &operator=(WorldModel const &); // NI

    double d_time;

    std::string d_teamName;

    bool d_halfTimeRestart;
    
    double d_gameTime;
    double d_prevGameTime;
    double d_timeStep;
    Types::PlayMode d_playMode;
    Types::PlayMode d_lastPlayMode;
    Types::Side d_team;
    unsigned d_scoreUs;
    unsigned d_scoreThem;

    std::map<unsigned,unsigned> d_opponentUnums;

    std::map<unsigned,unsigned> d_playerUnums;

    bool d_catchFallEnabled;
    bool d_getUpTheOldFashionedWay;

    double d_firstTime;
    unsigned int d_numMsgReceived;

    bool d_weGetKickOff;

    double d_ballRadius;
    double d_fieldLength;
    double d_fieldWidth;
    double d_goalWidth;

    //std::map<unsigned,PlayerInfo> d_players;
    //std::map<unsigned,PlayerInfo> d_opponents;

    void destroy();

    void updateGameState();

    WorldModel();

    PlayerInfo &getPlayerFromPid(unsigned pid);
    PlayerInfo &getOpponentFromPid(unsigned pid);

  };

  typedef Singleton<WorldModel> SWorldModel;


  // Inline method implementations


  inline float WorldModel::getTime() const
  {
    return d_time;
  }

  inline void WorldModel::setTeamName(std::string const &name)
  {
    d_teamName = name;
  }

  inline std::string WorldModel::getTeamName() const
  {
    return d_teamName;
  }

  inline Types::Side WorldModel::getSide() const
  {
    return d_team;
  }

  inline Types::PlayMode WorldModel::getPlayMode() const
  {
    return d_playMode;
  }

  inline Types::PlayMode WorldModel::getLastPlayMode() const
  {
    return d_lastPlayMode;
  }

  inline bool WorldModel::weJustScored() const
  {
    return (d_team == Types::LEFT && d_playMode == Types::GOAL_LEFT && d_lastPlayMode != Types::GOAL_LEFT) ||
           (d_team == Types::RIGHT && d_playMode == Types::GOAL_RIGHT && d_lastPlayMode != Types::GOAL_RIGHT);
  }

  inline bool WorldModel::theyJustScored() const
  {
    return (d_team == Types::RIGHT && d_playMode == Types::GOAL_LEFT && d_lastPlayMode != Types::GOAL_LEFT) ||
           (d_team == Types::LEFT && d_playMode == Types::GOAL_RIGHT && d_lastPlayMode != Types::GOAL_RIGHT);
  }

  inline double WorldModel::getGameTime() const
  {
    return d_gameTime;
  }

  inline double WorldModel::getPrevGameTime() const
  {
    return d_prevGameTime;
  }

  inline double WorldModel::getTimeStep() const
  {
    return d_timeStep;
  }

  inline double WorldModel::getFirstTime() const
  {
    return d_firstTime;
  }

  inline unsigned WorldModel::getNumMsgReceived() const
  {
    return d_numMsgReceived;
  }

  inline double WorldModel::getBallRadius() const
  {
    return d_ballRadius;
  }

  inline double WorldModel::getFieldLength() const
  {
    return d_fieldLength;
  }

  inline double WorldModel::getFieldWidth() const
  {
    return d_fieldWidth;
  }

  inline double WorldModel::getGoalWidth() const
  {
    return d_goalWidth;
  }

/*
  inline size_t WorldModel::getNumberOfPlayers() const
  {
    return d_players.size();
  }

  inline size_t WorldModel::getNumberOfOpponents() const
  {
    return d_opponents.size();
  }
*/

  inline bool WorldModel::weGetKickOff() const
  {
    return d_weGetKickOff;
  }
/*
  inline WorldModel::player_iterator WorldModel::beginPlayers() const
  {
    return d_players.begin();
  }

  inline WorldModel::player_iterator WorldModel::endPlayers() const
  {
    return d_players.end();
  }

  inline WorldModel::player_iterator WorldModel::beginOpponents() const
  {
    return d_opponents.begin();
  }

  inline WorldModel::player_iterator WorldModel::endOpponents() const
  {
    return d_opponents.end();
  }
*/
  inline unsigned WorldModel::getOurScore() const
  {
      return d_scoreUs;
  }

  inline unsigned WorldModel::getTheirScore() const
  {
      return d_scoreThem;
  }

};

#endif // __INC_BATS_WORLDMODEL_HH_
