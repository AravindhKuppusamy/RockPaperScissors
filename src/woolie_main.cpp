#include <iostream>
#include "WoolieRPS.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3){
        cout << "Usage: woolie_main #_woolies #_referees" << endl;
    }
    else {
        int nWoolies = stoi(argv[1]);
        int nReferees = stoi(argv[2]);
        if (nWoolies < 1 || nReferees < 1) {
            cout << "Error: #_woolies and #_referees must be greater than or equal to 1!" << endl;
            exit(1);
        }
        if (nWoolies % 2 != 0) {
            cout << "Error: #_woolies must be a power of 2!" << endl;
            exit(1);
        }

        WoolieRPS RPS((unsigned int) nWoolies, (unsigned int) nReferees);
        RPS.action();
    }

    return 0;
}
