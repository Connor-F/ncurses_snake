#include "Pos.h"

bool Pos::operator==(const Pos& input)
{
    return (input.get_x_pos() == x && input.get_y_pos() == y);
}

/*
 * allows user to get this current position object
 * return: this position object
 */
const Pos Pos::get_pos() const
{
    return *this;
}

/*
 * allows user to get the current x position of this point
 * return: current x position of this point
 */
const int Pos::get_x_pos() const
{
    return x;
}

/*
 * allows user to get the current y position of this point
 * return: current y position of this point
 */
const int Pos::get_y_pos() const
{
    return y;
}
