#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{

  RenderWindow window(VideoMode(320, 480), "The Game!");

  Texture t1, t2, t3;
  t1.loadFromFile("images/tiles.png");
  t2.loadFromFile("images/background.png");
  t3.loadFromFile("images/frame.png");

  Sprite s(t1), background(t2), frame(t3);

  while (window.isOpen())
  {
    Event e;
    while (window.pollEvent(e))
    {
      if (e.type == Event::Closed)
        window.close();
    }

    /////////draw//////////
    window.clear(Color::White);
    window.draw(background);
    window.draw(s);
    window.draw(frame);
    window.display();
  }

  return 0;
}
