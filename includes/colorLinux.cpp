//
// Created by sieger on 5/29/16.
//

#include <iostream>

enum Color{
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,

    RESET = 0
};

void setColor(Color color){
    std::cout << "\033[" << color << "m";
}