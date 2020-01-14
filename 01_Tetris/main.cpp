#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

struct Point
{
  int x, y;
} a[4], b[4];

int main()
{

  RenderWindow window(VideoMode(320, 480), "The Game!");

  Texture t1, t2, t3;
  t1.loadFromFile("images/tiles.png");
  t2.loadFromFile("images/background.png");
  t3.loadFromFile("images/frame.png");

  Sprite s(t1), background(t2), frame(t3);

  int colorNum = 1;

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

    /**
     * sf::IntRect 클래스는 사각형을 표현하는 간단한 유틸리티 타입입니다.
     * IntRect(좌표x, 좌표y, 가로, 세로)
     * 이 클래스의 생성자는 왼쪽-위 모퉁이의 좌표와 사각형의 사이즈를 인자로 받습니다.
     * setTextureRect는 sprite를 잘라서 사용
     */
    s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
    // 초기화 되어있는 x, y에 대입하기
    s.setPosition(0, 0);
    // 정사각형 바둑판으로 이동하기
    s.move(28, 31);
    window.draw(s);
    window.draw(frame);
    window.display();
  }

  return 0;
}
