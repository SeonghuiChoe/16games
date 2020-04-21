#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
  RenderWindow window(VideoMode(504, 504), "The Chess! (press SPACE)");

  Texture t1;
  t1.loadFromFile("images/figures.png");

  Sprite s(t1);

  while (window.isOpen())
  {
    Event e;
    while (window.pollEvent(e))
    {
      if (e.type == Event::Closed)
        window.close();
    }
    window.clear();
    window.draw(s);
    window.display();
  }

  return 0;
}
