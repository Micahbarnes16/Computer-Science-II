/* 
Name: Micah Barnes
Date: 12/08/2025
Course: CSCI 201 - M06 Programming Assignment Part 1
Program: NFL Team Program
Description: 
This program creates an abstract Player class and several derived classes 
for offense, defense, and special teams positions. The user can add 
players to a team and display everyone on the roster. 
*/

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <limits>
using namespace std;

// ====================== ABSTRACT PLAYER BASE CLASS ======================
class Player {
protected:
    string name;
    int playerID;
    string currentTeam;

public:
    Player(string n, int id, string team)
        : name(n), playerID(id), currentTeam(team) {}

    virtual ~Player() {}

    string getName() const { return name; }
    int getPlayerID() const { return playerID; }
    string getTeam() const { return currentTeam; }

    // Abstract methods required by assignment
    virtual string getPlayerPosition() const = 0;
    virtual string play() const = 0;
    virtual string toString() const = 0;
};

// ====================== INTERMEDIATE GROUP CLASSES ======================
class Offense : public Player {
public:
    Offense(string n, int id, string team) : Player(n, id, team) {}
};

class Defense : public Player {
public:
    Defense(string n, int id, string team) : Player(n, id, team) {}
};

class SpecialTeams : public Player {
public:
    SpecialTeams(string n, int id, string team) : Player(n, id, team) {}
};

// =========================== OFFENSE POSITIONS ===========================
class QuarterBack : public Offense {
public:
    QuarterBack(string n, int id, string team) : Offense(n, id, team) {}
    string getPlayerPosition() const override { return "Quarterback"; }
    string play() const override { return "throws the football"; }
    string toString() const override {
        return name + " (#" + to_string(playerID) + ") - Quarterback | Team: " 
               + currentTeam + " | Plays: " + play();
    }
};

class WideReceiver : public Offense {
public:
    WideReceiver(string n, int id, string team) : Offense(n, id, team) {}
    string getPlayerPosition() const override { return "Wide Receiver"; }
    string play() const override { return "catches passes downfield"; }
    string toString() const override {
        return name + " (#" + to_string(playerID) + ") - Wide Receiver | Team: "
               + currentTeam + " | Plays: " + play();
    }
};

class TightEnd : public Offense {
public:
    TightEnd(string n, int id, string team) : Offense(n, id, team) {}
    string getPlayerPosition() const override { return "Tight End"; }
    string play() const override { return "blocks and catches short passes"; }
    string toString() const override {
        return name + " (#" + to_string(playerID) + ") - Tight End | Team: "
               + currentTeam + " | Plays: " + play();
    }
};

class RunningBack : public Offense {
public:
    RunningBack(string n, int id, string team) : Offense(n, id, team) {}
    string getPlayerPosition() const override { return "Running Back"; }
    string play() const override { return "runs the ball and catches screens"; }
    string toString() const override {
        return name + " (#" + to_string(playerID) + ") - Running Back | Team: "
               + currentTeam + " | Plays: " + play();
    }
};

class OffensiveLineman : public Offense {
public:
    OffensiveLineman(string n, int id, string team) : Offense(n, id, team) {}
    string getPlayerPosition() const override { return "Offensive Lineman"; }
    string play() const override { return "blocks defenders"; }
    string toString() const override {
        return name + " (#" + to_string(playerID) + ") - Offensive Lineman | Team: "
               + currentTeam + " | Plays: " + play();
    }
};

// ============================= DEFENSE POSITIONS ============================
class DefensiveLineman : public Defense {
public:
    DefensiveLineman(string n, int id, string team) : Defense(n, id, team) {}
    string getPlayerPosition() const override { return "Defensive Lineman"; }
    string play() const override { return "rushes the quarterback and stops the run"; }
    string toString() const override {
        return name + " (#" + to_string(playerID) + ") - Defensive Lineman | Team: "
               + currentTeam + " | Plays: " + play();
    }
};

class Linebacker : public Defense {
public:
    Linebacker(string n, int id, string team) : Defense(n, id, team) {}
    string getPlayerPosition() const override { return "Linebacker"; }
    string play() const override { return "tackles runners and covers short passes"; }
    string toString() const override {
        return name + " (#" + to_string(playerID) + ") - Linebacker | Team: "
               + currentTeam + " | Plays: " + play();
    }
};

class DefensiveBack : public Defense {
public:
    DefensiveBack(string n, int id, string team) : Defense(n, id, team) {}
    string getPlayerPosition() const override { return "Defensive Back"; }
    string play() const override { return "covers receivers and defends passes"; }
    string toString() const override {
        return name + " (#" + to_string(playerID) + ") - Defensive Back | Team: "
               + currentTeam + " | Plays: " + play();
    }
};

// =========================== SPECIAL TEAMS POSITIONS ===========================
class Kicker : public SpecialTeams {
public:
    Kicker(string n, int id, string team) : SpecialTeams(n, id, team) {}
    string getPlayerPosition() const override { return "Kicker"; }
    string play() const override { return "kicks field goals and extra points"; }
    string toString() const override {
        return name + " (#" + to_string(playerID) + ") - Kicker | Team: "
               + currentTeam + " | Plays: " + play();
    }
};

class Holder : public SpecialTeams {
public:
    Holder(string n, int id, string team) : SpecialTeams(n, id, team) {}
    string getPlayerPosition() const override { return "Holder"; }
    string play() const override { return "holds the ball for the kicker"; }
    string toString() const override {
        return name + " (#" + to_string(playerID) + ") - Holder | Team: "
               + currentTeam + " | Plays: " + play();
    }
};

class Punter : public SpecialTeams {
public:
    Punter(string n, int id, string team) : SpecialTeams(n, id, team) {}
    string getPlayerPosition() const override { return "Punter"; }
    string play() const override { return "punts the football on 4th down"; }
    string toString() const override {
        return name + " (#" + to_string(playerID) + ") - Punter | Team: "
               + currentTeam + " | Plays: " + play();
    }
};

class Returner : public SpecialTeams {
public:
    Returner(string n, int id, string team) : SpecialTeams(n, id, team) {}
    string getPlayerPosition() const override { return "Returner"; }
    string play() const override { return "returns kickoffs and punts"; }
    string toString() const override {
        return name + " (#" + to_string(playerID) + ") - Returner | Team: "
               + currentTeam + " | Plays: " + play();
    }
};

// ============================== MENU FUNCTIONS ===============================
void addPlayer(vector<shared_ptr<Player>>& team) {
    string name, nflTeam;
    int id, choice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter player's name: ";
    getline(cin, name);

    cout << "Enter player's number: ";
    cin >> id;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter player's Team: ";
    getline(cin, nflTeam);

    cout << "\nChoose Position:\n"
         << "1. Quarterback\n2. Wide Receiver\n3. Tight End\n4. Running Back\n5. Offensive Lineman\n"
         << "6. Defensive Lineman\n7. Linebacker\n8. Defensive Back\n"
         << "9. Kicker\n10. Holder\n11. Punter\n12. Returner\nChoice: ";
    cin >> choice;

    switch (choice) {
        case 1: team.push_back(make_shared<QuarterBack>(name, id, nflTeam)); break;
        case 2: team.push_back(make_shared<WideReceiver>(name, id, nflTeam)); break;
        case 3: team.push_back(make_shared<TightEnd>(name, id, nflTeam)); break;
        case 4: team.push_back(make_shared<RunningBack>(name, id, nflTeam)); break;
        case 5: team.push_back(make_shared<OffensiveLineman>(name, id, nflTeam)); break;
        case 6: team.push_back(make_shared<DefensiveLineman>(name, id, nflTeam)); break;
        case 7: team.push_back(make_shared<Linebacker>(name, id, nflTeam)); break;
        case 8: team.push_back(make_shared<DefensiveBack>(name, id, nflTeam)); break;
        case 9: team.push_back(make_shared<Kicker>(name, id, nflTeam)); break;
        case 10: team.push_back(make_shared<Holder>(name, id, nflTeam)); break;
        case 11: team.push_back(make_shared<Punter>(name, id, nflTeam)); break;
        case 12: team.push_back(make_shared<Returner>(name, id, nflTeam)); break;
        default:
            cout << "Invalid position.\n";
            return;
    }

    cout << "Player added!\n";
}

void displayTeam(const vector<shared_ptr<Player>>& team) {
    cout << "\n========== TEAM ROSTER ==========\n";

    // --- OFFENSE ---
    cout << "\n----- OFFENSE -----\n";
    for (auto& p : team) {
        if (p->getPlayerPosition() == "Quarterback" ||
            p->getPlayerPosition() == "Wide Receiver" ||
            p->getPlayerPosition() == "Tight End" ||
            p->getPlayerPosition() == "Running Back" ||
            p->getPlayerPosition() == "Offensive Lineman") 
        {
            cout << p->toString() << endl;
        }
    }

    // --- DEFENSE ---
    cout << "\n----- DEFENSE -----\n";
    for (auto& p : team) {
        if (p->getPlayerPosition() == "Defensive Lineman" ||
            p->getPlayerPosition() == "Linebacker" ||
            p->getPlayerPosition() == "Defensive Back") 
        {
            cout << p->toString() << endl;
        }
    }

    // --- SPECIAL TEAMS ---
    cout << "\n----- SPECIAL TEAMS -----\n";
    for (auto& p : team) {
        if (p->getPlayerPosition() == "Kicker" ||
            p->getPlayerPosition() == "Holder" ||
            p->getPlayerPosition() == "Punter" ||
            p->getPlayerPosition() == "Returner") 
        {
            cout << p->toString() << endl;
        }
    }

    cout << "\nTotal players: " << team.size() << "\n";
}

// ============================== MAIN MENU ==============================
int main() {
    vector<shared_ptr<Player>> team;
    int menu = 0;

    while (menu != 3) {
        cout << "\n===== NFL TEAM MENU =====\n";
        cout << "1. Add Player\n2. Display Team\n3. Exit\nChoice: ";
        cin >> menu;

        if (menu == 1)
            addPlayer(team);
        else if (menu == 2)
            displayTeam(team);
        else if (menu == 3)
            cout << "Exiting program...\n";
        else
            cout << "Invalid choice.\n";
    }

    return 0;
}