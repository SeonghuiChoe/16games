#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int N = 6;
int ts = 54; //tile size
Vector2f offset(65, 55);

struct pipe
{
  int orientation;
  bool on;
} grid[N][N];

int main()
{
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
    }

    app.clear();
    app.draw(sBackground);

    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
      {
        pipe &p = grid[j][i];
        sPipe.setTextureRect(IntRect(ts * 2, 0, ts, ts));
        sPipe.setRotation(p.orientation);
        sPipe.setPosition(j * ts, i * ts);
        sPipe.move(offset);
        app.draw(sPipe);
      }
    app.display();
  }

  return 0;
}
