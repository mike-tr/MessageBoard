#include "Board.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace ariel {

char Board::empty_val = '_';

typedef unsigned int uint;
typedef unsigned long ulong;
/**
 * this method is a setter for a givem position, 
 * Its not a reference due to the fact that i dont wish accidently creating an empty space,
 * hence i must put a character in each and every place i create.
 * */
void Board::setCharAt(uint x, uint y, char c) {
    board[{x, y}] = c;
}

/**
 * this method returns the actuall character on x,y but if its empty it will return "_";
 * */
char Board::charAt(uint x, uint y) const {
    auto key = make_pair(x, y);
    if (board.count(key) == 1) {
        return board.at(key);
    }
    return empty_val;
}

/**
* given the start and end position of the newest message calculate the new bound of the "show" square.
 * */
void Board::updateBound(ulong start_x, ulong start_y, ulong size_x, ulong size_y) {
    //cout << start_x << " : " << start_y << " : " << size_x << " : " << size_y << endl;

    // if the new message starts after the min value then we need to offset the 'real' length of the message.
    // end  = new_start - old_start + length.
    if (start_x > bound.min_x) {
        size_x += start_x - bound.min_x;
    }

    // same but for the y axis.
    if (start_y > bound.min_y) {
        size_y += start_y - bound.min_y;
    }

    if (bound.min_x > start_x) {
        bound.min_x = start_x;
    }

    if (bound.min_y > start_y) {
        bound.min_y = start_y;
    }

    if (bound.size_x < size_x) {
        bound.size_x = size_x;
    }

    if (bound.size_y < size_y) {
        bound.size_y = size_y;
    }
}

void Board::post(uint row, uint column, Direction direction, const std::string &message) {
    uint length = message.length();
    if (length == 0) {
        // do nothing, We have this check because we do not want to recalculate bound.
        return;
    }

    if (direction == Direction::Horizontal) {
        updateBound(column, row, length, 1);
        for (uint i = 0; i < length; i++) {
            uint x = column + i;
            //charAt(x, row) = message.at(i);
            setCharAt(x, row, message.at(i));
        }
    } else {
        updateBound(column, row, 1, length);
        for (uint i = 0; i < length; i++) {
            uint y = row + i;
            setCharAt(column, y, message.at(i));
            //charAt(column, y) = message.at(i);
        }
    }
}

std::string Board::read(uint row, uint column, Direction direction, uint length) const {
    string message;
    if (direction == Direction::Horizontal) {
        for (uint i = 0; i < length; i++) {
            uint x = column + i;
            message += charAt(x, row);
        }
    } else {
        for (uint i = 0; i < length; i++) {
            uint y = row + i;
            message += charAt(column, y);
        }
    }

    return message;
}

void Board::show() const {
    if (bound.size_x == 0) {
        return;
    }

    //cout << "Bound {" << bound.min_x << " ," << bound.min_y << " :: " << bound.size_x << " ," << bound.size_y << " }" << endl;

    uint pre_length = to_string(bound.min_y + bound.size_y + 2).length() + 2;
    uint length = bound.size_x + 4;
    for (uint i = 0; i < bound.size_y + 2; i++) {
        //cout << length << endl;
        uint y = bound.min_y + i - 1;

        auto space = to_string(y) + ": ";
        while (space.length() < pre_length) {
            space += " ";
        }
        cout << space << read(y, bound.min_x - 2, Direction::Horizontal, length) << endl;
    }
}

} // namespace ariel