#include "Levels.h";


int pauseMenu()
{
	RenderWindow window(VideoMode(800, 600), "Pause Menu");

	Texture pause;
	if (!pause.loadFromFile("images/Pause_Menu.png"))
	{
		cout << "Error loading pause menu\n";
		return -1;
	}
	Sprite p(pause);
    p.setScale(0.6f, 0.5f);
	p.setPosition(20.f, -10.f);

	//arrow control
	RectangleShape cover[5];
	int space = 305;
	for (int i = 0; i < 5; i++)
	{
		cover[i].setSize(Vector2f(30, 30));
		cover[i].setFillColor(Color::Black);
		space += 46;
		cover[i].setPosition(185.f, space);
	}
	int arrow = 0;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Backspace)
					window.close();

				if (event.key.code == Keyboard::Down)
					if (arrow < 4)
						arrow++;

				if (event.key.code == Keyboard::Up)
					if (arrow > 0)
						arrow--;

				if (event.key.code == Keyboard::Enter)
					switch (arrow)
					{
					case 0: window.close(); break;
					case 1: window.close(); shop(); break;
					case 2: cout << "Saved\n"; break;
					case 3: return 2; break;
					case 4: return 1; break;
					}
			}
		}

		window.clear(Color::Black);
		window.draw(p);
		for (int i = 0; i < 5; i++)
			if (i == arrow)
				continue;
			else
				window.draw(cover[i]);
		window.display();
	}
	return 0;
}


void shop()
{
	RenderWindow window(VideoMode(800, 600), "Shop");

	Texture shop;
	if (!shop.loadFromFile("images/Shop.png"))
	{
		cout << "Error loading shop\n";
		return;
	}
	Sprite s(shop);
	s.setScale(0.6f, 0.5f);
	s.setPosition(20.f, 0.f);

	//button logic
	RectangleShape button[6];
	for (int i = 0; i < 6; i++)
	{
		button[i].setSize(Vector2f(105.f, 30.f));
		button[i].setFillColor(Color::Transparent);
	}
	button[0].setPosition(510.f, 158.f);
	button[1].setPosition(510.f, 239.f);
	button[2].setPosition(510.f, 324.f);
	button[3].setPosition(510.f, 406.f);
	button[4].setPosition(510.f, 488.f);
	button[5].setSize(Vector2f(166.f, 30.f));
	button[5].setPosition(310.f, 562.f);
	Clock btn;
	int z = 0;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					Vector2i mousePos = Mouse::getPosition(window);
					Vector2f worldPos = window.mapPixelToCoords(mousePos);

					for (int i = 0; i < 6; i++)
					{
						if (button[i].getGlobalBounds().contains(worldPos))
						{
							z = i;
							btn.restart();
							button[i].setFillColor(Color(0, 0, 0, 100));
							switch (i)
							{
							case 0: cout << "Life added\n"; break;
							case 1: cout << "Speed increased\n"; break;
							case 2: cout << "Power increased\n"; break;
							case 3: cout << "Distance increased\n"; break;
							case 4: cout << "balloon mode\n"; break;
							case 5: window.close(); pauseMenu(); break;
							}
							break;
						}
					}
				}
			}
		}
		if (btn.getElapsedTime().asSeconds() >= 0.1f)
		{
			button[z].setFillColor(Color::Transparent);
		}

		window.clear(Color::Black);
		window.draw(s);
		for (int i = 0; i < 6; i++)
			window.draw(button[i]);
		window.display();
	}
}

