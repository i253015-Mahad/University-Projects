#pragma once
#include "main-menu.h";
#include "Levels.h";
#include "Player.h";
//#include "Level.h";
//#include "LevelManager.h";
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <SFML/Graphics.hpp>;
#include <SFML/Audio.hpp>;
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;

//database class which stores every user's info

class Database
{
private:
	struct UserInfo
	{
		int userID;
		string userName, password, email, timeStamp;
	};
	struct ProgressInfo
	{
		int progressID, userID, currentLevel, livesRemaining, gemCount, highScore;
		string lastUpdated;
	};
	struct LeaderBoard
	{
		int entryID, userID, score, levelReached;
		string recordedAt;
	};
	UserInfo* u;
	ProgressInfo* p;
	LeaderBoard* l;
	int total;

public:
	Database();
	~Database();
	friend ostream& operator<<(ostream& out, Database& y);
	Database operator=(const Database& other);
	Database(const Database& other);
	int getTotal() const;
	UserInfo getUserInfo(int i) const;
	LeaderBoard getLeaderBoard(int i) const;
};

//Login and registration system
void signUp(Database& x, string username, string password, string email);
bool Login(Database& x, string userName, string password);
string hashing(string p);

//gui function
void start();
void loginPage();
void registerPage();

//usman
void Usman(int type);