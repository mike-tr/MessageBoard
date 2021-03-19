#include "Board.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace ariel {

char Board::empty_val = '_';
/**
 * this method return referense to the character on the given x,y;
 * returns 0 if its empty.
 * */
char &Board::charAt(unsigned int x, unsigned int y) {
    // char &c = board[make_tuple(x, y)];
    // if (c == 0) {
    //     c = empty_val;
    // }
    return board[make_tuple(x, y)];
}

/**
 * this method returns the actuall character on x,y but if its empty it will return "_";
 * */
char Board::charAt(unsigned int x, unsigned int y) const {
    auto key = make_tuple(x, y);
    if (board.count(key) == 1) {
        return board.at(key);
    }
    return empty_val;
}

void Board::updateBound(unsigned long start_x, unsigned long start_y, unsigned long size_x, unsigned long size_y) {
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

void Board::post(unsigned int row, unsigned int column, Direction direction, const std::string &message) {
    unsigned int length = message.length();
    if (length == 0) {
        throw invalid_argument{"Cannot post message of length : 0"};
    }

    // if (bound.min_x > column) {
    //     bound.min_x = column;
    // }

    // if (bound.max_x < column + length) {
    // }

    unsigned int addx = direction == Direction::Horizontal ? 1 : 0;
    unsigned int addy = direction == Direction::Vertical ? 1 : 0;

    updateBound(column, row, length * addx, length * addy);

    for (unsigned int i = 0; i < length; i++) {
        unsigned int x = column + i * addx;
        unsigned int y = row + i * addy;

        //cout << "post :: " << (int)direction << " :: " << x << " ," << y;

        charAt(x, y) = message.at(i);
        //cout << "c : " << charAt(x, y) << endl;
    }
}

std::string Board::read(unsigned int row, unsigned int column, Direction direction, unsigned int length) const {
    if (length == 0) {
        throw invalid_argument{"Cannot read message of length : 0"};
    }
    unsigned int addx = direction == Direction::Horizontal ? 1 : 0;
    unsigned int addy = direction == Direction::Vertical ? 1 : 0;

    string message;
    for (unsigned int i = 0; i < length; i++) {
        unsigned int x = column + i * addx;
        unsigned int y = row + i * addy;

        message += charAt(x, y);

        // cout << "read :: " << (int)direction << " :: " << x << " ," << y << " c : " << charAt(x, y) << endl;
    }
    return message;
}

void Board::show() const {
    if (bound.size_x == 0) {
        return;
    }

    unsigned int length = bound.size_x + 4;
    for (unsigned int i = 0; i < bound.size_y + 2; i++) {
        unsigned int y = bound.min_y + i - 1;
        cout << read(y, bound.min_x - 2, Direction::Horizontal, length) << endl;
    }
}

} // namespace ariel