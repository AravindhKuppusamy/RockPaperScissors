#include "Arena.h"
#include "Woolie.h"

#include <numeric>


Woolie::Woolie(unsigned int id, Arena* arena) :
        id_(id), thread_{}, result_{true}, arena_(arena) {
}

Woolie::~Woolie() {
    if(thread_.joinable())
        thread_.join();
}

ostream &operator<<(ostream &os, const Woolie &woolie) {
    return os << "Woolie-" << woolie.getID();
}

void Woolie::start() {
    thread_ = thread{&Woolie::run, this};
}

void Woolie::join() throw(WoolieException){
    thread_.join();
}

unsigned int Woolie::getID() const{
    return id_;
}

void Woolie::setResult(bool result) {
    result_ = result;
}

void Woolie::run() {
    while(this->result_){
        arena_->enterArena(this);
    }
}

void Woolie::displayStats() {
    unsigned int total = (unsigned int) accumulate(stats_.begin(), stats_.end(), 0);;
    cout << "\tRock: " << stats_[0] << ", " << (stats_[0]*100)/total << "%" << endl;
    cout << "\tPaper: " << stats_[1] << ", " << (stats_[1]*100)/total << "%" << endl;
    cout << "\tScissors: " << stats_[2] << ", " << (stats_[2]*100)/total << "%" << endl;
}

void Woolie::updateStats(vector<unsigned int> stats) {
    stats_[0] += stats[0];
    stats_[1] += stats[1];
    stats_[2] += stats[2];
}
