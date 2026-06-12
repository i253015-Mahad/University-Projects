#include "Mahad.h";

void signUp(Database &x, string username, string password, string email)
{
	password = hashing(password);
	time_t now = time(nullptr);
	char buffer[30];
	ctime_s(buffer, sizeof(buffer), &now);


	//making the table columns in data base file
	if (!ifstream("Database.txt"))
	{
		ofstream file("Database.txt");
		file << "                                DATABASE\n\n";
		file << "                                USER TABLE\n";
		file << "user_id\t|\tusername\t|\tpassword_hash\t|\temail\t\t\t\t|\tcreated_at\n";
		file << "\n\n                            PLAYER_PROGRESS\n";
		file << "progress_id\t|\tuser_id\t|\tcurrent_level\t|\tlives_remaining\t|\tgem_count\t|\thigh_score\t|\tlast_updated\n";
		file << "\n\n                              LEADERBOARD\n";
		file << "entry_id\t|\tuser_id\t|\tscore\t|\tlevel_reached\t|\trecorded_at\n";
		file << endl << "-----------------------------------------------------------------------------------\n";
		file.close();
	}

	//registering user in the database file
	ifstream file("Database.txt");
	if (!file)
	{
		cout << "Error opening file for entry!\n";
		return;
	}

	string line;
	int num = 0;
	int userID;
	bool ready = false, ready1 = false, ready2 = false;
	ofstream temp("TempDatabase.txt");

	while (getline(file, line))
	{
		//only for first table
		if ((ready || ready1 || ready2) && line[0] >= '0' && line[0] <= '9')
		{
			num++;
		}

		if (line[0] == 'u')
		{
			ready = true;
			temp << line << endl;
		}
		else if (ready && line.empty())
		{
			
			ready = false;
			userID = num + 1;
			temp << num + 1 << "\t|\t" << username; 
			if (username.size() >= 8)
			{
				temp << "\t|\t";
			}
			else
			{
				temp << "\t\t|\t";
			}
			
			temp << password; 
			if (password.size() >= 10)
			{
				temp << "\t|\t";
			}
			else
			{
				temp << "\t\t|\t";
			}
			
			temp << email; 
			if (email.size() >= 24)
			{
				temp << "\t|\t";
			}
			else
			{
				temp << "\t\t|\t";
			}
			
			temp << buffer << endl;
			num = 0;
		}
		else if (line[0] == 'p')
		{
			ready1 = true;
			temp << line << endl;
		}
		else if (ready1 && line.empty())
		{
			ready1 = false;
			temp << num + 1 << "\t\t|\t" << userID << "\t|\t" << 1 << "\t\t|\t" << 2 << "\t\t|\t" << 0 << "\t\t|\t" << 0 << "\t\t|\t" << buffer << endl;
			num = 0;
		}
		else if (line[0] == 'e')
		{
			ready2 = true;
			temp << line << endl;
		}
		else if (ready2 && line.empty())
		{
			ready2 = false;
			temp << num + 1 << "\t\t|\t" << userID << "\t|\t" << 0 << "\t|\t" << 1 << "\t\t|\t" << buffer << endl;
			num = 0;
		}
		else
		{
			temp << line << endl;
		}
	}
	file.close();
	temp.close();
	remove("Database.txt");
	rename("TempDatabase.txt", "Database.txt");

	Database y;
	x = y;

	cout << "User " << username << " signed up successfully!" << endl;
}

bool Login(Database& x, string userName, string password)
{
	//checking if correct
	int total = x.getTotal();
	bool finish = false;
	do
	{
		finish = false;
		bool good = false, final = false;

		
		password = hashing(password);

		for (int i = 0; i < total; i++)
		{
			if (userName == x.getUserInfo(i).userName)
			{
				good = true;
			}
			if (good)
			{
				for (int j = 0; j < total; j++)
				{
					if (password == x.getUserInfo(j).password)
					{
						final = true;
						finish = true;
						break;
					}
				}
			}
		}

		//final checking
		if (final)
		{
			cout << "Logged in successfully as " << userName << ". Enjoy! :)\n";
			return true;
		}
		else
		{
			cout << "Either username or password is incorrect :(\nTry again\n\n";
			return false;
		}
	} while (!finish);
}

string hashing(string p)
{
	int k = 0, count = 0, prime = 1;
	bool good = false;
	while (p[count] != '\0')
	{
		do
		{
			prime++;
			good = true;
			for (int i = 2; i < prime; i++)
			{
				if (prime % i == 0)
					good = false;
			}
		} while (!good);
		k += p[count]*prime;
		count++;
	}
	//cout << k << endl;
	p = to_string(k);

	return p;
}


//database class implementation
Database::Database()
{
	ifstream file("Database.txt");
	if (!file)
	{
		u = new UserInfo[1];
		p = new ProgressInfo[1];
		l = new LeaderBoard[1];
		total = 0;
	}
	else
	{
		string line;
		int num = 0;
		bool ready = false;
		while (getline(file, line))
		{
			if (line[0] == 'u')
			{
				ready = true;
			}
			if (ready && line[0] >= '0' && line[0] <= '9')
			{
				num++;
			}
			if (line[0] == 'p')
			{
				ready = false;
			}
		}
		total = num;
		u = new UserInfo[total];
		p = new ProgressInfo[total];
		l = new LeaderBoard[total];
		file.close();

		ifstream file("Database.txt");
		num = 0;
		bool user = false, progress = false, leaderboard = false;
		string temp;
		while (getline(file, line))
		{
			if (line[0] == 'u')
			{
				user = true;
			}
			if (user && line[0] >= '0' && line[0] <= '9')
			{
				num++;
				u[num-1].userID = num;
				//cout << "User " << num << ":\n";
				//cout << "UserID = " << u[num - 1].userID << endl;
				int count = 0;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\t')
				{
					u[num-1].userName += line[count];
					count++;
				}
				//cout << "Useername = " << u[num - 1].userName << endl;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\t')
				{
					u[num - 1].password += line[count];
					count++;
				}
				//cout << "Password = " << u[num - 1].password << endl;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\t')
				{
					u[num - 1].email += line[count];
					count++;
				}
				//cout << "Email = " << u[num - 1].email << endl;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\0')
				{
					u[num - 1].timeStamp += line[count];
					count++;
				}
				//cout << "Time Stamp = " << u[num - 1].timeStamp << endl << endl;
			}
			if (line[0] == 'p')
			{
				user = false;
				progress = true;
				num = 0;
			}
			if (progress && line[0] >= '0' && line[0] <= '9')
			{
				num++;
				p[num - 1].progressID = num;
				//cout << "User " << num << ":\n";
				//cout << "ProgressID = " << p[num - 1].progressID << endl;
				int count = 0;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\t')
				{
					temp += line[count];
					count++;
				}
				p[num - 1].userID = stoi(temp);
				//cout << "UserID = " << p[num - 1].userID << endl;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\t')
				{
					if (line[count-1] == '\t')
						temp = "";

					temp += line[count];
					count++;
				}
				p[num - 1].currentLevel = stoi(temp);
				//cout << "CurrentLevel = " << p[num - 1].currentLevel << endl;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\t')
				{
					if (line[count - 1] == '\t')
					temp = "";

					temp += line[count];
					count++;
				}
				p[num - 1].livesRemaining = stoi(temp);
				//cout << "LivesRemaining = " << p[num - 1].livesRemaining << endl;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\t')
				{
					if (line[count - 1] == '\t')
					temp = "";

					temp += line[count];
					count++;
				}
				p[num - 1].gemCount = stoi(temp);
				//cout << "GemCount = " << p[num - 1].gemCount << endl;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\t')
				{
					if (line[count - 1] == '\t')
					temp = "";

					temp += line[count];
					count++;
				}
				p[num - 1].highScore = stoi(temp);
				//cout << "HighScore = " << p[num - 1].highScore << endl;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\0')
				{
					p[num - 1].lastUpdated += line[count];
					count++;
				}
				//cout << "LastUpdated = " << p[num - 1].lastUpdated << endl << endl;
			}
			if (line[0] == 'e')
			{
				progress = false;
				leaderboard = true;
				num = 0;
			}
			if (leaderboard && line[0] >= '0' && line[0] <= '9')
			{
				num++;
				l[num - 1].entryID = num;
				//cout << "User " << num << ":\n";
				//cout << "EntryID = " << l[num - 1].entryID << endl;
				int count = 0;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\t')
				{
					if (line[count - 1] == '\t')
					temp = "";

					temp += line[count];
					count++;
				}
				l[num - 1].userID = stoi(temp);
				//cout << "UserID = " << l[num - 1].userID << endl;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\t')
				{
					if (line[count - 1] == '\t')
					temp = "";

					temp += line[count];
					count++;
				}
				l[num - 1].score = stoi(temp);
				//cout << "Score = " << l[num - 1].score << endl;
				while (line[count] != '|')
				{
					count++;
				}
				count += 2;
				while (line[count] != '\t')
				{
					if (line[count - 1] == '\t')
					temp = "";

					temp += line[count];
					count++;
				}
				l[num - 1].levelReached = stoi(temp);
				//cout << "LevelReached = " << l[num - 1].levelReached << endl;
				while (line[count] != '|')
				{
					count++;
				}
				count += 1;

				while (line[count] != '\0')
				{
					l[num - 1].recordedAt += line[count];
					count++;
				}
				//cout << "RecordedAt = " << l[num - 1].recordedAt << endl << endl;
			}
		}
		file.close();
	}
	//cout << "Total: " << total << endl;
}

Database::~Database()
{
	delete[] u;
	u = nullptr;
	delete[] p;
	p = nullptr;
	delete[] l;
	l = nullptr;
	cout << "Deleted\n";
}

ostream& operator<<(ostream& out, Database& y)
{
	bool back = false;
	for (int i = 0; i < y.total; i++)
	{
		out << "User " << i + 1 << ":\n";
		out << "UserID = " << y.u[i].userID << "\nUserName = " << y.u[i].userName << "\nPassword: " << y.u[i].password;
		out << "\nEmail = " << y.u[i].email << "\nTime Stamp = " << y.u[i].timeStamp << endl;
		int count = 0;
		while (y.u[i].userID != y.p[count].userID && count < y.total)
		{
			if (i == 0 || count + 1 != y.total)
				count++;
			else if (count + 1 == y.total)
				back = true;
			else if (i != 0 && back && count != 0)
				count--;
			else if (count == 0 && back)
				count = y.total;
		}
		if (count == y.total)
		{
			cout << "Error 1";
			return out;
		}

		out << "\nProgress Info: \nProgressID = " << y.p[count].progressID << "\nCurrent Level: " << y.p[count].currentLevel;
		out << "\nLives Remaining: " << y.p[count].livesRemaining << "\nGem Count = " << y.p[count].gemCount;
		out << "\nHigh Score = " << y.p[count].highScore << "\nLast Updated = " << y.p[count].lastUpdated << endl;
		count = 0;
		back = false;
		while (y.u[i].userID != y.l[count].userID && count < y.total)
		{
			if (i == 0 || count + 1 != y.total)
				count++;
			else if (count + 1 == y.total)
				back = true;
			else if (i != 0 && back && count != 0)
				count--;
			else if (count == 0 && back)
				count = y.total;
		}
		if (count == y.total)
		{
			cout << "Error 2";
			return out;
		}
		out << "Rank in leaderBoard = " << y.l[count].entryID << endl << endl << endl;
	}
	return out;
}

Database Database::operator=(const Database& other)
{
	if (this == &other)
		return *this;

	total = other.total;
	//deleting previous data
	delete[] u;
	u = nullptr;
	delete[] p;
	p = nullptr;
	delete[] l;
	l = nullptr;

	//allocating new space
	u = new UserInfo[total];
	p = new ProgressInfo[total];
	l = new LeaderBoard[total];

	for (int i = 0; i < total; i++)
	{
		//setting user info
		u[i].userID = other.u[i].userID;
		u[i].email = other.u[i].email;
		u[i].password = other.u[i].password;
		u[i].timeStamp = other.u[i].timeStamp;
		u[i].userName = other.u[i].userName;

		//setting progress info
		p[i].currentLevel = other.p[i].currentLevel;
		p[i].gemCount = other.p[i].gemCount;
		p[i].highScore = other.p[i].highScore;
		p[i].lastUpdated = other.p[i].lastUpdated;
		p[i].livesRemaining = other.p[i].livesRemaining;
		p[i].progressID = other.p[i].progressID;
		p[i].userID = other.p[i].userID;

		//setting leaderboard info
		l[i].entryID = other.l[i].entryID;
		l[i].levelReached = other.l[i].levelReached;
		l[i].recordedAt = other.l[i].recordedAt;
		l[i].score = other.l[i].score;
		l[i].userID = other.l[i].userID;
	}
	return *this;
}

Database::Database(const Database& other)
{
	total = other.total;

	if (total == 0)
	{
		u = nullptr;
		p = nullptr;
		l = nullptr;
	}
	else
	{
		u = new UserInfo[total];
		p = new ProgressInfo[total];
		l = new LeaderBoard[total];

		for (int i = 0; i < total; i++)
		{
			//setting user info
			u[i].userID = other.u[i].userID;
			u[i].email = other.u[i].email;
			u[i].password = other.u[i].password;
			u[i].timeStamp = other.u[i].timeStamp;
			u[i].userName = other.u[i].userName;

			//setting progress info
			p[i].currentLevel = other.p[i].currentLevel;
			p[i].gemCount = other.p[i].gemCount;
			p[i].highScore = other.p[i].highScore;
			p[i].lastUpdated = other.p[i].lastUpdated;
			p[i].livesRemaining = other.p[i].livesRemaining;
			p[i].progressID = other.p[i].progressID;
			p[i].userID = other.p[i].userID;

			//setting leaderboard info
			l[i].entryID = other.l[i].entryID;
			l[i].levelReached = other.l[i].levelReached;
			l[i].recordedAt = other.l[i].recordedAt;
			l[i].score = other.l[i].score;
			l[i].userID = other.l[i].userID;
		}
	}
}

int Database::getTotal() const
{
	return total;
}

Database::UserInfo Database::getUserInfo(int i) const
{
	return u[i];
}

Database::LeaderBoard Database::getLeaderBoard(int i) const
{
	return l[i];
}