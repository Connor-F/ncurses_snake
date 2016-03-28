#ifndef GUARD_Game_Manager_h
#define GUARD_Game_Manager_h

#include <iostream>

#include "Window.h"

/*
 * controls the game
 */
class Game_Manager
{
    private:
        static int score;
        Window game_window;

    public:
        Game_Manager(int delay) :game_window(delay) { } 

        void start_game();
        static void game_over()
        {
            endwin();
            std::cout << "Score: " << score << '\n';
        }
};

#endif
