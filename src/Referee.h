#ifndef ROCKPAPERSCISSORS_REFEREE_H
#define ROCKPAPERSCISSORS_REFEREE_H

#include <map>
#include <thread>
#include <iostream>
#include "rng.h"
#include "woolie_exception.h"

using namespace::std;

class Arena;
class Woolie;

/**
 * Represents a referee who officates the matches in the Rock-Paper-Scissors tournament.
 *
 *  @author Aravindh Kuppusamy
 */
class Referee {
public:
    /** Constructing the Referee thread class with the given ID and the
     *   arena to enter into.
     *
     *  @param id          ID of the referee
     *  @param arena       Arena to enter into
     */
    Referee(unsigned int id, Arena* arena);

    /** Referee exits the tournament */
    virtual ~Referee();

    /** Starts the referee thread. Calls run method */
    void start();

    /** Referees conducts the matches with two woolies */
    void run();

    /** Detaches the referee thread from the arena. */
    void detach();

    /** Returns whether the referee is free to conduct next match
     *
     *  @return           if the referee is free. i.e., Doesnt have two woolies attached.
     */
    bool isFree();

    /** Returns the ID of the referee
     *
     *  @return           ID of the referee
     */
    unsigned int getID() const;

    /** Attaches a reference of the woolie for whom the referee will organize
     *   a match with another woolie.
     *
     *  @param            woolie for which the referee should conduct a match
     */
    void addWoolie(Woolie* woolie);

    /**
     * Prints the referee name (Referee-#ID)
     *
     * @param os             the output stream to insert into
     * @param woolie         the referee
     * @return               the output stream
     */
    friend ostream& operator<<(ostream& os, const Referee& referee);

private:

    /** RPS match is conducted and prints the result */
    void playMatch();

    /** Determines the winner among two woolies for the current turn and the winner is returned
     *
     *  @param player1         Woolie 1
     *  @param player2         Woolie 2
     *  @return                Whether woolie-1 is winner or not
     */
    bool findWinner(unsigned int player1, unsigned int player2);

    /** Map to relate numbers with Rock, Paper and Scissors */
    map<unsigned int, string> charMap;

    /** Random number generator */
    RNG rng_;

    /** Woolie Thread */
    thread thread_;

    /** ID of the woolie */
    unsigned int id_;

    /** Woolie-1*/
    Woolie *woolie1_ = nullptr;

    /** Woolie-2 */
    Woolie *woolie2_ = nullptr;

    /** Arena where the tournament runs */
    Arena* arena_;
};

#endif //ROCKPAPERSCISSORS_REFEREE_H
