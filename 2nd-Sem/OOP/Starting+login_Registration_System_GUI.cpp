#include "Mahad.h";

void start()
{
    bool blink = false;
    RenderWindow window(VideoMode(800, 600), "Starting page");

    //starting screen
    Texture title;
    if (!title.loadFromFile("images/SnowBros_Title.png"))
    {
        cout << "Error loading title image\n";
        return;
    }

    Sprite start(title);
    start.setScale(3.f, 3.f);
    start.setPosition(10.f, -15.f);

    RectangleShape rec(Vector2f(450.f, 30.f));
    rec.setPosition(175.f, 430.f);
    rec.setFillColor(Color::Black);

    Clock wait;

    //music
    Music music;
    if (!music.openFromFile("sounds/Starting.ogg"))
    {
        cout << "Error playing background music\n";
        return;
    }
    music.play();

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
                    music.stop();
                    loginPage();
                }
            }
        }

        if (wait.getElapsedTime().asSeconds() >= 0.7f)
        {
            (blink) ? blink = false : blink = true;
            wait.restart();
        }

        window.clear(Color::Black);
        window.draw(start);
        if (blink)
        {
            window.draw(rec);
        }
        window.display();
    }
}

void loginPage()
{
    Database x;
    bool auth = false;

    RenderWindow window(VideoMode(800, 600), "Login Page");

    Texture login;
    if (!login.loadFromFile("images/Login_Page.png"))
    {
        cout << "Error loading login page\n";
        return;
    }

    Sprite page(login);
    page.setScale(0.68f, 0.47f);
    page.setPosition(0.f, -10.f);

    //inputting username and password
    Font font;
    if (!font.loadFromFile("PixelPurl.ttf"))
    {
        cout << "Error loading font\n";
        return;
    }

    Text textU;
    textU.setFont(font);
    textU.setCharacterSize(40);
    textU.setPosition(210.f, 255.f);
    textU.setFillColor(Color::White);

    Text textP;
    textP.setFont(font);
    textP.setCharacterSize(40);
    textP.setPosition(210.f, 372.f);
    textP.setFillColor(Color::White);

    string user = "", pass = "", psteric = "";
    bool u = true, p = false;

    //cursor logic
    RectangleShape cursor(Vector2f(2.f, 35.f));
    cursor.setFillColor(Color::White);
    cursor.setPosition(210.f, 379.f);

    Clock blink;
    bool c = false;

    //login button
    RectangleShape log(Vector2f(340.f, 40.f));
    log.setPosition(230.f, 455.f);
    log.setFillColor(Color::Transparent);

    Clock logging;

    //register button
    RectangleShape reg(Vector2f(340.f, 40.f));
    reg.setPosition(230.f, 525.f);
    reg.setFillColor(Color::Transparent);


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
                    if (u)
                    {
                        cout << "Changed\n";
                        p = true;
                        u = false;
                        continue;
                    }
                    if (p)
                    {
                        cout << "Changed again\n";
                        u = true;
                        p = false;
                    }
                }
            }

            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if (event.text.unicode == 13)//enter
                        continue;

                    char entered = static_cast <char>(event.text.unicode);

                    if (entered == '\b')
                    {
                        if (u && !user.empty())
                            user.pop_back();

                        if (p && !pass.empty())
                            pass.pop_back();
                    }
                    else if (entered != '\b')
                    {
                        if (u && user.size() <= 15)
                            user += entered;
                        if (p && pass.size() <= 15) 
                        {
                            pass += entered;
                            psteric += "*";
                        }
                    }
                }
            }

            //mouse interaction
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f worldPos = window.mapPixelToCoords(mousePos);

                    if (log.getGlobalBounds().contains(worldPos))
                    {
                        cout << "Login button pressed\n";
                        auth = Login(x, user, pass);
                        log.setFillColor(Color(0, 0, 0, 100));
                        logging.restart();
                        user = "";
                        pass = "";
                    }

                    else if (reg.getGlobalBounds().contains(worldPos))
                    {
                        cout << "Register button pressed\n";
                        reg.setFillColor(Color(0, 0, 0, 100));
                        logging.restart();
                        window.close();
                        registerPage();
                    }
                }
            }
        }

        if (blink.getElapsedTime().asSeconds() >= 0.7f)
        {
            (c) ? c = false : c = true;
            blink.restart();
        }

        if (logging.getElapsedTime().asSeconds() >= 0.1f)
        {
            log.setFillColor(Color::Transparent);
            reg.setFillColor(Color::Transparent);
        }

        Vector2f cursorPos; 
        if (u)
            cursorPos = textU.findCharacterPos(user.size());
        else if (p)
            cursorPos = textP.findCharacterPos(pass.size());
        cursor.setPosition(cursorPos.x, cursorPos.y + 12.f);

        textU.setString(user);
        textP.setString(psteric);

        window.clear(Color::Blue);
        window.draw(page);
        window.draw(textU);
        window.draw(textP);
        if (c)
            window.draw(cursor);
        window.draw(log);
        window.draw(reg);
        window.display();

        if (auth)
        {
            window.close();
            mainMenu();
        }
    }
}

void registerPage()
{
    Database x;

    RenderWindow window(VideoMode(800, 600), "Registration Page");

    Texture r;
    if (!r.loadFromFile("images/Registration_Page.png"))
    {
        cout << "Error loading registration page\n";
        return;
    }
    Sprite pic(r);
    pic.setScale(0.677f, 0.452f);
    pic.setPosition(0.f, 0.f);

    //inputting username, email,  and password
    Font font;
    if (!font.loadFromFile("PixelPurl.ttf"))
    {
        cout << "Error loading font\n";
        return;
    }

    Text textU;
    textU.setFont(font);
    textU.setCharacterSize(40);
    textU.setPosition(210.f, 225.f);
    textU.setFillColor(Color::White);
   

    Text textP;
    textP.setFont(font);
    textP.setCharacterSize(40);
    textP.setPosition(210.f, 395.f);
    textP.setFillColor(Color::White);

    Text textE;
    textE.setFont(font);
    textE.setCharacterSize(40);
    textE.setPosition(210.f, 310.f);
    textE.setFillColor(Color::White);

    string user = "", pass = "", email = "";
    bool u = true, p = false, e = false;

    //cursor logic
    RectangleShape cursor(Vector2f(2.f, 35.f));
    cursor.setFillColor(Color::White);
    cursor.setPosition(210.f, 379.f);

    Clock blink;
    bool c = false;

    //back to login button
    RectangleShape log(Vector2f(340.f, 40.f));
    log.setPosition(230.f, 525.f);
    log.setFillColor(Color::Transparent);

    Clock logging;

    //register button
    RectangleShape reg(Vector2f(340.f, 40.f));
    reg.setPosition(230.f, 465.f);
    reg.setFillColor(Color::Transparent);

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
                    if (u)
                    {
                        cout << "Changed\n";
                        u = false;
                        p = false;
                        e = true;
                    }
                    else if (p)
                    {
                        cout << "Changed last\n";
                        p = false;
                        e = false;
                        u = true;
                    }
                    else if (e)
                    {
                        cout << "Changes again\n";
                        e = false;
                        u = false;
                        p = true;
                    }
                }
            }

            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if (event.text.unicode == 13)
                        continue;
                    char entered = static_cast <char>(event.text.unicode);

                    if (entered == '\b')
                    {
                        if (u && !user.empty())
                            user.pop_back();

                        if (p && !pass.empty())
                            pass.pop_back();

                        if (e && !email.empty())
                            email.pop_back();
                    }
                    else if (entered != '\b')
                    {
                        if (u && user.size() <= 15)
                            user += entered;
                        if (p && pass.size() <= 15)
                        {
                            pass += entered; 
                        }
                        if (e && email.size() <= 24)
                            email += entered;
                    }
                }
            }

            //mouse interaction
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f worldPos = window.mapPixelToCoords(mousePos);

                    if (log.getGlobalBounds().contains(worldPos))
                    {
                        cout << "Back to login button pressed\n";
                        log.setFillColor(Color(0, 0, 0, 100));
                        logging.restart();
                        window.close();
                        loginPage();
                    }

                    else if (reg.getGlobalBounds().contains(worldPos))
                    {
                        cout << "Register button pressed\n";
                        reg.setFillColor(Color(0, 0, 0, 100));
                        logging.restart();
                        signUp(x, user, pass, email);
                        cout << "You can now log in :)\n";
                        user = "";
                        pass = "";
                        email = "";
                    }
                }
            }
        }

        if (logging.getElapsedTime().asSeconds() >= 0.1f)
        {
            log.setFillColor(Color::Transparent);
            reg.setFillColor(Color::Transparent);
        }

        if (blink.getElapsedTime().asSeconds() >= 0.7f)
        {
            (c) ? c = false : c = true;
            blink.restart();
        }

        Vector2f cursorPos;
        if (u)
            cursorPos = textU.findCharacterPos(user.size());
        else if (p)
            cursorPos = textP.findCharacterPos(pass.size());
        else if (e)
            cursorPos = textE.findCharacterPos(email.size());
        cursor.setPosition(cursorPos.x, cursorPos.y + 12.f);

        textU.setString(user);
        textE.setString(email);
        textP.setString(pass);

        window.clear(Color::Blue);
        window.draw(pic);
        window.draw(textU);
        window.draw(textP);
        window.draw(textE);
        if (c)
            window.draw(cursor);
        window.draw(log);
        window.draw(reg);
        window.display();
    }
}