#include <iostream>
#include "Actor.h"

/* assigns a to member data x, and b to member data y */
Actor::Actor(int a, int b) {
    x = a;
    y = b;
}

void Actor::restart() {
    std::cout << "The game has been reset\n";
    std::cout << "Good luck next time!\n";
}

int Actor::run(int a, int b) {
    x = a;
    y = b;
    std::cout << "The player is now in location ("
        << x << ", " << y << ").\n";

    return 7;
}