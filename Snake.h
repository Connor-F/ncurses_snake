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

        Snake_Segment& get_segment(std::vector<Snake_Segment>::size_type); // todo: remove?

        void grow();
        void go();

        bool has_hit_wall();
        bool has_hit_self();
        bool has_died();
};

#endif
