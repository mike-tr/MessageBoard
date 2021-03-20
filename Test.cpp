/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: <Please write your names here>
 * 
 * Date: 2021-02
 */

#include "Board.hpp"
#include "doctest.h"
using namespace ariel;

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

const int number_of_tests = 20;
const int range = 'z' - '0';

TEST_CASE("Test post, read on random messages as well as empty spaces ( main test )") {
    srand(time(nullptr));

    string empty = "";
    string message = "";
    for (unsigned int i = 1; i < number_of_tests + 1; i++) {
        Board board;
        message += '0' + rand() % range;
        empty += "_";
        unsigned int rand_y = (unsigned int)rand();
        unsigned int rand_x = (unsigned int)rand();

        //cout << i << " :: " << message << " :: l : " << message.length() << ", l2 :" << empty.length() << endl;

        // check that the empty string is of the right length
        CHECK(board.read(rand_y, rand_x, Direction::Horizontal, i).length() == i);
        CHECK(board.read(rand_y, rand_x, Direction::Vertical, i).length() == i);

        // check that the empty string is indeed full of underlines.
        CHECK(board.read(rand_y, rand_x, Direction::Horizontal, i) == empty);
        CHECK(board.read(rand_y, rand_x, Direction::Vertical, i) == empty);

        // print abc vertically this b will be overwritten.
        string m1 = "abc";
        board.post(rand_y - 1, rand_x, Direction::Vertical, m1);

        // post the message horizontally and read it.
        board.post(rand_y, rand_x, Direction::Horizontal, message);
        CHECK(board.read(rand_y, rand_x, Direction::Horizontal, i) == message);
        CHECK(board.read(rand_y, rand_x - 1, Direction::Horizontal, i + 2) == ("_" + message + "_"));

        // read the overwritten "abc" message.
        m1.at(1) = message.at(0);
        //cout << m1 << " :: " << message.at(0) << endl;
        CHECK(board.read(rand_y - 1, rand_x, Direction::Vertical, 3) == m1);

        // RESET BOARD

        board.post(rand_y, rand_x, Direction::Horizontal, empty);
        board.post(rand_y - 1, rand_x, Direction::Vertical, "___");

        // END RESET

        // post message "abc" that will be overwriten on the b
        m1 = "abc";
        board.post(rand_y, rand_x - 1, Direction::Horizontal, m1);

        // Post message and check message
        board.post(rand_y, rand_x, Direction::Vertical, message);
        CHECK(board.read(rand_y, rand_x, Direction::Vertical, i) == message);
        CHECK(board.read(rand_y - 1, rand_x, Direction::Vertical, i + 2) == ("_" + message + "_"));

        // check that the new message "abc" we printed is indeed overwriten
        m1.at(1) = message.at(0);
        CHECK(board.read(rand_y, rand_x - 1, Direction::Horizontal, 3) == m1);
    }
}

TEST_CASE("Test length 0") {
    /**
     * we do not want to allow posting empty string, and we dont want to allow reading string of size 0.
     * the latter might be possible, but posting empty string is a big NO NO.
     * */
    Board board;
    for (unsigned int i = 1; i < number_of_tests + 1; i++) {
        unsigned int rand_y = (unsigned int)rand();
        unsigned int rand_x = (unsigned int)rand();

        CHECK(board.read(rand_y, rand_x, Direction::Horizontal, 0) == "");
        CHECK_NOTHROW(board.post(rand_y, rand_x, Direction::Horizontal, ""));
        CHECK(board.read(rand_y, rand_x, Direction::Horizontal, 1) == "_");

        CHECK_NOTHROW(board.post(rand_y, rand_x, Direction::Horizontal, "a"));
        CHECK_NOTHROW(board.post(rand_y, rand_x, Direction::Horizontal, ""));
        CHECK(board.read(rand_y, rand_x, Direction::Horizontal, 1) == "a");

        board = Board();
        CHECK(board.read(rand_y, rand_x, Direction::Vertical, 0) == "");
        CHECK_NOTHROW(board.post(rand_y, rand_x, Direction::Vertical, ""));
        CHECK(board.read(rand_y, rand_x, Direction::Vertical, 1) == "_");

        CHECK_NOTHROW(board.post(rand_y, rand_x, Direction::Vertical, "a"));
        CHECK_NOTHROW(board.post(rand_y, rand_x, Direction::Vertical, ""));
        CHECK(board.read(rand_y, rand_x, Direction::Vertical, 1) == "a");
    }
}

TEST_CASE("Test multiple boards") {
    // test that content from boardA do not appear on board B
    Board boardA;
    Board boardB;

    srand(time(nullptr));

    string empty = "";
    string message = "";
    for (unsigned int i = 1; i < number_of_tests + 1; i++) {
        message += '0' + rand() % range;
        empty += "_";

        unsigned int rand_y = (unsigned int)rand();
        unsigned int rand_x = (unsigned int)rand();

        // check that posting on A doesnt affect B and vise versa.
        boardA.post(rand_y, rand_x, Direction::Horizontal, message);
        CHECK(boardB.read(rand_y, rand_x, Direction::Horizontal, i) == empty);
        CHECK(boardB.read(rand_y, rand_x, Direction::Vertical, i) == empty);
        boardB.post(rand_y, rand_x, Direction::Horizontal, empty);
        CHECK(boardA.read(rand_y, rand_x, Direction::Horizontal, i) == message);

        // reset BoardA.
        boardA = Board();

        boardB.post(rand_y, rand_x, Direction::Vertical, message);
        CHECK(boardA.read(rand_y, rand_x, Direction::Horizontal, i) == empty);
        CHECK(boardA.read(rand_y, rand_x, Direction::Vertical, i) == empty);
        boardA.post(rand_y, rand_x, Direction::Vertical, empty);
        CHECK(boardB.read(rand_y, rand_x, Direction::Vertical, i) == message);
    }
}

TEST_CASE("Test random mamble wrong direction") {
    /* *
    * in this test we will check if maybe the post are in the wrong direction.
    */

    for (unsigned int i = 0; i < number_of_tests; i++) {
        Board board;
        unsigned int rand_y = (unsigned int)rand();
        unsigned int rand_x = (unsigned int)rand();

        string msg = "abcd";
        string empty = "a___";

        board.post(rand_y, rand_x, Direction::Horizontal, msg);
        CHECK(board.read(rand_y, rand_x, Direction::Vertical, 4) == empty);
        CHECK(board.read(rand_y, rand_x, Direction::Horizontal, 4) == msg);

        board.post(rand_y, rand_x, Direction::Horizontal, "ffff");
        board.post(rand_y, rand_x, Direction::Vertical, msg);

        CHECK(board.read(rand_y, rand_x, Direction::Vertical, 4) == msg);
        CHECK(board.read(rand_y, rand_x, Direction::Horizontal, 4) == "afff");
    }
}

// TEST_CASE("EVIL, TEST ON CONST BOARD") {
//     /**
//      * Given a const board, can you still read from it?
//      * posting should be illigal but not reading.
//      *
//      * this test can't fail but it might not compile.
//      * */

//     Board board;
//     board.post(123, 123, Direction::Horizontal, "abc");

//     const Board &ref = board;
//     CHECK(board.read(123, 123, Direction::Horizontal, 3) == ref.read(123, 123, Direction::Horizontal, 3));
//     CHECK(board.read(123, 123, Direction::Vertical, 3) == ref.read(123, 123, Direction::Vertical, 3));
// }

TEST_CASE("END OF THE INTEGER") {
    /**
     * this test check's whether the board is indeed infinite.
     * a.k.a it should be possible to read from -1 the last index.
     * */

    string empty = "";
    for (unsigned int i = 1; i < number_of_tests; i++) {
        Board board;
        unsigned int rand_y = (unsigned int)rand();
        unsigned int rand_x = (unsigned int)rand();

        unsigned int max_v = (unsigned int)(-1);

        empty += "_";
        CHECK(board.read(rand_y, max_v, Direction::Vertical, i) == empty);
        CHECK(board.read(max_v, rand_x, Direction::Vertical, i) == empty);

        // POST on the edge of the screen!
        board.post(rand_y, max_v, Direction::Vertical, "abc");
        CHECK(board.read(rand_y, max_v, Direction::Vertical, 3) == "abc");

        board.post(max_v, rand_x, Direction::Horizontal, "abc");
        CHECK(board.read(max_v, rand_x, Direction::Horizontal, 3) == "abc");
    }
}

/* Add more test cases here */