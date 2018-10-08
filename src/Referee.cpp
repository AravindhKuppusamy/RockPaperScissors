#include "Arena.h"
#include "Referee.h"
#include "Woolie.h"

using std::this_thread::sleep_for;
using std::chrono::milliseconds;


Referee::Referee(unsigned int id, Arena* arena) :
        id_(id), thread_{}, arena_{arena}, rng_{0}{
    charMap[0] = "R";
    charMap[1] = "P";
    charMap[2] = "S";
}

Referee::~Referee() {
}

void Referee::start() {
    thread_ = thread{&Referee::run, this};
}

void Referee::run() {
    while(true){
        sleep_for(milliseconds(100));
        if((woolie1_ != nullptr) && (woolie2_ != nullptr)){
            playMatch();
            woolie1_ = nullptr;
            woolie2_ = nullptr;
        }
    }
}

void Referee::playMatch(){
    unsigned int xWins = 0, yWins = 0;
    string xRolls = "", yRolls = "";
    vector<unsigned int> stats1{0, 0, 0};
    vector<unsigned int> stats2{0, 0, 0};

    while (xWins+yWins < 3){
        auto player1 = rng_.rand();
        auto player2 = rng_.rand();

        stats1[player1] += 1;
        stats2[player2] += 1;
        xRolls += charMap[player1] + ",";
        yRolls += charMap[player2] + ",";

        if (player1 == player2)
            continue;
        findWinner(player1, player2) ? xWins += 1 : yWins += 1;
    }

    woolie1_->updateStats(stats1);
    woolie2_->updateStats(stats2);
    xRolls.pop_back();
    yRolls.pop_back();

    if (xWins > yWins){
        cout << *woolie1_ << " [" <<xRolls<< "]" << " *W* " << "vs "
             << *woolie2_ << " [" <<yRolls<< "]" << " *L*" << ", officiated by " << *this << endl;
        woolie1_->setResult(true);
        woolie2_->setResult(false);
    }
    else{
        cout << *woolie2_ << " [" <<yRolls<< "]" << " *W* " << "vs "
             << *woolie1_ << " [" <<xRolls<< "]" << " *L*" << ", officiated by " << *this << endl;
        woolie1_->setResult(false);
        woolie2_->setResult(true);
    }
    arena_->updateStatistics(stats1, stats2);
}

bool Referee::findWinner(unsigned int player1, unsigned int player2){
    if ((player1==0 && player2==2) || (player1==2 && player2==0))
        return player1<player2;
    else
        return player1>player2;
}

void Referee::detach() {
    thread_.detach();
}

unsigned int Referee::getID() const{
    return id_;
}

bool Referee::isFree() {
    return (woolie1_ == nullptr) || (woolie2_ == nullptr);
}

void Referee::addWoolie(Woolie *woolie) {
    if (woolie1_ == nullptr)
        woolie1_ = woolie;
    else
        if (woolie2_ == nullptr)
            woolie2_ = woolie;
        else
            cerr << "*******" << endl;
}

ostream &operator<<(ostream& os, const Referee& referee) {
    return os << "Referee-" << referee.getID();
}
