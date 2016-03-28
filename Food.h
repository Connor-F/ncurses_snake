#ifndef GUARD_Food_h
#define GUARD_Food_h

#include <string>

#include "Pos.h"

/*
 * represents a piece of food on the game board
 */
class Food
{
    private:
        Pos position;
        std::string food_icon;
    public:
        Food(Pos pos) : position(pos), food_icon("x") { }

        const Pos& get_pos() const;
        const std::string& get_food_icon() const;
};

#endif
