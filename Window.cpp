#include <random>
#include <iterator>
#include <algorithm>

#include <unistd.h>

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
 * checks if the snake head is on a piece of Food (therefore eating it aka removing it from the food vector)
 * return: true if it is, false if not
 */
bool Window::is_on_food()
{
    Snake_Segment head = snake.get_front();
    int x_head = head.get_pos().get_x_pos();
    int y_head = head.get_pos().get_y_pos();
    for(std::vector<Food>::const_iterator it = food.begin(); it != food.end(); it++)
    {
        int x_food = it->get_pos().get_x_pos();
        int y_food = it->get_pos().get_y_pos();

        //todo: use Pos == Pos
        if(x_head == x_food && y_head == y_food) // eaten a piece of food!
        {
            food.erase(it);
            return true;
        }
    }

    return false;
}

/*
 * used to spawn a new piece of Food onto the screen
 * return: a new Food object that the snake can eat
 */
Food Window::create_food()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distrx(2, max_x - 2); // define the range
    int x = distrx(eng);
    std::uniform_int_distribution<> distry(2, max_y - 2); // define the range
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
    snake.go(); // start snake off
    food.push_back(create_food()); // initial piece of food

    bool dead = false;
    while(!dead) // game loop
    {
        char input = getch();
        if(input != ERR) // user pressed something
            handle_input(input);

        update_directions();
        if(is_on_food())
        {
            snake.grow();
            food.push_back(create_food()); // create new food
        }

        if(snake.has_died())
            dead = true;

        draw_screen();
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


        if(snake.get_segments().size() > 1)
        {
        printw(" draw_snake(): has dir=%d   ", it->get_direction());
        refresh();
        sleep(1);
        }



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
 * used to update the direction of every segment, needed as the
 * snake can turn so at some point other segments will need to turn
 */
void Window::update_directions()
{
    // todo: here is problem
    std::vector<Snake_Segment> segments_copy;
    std::copy(snake.get_segments().begin(), snake.get_segments().end(), back_inserter(segments_copy));

    std::vector<Snake_Segment>::size_type curr, next;
    for(curr = 0, next = 1; curr < snake.get_segments().size(); curr++, next++)
    {
        if(next >= snake.get_segments().size()) // no more next segments to use (at tail)
            return;

        Snake_Segment curr_segment = snake.get_segment(curr);
        Snake_Segment next_segment = snake.get_segment(next);

        // change this segments direction to the one ahead of it
        //next_segment.set_direction(curr_segment.get_direction());
        printw("bef: currd=%d nextd=%d x=%d y=%d ", curr_segment.get_direction(), next_segment.get_direction(), next_segment.get_pos().get_x_pos(), next_segment.get_pos().get_y_pos());
        refresh();
        sleep(3);
        next_segment.set_direction(segments_copy.at(curr).get_direction());
        printw("aft: currd=%d nextd=%d x=%d y=%d ", curr_segment.get_direction(), next_segment.get_direction(), next_segment.get_pos().get_x_pos(), next_segment.get_pos().get_y_pos());
        refresh();
        sleep(3);
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
