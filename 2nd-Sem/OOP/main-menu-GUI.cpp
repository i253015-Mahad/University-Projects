#include "main-menu.h";

void mainMenu()
{
	RenderWindow window(VideoMode(800, 600), "Main Menu");

	Texture m;
	if (!m.loadFromFile("images/Main_Menu.png"))
	{
		cout << "Error loading main menu\n";
		return;
	}
	Sprite pic(m);
	pic.setScale(0.6f, 0.535f);

	//arrow control
	float x = 315;
	int arrow = 0;
	RectangleShape b[5];
	for (int i = 0; i < 5; i++)
	{
		b[i].setSize(Vector2f(30.f, 30.f));
		b[i].setFillColor(Color::Black);
		if (i != 2)
		{
			x += 45;
			b[i].setPosition(250.f, x);
		}
		else
		{
			x += 50;
			b[i].setPosition(250.f, x);
		}
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Down)
				{
					if (arrow < 4)
						arrow++;
				}
				if (event.key.code == Keyboard::Up)
				{
					if (arrow > 0)
						arrow--;
				}

				//selection
				if (event.key.code == Keyboard::Enter)
				{
					switch (arrow)
					{
					case 0: 
						window.close(); newGame(); break;
					case 1:
						cout << "Continue\n"; break;
					case 2:
						window.close(); leaderBoard(); break;
					case 3:
						window.close(); settings(); break;
					case 4:
						window.close(); break;
					}
				}
			}
		}

		window.clear(Color::Blue);
		window.draw(pic);
		for (int i = 0; i < 5; i++)
		{
			if (arrow == i)
				continue;
			window.draw(b[i]);
		}
		window.display();
	}
}

void newGame()
{
	RenderWindow window(VideoMode(800, 600), "New Game");

	Texture n;
	if (!n.loadFromFile("images/New_Game.png"))
	{
		cout << "Error loading new game menu\n";
		return;
	}
	Sprite pic(n);
	pic.setScale(0.571f, 0.535f);

	Texture ex;
	if (!ex.loadFromFile("images/Exit_Button.png"))
	{
		cout << "Error loading exit button\n";
		return;
	}
	Sprite exitButton(ex);
	exitButton.setScale(1.f, 1.f);
	exitButton.setPosition(210.f, 540.f);

	//arrow logic
	int arrow = 0;
	RectangleShape b[3];
	for (int i = 0; i < 3; i++)
	{
		b[i].setSize(Vector2f(40.f, 40.f));
		b[i].setFillColor(Color::Black);
	}
	b[0].setPosition(220.f, 395.f);
	b[1].setPosition(220.f, 470.f);
	b[2].setPosition(220.f, 540.f);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Down)
					if (arrow < 2)
						arrow++;
				if (event.key.code == Keyboard::Up)
					if (arrow > 0)
						arrow--;

				if (event.key.code == Keyboard::Enter)
					if (arrow == 0)
					{
						window.close();
						Usman(1);
					}
					else if (arrow == 1)
					{
						window.close();
						Usman(2);
					}
					else
					{
						window.close();
						mainMenu();
					}
			}
		}

		window.clear(Color::Green);
		window.draw(pic);
		window.draw(exitButton);
		if (arrow == 0)
		{
			window.draw(b[1]);
			window.draw(b[2]);
		}
		else if (arrow == 1)
		{
			window.draw(b[0]);
			window.draw(b[2]);
		}
		else
		{
			window.draw(b[0]);
			window.draw(b[1]);
		}
		window.display();
	}
}

void levelSelection()
{
	RenderWindow window(VideoMode(800, 600), "Level selection");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color::Blue);

		window.display();
	}
}