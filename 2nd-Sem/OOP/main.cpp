#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "StateMachine.h"
#include "Events.h"
#include "PlayingState.h"
#include "GameOverState.h"
#include "Mahad.h";
using namespace sf;

void Usman(int type) {
    RenderWindow window(VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);

    Keyboard::Key p1[4] = { Keyboard::A, Keyboard::D, Keyboard::W, Keyboard::V };
    Keyboard::Key p2[4] = { Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::K };
    Keyboard::Key pause = Keyboard::Escape;
    if (settingOpen(2))
    {
        pause = implement(p1, p2, pause, 3, 0);
        for (int i = 0; i < 4; i++)
        {
            p1[i] = implement(p1, p2, pause, 1, i);
        }
     }

    InputManager input;
    input.loadDefaults(p1, p2, pause);

    StateMachine stateMachine;
    stateMachine.push(new PlayingState(window, input, type));

    Clock clock;
    const float FIXED_DT = 1.0f / 60.0f;
    float accumulator = 0.0f;

    //background music
    Music music;
    if (!music.openFromFile("sounds/GamePlay.ogg"))
    {
        cout << "Error playing music\n";
        return;
    }
    music.setLoop(true);
    music.play();

    while (window.isOpen()) {
        float frameTime = clock.restart().asSeconds();
        if (frameTime > 0.2f) frameTime = 0.2f;
        accumulator += frameTime;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == pause)
                {
                    music.pause();
                    int x = pauseMenu();
                    if (x == 1)
                    {
                        window.close();
                        mainMenu();
                    }
                    else if (x == 2)
                    {
                        window.close();
                        loginPage();
                    }
                    music.play();
                }
            }
        }

        input.update();

        while (accumulator >= FIXED_DT) {
            if (!stateMachine.isEmpty()) {
                stateMachine.current()->handleInput(input);
                stateMachine.current()->update(FIXED_DT);
            }
            accumulator -= FIXED_DT;
        }

        // Check for game over transition
        if (!stateMachine.isEmpty()) {
            PlayingState* ps = dynamic_cast<PlayingState*>(
                stateMachine.current());
            if (ps != nullptr && ps->isGameOver())
                stateMachine.change(new GameOverState(window));
        }

        window.clear(Color(20, 20, 40));
        if (!stateMachine.isEmpty())
            stateMachine.current()->draw(window, false);
        window.display();
    }

    return;
}

int main()
{
    start();
}