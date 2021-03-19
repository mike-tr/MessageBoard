#ifndef BOARD_CPP
#define BOARD_CPP

#include "Direction.hpp"
#include <string>

namespace ariel {
class Board {
private:
public:
    /**
     * Post a message on the board, note that old message on the same spot will get overwriten.
     * row, columnm - positon
     * direction - the direction of the message horizontal - left to right,  Vertical - Top to Button.
     * string - the actuall message
     * */
    void post(unsigned int row, unsigned int column, Direction direction, std::string message);
    /**
     * Read the message from the board starting from given possition and going in the specified direction,
     * stop when read "length" worth of letters.
     * row, columnm - positon
     * direction - the direction of the message horizontal - left to right,  Vertical - Top to Button.
     * length - the length of the post to read ( a.k.a the length of the returned string ).
     * */
    std::string read(unsigned int row, unsigned int column, Direction direction, unsigned int length) const;

    /**
     * print on screen, the board,
     * min index shown would be for X : Max(0, bound().minX()) - 1), Y : Max(0,  bound().miny()
     * max index shown would befor X : bound().maxX() + 1, Y : bound().maxY() + 1
     * 
     * print everything in that area.
     * */
    void show() const;
};
} // namespace ariel

#endif