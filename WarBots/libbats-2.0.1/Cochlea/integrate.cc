#include "cochlea.ih"

void Cochlea::integrate(rf<Predicate> const &pred)
{
  _debugLevel1("Intergrating: " << *pred);

  //cout << "hoei1" << endl;
  //cerr << *pred << endl;
  //cout << "hoei2" << endl;

  Vector4d vect, vect2;

  InfoID HJID(iNone), UJID(iNone), TID(iNone), id2, id3;

  string str;
  unsigned pid;

  unsigned currentPID = 100;
  bool currentTeam = true;

  Vector4d now;

  double hearTime, hearAngle;
  string hearMessage;

  bool us;

  for (unsigned i = 0; i < iInfoID; ++i)
    d_info[i] = Vector4d(0,0,0,0);

  d_info[iTeam].x() = Types::UNKNOWN_SIDE;  // since UNKNOWN_SIDE is not 0 anymore the team will always be reset to LEFT
                                            // this is a bit of a dirty hack but it should help

  //double val = 0;

  // I have a slightly better idea for the following algorithm
  // but that would take more time to implement.

  for (Predicate::const_iterator i = pred->begin();
       i != pred->end(); ++i) {

    //cout << "pred: " << rf_cast<Predicate>(*i)->getStr() << endl;

    InfoID id = translateInfo(rf_cast<Predicate>(*i)->getStr());
    //cout << "id: " << id;


    d_dt[id] = now[0] - d_timestamps[id];
    d_timestamps[id] = now[0];

    switch (id) {

    case iGameState:
      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {

        id = translateInfo(rf_cast<Predicate>(*j)->getStr());
        d_dt[id] = now[0] - d_timestamps[id];
        d_timestamps[id] = now[0];

        switch (id) {

        case iUnum:
          d_info[iUnum] = parseScalar(rf_cast<Predicate>(*j));
          break;

        case iTeam:
          if ((*j)->getChild(0))
            d_info[iTeam].x() = (rf_cast<Predicate>((*j)->getChild(0))->getStr() == "left" ? Types::LEFT : Types::RIGHT);
          break;

        case iGameTime:
          d_info[iGameTime] = parseScalar(rf_cast<Predicate>(*j));
          break;

        case iPlayMode:
          if ((*j)->getChild(0))
            d_info[iPlayMode].x() = (d_playModeMap[rf_cast<Predicate>((*j)->getChild(0))->getStr()]);
          break;

        default:
          break;
        }
      }

      break;

    case iVision:
      //cout << "vision" << endl;
      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {

        //cout << "pred2: " << rf_cast<Predicate>(*j)->getStr() << endl;;
        id = translateInfo(rf_cast<Predicate>(*j)->getStr());
        //cout << "id2: " << id;

        d_dt[id] = now[0] - d_timestamps[id];
        d_timestamps[id] = now[0];

        switch (id) {

        case iVisionBall:
          _debugLevel1("Got ball!");
        case iVisionFlag1L:
        case iVisionFlag1R:
        case iVisionFlag2L:
        case iVisionFlag2R:
        case iVisionGoal1L:
        case iVisionGoal1R:
        case iVisionGoal2L:
        case iVisionGoal2R:
          if ((*j)->getChild(0))
            vect = parseVect(rf_cast<Predicate>((*j)->getChild(0)));
          vect.y() = (vect.y() / 180.0 * M_PI);
          vect.z() = (vect.z() / 180.0 * M_PI);
          d_info[id] = vect;
          break;

        case iP:
          if ((*j)->getChild(0) && (*j)->getChild(0)->getChild(0))
            str = rf_cast<Predicate>((*j)->getChild(0)->getChild(0))->getStr();

          pid = 12;
          if ((*j)->getChild(0) && (*j)->getChild(1)->getChild(0))
            pid = rf_cast<Predicate>((*j)->getChild(1)->getChild(0))->getInt();


          if (pid > 11)
            continue;

          us = str == d_teamName;
          if (us) {
            id2 = (InfoID)(iVisionPlayer1 + pid - 1);
            _debugLevel1("PID/Team: " << currentPID << "/" << currentTeam);
          } else {
            d_opponentName = str;
            id2 = (InfoID)(iVisionOpponent1 + pid - 1);
            _debugLevel1("PID/Team: " << currentPID << "/" << currentTeam);
          }

          // Go through body parts
          for (Predicate::const_iterator k = (*j)->begin();
             k != (*j)->end(); ++k)
          {
            id = translateInfo(rf_cast<Predicate>(*k)->getStr());
            switch (id)
            {
            case iBodyHead:
              if((*k)->getChild(0))
                vect = parseVect(rf_cast<Predicate>((*k)->getChild(0)));
              vect.y() = (vect.y() / 180.0 * M_PI);
              vect.z() = (vect.z() / 180.0 * M_PI);
              _debugLevel4("vect: " << vect);
              d_info[id2] = vect;
              d_dt[id2] = now[0] - d_timestamps[id2];
              d_timestamps[id2] = now[0];
              break;

            case iBodyRLowerArm:
              if((*k)->getChild(0))
                vect = parseVect(rf_cast<Predicate>((*k)->getChild(0)));
              vect.y() = (vect.y() / 180.0 * M_PI);
              vect.z() = (vect.z() / 180.0 * M_PI);
              _debugLevel4("vect: " << vect);
              id3 = (InfoID)((us ? iRLowerArmPlayer1 : iRLowerArmOpponent1) + pid - 1);
              d_info[id3] = vect;
              d_dt[id3] = now[0] - d_timestamps[id2];
              d_timestamps[id3] = now[0];
              break;

            case iBodyLLowerArm:
              if((*k)->getChild(0))
                vect = parseVect(rf_cast<Predicate>((*k)->getChild(0)));
              vect.y() = (vect.y() / 180.0 * M_PI);
              vect.z() = (vect.z() / 180.0 * M_PI);
              _debugLevel4("vect: " << vect);
              id3 = (InfoID)((us ? iLLowerArmPlayer1 : iLLowerArmOpponent1) + pid - 1);
              d_info[id3] = vect;
              d_dt[id3] = now[0] - d_timestamps[id2];
              d_timestamps[id3] = now[0];
              break;

            case iBodyRFoot:
              if((*k)->getChild(0))
                vect = parseVect(rf_cast<Predicate>((*k)->getChild(0)));
              vect.y() = (vect.y() / 180.0 * M_PI);
              vect.z() = (vect.z() / 180.0 * M_PI);
              _debugLevel4("vect: " << vect);
              id3 = (InfoID)((us ? iRFootPlayer1 : iRFootOpponent1) + pid - 1);
              d_info[id3] = vect;
              d_dt[id3] = now[0] - d_timestamps[id2];
              d_timestamps[id3] = now[0];
              break;

            case iBodyLFoot:
              if((*k)->getChild(0))
                vect = parseVect(rf_cast<Predicate>((*k)->getChild(0)));
              vect.y() = (vect.y() / 180.0 * M_PI);
              vect.z() = (vect.z() / 180.0 * M_PI);
              _debugLevel4("vect: " << vect);
              id3 = (InfoID)((us ? iLFootPlayer1 : iLFootOpponent1) + pid - 1);
              d_info[id3] = vect;
              d_dt[id3] = now[0] - d_timestamps[id2];
              d_timestamps[id3] = now[0];
              break;

            default:
              break;
            }

          }
          break;

        default:
          break;

        };

      }
      break;

    case iGyro:
      id = iTorsoGyro;
      d_dt[id] = now[0] - d_timestamps[id];
      d_timestamps[id] = now[0];
      if((*i)->getChild(1))
        d_info[id] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));

      _debugLevel4("d_info[iTorsoGyro]: " << d_info[iTorsoGyro]);

      break;

    case iAcc:
      d_dt[id] = now[0] - d_timestamps[id];
      d_timestamps[id] = now[0];
      if((*i)->getChild(1))
        d_info[id] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));
      break;
      
    case iForceResistancePerceptor:
      TID = iNone;
      _debugLevel4("iForceResistancePerceptor");
      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j)
        {
          id = translateInfo(rf_cast<Predicate>(*j)->getStr());

          d_dt[id] = now[0] - d_timestamps[id];
          d_timestamps[id] = now[0];

          switch (id) {
          case iName:
            if ((*j)->getChild(0))
              TID = translateInfo(rf_cast<Predicate>((*j)->getChild(0))->getStr());
            _debugLevel4("TID: " << TID);
            break;

          case iContact:
            vect = parseVect(rf_cast<Predicate>(*j));
            _debugLevel4("vect: " << vect);
            break;

          case iForce:
            vect2 = parseVect(rf_cast<Predicate>(*j));

			if (d_frpFix) {
			  if (vect2.norm() != 0 && d_info[iPlayMode].x() != Types::BEFORE_KICKOFF)
				d_frpFix = false;
			  else
				vect2.z() = (1.0);
			}

            _debugLevel4("vect2: " << vect2);
            break;

          default:
            break;
          }
        }

      d_dt[TID] = now[0] - d_timestamps[TID];
      d_timestamps[TID] = now[0];
      d_info[TID] = vect;
      d_info[TID + 1] = vect2;
      break;

    case iTime:
      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {

        id = translateInfo(rf_cast<Predicate>(*j)->getStr());

        d_dt[id] = now[0] - d_timestamps[id];
        d_timestamps[id] = now[0];

        switch (id) {

        case iNow:
          now = parseScalar(rf_cast<Predicate>(*j));
          d_info[iNow] = now;
          break;

        case iStep:
          d_info[iStep] = parseScalar(rf_cast<Predicate>(*j));
          break;

        default:
          break;


        };


      }
      break;

    case iUJ:
      vect = Vector4d(0.0,0.0,0.0,0.0);
      vect2 = Vector4d(0.0,0.0,0.0,0.0);

      UJID = iNone;

      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {

        id = translateInfo(rf_cast<Predicate>(*j)->getStr());

        switch (id) {
        case iName:
          UJID = translateInfo(rf_cast<Predicate>((*j)->getChild(0))->getStr());
          _debugLevel4(rf_cast<Predicate>((*j)->getChild(0))->getStr());
          break;

        case iAxis1:
          vect.x() = (*rf_cast<Predicate>((*j)->getChild(0)));
          _debugLevel4("joint: " << vect.x());
          break;

        case iRate1:
          vect.y() = (*rf_cast<Predicate>((*j)->getChild(0)));
          break;

        case iAxis2:
          vect2.x() = (*rf_cast<Predicate>((*j)->getChild(0)));
          _debugLevel4("joint: " << vect2.x());
          break;

        case iRate2:
          vect2.y() = (*rf_cast<Predicate>((*j)->getChild(0)));
          break;

        default:
          _debugLevel4("Unknown id: " << rf_cast<Predicate>(*j)->getStr());
          break;
        };

      }

      if (UJID) {
        d_dt[UJID] = now[0] - d_timestamps[UJID];
        d_timestamps[UJID] = now[0];
        d_dt[UJID+1] = now[0] - d_timestamps[UJID];
        d_timestamps[UJID+1] = now[0];
        d_info[UJID] = vect;
        d_info[UJID+1] = vect2;
      } else
        _debugLevel4("Unknown UJID!");
      break;

    case iHJ:
      vect = Vector4d(0.0,0.0,0.0,0.0);

      HJID = iNone;

      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {

        id = translateInfo(rf_cast<Predicate>(*j)->getStr());

        switch (id) {
        case iName:
          HJID = translateInfo(rf_cast<Predicate>((*j)->getChild(0))->getStr());
          break;

        case iAxis:
          vect.x() = (*rf_cast<Predicate>((*j)->getChild(0)));
          _debugLevel4("joint: " << HJID << " " << vect.x());
          break;

        case iRate:
          vect.y() = (*rf_cast<Predicate>((*j)->getChild(0)));
          break;

        default:
          break;
        };

      }

      if (HJID)
        {
          d_dt[HJID] = now[0] - d_timestamps[HJID];
          d_timestamps[HJID] = now[0];
          d_info[HJID] = vect;
        }
      else
        _debugLevel4("Unknown HJID!");
      break;

    case iHJT:
      vect = Vector4d(0.0,0.0,0.0,0.0);

      HJID = iNone;

      for (Predicate::const_iterator j = (*i)->begin();
           j != (*i)->end(); ++j) {

        id = translateInfo(rf_cast<Predicate>(*j)->getStr());

        switch (id) {
        case iName:
          HJID = translateInfo(rf_cast<Predicate>((*j)->getChild(0))->getStr());
          break;

        case iAxis:
		  vect = parseVect(rf_cast<Predicate>(*j));
          _debugLevel2("joint: " << HJID << " " << vect);
          break;

        default:
          break;
        };

      }

      if (HJID)
        d_info[HJID] = vect;
      else
        _debugLevel4("Unknown HJID!");
      break;

    case iHear:
    
      if ((*i)->getChild(0))
        hearTime = *rf_cast<Predicate>((*i)->getChild(0));

      if ((*i)->getChild(1))
      {
        // Ignore messages from self
        if (rf_cast<Predicate>((*i)->getChild(1))->getStr() == "self")
          break;
        hearAngle = *rf_cast<Predicate>((*i)->getChild(1));
      }

      if ((*i)->getChild(0))
        hearMessage = rf_cast<Predicate>((*i)->getChild(2))->getStr();
      
      d_dt[iHear] = now[0] - d_timestamps[iHear];
      d_timestamps[iHear] = now[0];

      d_hearMessage = HearMessage(hearTime, hearAngle, hearMessage);

      break;

    case iBody:
      _debugLevel1("ERROR!! Wrong Body!! Body (pid="<<currentPID<<")");

      id = translateInfo(rf_cast<Predicate>((*i)->getChild(0))->getStr());

      if (currentPID == 100) {

        if (id < iInfoID)
          d_info[id] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));

      } else {

        if (currentTeam) {

          switch (id) {

          case iBodyRLowerArm:
            d_info[iRLowerArmPlayer1 + currentPID] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));
            break;

          case iBodyLLowerArm:
            d_info[iLLowerArmPlayer1 + currentPID] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));
            break;

          case iBodyRFoot:
            d_info[iRFootPlayer1 + currentPID] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));
            break;

          case iBodyLFoot:
            d_info[iRFootPlayer1 + currentPID] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));
            break;

          default:
            break;
          };

        } else {

          switch (id) {

          case iBodyRLowerArm:
            d_info[iRLowerArmOpponent1 + currentPID] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));
            break;

          case iBodyLLowerArm:
            d_info[iLLowerArmOpponent1 + currentPID] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));
            break;

          case iBodyRFoot:
            d_info[iRFootOpponent1 + currentPID] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));
            break;

          case iBodyLFoot:
            d_info[iRFootOpponent1 + currentPID] = parseVect(rf_cast<Predicate>((*i)->getChild(1)));
            break;

          default:
            break;
          };
        }

      }
      break;

    default:
      break;
    };


  }
  //cout << "hoei1" << endl;
}
