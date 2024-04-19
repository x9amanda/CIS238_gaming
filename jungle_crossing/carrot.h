#include "Vector2.h" // Assuming you have a Vector2 class for 2D vectors

class Carrot {
public:
    // Constructors
    Carrot() : position(Vector2()), size(Vector2()), collected(false) {}
    Carrot(const Vector2& pos, const Vector2& s) : position(pos), size(s), collected(false) {}

    // Destructor
    ~Carrot() {}

    // Getters and setters
    Vector2 getPosition() const { return position; }
    void setPosition(const Vector2& pos) { position = pos; }

    Vector2 getSize() const { return size; }
    void setSize(const Vector2& s) { size = s; }

    bool isCollected() const { return collected; }
    void setCollected(bool value) { collected = value; }

private:
    Vector2 position; // Position of the carrot
    Vector2 size;     // Size of the carrot
    bool collected;   // Flag indicating whether the carrot has been collected
};