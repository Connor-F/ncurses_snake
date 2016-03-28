#include "Snake.h"
#include "Window.h"

/*
 * allows user to get the front (head) 
 * of the snake
 * return: the Snake_Segment at the front of the snake
 */
Snake_Segment& Snake::get_front()
{
    return snake.at(0);
}

/*
 * allows user to get the back (end)
 * of the snake
 * return: the Snake_Segment at the back of the snake
 */
const Snake_Segment& Snake::get_back()
{
    return snake.at(snake.size() - 1);
}

/*
 * allows user to add a new Snake_Segment to the back
 * of the snake (called after snake has eaten a piece of food)
 * param: seg: the Snake_Segment to add to the back
 */
void Snake::add_to_back(const Snake_Segment seg)
{
    snake.push_back(seg);
}

/*
 * used to get the whole snake (every segment)
 * return: const reference to a vector that makes up the snake
 */
std::vector<Snake_Segment>& Snake::get_segments()
{
    return snake;
}

/*
 * checks if the front of the snake has hit a wall (game over)
 * return: true if it has, false if not
 */
bool Snake::has_hit_wall()
{
    Snake_Segment head = get_front();
    int x = head.get_pos().get_x_pos();
    int y = head.get_pos().get_y_pos();
    return x == 0 || x == Window::max_x || y == 0 || y == Window::max_y; // hit a wall, dead
}

/*
 * checks to see if the head collided with part of the body
 * return: true if it did, false if it didn't
 */
bool Snake::has_hit_self()
{
    Snake_Segment head = get_front();
    int x_head = head.get_pos().get_x_pos();
    int y_head = head.get_pos().get_y_pos();
    //                                                                + 1 to not included head
    for(std::vector<Snake_Segment>::const_iterator it = snake.begin() + 1; it != snake.end(); it++)
    {
        int x_seg = it->get_pos().get_x_pos();
        int y_seg = it->get_pos().get_y_pos();

        if(x_head == x_seg && y_head == y_seg) // head collided with a body segment
            return true;
    }

    return false;
}

/*
 * checks if the snake head is on a piece of Food (therefore eating it)
 * return: true if it is, false if not
 */
bool Snake::is_on_food()
{
    return false;
}

/*
 * checks if the snake has died from crashing into wall / itself
 * return: true if the snake has died, false if not
 */
bool Snake::has_died()
{
    return has_hit_wall() || has_hit_self();
}
