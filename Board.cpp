#include "Board.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace ariel {

char Board::empty_val = '_';

typedef unsigned int uint;
typedef unsigned long ulong;
/**
 * this method return referense to the character on the given x,y;
 * returns 0 if its empty.
 * */
char &Board::charAt(uint x, uint y) {
    // char &c = board[make_tuple(x, y)];
    // if (c == 0) {
    //     c = empty_val;
    // }
    return board[make_tuple(x, y)];
}

/**
 * this method returns the actuall character on x,y but if its empty it will return "_";
 * */
char Board::charAt(uint x, uint y) const {
    auto key = make_tuple(x, y);
    if (board.count(key) == 1) {
        return board.at(key);
    }
    return empty_val;
}

void Board::updateBound(ulong start_x, ulong start_y, ulong size_x, ulong size_y) {
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

    //cout << bound.min_x << " ," << bound.min_y << " ," << bound.size_x << " ," << bound.size_y << endl;
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
            charAt(x, row) = message.at(i);
        }
    } else {
        updateBound(column, row, 1, length);
        for (uint i = 0; i < length; i++) {
            uint y = row + i;
            charAt(column, y) = message.at(i);
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

    uint length = bound.size_x + 4;
    for (uint i = 0; i < bound.size_y + 2; i++) {
        uint y = bound.min_y + i - 1;
        cout << read(y, bound.min_x - 2, Direction::Horizontal, length) << endl;
    }
}

} // namespace ariel