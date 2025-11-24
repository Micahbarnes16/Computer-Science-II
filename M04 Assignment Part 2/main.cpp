/*
   Name: Micah Barnes
   Date: 11/24/2025
   Course: CSCI 201 - Computer Science II
   Assignment: M04 - Part 2
   Program: Nerf Gun Class and Operator Overloading
   Description:
      Program creates several Nerf guns, displays info, compares ammo,
      and performs one random action per gun.
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "nerfGun.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));
    vector<nerfGun> guns;

    try {
        guns.push_back(nerfGun("Elite Disruptor", 90, 6));
        guns.push_back(nerfGun("Elite Rampage", 80, 25));
        guns.push_back(nerfGun("Mega Mastodon", 75, 24));
        guns.push_back(nerfGun("Nemesis MXVII-10K", 100, 100));
        guns.push_back(nerfGun("Ultra One", 120, 25));
    }
    catch (const exception& e) {
        cout << "Error creating gun: " << e.what() << endl;
        return 1;
    }

    cout << "\n=== Initial Gun Info ===\n";
    for (const auto& g : guns)
        cout << g << endl;

    nerfGun* mostAmmo = &guns[0];
    for (auto& g : guns)
        if (*mostAmmo < g)
            mostAmmo = &g;

    cout << "\nGun with most ammo: " << mostAmmo->getModel()
         << " (" << mostAmmo->getDartCount() << " darts)\n";

    cout << "\n=== Random Actions ===\n";

    for (auto& g : guns) {

        int fireRequest = (rand() % g.getCapacity()) + 1;
        int reloadRequest = (rand() % g.getCapacity()) + 1;


        int start = g.getDartCount();

        // Fire
        for (int i = 0; i < fireRequest; i++) {
            try { g--; }
            catch (...) { break; }
        }

        int afterFire = g.getDartCount();
        int actualFired = start - afterFire;

        // Reload
        try { g += reloadRequest; }
        catch (...) { /* no reload if exception */ }

        int finalDarts = g.getDartCount();
        int actualReloaded = finalDarts - afterFire;
        if (actualReloaded < 0) actualReloaded = 0;

        cout << g.getModel()
             << "  Darts fired: " << actualFired
             << "  Darts reloaded: " << actualReloaded
             << "  Darts left: " << finalDarts
             << endl;
    }

    cout << "\n=== Program Complete ===\n";
    return 0;
}

