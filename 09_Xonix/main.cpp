#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int M = 25;
const int N = 40;

int grid[M][N] = {0};
int ts = 18; //tile size

int main()
{
  srand(time(0));

  RenderWindow window(VideoMode(N * ts, M * ts), "Xonix Game!");
  window.setFramerateLimit(60);

  Texture t1;
  t1.loadFromFile("images/tiles.png");

  Sprite sTile(t1);

  int x = 0, y = 0, dx = 0, dy = 0;
  float timer = 0, delay = 0.07;
  Clock clock;

  while (window.isOpen())
  {
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;

    Event e;
    while (window.pollEvent(e))
    {
      if (e.type == Event::Closed)
        window.close();
    }

    if (e.key.code == Keyboard::Left) { dx = -1; dy = 0; }
    if (e.key.code == Keyboard::Right) { dx = 1; dy = 0; }
    if (e.key.code == Keyboard::Up) { dx = 0; dy = -1; }
    if (e.key.code == Keyboard::Down) { dx = 0; dy = 1; }

    if (timer > delay)
    {
      x += dx;
      y += dy;
      timer = 0;
    }

    /////////draw//////////
    window.clear();

    sTile.setTextureRect(IntRect(36, 0, ts, ts));
    sTile.setPosition(x * ts, y * ts);
    window.draw(sTile);

    window.display();
  }

  return 0;
}
