#include <SFML/Graphics.hpp>
#include <fstream>
#include <time.h>
using namespace sf;

int field[50][50][50] = {0};

int &f(int x, int y, int z) { return field[y + 2][x + 2][z]; }
int &f(Vector3i v) { return f(v.x, v.y, v.z); }

int main()
{
  srand(time(0));

  RenderWindow app(VideoMode(740, 570), "Mahjong Solitaire!");

  Texture t1, t2;
  t1.loadFromFile("files/tiles.png");
  t2.loadFromFile("files/background.png");
  Sprite s(t1), sBackground(t2);
  int w = 48, h = 66;
  int stepX = w / 2 - 2, stepY = h / 2 - 2;

  ////load from file////
  std::fstream myfile("files/map.txt");
  for (int y = 0; y < 18; y++)
    for (int x = 0; x < 30; x++)
    {
      char a;
      myfile >> a;
      int n = a - '0';
      for (int z = 0; z < n; z++)
        if (f(x - 1, y - 1, z))
          f(x - 1, y, z) = f(x, y - 1, z) = 0;
        else
          f(x, y, z) = 1;
    }

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
    for (int z = 0; z < 10; z++)
      for (int x = 30; x >= 0; x--)
        for (int y = 0; y < 18; y++)
        {
          int k = f(x, y, z);
          if (k == 0)
            continue;
          s.setTextureRect(IntRect(42 * w, 0, w, h));
          s.setPosition(x * stepX, y * stepY);
          s.move(30, 0); //desk offset
          app.draw(s);
        }

    app.display();
  }

  return 0;
}
