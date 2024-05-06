#include "CollisionHandler.h"

bool CheckCollision(const Vector2& posA, const Vector2& posB, int widthA, int heightA, int widthB, int heightB) {
    if (posA.x < posB.x + widthB &&
        posA.x + widthA > posB.x &&
        posA.y < posB.y + heightB &&
        posA.y + heightA > posB.y) {
        return true;
    }
    return false;
}