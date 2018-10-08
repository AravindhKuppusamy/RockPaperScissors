#include "Arena.h"
#include "Referee.h"
#include "Woolie.h"

using std::this_thread::sleep_for;
using std::chrono::milliseconds;

unsigned int Arena::NEXT_ROUND = 1;

Arena::Arena(unsigned int nWoolies, unsigned int nReferees) : nWoolies_{nWoolies}, nReferees_{nReferees},
        woolies_in_this_round_{nWoolies}, woolies_finished_this_round{0}{
    cout << "WoolieRPST Round #1 BEGINS!" << endl;
}

Arena::~Arena() {
}

void Arena::populateReferees(){
    for(unsigned int i = 0; i < nReferees_;){
        referees_.emplace_back(new Referee(++i, this));
    }
    for(unsigned int i = 0; i < nReferees_; i++){
        referees_[i]->start();
    }
    for(unsigned int i = 0; i < nReferees_; i++){
        referees_[i]->detach();
    }
}

void Arena::removeReferees(){
    for(unsigned int i = 0; i < nReferees_; i++){
        delete referees_[i];
    }
}

void Arena::enterArena(Woolie *woolie) {
    if (woolies_in_this_round_ == 1){
        printStatistics(woolie);
        return;
    }

    {
        lock_guard<mutex> lg{wMutex_};
        woolies_.emplace_back(woolie);
    }

    {
        unique_lock<mutex> lock_match_with_referee{wMutex_};
        qStart.wait(lock_match_with_referee,
                    [woolie, this]()->bool{
                        return ((woolies_.front() == woolie) && (referees_.size() > 0) && (referees_.front()->isFree()));
                    });
        referees_.front()->addWoolie(woolie);
        if (!referees_.front()->isFree()){
            rotate(referees_.begin(), referees_.begin()+1, referees_.end());
        }

        woolies_.pop_front();
        woolies_finished_this_round += 1;
        sleep_for(milliseconds(200));
        qStart.notify_all();
    }

    {
        if (woolies_finished_this_round == woolies_in_this_round_)
            round_incremented = false;
        unique_lock<mutex> lock_exit{waitForNextRound_};
        nextRound_.wait(lock_exit,
                        [this]()->bool{
                            return (woolies_finished_this_round == woolies_in_this_round_);
                        });
        nextRound_.notify_all();
    }

    {
        lock_guard<mutex> print{printMutex_};
        sleep_for(milliseconds(500));
        if (!round_incremented) {
            cout << "WoolieRPST Round #" << round_ << " ENDS!" << endl;
            round_ += NEXT_ROUND;
            woolies_in_this_round_ /= 2;
            woolies_finished_this_round = 0;
            round_incremented = true;
            if (woolies_in_this_round_ != 1)
                cout << "WoolieRPST Round #" << round_ << " BEGINS!" << endl;
        }

    }

}

void Arena::printStatistics(Woolie* woolie) {
    woolie->setResult(false);

    cout << "Woolie-" << woolie->getID() << " is the WoolieRPST champion!" << endl;
    woolie->displayStats();

    cout << "Woolie RPS Tournament statistics:" << endl;
    cout << "\tNumber of woolies: " << nWoolies_ << endl;
    cout << "\tNumber of referees: " << nReferees_ << endl;
    displayStats();
}

void Arena::displayStats() {
    unsigned int total = (unsigned int) accumulate(stats_.begin(), stats_.end(), 0);
    cout << "\tRock: " << stats_[0] << ", " << (stats_[0]*100)/total << "%" << endl;
    cout << "\tPaper: " << stats_[1] << ", " << (stats_[1]*100)/total << "%" << endl;
    cout << "\tScissors: " << stats_[2] << ", " << (stats_[2]*100)/total << "%" << endl;
}

void Arena::updateStatistics(vector<unsigned int> stats1, vector<unsigned int> stats2) {
    {
        lock_guard<mutex> update{updateMutex_};
        stats_[0] += stats1[0] + stats2[0];
        stats_[1] += stats1[1] + stats2[1];
        stats_[2] += stats1[2] + stats2[2];
    }
}
