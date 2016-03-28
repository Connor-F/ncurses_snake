#include <random>

#include "Window.h"
#include "Game_Manager.h"

int Window::max_x = -1;
int Window::max_y = -1;

/*
 * draws the border of the game to the screen
 */
void Window::draw_game_frame()
{
    wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
}

/*
 * used to spawn a new piece of Food onto the screen
 * return: a new Food object that the snake can eat
 */
Food Window::create_food()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distrx(1, max_x - 1); // define the range
    int x = distrx(eng);
    std::uniform_int_distribution<> distry(1, max_y - 1); // define the range
    int y = distry(eng);

    return Food(Pos(x, y));
}

void Window::start_ncurses()
{
    initscr();
    cbreak(); // prevent line buffering, get chars as soon as typed
    noecho(); // don't print chars to screen when typed
    curs_set(FALSE); // hide cursor
    timeout(ms_delay); // wait delay milliseconds for input
    getmaxyx(stdscr, max_y, max_x); // use ncurses to get screen size
}

/*
 * initialises neccessary componenets so the game can be played, then
 * handles the playing of the game
 */
void Window::start_game()
{
    start_ncurses();
    snake.add_to_back(Snake_Segment(Pos(max_x / 2, max_y / 2), NORTH)); // start in middle
    food.push_back(create_food()); // initial piece of food

    bool dead = false;
    while(!dead)
    {
        char input = getch();
        if(input != ERR) // user pressed something
            handle_input(input);

        draw_screen();
        if(snake.has_died())
            dead = true;
    }

    Game_Manager::game_over();
}

/*
 * draws the food pieces onto the screen
 */
void Window::draw_food()
{
    for(std::vector<Food>::const_iterator it = food.begin(); it != food.end(); it++)
        mvprintw(it->get_pos().get_y_pos(), it->get_pos().get_x_pos(), "%s", it->get_food_icon().c_str());
}

/*
 * draws the snake onto the screen
 */
void Window::draw_snake()
{
    for(std::vector<Snake_Segment>::iterator it = snake.get_segments().begin(); it != snake.get_segments().end(); it++)
    {
        int x, y;
        x = it->get_pos().get_x_pos();
        y = it->get_pos().get_y_pos();
        mvprintw(y, x, "%s", it->get_segment_icon().c_str()); // draw segment to screen

        // after drawing the snake segment, we advance it one cell in the correct
        // direction (depends on the direction of the segment ahead of it)
        switch(it->get_direction())
        {
            case NORTH:
                it->set_pos(Pos(x, y - 1)); // move up 1 cell
                break;
            case EAST:
                it->set_pos(Pos(x + 1, y)); // move right 1 cell
                break;
            case SOUTH:
                it->set_pos(Pos(x, y + 1)); // move down 1 cell
                break;
            case WEST:
                it->set_pos(Pos(x - 1, y)); // move left 1 cell
                break;
        }
    }
}

/*
 * uses the players input to move the snake
 * param: input: the character the player typed
 */
void Window::handle_input(char input)
{
    switch(input)
    {
        case 'w':
        case 'W':
            snake.get_front().set_direction(NORTH); // the front segment dictates the direction of the snake
            break;                                  // so only need to set the front
        case 'a':
        case 'A':
            snake.get_front().set_direction(WEST);
            break;
        case 's':
        case 'S':
            snake.get_front().set_direction(SOUTH);
            break;
        case 'd':
        case 'D':
            snake.get_front().set_direction(EAST);
            break;
    }
}

/*
 * draws the snake and food to the screen
 */
void Window::draw_screen()
{
    erase();
    draw_game_frame();
    draw_snake();
    draw_food();
    refresh();
}
