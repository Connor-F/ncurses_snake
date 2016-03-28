#ifndef GUARD_Window_h
#define GUARD_Window_h

#include <vector>
#include <ncurses.h>

#include "Food.h"
#include "Snake.h"

/*
 * represents the game window and associated functions
 * to play the game
 */
class Window
{
    private:
        /* the food that is on the board */
        std::vector<Food> food;
        /* current game session score */
        int score;
        /* the Snake that is on the screen */
        Snake snake;
        /* milliseconds to wait for user input */
        int ms_delay;

        void start_ncurses();
        void draw_game_frame();
        void draw_food();
        void draw_snake();
        void draw_screen();
        void update_directions();

        Food create_food();
        bool is_on_food();

        void handle_input(char);

    public:
        Window(int delay) : ms_delay(delay) { }

        /* screen max x size */
        static int max_x;
        /* screen max y size */
        static int max_y;

        void start_game();
};

#endif
