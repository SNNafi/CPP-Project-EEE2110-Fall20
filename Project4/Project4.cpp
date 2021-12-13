//
// Created by Shahriar Nasim Nafi on 29/9/21.
//
// NOT COMPLETED
//

#include <iostream> // input output
#include <vector> // vector
// file read write
#include <sstream> // string stream
#include <fstream> // file stream
#include<ctime> // random number genarate
#include<algorithm> // for sorting
using namespace std;


class Player {

    // class member
public:
    string name;
    int age;
    int battingInnings;
    int totalRuns;
    int highestScores;
    double average;
    double strikeRate;
    int bowlInnings;
    double averageRunOver;
    int wickets;

    int currentMatchFirstInningRun = 0;
    int currentMatchSecondInningRun = 0;

    int currentMatchFirstInningWickets = 0;
    int currentMatchSecondInningWickets = 0;

    int currentMatchFirstInningBowlingOver = 0;
    int currentMatchSecondInningBowlingOver = 0;

    int currentMatchFirstInningGivenRuns = 0;
    int currentMatchSecondInningGivenRuns = 0;

    bool isOutInCurrentMatchFirstInning = false;
    bool isOutInCurrentMatchSecondInning = false;

};


// sorting function
bool sortByFirstInningRun(Player const &a, Player const &b) {
    return a.currentMatchFirstInningRun > b.currentMatchFirstInningRun;
}

bool sortBySecondInningRun(Player const &a, Player const &b) {
    return a.currentMatchSecondInningRun > b.currentMatchSecondInningRun;
}

bool sortByFirstInningWicket(Player const &a, Player const &b) {
    return a.currentMatchFirstInningWickets > b.currentMatchFirstInningWickets;
}

bool sortBySecondInningWicket(Player const &a, Player const &b) {
    return a.currentMatchSecondInningWickets > b.currentMatchSecondInningWickets;
}




// class holds multiple type of data
class Cricket {
public:
    // for storing multiple player object
    vector<Player> players;


    // constructor special type of funtion
    Cricket() {
        loadPlayers();
    }

private:
    void loadPlayers() {
        string playerText;
        int count = 1;
        // object
        ifstream MyReadFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project4/players1.txt");
        while (getline(MyReadFile, playerText)) {
            if (count != 1) {
                Player player;
                stringstream ss(playerText);
                string info;
                int index = 1;
                while (ss >> info) {
                    if (index == 1) {
                        player.name = info;
                    } else if (index == 2) {
                        stringstream toInt(info);
                        toInt >> player.age;
                    } else if (index == 3) {
                        stringstream toInt(info);
                        toInt >> player.battingInnings;
                    } else if (index == 4) {
                        stringstream toInt(info);
                        toInt >> player.totalRuns;
                    } else if (index == 5) {
                        stringstream toInt(info);
                        toInt >> player.highestScores;
                    } else if (index == 6) {
                        stringstream toInt(info);
                        toInt >> player.average;
                    } else if (index == 7) {
                        stringstream toInt(info);
                        toInt >> player.strikeRate;
                    } else if (index == 8) {
                        stringstream toInt(info);
                        toInt >> player.bowlInnings;
                    } else if (index == 9) {
                        stringstream toInt(info);
                        toInt >> player.averageRunOver;
                    } else if (index == 10) {
                        stringstream toInt(info);
                        toInt >> player.wickets;
                    }
                    index++;


                }
                players.push_back(player);
            }
            count++;
        }
        MyReadFile.close();
    }
};


class Team {
public:
    string teamName;
    int score = 0;
    int highScorerOne = 0;
    int highScorerTwo = 0;
    int highScorerThree = 0;
    string bowlerOne;
    string bowlerTwo;
    int bowlerThree;

    // default constructor
    Team() {

    }

    Team(string name) {
        teamName = name;
    }

};



class Inning {
public:
    Team teamA = Team("A");
    Team teamB = Team("B");
    string aheadTeam;
    int aheadscore;
    int wicketGoneTeamA = 0;
    int wicketGoneTeamB = 0;

    Inning() {
//        aheadTeam = scoreA > scoreB ? "A" : "B";
//        aheadscore = scoreA > scoreB ? scoreA - scoreB : scoreB - scoreA;
    }

    void getAhead() {
        if (teamA.score > teamB.score) {
            cout << "Team A ahead by " << teamA.score - teamB.score << " runs" << endl;
        } else {
            cout << "Team B ahead by " << teamB.score - teamA.score << " runs" << endl;
        }
    }

};

class ScoreBpard {

public:
    Inning firstInning;
    Inning secondInning;
    int latestScore;
    vector<Player> teamA;
    vector<Player> teamB;
    int currentBattingPlayerNumber = 0;
    int firstBatting = rand() % 2;
    vector<int> bowlersIndex = {4, 5, 6, 7, 8, 9, 10, 11};
    int currentBowlerNumber = 0;
    int currentDeliveryNumber = 7;


    void startMatch(vector<Player> &players) {
        for (int i = 0; i < 11; i++) {
            teamA.push_back(players[i]);
        }
        for (int i = 11; i < players.size(); i++) {
            teamB.push_back(players[i]);
        }
    }

    void playFirstInning() {
        if (firstBatting == 0) {
            for (int i = 0; i < 10; i++) {
                currentBowler(teamA, 2);
                for (int j = 0; j < 6; j++) {
                    int outComes = outCome();
                    if (outComes == 7) {
                        teamB[currentBattingPlayerNumber].isOutInCurrentMatchFirstInning = true;
                        teamA[currentBowlerNumber].currentMatchFirstInningWickets += 1;
                        firstInning.wicketGoneTeamB += 1;
                        if (currentBattingPlayerNumber < 11) {
                            currentBattingPlayerNumber++;
                        } else {
                            break;
                        }
                    } else {
                        teamB[currentBattingPlayerNumber].currentMatchFirstInningRun += outComes;
                        teamA[currentBowlerNumber].currentMatchFirstInningGivenRuns += outComes;
                        firstInning.teamB.score += outComes;
                    }
                    currentDeliveryNumber++;
                }

            }
            currentBattingPlayerNumber = 0;
            for (int i = 0; i < 10; i++) {
                currentBowler(teamB, 2);
                for (int j = 0; j < 6; j++) {
                    int outComes = outCome();
                    if (outComes == 7) {
                        teamA[currentBattingPlayerNumber].isOutInCurrentMatchFirstInning = true;
                        teamB[currentBowlerNumber].currentMatchFirstInningWickets += 1;
                        firstInning.wicketGoneTeamA += 1;
                        if (currentBattingPlayerNumber < 11) {
                            currentBattingPlayerNumber++;
                        } else {
                            break;
                        }
                    } else {
                        teamA[currentBattingPlayerNumber].currentMatchFirstInningRun += outComes;
                        teamB[currentBowlerNumber].currentMatchFirstInningGivenRuns += outComes;
                        firstInning.teamA.score += outComes;
                    }
                    currentDeliveryNumber++;
                }

            }
        } else {
            for (int i = 0; i < 10; i++) {
                currentBowler(teamB, 2);
                for (int j = 0; j < 6; j++) {
                    int outComes = outCome();
                    if (outComes == 7) {
                        teamA[currentBattingPlayerNumber].isOutInCurrentMatchFirstInning = true;
                        teamB[currentBowlerNumber].currentMatchFirstInningWickets += 1;
                        firstInning.wicketGoneTeamA += 1;
                        if (currentBattingPlayerNumber < 11) {
                            currentBattingPlayerNumber++;
                        } else {
                            break;
                        }
                    } else {
                        teamA[currentBattingPlayerNumber].currentMatchFirstInningRun += outComes;
                        teamB[currentBowlerNumber].currentMatchFirstInningGivenRuns += outComes;
                        firstInning.teamA.score += outComes;
                    }
                    currentDeliveryNumber++;
                }

            }
            currentBattingPlayerNumber = 0;
            for (int i = 0; i < 10; i++) {
                currentBowler(teamA, 2);
                for (int j = 0; j < 6; j++) {
                    int outComes = outCome();
                    if (outComes == 7) {
                        teamB[currentBattingPlayerNumber].isOutInCurrentMatchFirstInning = true;
                        teamA[currentBowlerNumber].currentMatchFirstInningWickets += 1;
                        firstInning.wicketGoneTeamB += 1;
                        if (currentBattingPlayerNumber < 11) {
                            currentBattingPlayerNumber++;
                        } else {
                            break;
                        }
                    } else {
                        teamB[currentBattingPlayerNumber].currentMatchFirstInningRun += outComes;
                        teamA[currentBowlerNumber].currentMatchFirstInningGivenRuns += outComes;
                        firstInning.teamB.score += outComes;
                    }
                    currentDeliveryNumber++;
                }

            }
        }


    }

    void playSecondInning() {
        if (firstBatting == 1) {
            for (int i = 0; i < 10; i++) {
                currentBowler(teamA, 2);
                for (int j = 0; j < 6; j++) {
                    int outComes = outCome();
                    if (outComes == 7) {
                        teamB[currentBattingPlayerNumber].isOutInCurrentMatchSecondInning = true;
                        teamA[currentBowlerNumber].currentMatchSecondInningWickets += 1;
                        secondInning.wicketGoneTeamB += 1;
                        if (currentBattingPlayerNumber < 11) {
                            currentBattingPlayerNumber++;
                        } else {
                            break;
                        }
                    } else {
                        teamB[currentBattingPlayerNumber].currentMatchSecondInningRun += outComes;
                        teamA[currentBowlerNumber].currentMatchSecondInningGivenRuns += outComes;
                        secondInning.teamB.score += outComes;
                    }
                    currentDeliveryNumber++;
                }

            }
            currentBattingPlayerNumber = 0;
            for (int i = 0; i < 10; i++) {
                currentBowler(teamB, 2);
                for (int j = 0; j < 6; j++) {
                    int outComes = outCome();
                    if (outComes == 7) {
                        teamA[currentBattingPlayerNumber].isOutInCurrentMatchSecondInning = true;
                        teamB[currentBowlerNumber].currentMatchSecondInningWickets += 1;
                        secondInning.wicketGoneTeamA += 1;
                        if (currentBattingPlayerNumber < 11) {
                            currentBattingPlayerNumber++;
                        } else {
                            break;
                        }
                    } else {
                        teamA[currentBattingPlayerNumber].currentMatchSecondInningRun += outComes;
                        teamB[currentBowlerNumber].currentMatchSecondInningGivenRuns += outComes;
                        secondInning.teamA.score += outComes;
                    }
                    currentDeliveryNumber++;
                }

            }
        } else {
            for (int i = 0; i < 10; i++) {
                currentBowler(teamB, 2);
                for (int j = 0; j < 6; j++) {
                    int outComes = outCome();
                    if (outComes == 7) {
                        teamA[currentBattingPlayerNumber].isOutInCurrentMatchSecondInning = true;
                        teamB[currentBowlerNumber].currentMatchSecondInningWickets += 1;
                        secondInning.wicketGoneTeamA += 1;
                        if (currentBattingPlayerNumber < 11) {
                            currentBattingPlayerNumber++;
                        } else {
                            break;
                        }
                    } else {
                        teamA[currentBattingPlayerNumber].currentMatchSecondInningRun += outComes;
                        teamB[currentBowlerNumber].currentMatchSecondInningGivenRuns += outComes;
                        secondInning.teamA.score += outComes;
                    }
                    currentDeliveryNumber++;
                }

            }
            currentBattingPlayerNumber = 0;
            for (int i = 0; i < 10; i++) {
                currentBowler(teamA, 2);
                for (int j = 0; j < 6; j++) {
                    int outComes = outCome();
                    if (outComes == 7) {
                        teamB[currentBattingPlayerNumber].isOutInCurrentMatchSecondInning = true;
                        teamA[currentBowlerNumber].currentMatchSecondInningWickets += 1;
                        secondInning.wicketGoneTeamB += 1;
                        if (currentBattingPlayerNumber < 11) {
                            currentBattingPlayerNumber++;
                        } else {
                            break;
                        }
                    } else {
                        teamB[currentBattingPlayerNumber].currentMatchSecondInningRun += outComes;
                        teamA[currentBowlerNumber].currentMatchSecondInningGivenRuns += outComes;
                        secondInning.teamB.score += outComes;
                    }
                    currentDeliveryNumber++;
                }

            }
        }


    }

//not  for acceessing in outside
private:
    // if 7 , player out else run
    int outCome() {
        return rand() % 8;
    }


    // set current bowler after each over played
    void currentBowler(vector<Player> &team, int inning) {
        if (currentDeliveryNumber > 6) {
            currentDeliveryNumber = 1;
            int index = bowlersIndex[rand() % 6];
            Player bowler = team[index];
            if (inning == 1 ? bowler.currentMatchFirstInningBowlingOver :
                bowler.currentMatchSecondInningBowlingOver < 3) {
                currentBowlerNumber = index;
            } else {
                currentBowler(team, inning);
            }
        }
    }

    // search player name
    int lookPlayerIndex(vector<Player> &players, string name) {
        for (int i = 1; i < players.size(); i++) {
            if (players[i].name == name) {
                return i;
            }
        }
        return -1;
    }


};

class SummeryBoard {
public:

    // update player state after play ends
    void updateState(vector<Player> &players, vector<Player> &teamA, vector<Player> &teamB) {
        for (int i = 0; i < teamA.size(); i++) {
            Player player = teamA[i];
            int playerIndex = searchPlayerbyName(player.name, players);
            player.totalRuns =
                    player.totalRuns + player.currentMatchFirstInningRun + player.currentMatchSecondInningRun;
            player.battingInnings += 1;
            player.average = (double) player.totalRuns / player.battingInnings;
            player.highestScores = max(player.highestScores,
                                       max(player.currentMatchFirstInningRun, player.currentMatchSecondInningRun));

            // if player is bowler
            if (i == 4 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10, i == 11) {
                player.bowlInnings += 1;
                int givenRuns = player.currentMatchFirstInningGivenRuns + player.currentMatchSecondInningGivenRuns;
                int playerOver = player.currentMatchFirstInningBowlingOver + player.currentMatchSecondInningBowlingOver;
                player.averageRunOver = (double) givenRuns / playerOver;
                player.wickets =
                        player.wickets + player.currentMatchFirstInningWickets + player.currentMatchSecondInningWickets;
            }
            players[playerIndex] = player;
        }

        for (int i = 0; i < teamB.size(); i++) {
            Player player = teamB[i];
            int playerIndex = searchPlayerbyName(player.name, players);
            player.totalRuns =
                    player.totalRuns + player.currentMatchFirstInningRun + player.currentMatchSecondInningRun;
            player.battingInnings += 1;
            player.average = (double) player.totalRuns / player.battingInnings;
            player.highestScores = max(player.highestScores,
                                       max(player.currentMatchFirstInningRun, player.currentMatchSecondInningRun));

            // if player is bowler
            if (i == 4 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10, i == 11) {
                player.bowlInnings += 1;
                int givenRuns = player.currentMatchFirstInningGivenRuns + player.currentMatchSecondInningGivenRuns;
                int playerOver = player.currentMatchFirstInningBowlingOver + player.currentMatchSecondInningBowlingOver;
                player.averageRunOver = (double) givenRuns / playerOver;
                player.wickets =
                        player.wickets + player.currentMatchFirstInningWickets + player.currentMatchSecondInningWickets;
            }
            players[playerIndex] = player;
        }

        updateToTextFile(players);
    }


    // print mactch summery
    void matchSummery(ScoreBpard &scoreBpard) {
        vector<Player> teamA = scoreBpard.teamA;
        vector<Player> teamB = scoreBpard.teamB;


        cout << "First Innings: " << endl;
        cout << "Team A: " << scoreBpard.firstInning.teamA.score << "/" << scoreBpard.firstInning.wicketGoneTeamA
             << endl;

        // team a 1st ini
        sort(teamA.begin(), teamA.end(), sortByFirstInningRun);
        sort(teamB.begin(), teamB.end(), sortByFirstInningWicket);
        cout << teamA[0].name << ": " << teamA[0].currentMatchFirstInningRun << "   " << teamB[0].name << ": "
             << teamB[0].currentMatchFirstInningWickets << "-"
             << teamB[0].currentMatchFirstInningGivenRuns << endl;
        cout << teamA[1].name << ": " << teamA[1].currentMatchFirstInningRun << "   " << teamB[1].name << ": "
             << teamB[1].currentMatchFirstInningWickets << "-"
             << teamB[1].currentMatchFirstInningGivenRuns << endl;
        cout << teamA[2].name << ": " << teamA[2].currentMatchFirstInningRun << "   " << teamB[2].name << ": "
             << teamB[2].currentMatchFirstInningWickets << "-"
             << teamB[2].currentMatchFirstInningGivenRuns << endl;


        cout << endl;

        cout << "Team B: " << scoreBpard.firstInning.teamB.score << "/" << scoreBpard.firstInning.wicketGoneTeamB
             << endl;
        // team b 1st ini

        sort(teamB.begin(), teamB.end(), sortByFirstInningRun);
        sort(teamA.begin(), teamA.end(), sortByFirstInningWicket);
        cout << teamB[0].name << ": " << teamB[0].currentMatchFirstInningRun << "   " << teamA[0].name << ": "
             << teamA[0].currentMatchFirstInningWickets << "-"
             << teamA[0].currentMatchFirstInningGivenRuns << endl;
        cout << teamB[1].name << ": " << teamB[1].currentMatchFirstInningRun << "   " << teamA[1].name << ": "
             << teamA[1].currentMatchFirstInningWickets << "-"
             << teamA[1].currentMatchFirstInningGivenRuns << endl;
        cout << teamB[2].name << ": " << teamB[2].currentMatchFirstInningRun << "   " << teamA[2].name << ": "
             << teamA[2].currentMatchFirstInningWickets << "-"
             << teamA[2].currentMatchFirstInningGivenRuns << endl;


        cout << endl;
        scoreBpard.firstInning.getAhead();
        cout << endl;
        cout << endl;


        // 2nd innings


        cout << "Second Innings: " << endl;
        cout << "Team A: " << scoreBpard.secondInning.teamA.score << "/" << scoreBpard.secondInning.wicketGoneTeamA
             << endl;


        // team a 1st ini

        sort(teamA.begin(), teamA.end(), sortBySecondInningRun);
        sort(teamB.begin(), teamB.end(), sortBySecondInningWicket);
        cout << teamA[0].name << ": " << teamA[0].currentMatchSecondInningRun << "   " << teamB[0].name << ": "
             << teamB[0].currentMatchSecondInningWickets << "-"
             << teamB[0].currentMatchSecondInningGivenRuns << endl;
        cout << teamA[1].name << ": " << teamA[1].currentMatchSecondInningRun << "   " << teamB[1].name << ": "
             << teamB[1].currentMatchSecondInningWickets << "-"
             << teamB[1].currentMatchSecondInningGivenRuns << endl;
        cout << teamA[2].name << ": " << teamA[2].currentMatchSecondInningRun << "   " << teamB[2].name << ": "
             << teamB[2].currentMatchSecondInningWickets << "-"
             << teamB[2].currentMatchSecondInningGivenRuns << endl;


        cout << endl;

        cout << "Team B: " << scoreBpard.secondInning.teamB.score << "/" << scoreBpard.secondInning.wicketGoneTeamB
             << endl;
        // team b 1st ini


        sort(teamB.begin(), teamB.end(), sortBySecondInningRun);
        sort(teamA.begin(), teamA.end(), sortBySecondInningWicket);
        cout << teamB[0].name << ": " << teamB[0].currentMatchSecondInningRun << "   " << teamA[0].name << ": "
             << teamA[0].currentMatchSecondInningWickets << "-"
             << teamA[0].currentMatchSecondInningGivenRuns << endl;
        cout << teamB[1].name << ": " << teamB[1].currentMatchSecondInningRun << "   " << teamA[1].name << ": "
             << teamA[1].currentMatchSecondInningWickets << "-"
             << teamA[1].currentMatchSecondInningGivenRuns << endl;
        cout << teamB[2].name << ": " << teamB[2].currentMatchSecondInningRun << "   " << teamA[2].name << ": "
             << teamA[2].currentMatchSecondInningWickets << "-"
             << teamA[2].currentMatchSecondInningGivenRuns << endl;
        cout << endl;
        scoreBpard.secondInning.getAhead();
        cout << endl;
        cout << endl;
        int teamATotal = scoreBpard.firstInning.teamA.score + scoreBpard.secondInning.teamA.score;
        int teamBTotal = scoreBpard.firstInning.teamB.score + scoreBpard.secondInning.teamB.score;
        if (teamATotal > teamBTotal) {
            cout << "Team A Won by " << teamATotal - teamBTotal << " runs" << endl;
        } else {
            cout << "Team B Won by " << teamBTotal - teamATotal << " runs" << endl;
        }

    }

private:
    // update scores to text file
    void updateToTextFile(vector<Player> &players) {
        ofstream MyFile("/Users/snnafi/Desktop/CLionProjects/Projects_EEE2110_Fall20/Project4/players.txt");
        for (int i = 0; i < players.size(); i++) {
            Player player = players[i];
            MyFile << player.name << "\t\t" << player.age << "\t" << player.battingInnings << "\t"
                   << player.totalRuns
                   << "\t" << player.highestScores << "\t" << player.average << "\t" << player.strikeRate << "\t"
                   << player.bowlInnings << "\t"
                   << player.averageRunOver
                   << "\t" << player.wickets << endl;
        }

        MyFile.close();
    }


    int searchPlayerbyName(string name, vector<Player> &players) {
        for (int i = 0; i < players.size(); i++) {
            if (players[i].name == name) {
                return i;
            }
        }
        return 0;
    }

};


int main() {
    srand(time(NULL));
    // object of cricket class
    Cricket cricket = Cricket();
    // object of ScoreBpard class
    ScoreBpard scoreBpard;
    // object of SummeryBoard class
    SummeryBoard summeryBoard;

//    cout << cricket.players[1].name << endl;
//    cout << cricket.players[1].wickets << endl;
//    cout << cricket.players[1].averageRunOver << endl;
//    for (int i = 1; i < 10; i++) {
//        cout << rand() % 8 << endl;
//    }
    scoreBpard.startMatch(cricket.players);
    scoreBpard.playFirstInning();
    scoreBpard.playSecondInning();
    summeryBoard.updateState(cricket.players, scoreBpard.teamA, scoreBpard.teamA);
    summeryBoard.matchSummery(scoreBpard);

    cout << endl;
    cout << endl;
    cout << "First Innings: " << endl;
    cout << "Run for Team A players" << endl;
    for (int i = 0; i < scoreBpard.teamA.size(); i++) {
        cout << scoreBpard.teamA[i].name << " scores " << scoreBpard.teamA[i].currentMatchFirstInningRun << endl;
    }
    cout << endl;
    cout << "Run for Team B players" << endl;
    for (int i = 0; i < scoreBpard.teamB.size(); i++) {
        cout << scoreBpard.teamB[i].name << " scores " << scoreBpard.teamB[i].currentMatchFirstInningRun << endl;
    }
    cout << endl;
    cout << endl;
    cout << "Second Innings: " << endl;
    cout << "Run for Team A players" << endl;
    for (int i = 0; i < scoreBpard.teamA.size(); i++) {
        cout << scoreBpard.teamA[i].name << " scores " << scoreBpard.teamA[i].currentMatchSecondInningRun << endl;
    }
    cout << endl;
    cout << "Run for Team B players" << endl;
    for (int i = 0; i < scoreBpard.teamB.size(); i++) {
        cout << scoreBpard.teamB[i].name << " scores " << scoreBpard.teamB[i].currentMatchSecondInningRun << endl;
    }

}
