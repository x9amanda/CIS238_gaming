#include <iostream>
#include "Actor.h"

int main() {
    Actor actor(5,6);

    actor.restart();

    actor.run(100, 1000);

    actor.run(10, 100);

    actor.run(1, 1);

    actor.restart();
}