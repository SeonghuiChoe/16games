#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int N = 6;
int ts = 54; //tile size
Vector2f offset(65, 55);

struct pipe
{
  int orientation;
  float angle;
  bool on;

  pipe() { angle = 0; }
} grid[N][N];

int main()
{
  srand(time(0));

  RenderWindow app(VideoMode(390, 390), "The Pipe Puzzle!");

  Texture t1, t2;
  t1.loadFromFile("images/background.png");
  t2.loadFromFile("images/pipes.png");

  Sprite sBackground(t1), sPipe(t2);
  sPipe.setOrigin(27, 27);

  while (app.isOpen())
  {
    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed)
        app.close();

      if (e.type == Event::MouseButtonPressed)
        if (e.mouseButton.button == Mouse::Left)
        {
          Vector2i pos = Mouse::getPosition(app) + Vector2i(ts / 2, ts / 2) - Vector2i(offset);
          pos /= ts;
          grid[pos.x][pos.y].orientation++;
        }
    }

    app.clear();
    app.draw(sBackground);

    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
      {
        pipe &p = grid[j][i];

        p.angle += .05;
        if (p.angle > p.orientation * 90)
          p.angle = p.orientation * 90;
        sPipe.setTextureRect(IntRect(ts * 2, 0, ts, ts));
        sPipe.setRotation(p.angle);
        sPipe.setPosition(j * ts, i * ts);
        sPipe.move(offset);
        app.draw(sPipe);
      }
    app.display();
  }

  return 0;
}
