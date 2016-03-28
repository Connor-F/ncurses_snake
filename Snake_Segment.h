#ifndef GUARD_Snake_Segment_h
#define GUARD_Snake_Segment_h

#include <string>

#include "Pos.h"

/*
 * direction indicators for each snake segment
 */
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

/*
 * reperesnts one piece of the snakes body
 */
class Snake_Segment
{
    private:
        Pos position;
        int direction;
        std::string segment_icon;
    public:
        Snake_Segment(Pos pos, int dir) : position(pos), direction(dir), segment_icon("o") { }

        const std::string& get_segment_icon() const;
        const Pos get_pos() const;
        void set_pos(Pos);
        void set_direction(int);
        int get_direction();
};

#endif
