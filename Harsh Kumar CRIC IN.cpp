#include<vector>
#include <iostream>
#include <cstdlib>
#include<ctime>
#include <limits>
#include <unistd.h>
using namespace std;
class Player
{
public:
    Player();
    string name;
    int index;
    int runsScored;
    int ballsPlayed;
    int ballsBowled;
    int runsGiven;
    int wicketsTaken;
};
class Team{
public:
    Team();
    string name;
    int totalRunsScored;
    int wicketsLost;
    int totalBallsBowled;
    vector<Player> players;
};
class Game{
public:
    Game();
    int playersPerTeam;
    int maxballs;
    int totalPlayers;
    string players[11];
    bool isFirstInnings;
    Team teamA, teamB;
    Team *battingTeam, *bowlingTeam;
    Player *batsman, *bowler;

    void welcome();
    void enter();
    void pool();
    int takeIntegerInput();
    void selectPlayers();
    void showSelectedPlayers();
    void toss();
    void startFirstInnings();
    void initializePlayers();
    void playInnings();
    void bat();
    bool validateInningsScore();
    void scoreCard();
    void startSecondInnings();
    void bat2();
    void scoreCard2();
    void winner();
    void summary();
};

Player::Player()
{
    runsScored=0;
    ballsPlayed=0;
    ballsBowled=0;
    runsGiven=0;
    wicketsTaken=0;
};
Team::Team(){
    totalRunsScored=0;
    wicketsLost=0;
    totalBallsBowled=0;
}

Game::Game()
{
    playersPerTeam=5;
    maxballs=6;
    totalPlayers=11;

    players[0]="Virat";
    players[1]="Dhoni";
    players[2]="Rohit";
    players[3]="Dhawan";
    players[4]="Pant";
    players[5]="Karthik";
    players[6]="KLRahul";
    players[7]="Jadeja";
    players[8]="Hardik";
    players[9]="Bumrah";
    players[10]="BKumar";

    isFirstInnings=false;
    teamA.name="Team-A";
    teamB.name="Team-B";
}

void Game::welcome()
{
    cout<<"-----------------------------------------------"<<endl;
    cout<<"|===================CRIC-IN===================|"<<endl;
    cout<<"|                                             |"<<endl;
    cout<<"|        Welcome to Visual Cricket Game       |"<<endl;;
    cout<<"-----------------------------------------------"<<endl<<endl<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"|===================== Instructions =====================|"<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"|                                                        |"<<endl;
    cout<<"| 1. Create 2 teams ( Team-A and Team-B ) with 4 players |"<<endl;
    cout<<"|    each ) from a given pool of 11 players.             |"<<endl;
    cout<<"| 2. Lead the toss and decide the choice of play.        |"<<endl;
    cout<<"| 3. Each innings will be of 6 balls.                    |"<<endl;
    cout<<"----------------------------------------------------------"<<endl<<endl<<endl;
}

void Game::enter()
{
    char temp;
    cout<<"Press Enter key to continue:"<<endl;
    cin.get(temp);
}

void Game::pool()
{
    cout<<"----------------------------------------------"<<endl;
    cout<<"|=================== Pool ===================|"<<endl;
    cout<<"----------------------------------------------"<<endl;
    for(int i=0;i<totalPlayers;i++)
    {
        cout<<"\t\t  "<<"["<<i<<"]"<<" "<<players[i]<<endl;
    }
    cout<<endl<<endl;
}

int Game::takeIntegerInput()
{
    int n;
    cin>>n;
    return n;
}

void Game::selectPlayers()
{
    cout<<endl;
    cout<<"----------------------------------------------"<<endl;
    cout<<"|========= Create Team-A and Team-B =========|"<<endl;
    cout<<"----------------------------------------------"<<endl;
    int a[11]={0};
    for(int i=0;i<playersPerTeam;i++)
    {
        teamASelection:
            cout<<endl<<"Select player "<<i+1<<" for Team A - ";

            int playerIndexTeamA = takeIntegerInput();

            if(playerIndexTeamA<0 || playerIndexTeamA>10){
                cout<<endl<<"Please select from the above given players only."<<endl;
                goto teamASelection;
            }
            else if(a[playerIndexTeamA]!=0)
            {
                cout<<endl<<"The player's already been selected!! Select another."<<endl;
                goto teamASelection;
            }
            else{
            a[playerIndexTeamA]++;
            Player teamAPlayer;
            teamAPlayer.index=playerIndexTeamA;
            teamAPlayer.name=players[playerIndexTeamA];
            teamA.players.push_back(teamAPlayer);
            }

        teamBSelection:
            cout<<endl<<"Select player "<<i+1<<" for Team B - ";

            int playerIndexTeamB = takeIntegerInput();

            if(playerIndexTeamB<0 || playerIndexTeamB>10){
                cout<<endl<<"Please select from the above given players only."<<endl;
                goto teamBSelection;
            }
            else if(a[playerIndexTeamB]!=0)
            {
                cout<<endl<<"The player's already been selected!! Select another."<<endl;
                goto teamBSelection;
            }
            else{
            a[playerIndexTeamB]++;
            Player teamBPlayer;
            teamBPlayer.index=playerIndexTeamB;
            teamBPlayer.name=players[playerIndexTeamB];
            teamB.players.push_back(teamBPlayer);
            }
    }
    cout<<endl<<endl;
}

void Game::showSelectedPlayers()
{
    vector<Player> teamAPlayers = teamA.players;
    vector<Player> teamBPlayers = teamB.players;

    cout << "--------------------------\t\t--------------------------" << endl;
    cout << "|=======  Team-A  =======|\t\t|=======  Team-B  =======|" << endl;
    cout << "--------------------------\t\t--------------------------" << endl;

    for (int i = 0; i < playersPerTeam; i++) {
        cout << "|\t" << "[" << i << "] " << teamAPlayers[i].name << "\t |"
        	<< "\t\t"
			<< "|\t" << "[" << i << "] " << teamBPlayers[i].name << "\t |" << endl;
    }
    cout << "--------------------------\t\t--------------------------" << endl << endl;
}

void Game::toss()
{
    string s;
    cout<<endl<<endl;
    cout << "----------------------------"<< endl;
    cout << "|======= Let's Toss =======|"<< endl;
    cout << "----------------------------"<<endl<<endl;
    cout<<"Press enter to flip the coin...."<<endl<<endl;
    char temp;
    cin.get(temp);
    srand(time(NULL));
    int i;
    i=(rand()%2);
    usleep(2000000);
    if(i==0)
        s="Team-A ";
    else s="Team-B ";
    cout<<s<<"won the toss.."<<endl<<endl<<endl;
    TossSelection:
        cout<<"Press 1 to bat first."<<endl;
        cout<<"Or 2 to bowl first."<<endl;
        int k;
        cin>>k;
        if(k==1)
            cout<<endl<<s<<"won the toss and elected to bat first!!"<<endl;
        else if(k==2)
            cout<<endl<<s<<"won the toss and elected to bowl first!!"<<endl;
        else{
            cout<<endl<<"Invalid output! Try again!"<<endl<<endl;
            goto TossSelection;
        }
    if((s.compare("Team-A ")==0 && k==1) || (s.compare("Team-B ")==0 && k==2))
    {
        battingTeam=&teamA;
        bowlingTeam=&teamB;
    }
    else{
        battingTeam=&teamB;
        bowlingTeam=&teamA;
    }
    cout<<endl<<endl;
}

void Game::startFirstInnings()
{
    cout<<"\t\t\t|| FIRST INNINGS STARTS ||"<<endl<<endl<<endl;
    isFirstInnings=true;
    initializePlayers();
    playInnings();
}

void Game::initializePlayers()
{
    batsman = &battingTeam->players[0];
    bowler=&bowlingTeam->players[0];
    cout<<battingTeam->name<<" - "<<batsman->name<<" is batting. "<<endl;
    cout<<bowlingTeam->name<<" - "<<bowler->name<<" is bowling. "<<endl<<endl<<endl;
}

void Game::playInnings()
{
    for(int i=0;i<maxballs;i++)
    {
        char temp;
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Press Enter to bowl..";
        if(i==0)
            if(isFirstInnings)
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(temp);
        cout<<"Bowling..."<<endl<<endl<<endl;
        if(isFirstInnings)
            bat();
        else bat2();
        cout<<endl;
        if(isFirstInnings)
            scoreCard();
        else scoreCard2();
        if(!validateInningsScore())
        {
            break;
        }
    }
}

void Game::bat()
{
    srand(time(NULL));
    int runsScored=rand()%7;

    batsman->runsScored+=runsScored;
    battingTeam->totalRunsScored+=runsScored;
    batsman->ballsPlayed++;

    bowler->ballsBowled++;
    bowlingTeam->totalBallsBowled++;
    bowler->runsGiven+=runsScored;

    if(runsScored==0)
    {
        cout<<bowler->name<<" to "<<batsman->name<<" OUT!"<<endl;
        battingTeam->wicketsLost++;
        bowler->wicketsTaken++;

        int index=battingTeam->wicketsLost;
        batsman=&battingTeam->players[index];
    }
    else
        cout<<bowler->name<<" to "<<batsman->name<<" "<<runsScored<<" runs!"<<endl;
}

bool Game::validateInningsScore()
{
    if(isFirstInnings)
    {
        if(battingTeam->wicketsLost == playersPerTeam || bowlingTeam->totalBallsBowled == maxballs)
        {
            cout<<"\t\t\t|| FIRST INNINGS ENDS ||"<<endl<<endl;
            cout<<battingTeam->name<<"  "<<battingTeam->totalRunsScored<<" - "<<battingTeam->wicketsLost<< " ("<<bowlingTeam->totalBallsBowled<<")"<<endl;
            cout<<bowlingTeam->name<<" needs "<<battingTeam->totalRunsScored+1<<" runs to win the match. "<<endl<<endl<<endl;
            return false;
        }
    }
    else
    {
        if(bowlingTeam->wicketsLost == playersPerTeam || battingTeam->totalBallsBowled == maxballs || bowlingTeam->totalRunsScored>battingTeam->totalRunsScored)
        {
            cout<<"\t\t\t|| SECOND INNINGS ENDS ||"<<endl<<endl;
            return false;
        }
    }
    return true;
}

void Game::scoreCard()
{
    cout<<"--------------------------------------------------------------------------"<<endl;
    cout<<"\t "<<battingTeam->name<<"  "<<battingTeam->totalRunsScored<<" - "<<battingTeam->wicketsLost<<" ("<<bowlingTeam->totalBallsBowled<<") | "<<batsman->name<<" "<<batsman->runsScored<<" ("<<batsman->ballsPlayed<<") \t"<<bowler->name<<" "<<bowler->ballsBowled<<" - "<<bowler->runsGiven<<" - "<<bowler->wicketsTaken<<endl;
    cout<<"--------------------------------------------------------------------------"<<endl<<endl;
}

void Game::startSecondInnings()
{
    cout<<"\t\t\t|| SECOND INNINGS STARTS ||"<<endl<<endl<<endl;
    isFirstInnings=false;
    batsman = &bowlingTeam->players[0];
    bowler = &battingTeam->players[0];
    cout<<bowlingTeam->name<<" - "<<batsman->name<<" is batting. "<<endl;
    cout<<battingTeam->name<<" - "<<bowler->name<<" is bowling. "<<endl<<endl<<endl;
    playInnings();
}

void Game::bat2()
{
    srand(time(NULL));
    int runsScored=rand()%7;

    batsman->runsScored+=runsScored;
    bowlingTeam->totalRunsScored+=runsScored;
    batsman->ballsPlayed++;

    bowler->ballsBowled++;
    battingTeam->totalBallsBowled++;
    bowler->runsGiven+=runsScored;

    if(runsScored==0)
    {
        cout<<bowler->name<<" to "<<batsman->name<<" OUT!"<<endl;
        bowlingTeam->wicketsLost++;
        bowler->wicketsTaken++;

        int index=bowlingTeam->wicketsLost;
        batsman=&bowlingTeam->players[index];
    }
    else
        cout<<bowler->name<<" to "<<batsman->name<<" "<<runsScored<<" runs!"<<endl;
}

void Game::scoreCard2()
{
    cout<<"--------------------------------------------------------------------------"<<endl;
    cout<<"\t "<<bowlingTeam->name<<"  "<<bowlingTeam->totalRunsScored<<" - "<<bowlingTeam->wicketsLost<<" ("<<battingTeam->totalBallsBowled<<") | "<<batsman->name<<" "<<batsman->runsScored<<" ("<<batsman->ballsPlayed<<") \t"<<bowler->name<<" "<<bowler->ballsBowled<<" - "<<bowler->runsGiven<<" - "<<bowler->wicketsTaken<<endl;
    cout<<"--------------------------------------------------------------------------"<<endl<<endl;
}

void Game::winner()
{
    if(bowlingTeam->totalRunsScored>battingTeam->totalRunsScored)
        cout<<endl<<bowlingTeam->name<<" won the match by "<<playersPerTeam-bowlingTeam->wicketsLost<<" wickets!!"<<endl;
    else if(bowlingTeam->totalRunsScored<battingTeam->totalRunsScored)
        cout<<endl<<battingTeam->name<<" won the match by "<<battingTeam->totalRunsScored-bowlingTeam->totalRunsScored<<" runs!!"<<endl;
}

void Game::summary()
{
    cout<<endl<<endl<<"\t\t\t\     || MATCH ENDS ||"<<endl<<endl;
    cout<<battingTeam->name<<" "<<battingTeam->totalRunsScored<<"-"<<battingTeam->wicketsLost<<" ("<<bowlingTeam->totalBallsBowled<<")"<<endl;
    cout<<"================================================="<<endl;
    cout<<"| PLAYER\t\tBATTING\t\tBOWLING\t|"<<endl;
    for(int i=0;i<playersPerTeam;i++)
    {
    cout<<"|-----------------------------------------------|"<<endl;
    cout<<"| ["<<i<<"] "<<battingTeam->players[i].name<<"\t\t"<<battingTeam->players[i].runsScored<<"("<<battingTeam->players[i].ballsPlayed<<")\t\t"<<battingTeam->players[i].ballsBowled<<"-"<<battingTeam->players[i].runsGiven<<"-"<<battingTeam->players[i].wicketsTaken<<"\t|"<<endl;
    }
    cout<<"================================================="<<endl<<endl;
    cout<<bowlingTeam->name<<" "<<bowlingTeam->totalRunsScored<<"-"<<bowlingTeam->wicketsLost<<" ("<<battingTeam->totalBallsBowled<<")"<<endl;
    cout<<"================================================="<<endl;
    cout<<"| PLAYER\t\tBATTING\t\tBOWLING\t|"<<endl;
    for(int i=0;i<playersPerTeam;i++)
    {
    cout<<"|-----------------------------------------------|"<<endl;
    cout<<"| ["<<i<<"] "<<bowlingTeam->players[i].name<<"\t\t"<<bowlingTeam->players[i].runsScored<<"("<<bowlingTeam->players[i].ballsPlayed<<")\t\t"<<bowlingTeam->players[i].ballsBowled<<"-"<<bowlingTeam->players[i].runsGiven<<"-"<<bowlingTeam->players[i].wicketsTaken<<"\t|"<<endl;
    }
    cout<<"================================================="<<endl;
}

int main()
{
    Game game;
    game.welcome();
    game.enter();
    game.pool();
    game.enter();
    game.selectPlayers();
    game.showSelectedPlayers();

    char temp;
    cout<<"Starting the toss..."<<endl;
    cin.get(temp);
    usleep(2000000);

    game.toss();
    game.startFirstInnings();
    game.startSecondInnings();
    game.winner();
    game.summary();
    return 0;
}
