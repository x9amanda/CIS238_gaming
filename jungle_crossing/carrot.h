struct Vector2
{
  float x;
  float y;
};

class Carrot
{
public:
  // Constructors
  Carrot() : carrotPosition(Vector2()), carrotSize(Vector2()), carrotCollected(false) {}
  Carrot(const Vector2 &pos, const Vector2 &s) : carrotPosition(pos), size(s), collected(false) {}

  // Destructor
  ~Carrot() {}

  // Getters and setters
  Vector2 getPosition() const { return carrotPosition; }
  void setPosition(const Vector2 &carrotPosition) { carrotPosition = carrotPosition; }

  Vector2 getSize() const { return size; }
  void setSize(const Vector2 &s) { size = s; }

  bool isCollected() const { return collected; }
  void setCollected(bool value) { collected = value; }

private:
  Vector2 carrotPosition; // Position of the carrot
  Vector2 size;           // Size of the carrot
  bool collected;         // Flag indicating whether the carrot has been collected
};