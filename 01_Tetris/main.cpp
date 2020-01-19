#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct Point
{
  int x, y;
} a[4], b[4];

int figures[7][4] =
    {
        1, 3, 5, 7, // I
        2, 4, 5, 7, // Z
        3, 5, 4, 6, // S
        3, 5, 4, 7, // T
        2, 3, 5, 7, // L
        3, 5, 7, 6, // J
        2, 3, 4, 5, // O
};

int main()
{
  RenderWindow window(VideoMode(320, 480), "The Game!");

  Texture t1, t2, t3;
  t1.loadFromFile("images/tiles.png");
  t2.loadFromFile("images/background.png");
  t3.loadFromFile("images/frame.png");

  Sprite s(t1), background(t2), frame(t3);

  int colorNum = 1;
  int dx = 0;
  bool rotate = 0;

  while (window.isOpen())
  {
    Event e;
    while (window.pollEvent(e))
    {
      if (e.type == Event::Closed)
        window.close();

      if (e.type == Event::KeyPressed)
      {
        if (e.key.code == Keyboard::Up)
          rotate = true;
        else if (e.key.code == Keyboard::Left)
          dx = -1;
        else if (e.key.code == Keyboard::Right)
          dx = 1;
      }
    }

    //// <- Move -> ///
    for (int i = 0; i < 4; i++)
    {
      a[i].x += dx;
    }

    //////Rotate//////
    if (rotate)
    {
      //center of rotation
      Point p = a[1];
      // TODO
      for (int i = 0; i < 4; i++)
      {
        int x = a[i].y - p.y;
        int y = a[i].x - p.x;
        a[i].x = p.x - x;
        a[i].y = p.y + y;
      }
    }

    int n = 3;
    if (a[0].x == 0)
      for (int i = 0; i < 4; i++)
      {
        a[i].x = figures[n][i] % 2;
        a[i].y = figures[n][i] / 2;
      }
    dx = 0;
    rotate = 0;

    /////////draw//////////
    window.clear(Color::White);
    window.draw(background);

    for (int i = 0; i < 4; i++)
    {
      /**
       * sf::IntRect 클래스는 사각형을 표현하는 간단한 유틸리티 타입입니다.
       * IntRect(좌표x, 좌표y, 가로, 세로)
       * 이 클래스의 생성자는 왼쪽-위 모퉁이의 좌표와 사각형의 사이즈를 인자로 받습니다.
       * setTextureRect는 sprite를 잘라서 사용
       */
      s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
      // 초기화 되어있는 x, y에 대입하기
      s.setPosition(a[i].x * 18, a[i].y * 18);
      // 정사각형 바둑판으로 이동하기
      s.move(28, 31);
      window.draw(s);
    }
    window.draw(frame);
    window.display();
  }

  return 0;
}
