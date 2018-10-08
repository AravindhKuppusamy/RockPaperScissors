#ifndef ROCKPAPERSCISSORS_WOOLIERPS_H
#define ROCKPAPERSCISSORS_WOOLIERPS_H

#include <thread>
#include <vector>

#include "Arena.h"
#include "Woolie.h"
#include "Referee.h"

using namespace::std;

/**
 * Main class of Rock Paper Scissor Game.
 *  Creates the woolie threads and send them to arena where the tournament runs.
 *
 *  @author Aravindh Kuppusamy
 */
class WoolieRPS {
public:
    /** Constructing the WoolieRPS main class with woolie threads and referees and
     *   the arena.
     *
     *  @param nWoolies          number of Woolies
     *  @param nReferees         number of Referees
     */
    WoolieRPS(unsigned int nWoolies, unsigned int nReferees);

    /** Destroys the WoolieRPS main class. */
    ~WoolieRPS();

    /**
     * Creates the arena and woolies threads and sends them to arena.
     */
    void action();

private:
    /** Number of Woolies */
    unsigned int nWoolies_;

    /** Number of Referees */
    unsigned int nReferees_;

    /** Arena where the tournament runs */
    Arena* RodLaver_;

    /** Vector of Woolie threads */
    vector<Woolie*> woolies_;
};


#endif //ROCKPAPERSCISSORS_WOOLIERPS_H
