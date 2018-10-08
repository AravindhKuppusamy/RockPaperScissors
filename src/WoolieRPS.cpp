#include "WoolieRPS.h"

WoolieRPS::WoolieRPS(unsigned int nWoolies, unsigned int nReferees) :
        nWoolies_(nWoolies), nReferees_(nReferees){
}

void WoolieRPS::action() {
    RodLaver_ = new Arena(nWoolies_, nReferees_);
    RodLaver_->populateReferees();

    for(unsigned int i = 0; i < nWoolies_;){
        woolies_.emplace_back(new Woolie{++i, RodLaver_});
    }
    for(unsigned int i = 0; i < nWoolies_; i++){
        woolies_[i]->start();
    }
    for(unsigned int i = 0; i < nWoolies_; i++){
        woolies_[i]->join();
    }

    RodLaver_->removeReferees();
}

WoolieRPS::~WoolieRPS() {
    for(unsigned int i = 0; i < nWoolies_; i++){
        delete woolies_[i];
    }
    delete RodLaver_;
}

