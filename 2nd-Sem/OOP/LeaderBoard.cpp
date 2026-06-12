#include "main-menu.h";

void leaderBoard()
{
	RenderWindow window(VideoMode(800, 600), "LeaderBoard");

	Database x;
	updateLeaderBoard(x);
	Font font;
	if (!font.loadFromFile("PixelPurl.ttf"))
	{
		cout << "Error loading font\n";
		return;
	}
	Text r[10];
	float y = 220.f;
	for (int i = 0; i < 10; i++)
	{
		y += 30;
		r[i].setFont(font);
		r[i].setFillColor(Color::Yellow);
		r[i].setCharacterSize(32);
		r[i].setPosition(230.f, y);
	}
	
	ifstream file("Database.txt");
	if (!file)
	{
		cout << "Error opening database file in leaderboard\n";
		return;
	}
	string* temp = new string[x.getTotal()];
	string line;
	bool good = false;
	int count = 0;
	while (getline(file, line))
	{
		if (line[0] == 'e')
			good = true;
		if (good && line[0] >= '0' && line[0] <= '9')
		{
			temp[count] = line;
			count++;
		}
	}
	file.close();
	string set[10];

	for (int i = 0; i < 10; i++)
	{
		if (i < x.getTotal())
		{
			int count = 0;
			set[i] = "";
			while (temp[i][count] != '|')
			{
				count++;
			}
			count++;
			while (temp[i][count] != '|')
			{
				if (temp[i][count] >= '0' || temp[i][count] <= '9')
					set[i] += temp[i][count];
				count++;
			}
			set[i] += "\t\t";
			int check = 0;
			count++;
			while (temp[i][count] != '|')
			{
				if (temp[i][count] >= '0' || temp[i][count] <= '9')
				{
					set[i] += temp[i][count]; check++;
				}
				count++;
			}

			set[i] += "\t\t\t";
			count++;
			while (temp[i][count] != '|')
			{
				if (temp[i][count] >= '0' || temp[i][count] <= '9')
					set[i] += temp[i][count];
				count++;
			}
			r[i].setString(set[i]);
		}
	}

	Texture lead;
	if (!lead.loadFromFile("images/LeaderBoard.png"))
	{
		cout << "Error loading leaderBoard\n";
		return;
	}
	Sprite l(lead);
	l.setScale(0.58, 0.535);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Enter)
				{
					window.close();
					mainMenu();
				}
			}
		}

		window.clear(Color::Blue);
		window.draw(l);
		for (int i = 0; i < x.getTotal(); i++)
			window.draw(r[i]);
		window.display();
	}
}

void updateLeaderBoard(Database& x)
{
	int t = x.getTotal();
	int* sort = new int[t];
	int* score = new int[t];
	for (int i = 0; i < t; i++)
	{
		sort[i] = x.getLeaderBoard(i).userID;
		score[i] = x.getLeaderBoard(i).score;
	}

	for (int i = 0; i < t; i++)
	{
		for (int j = i; j < t; j++)
		{
			if (score[i] < score[j])
			{
				int temp = score[i];
				score[i] = score[j];
				score[j] = temp;
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
			}
		}
	}
	delete[] score;
	score = nullptr;

	ofstream file("temp.txt");
	if (!file)
	{
		cout << "Error opening file\n";
		return;
	}

	ifstream old("Database.txt");
	if (!old)
	{
		cout << "Error opening database file\n";
		return;
	}
	string l, end;
	bool go = false;
	string* store = new string[t];
	int count = 0;
	while (getline(old, l))
	{
		if (l[0] == 'e')
		{
			go = true;
		}
		if (go && l[0] >= '0' && l[0] <= '9')
		{
			store[count] = l;
			count++;
		}
		else if (l[0] == '-')
		{
			end = l;
		}
		else
		{
			file << l << endl;
		}
	}
	old.close();
	cout << "\n\n";
	for (int i = 0; i < t; i++)
	{
		for (int j = 0; j < t; j++)
		{
			if (store[j][0] == to_string(sort[i]))
				file << store[j] << endl;
		}
	}
	file << end << endl;
	file.close();
	remove("Database.txt");
	rename("temp.txt", "Database.txt");

	delete[] store;
	store = nullptr;
	delete[] sort;
	sort = nullptr;
}