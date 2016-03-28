#include "Food.h"

/*
 * get the current position of the food item
 * return: the Pos where the food is located
 */
const Pos& Food::get_pos() const
{
    return position;
}

/*
 * get the icon that represents a piece of food
 * return: a string that contains the icon of food
 */
const std::string& Food::get_food_icon() const
{
    return food_icon;
}
