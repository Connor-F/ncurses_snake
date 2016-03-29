#include "Snake_Segment.h"

#include <ncurses.h> //todo: remove both
#include <unistd.h>

// todo: remove
void Snake_Segment::set_segment_icon(std::string input)
{
    segment_icon = input;
}

bool Snake_Segment::operator!=(const Snake_Segment& input)
{
    return position != input.get_pos();
}

bool Snake_Segment::operator==(const Snake_Segment& input)
{
    return position == input.get_pos();
}

/*
 * allows the snake to be drawn with defined icon
 * return: string contaning the icon used for parts of the snake
 */
const std::string& Snake_Segment::get_segment_icon() const
{
    return segment_icon;
}

/*
 * allows retrieval of Pos of current segment
 * return: Pos of this segment
 */
Pos Snake_Segment::get_pos() const
{
    return position;
}

/*
 * allows the direction of the segment to change
 * param: dir: the new direction to face
 */
void Snake_Segment::set_direction(int dir)
{
    /*printw("dir before:%d   dir recvd:%d  ", direction, dir);
    refresh();
    sleep(3);*/
    direction = dir;
    /*printw("dir after:%d  ", direction);
    refresh();
    sleep(3);*/
}

/*
 * allows for the segment to move to a new position
 * param: pos: the new position to move to
 */
void Snake_Segment::set_pos(Pos pos)
{
    position = pos;
}

/*
 * get the direction the current segment is facing
 * return: int indicating the direction this segment is facing
 */
int Snake_Segment::get_direction()
{
    return direction;
}
