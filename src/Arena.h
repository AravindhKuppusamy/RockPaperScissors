#ifndef ROCKPAPERSCISSORS_ARENA_H
#define ROCKPAPERSCISSORS_ARENA_H

#include <queue>
#include <mutex>
#include <algorithm>
#include <condition_variable>
#include <unordered_set>
#include "woolie_exception.h"

using namespace::std;

class Referee;
class Woolie;

/**
 * Represents the arena where the matches are held in the Rock-Paper-Scissors tournament.
 *
 *  @author Aravindh Kuppusamy
 */
class Arena {
public:
    /** Constructing the arena where the RPS tournament is gonna happen
     *
     *  @param nReferees         Number of woolies who participates in the tournament
     *  @param nWoolies          Number of referees who officiates the matches
     */
    Arena(unsigned int nWoolies, unsigned int nReferees);

    /** Arena is destroyed */
    ~Arena();

    /** Referees are populated in the arena */
    void populateReferees();

    /** Referee exits the arena */
    void removeReferees();

    /** Updates the statistics of the woolies for whom the match was over in the tournament
     *
     *  @param stats1       Number of Rocks, Papers and Scissors put by woolie1 in the current game
     *  @param stats2       Number of Rocks, Papers and Scissors put by woolie2 in the current game
     */
    void updateStatistics(vector<unsigned int> stats1, vector<unsigned int> stats2);

    /** Woolies enter the arena and wait in a queue for matches
     *
     *  @param woolie       Woolie who enters the arena
     */
    void enterArena(Woolie *woolie);

    /** Prints the statistics of the woolie who won the tournament
     *
     *  @param woolie       Woolie who won the tournament
     */
    void printStatistics(Woolie* woolie);

    /** Prints the statistics of the whole tournament */
    void displayStats();

private:
    /** Current round in the tournament */
    unsigned int round_ = 1;

    /** Static variable to increment the current round */
    static unsigned int NEXT_ROUND;

    /** Flag to check whether the round is incremented or not */
    bool round_incremented;

    /** Statistics of the whole tournament */
    vector<unsigned int> stats_{0, 0, 0};

    /** Total number of woolies */
    unsigned int nWoolies_;

    /** Total number of referees */
    unsigned int nReferees_;

    /** Number of woolies in the current round */
    unsigned int woolies_in_this_round_;

    /** Number of woolies who finished the current round */
    unsigned int woolies_finished_this_round;

    /** Queue to store referees */
    deque<Referee*> referees_;

    /** Queue where the woolies wait */
    deque<Woolie*> woolies_;

    /** Mutex for the woolie queue */
    mutex wMutex_;

    /** Mutex for printing */
    mutex printMutex_;

    /** Mutex for updating statistics */
    mutex updateMutex_;

    /** Mutex for making woolies waiting for next round */
    mutex waitForNextRound_;

    /** Conditional variable for waitForNextRound mutex */
    condition_variable nextRound_;

    /** Conditional variable for woolie queue mutex */
    condition_variable qStart;
};


#endif //ROCKPAPERSCISSORS_ARENA_H
