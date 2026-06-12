#include "main-menu.h";

void settings()
{
	RenderWindow window(VideoMode(800, 600), "Settings");

	Texture s;
	if (!s.loadFromFile("images/Settings.png"))
	{
		cout << "Error loading settings page\n";
		return;
	}
	Sprite set(s);
	set.setScale(0.6f, 0.53f);

	//arrow logic
	int arrow = 0;
	RectangleShape b[3];
	for (int i = 0; i < 3; i++)
	{
		b[i].setSize(Vector2f(20.f, 20.f));
		b[i].setFillColor(Color::Black);
	}
	b[0].setPosition(285.f, 520.f);
	b[1].setPosition(285.f, 550.f);
	b[2].setPosition(285.f, 575.f);

	//key binding logic
	//blinking mechanics
	RectangleShape bind[10];
	for (int i = 0; i < 10; i++)
	{
		bind[i].setSize(Vector2f(65.f, 15.f));
		bind[i].setFillColor(Color::Black);
	}
	bind[0].setPosition(710.f, 293.f);
	bind[1].setPosition(710.f, 332.f);
	bind[2].setPosition(710.f, 372.f);
	bind[3].setPosition(710.f, 412.f);
	bind[4].setPosition(710.f, 452.f);
	bind[5] = bind[0];
	bind[6] = bind[1];
	bind[7] = bind[2];
	bind[8] = bind[3];
	bind[9] = bind[4];
	int z = 0;
	bool blinker = false;
	Clock keyBind;
	bool startBlinking = false;

	//changing keys mechanics
	Font font;
	if (!font.loadFromFile("PixelPurl.ttf"))
	{
		cout << "Error loading font in settings\n";
		return;
	}

	Text keys[5];
	for (int i = 0; i < 5; i++)
	{
		keys[i].setFont(font);
		keys[i].setCharacterSize(24);
		keys[i].setFillColor(Color::Yellow);
	}
	string setKeys[5] = {"A", "D", "W", "V", "Esc"};
	Keyboard::Key p1[5] = { Keyboard::A, Keyboard::D, Keyboard::W, Keyboard::V, Keyboard::Escape};
	Keyboard::Key p2[4] = { Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::K };
	Keyboard::Key pause = Keyboard::Escape;
	int y = 0;

	//volume settings
	string volumeSays[3] = {"100", "100", "100"};
	Text volumeShow[3];
	int mvt = 0, musicvt = 0, sfxt = 0;
	for (int i = 0; i < 3; i++)
	{
		volumeShow[i].setFont(font);
		volumeShow[i].setFillColor(Color::Yellow);
		volumeShow[i].setCharacterSize(28);
		volumeShow[i].setString(volumeSays[i]);
	}
	//master volume
	RectangleShape mv[22];
	float volume = 60.8;
	for (int i = 0; i < 21; i++)
	{
		mv[i].setSize(Vector2f(8.f, 13.f));
		mv[i].setFillColor(Color::Transparent);
		mv[i].setOutlineThickness(1);
		mv[i].setOutlineColor(Color::Yellow);
		volume += 12.1;
		mv[i].setPosition(volume, 312.f);
	}
	mv[20].setFillColor(Color::Black);
	mv[20].setOutlineColor(Color::Black);
	mv[20].setPosition(volume-1, 312.f);
	//number show
	mv[21].setSize(Vector2f(35.f, 15.f));
	mv[21].setFillColor(Color::Black);
	mv[21].setPosition(341.f, 311.f);
	volumeShow[0].setPosition(341.f, 297.f);

	//music volume
	RectangleShape musicv[22];
	volume = 60.8;
	for (int i = 0; i < 21; i++)
	{
		musicv[i].setSize(Vector2f(8.f, 13.f));
		musicv[i].setFillColor(Color::Transparent);
		musicv[i].setOutlineThickness(1);
		musicv[i].setOutlineColor(Color::Yellow);
		volume += 12.1;
		musicv[i].setPosition(volume, 372.f);
	}
	musicv[20].setFillColor(Color::Black);
	musicv[20].setOutlineColor(Color::Black);
	musicv[20].setPosition(volume - 1, 372.f);

	musicv[21].setSize(Vector2f(35.f, 15.f));
	musicv[21].setFillColor(Color::Black);
	musicv[21].setPosition(341.f, 371.f);
	volumeShow[1].setPosition(341.f, 357.f);

	//SFX
	RectangleShape sfx[22];
	volume = 60.8;
	for (int i = 0; i < 21; i++)
	{
		sfx[i].setSize(Vector2f(8.f, 13.f));
		sfx[i].setFillColor(Color::Transparent);
		sfx[i].setOutlineThickness(1);
		sfx[i].setOutlineColor(Color::Yellow);
		volume += 12.1;
		sfx[i].setPosition(volume, 432.f);
	}
	sfx[20].setFillColor(Color::Black);
	sfx[20].setOutlineColor(Color::Black);
	sfx[20].setPosition(volume - 1, 433.f);

	sfx[21].setSize(Vector2f(35.f, 15.f));
	sfx[21].setFillColor(Color::Black);
	sfx[21].setPosition(341.f, 431.f);
	volumeShow[2].setPosition(341.f, 417.f);

	//mute button
	RectangleShape muteButton(Vector2f(50.f, 15.f));
	muteButton.setFillColor(Color::Black);
	muteButton.setPosition(275.f, 480.f);

	Text toggleMute;
	toggleMute.setFont(font);
	toggleMute.setCharacterSize(24);
	toggleMute.setFillColor(Color::Yellow);
	toggleMute.setPosition(285.f, 470.f);
	string muteSays = "OFF";
	toggleMute.setString(muteSays);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Down && !startBlinking)
					if (arrow < 2)
						arrow++;

				if (event.key.code == Keyboard::Up && !startBlinking)
					if (arrow > 0)
						arrow--;

				if (event.key.code == Keyboard::Enter && !startBlinking)
				{
					if (arrow == 0)
					{
						cout << "Reset done\n";
						Keyboard::Key p1[5] = { Keyboard::A, Keyboard::D, Keyboard::W, Keyboard::V, Keyboard::Escape };
						Keyboard::Key p2[4] = { Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::K };
						pause= Keyboard::Escape;
						implement(p1, p2, pause, 0, 0);
						setKeys[0] = "A";
						setKeys[1] = "D";
						setKeys[2] = "W";
						setKeys[3] = "V";
						setKeys[4] = "Esc";
					}
					if (arrow == 1)
					{
						cout << "Saved\n";
						settingOpen(1);
						implement(p1, p2, pause, 0, 0);
					}
					if (arrow == 2)
					{
						window.close(); mainMenu();
					}
				}

				if (startBlinking)
				{
					bool good = true;
					string c2;
					char c = 'A';
					if (event.key.code >= Keyboard::A && event.key.code <= Keyboard::Z)
					{
					    c = 'A' + (event.key.code - Keyboard::A);
						for (int i = 0; i < 5; i++)
						{
							if (setKeys[i] == c)
								good = false;
						}
						if (good)
						{
							setKeys[z] = c; startBlinking = false; blinker = false;
							switch (c)
							{
							case 'A': p1[z] = Keyboard::A; break;
							case 'B': p1[z] = Keyboard::B; break;
							case 'C': p1[z] = Keyboard::C; break;
							case 'D': p1[z] = Keyboard::D; break;
							case 'E': p1[z] = Keyboard::E; break;
							case 'F': p1[z] = Keyboard::F; break;
							case 'G': p1[z] = Keyboard::G; break;
							case 'H': p1[z] = Keyboard::H; break;
							case 'I': p1[z] = Keyboard::I; break;
							case 'J': p1[z] = Keyboard::J; break;
							case 'K': p1[z] = Keyboard::K; break;
							case 'L': p1[z] = Keyboard::L; break;
							case 'M': p1[z] = Keyboard::M; break;
							case 'N': p1[z] = Keyboard::N; break;
							case 'O': p1[z] = Keyboard::O; break;
							case 'P': p1[z] = Keyboard::P; break;
							case 'Q': p1[z] = Keyboard::Q; break;
							case 'R': p1[z] = Keyboard::R; break;
							case 'S': p1[z] = Keyboard::S; break;
							case 'T': p1[z] = Keyboard::T; break;
							case 'U': p1[z] = Keyboard::U; break;
							case 'V': p1[z] = Keyboard::V; break;
							case 'W': p1[z] = Keyboard::W; break;
							case 'X': p1[z] = Keyboard::X; break;
							case 'Y': p1[z] = Keyboard::Y; break;
							case 'Z': p1[z] = Keyboard::Z; break;
							}
							pause = p1[4];
						}
					}
					c2 = c;
					switch (event.key.code)
					{
					case Keyboard::Space: c2 = "SPACE"; break;
					case Keyboard::Enter: c2 = "ENTER"; break;
					case Keyboard::Up: c2 = "UP"; break;
					case Keyboard::Down: c2 = "DOWN"; break;
					case Keyboard::Left: c2 = "LEFT"; break;
					case Keyboard::Right: c2 = "RIGHT"; break;
					case Keyboard::Escape: c2 = "Esc"; break;
					default: break;
					}
					good = true;
					for (int i = 0; i < 5; i++)
					{
						if (setKeys[i] == c2)
							good = false;
					}
					if (good)
					{
						setKeys[z] = c2; startBlinking = false; blinker = false;
						char x = c2[0];
						switch (x)
						{
						case 'S': p1[z] = Keyboard::Space; break;
						case 'E': p1[z] = Keyboard::Enter; break;
						case 'U': p1[z] = Keyboard::Up; break;
						case 'D': p1[z] = Keyboard::Down; break;
						case 'L': p1[z] = Keyboard::Left; break;
						case 'R': p1[z] = Keyboard::Right; break;
						case 'e': p1[z] = Keyboard::Escape; break;
						}
						pause = p1[4];
					}
				}
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					Vector2i mousePos = Mouse::getPosition(window);
					Vector2f worldPos = window.mapPixelToCoords(mousePos);
					for (int i = 0; i < 5; i++)
					{
						if (bind[i].getGlobalBounds().contains(worldPos))
						{
							z = i;
							startBlinking = true;
						}
					}
					//volume control
					for (int i = 0; i < 20; i++)
					{
						if (mv[i].getGlobalBounds().contains(worldPos))
						{
							muteSays = "OFF";
							for (int j = 0; j <= i; j++)
							{
								mv[j].setFillColor(Color::Transparent);
							}
							for (int j = i + 1; j < 20; j++)
							{
								mv[j].setFillColor(Color::Black);
							}
						}
						else if (musicv[i].getGlobalBounds().contains(worldPos))
						{
							muteSays = "OFF";
							for (int j = 0; j <= i; j++)
							{
								musicv[j].setFillColor(Color::Transparent);
							}
							for (int j = i + 1; j < 20; j++)
							{
								musicv[j].setFillColor(Color::Black);
							}
						}
						else if (sfx[i].getGlobalBounds().contains(worldPos))
						{
							muteSays = "OFF";
							for (int j = 0; j <= i; j++)
							{
								sfx[j].setFillColor(Color::Transparent);
							}
							for (int j = i + 1; j < 20; j++)
							{
								sfx[j].setFillColor(Color::Black);
							}
						}
					}
					if (toggleMute.getGlobalBounds().contains(worldPos))
					{
						if (muteSays == "OFF")
						{
							muteSays = "ON";
							for (int i = 0; i < 20; i++)
							{
								mv[i].setFillColor(Color::Black);
								musicv[i].setFillColor(Color::Black);
								sfx[i].setFillColor(Color::Black);
							}
						}
						else
						{
							muteSays = "OFF";
							for (int i = 0; i < 20; i++)
							{
								mv[i].setFillColor(Color::Transparent);
								musicv[i].setFillColor(Color::Transparent);
								sfx[i].setFillColor(Color::Transparent);
							}
						}
					}
				}
			}
		}

		if (startBlinking && keyBind.getElapsedTime().asSeconds() >= 0.7f)
		{
			(blinker) ? blinker = false : blinker = true;
			keyBind.restart();
		}

		y = 243;
		for (int i = 0; i < 5; i++)
		{
			keys[i].setString(setKeys[i]);
			y += 40;
			if (setKeys[i].size() == 1)
				keys[i].setPosition(737.f, y);
			else
				keys[i].setPosition(722.f, y);
		}

		toggleMute.setString(muteSays);

		//volume display number logic
		for (int i = 0; i < 20; i++)
		{
			if (mv[i].getFillColor() == Color::Black && mv[i - 1].getFillColor() == Color::Transparent)
				mvt = i * 5;
			else if (mv[0].getFillColor() == Color::Black)
				mvt = 0;
			else if (mv[19].getFillColor() == Color::Transparent)
				mvt = 100;

			if (musicv[i].getFillColor() == Color::Black && musicv[i - 1].getFillColor() == Color::Transparent)
				musicvt = i * 5;
			else if (musicv[0].getFillColor() == Color::Black)
				musicvt = 0;
			else if (musicv[19].getFillColor() == Color::Transparent)
				musicvt = 100;

			if (sfx[i].getFillColor() == Color::Black && sfx[i - 1].getFillColor() == Color::Transparent)
				sfxt = i * 5;
			else if (sfx[0].getFillColor() == Color::Black)
				sfxt = 0;
			else if (sfx[19].getFillColor() == Color::Transparent)
				sfxt = 100;
		}
		volumeSays[0] = to_string(mvt);
		volumeShow[0].setString(volumeSays[0]);

		volumeSays[1] = to_string(musicvt);
		volumeShow[1].setString(volumeSays[1]);

		volumeSays[2] = to_string(sfxt);
		volumeShow[2].setString(volumeSays[2]);

		window.clear(Color::Black);
		window.draw(set);
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
		for (int i = 5; i < 10; i++)
			window.draw(bind[i]);
		for (int i = 0; i < 5; i++)
			window.draw(keys[i]);
		if (blinker)
			window.draw(bind[z]);
		//volume
		for (int i = 0; i < 22; i++)
		{
			window.draw(mv[i]); window.draw(musicv[i]); window.draw(sfx[i]);
		}
		for (int i = 0; i < 3; i++)
			window.draw(volumeShow[i]);
		window.draw(muteButton);
		window.draw(toggleMute);
		window.display();
	}
}

Keyboard::Key implement(Keyboard::Key x[4], Keyboard::Key y[4], Keyboard::Key p, int get, int num)
{
	static Keyboard::Key p1[4];
	static Keyboard::Key p2[4];
	static Keyboard::Key pause;
	
	if (get == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			p1[i] = x[i];
			p2[i] = y[i];
		}
		pause = p;
	}
	

	else if (get == 1)
		return p1[num];
	else if (get == 2)
		return p2[num];
	else if (get == 3)
		return pause;
}

bool settingOpen(int i)
{
	static bool open = false;

	if (i == 1)
		open = true;
	else if (i == 2)
		return open;
}