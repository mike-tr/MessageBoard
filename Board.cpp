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

    if (size_x == 0) {
        size_x = 1;
    } else if (size_y == 0) {
        size_y = 1;
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

    uint addx = direction == Direction::Horizontal ? 1 : 0;
    uint addy = direction == Direction::Vertical ? 1 : 0;

    updateBound(column, row, length * addx, length * addy);

    for (uint i = 0; i < length; i++) {
        uint x = column + i * addx;
        uint y = row + i * addy;

        //cout << "post :: " << (int)direction << " :: " << x << " ," << y;

        charAt(x, y) = message.at(i);
        //cout << "c : " << charAt(x, y) << endl;
    }
}

std::string Board::read(uint row, uint column, Direction direction, uint length) const {
    if (length == 0) {
        throw invalid_argument{"Cannot read message of length : 0"};
    }
    uint addx = direction == Direction::Horizontal ? 1 : 0;
    uint addy = direction == Direction::Vertical ? 1 : 0;

    string message;
    for (uint i = 0; i < length; i++) {
        uint x = column + i * addx;
        uint y = row + i * addy;

        message += charAt(x, y);

        // cout << "read :: " << (int)direction << " :: " << x << " ," << y << " c : " << charAt(x, y) << endl;
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