#ifndef GUARD_Snake_h
#define GUARD_Snake_h

#include <vector>

#include "Snake_Segment.h"

/*
 * represents the snake on the screen. A Snake
 * is made up of Snake_Segments
 */
class Snake
{
    private:
        /* the snake itself */
        std::vector<Snake_Segment> snake;
    public:
        Snake_Segment& get_front();
        const Snake_Segment& get_back();
        std::vector<Snake_Segment>& get_segments();
        void add_to_back(Snake_Segment);

        bool has_hit_wall();
        bool has_hit_self();
        bool is_on_food();
        bool has_died();
};

#endif
