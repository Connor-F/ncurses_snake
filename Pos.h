#ifndef GUARD_Pos_h
#define GUARD_Pos_h

/*
 * represents a 2D coordinate on the game board
 */
class Pos
{
    private:
        int x, y;
    public:
        Pos(int x_pos, int y_pos) : x(x_pos), y(y_pos) { }

        bool operator==(const Pos&);
        bool operator!=(const Pos&);
        const Pos get_pos() const;
        const int get_x_pos() const;
        const int get_y_pos() const;
};

#endif
