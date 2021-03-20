/**
 * Demo program for message-board exercise.
 * 
 * Author: Erel Segal-Halevi
 * Since : 2021-03
 */

#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;

#include <vector>

int main() {
    ariel::Board board;

    board.post(/*row=*/100, /*column=*/200, Direction::Horizontal, "abcde");
    board.post(/*row=*/98, /*column=*/202, Direction::Vertical, "abcde");
    board.show();

    cout << endl;
    board.post(/*row=*/102, /*column=*/200, Direction::Horizontal, "?-?-?-?");
    board.post(/*row=*/98, /*column=*/205, Direction::Vertical, "12345");
    board.show();

    cout << endl;
    board.post(110, 210, Direction::Horizontal, "iam do not belong");
    board.show();

    // cout << board.read(/*row=*/99, /*column=*/201, Direction::Vertical, /*length=*/3) << endl;
    // // prints "_b_" (starts at row 99 which is empty; then at row 100 there is "b"; then row 101 is empty again).
    // board.post(/*row=*/99, /*column=*/202, Direction::Vertical, "xyz");
    // board.post(/*row=*/99, /*column=*/204, Direction::Vertical, "xyz");
    // cout << board.read(/*row=*/100, /*column=*/200, Direction::Horizontal, /*length=*/6) << endl;

    //board.show(); // shows the board in a reasonable way. For example:
    //    98:  _________
    //    99:  ____x____
    //    100: __abyd___
    //    101: ____z____
    //    102: _________
}
