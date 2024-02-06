#include <iostream>

class Actor {

    public:
        /* constructor for an actor with an initial position */
        Actor(int, int);

        /* move the actor to a new coordinate location */
        int run(int x, int y);

        /* reset the game and move actor to initial position */
        void restart();

    private:
    // class member data
        int x;
        int y;
};