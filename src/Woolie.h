#ifndef ROCKPAPERSCISSORS_WOOLIE_H
#define ROCKPAPERSCISSORS_WOOLIE_H

#include <thread>
#include <vector>
#include <iostream>
#include "woolie_exception.h"

using namespace::std;

class Arena;

/**
 * Represents a woolie who participates in the Rock-Paper-Scissors tournament.
 *
 *  @author Aravindh Kuppusamy
 */
class Woolie {
public:

    /** Constructing the Woolie thread class with the given ID and the
     *   arena to enter into.
     *
     *  @param id          ID of the woolie
     *  @param arena       Arena to enter into
     */
    Woolie(unsigned int id, Arena* arena);

    /** Woolies exits the tournament */
    virtual ~Woolie();

    /** Returns the ID of the woolie
     *
     *  @return           ID of the woolie
     */
    unsigned int getID() const;

    /** Gets the information whether the woolie is still in the tournament or not!
     *
     *  @param result       True if the woolie is still in tournament; False otherwise
     */
    void setResult(bool result);

    /** Updates the statistics of the woolie in the tournament
     *
     *  @param stats       Number of Rocks, Papers and Scissors put by woolie in the current game
     */
    void updateStats(vector<unsigned int> stats);

    /** Prints the statistics of the woolie in the tournament */
    void displayStats();

    /** Starts the woolie thread. Calls run method */
    void start();

    /** Woolie enters the arena until he loses the round */
    void run();

    /** Joins the woolie thread with the woolieRPS.
     *
     * @throw       Woolie Exception
     */
    void join() throw (WoolieException);

    /**
     * Prints the woolie name (Woolie-#ID)
     *
     * @param os             the output stream to insert into
     * @param woolie         the woolie
     * @return               the output stream
     */
    friend ostream& operator<<(ostream& os, const Woolie& woolie);

private:
    /** Woolie Thread */
    thread thread_;

    /** ID of the woolie */
    unsigned int id_;

    /** Result of the round */
    bool result_;

    /** Statistics of the woolie in the tournament */
    vector<unsigned int> stats_{0, 0, 0};

    /** Arena where the tournament runs */
    Arena* arena_;
};

#endif //ROCKPAPERSCISSORS_WOOLIE_H
