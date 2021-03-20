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
 * this function updates the Max visable latter on the board and the min visable position
 * this is used to know with part of the board to "show".
 * */
void Board::updateBound(ulong start_x, ulong start_y, ulong size_x, ulong size_y) {
    //cout << start_x << " : " << start_y << " : " << size_x << " : " << size_y << endl;
    if (start_x > bound.min_x) {
        size_x += start_x - bound.min_x;
    }

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
        throw invalid_argument{"Cannot post message of length : 0"};
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
    if (length == 0) {
        throw invalid_argument{"Cannot read message of length : 0"};
    }

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
    uint length = bound.size_x + 4;
    for (uint i = 0; i < bound.size_y + 2; i++) {
        //cout << length << endl;
        uint y = bound.min_y + i - 1;
        cout << read(y, bound.min_x - 2, Direction::Horizontal, length) << endl;
    }
}

} // namespace ariel