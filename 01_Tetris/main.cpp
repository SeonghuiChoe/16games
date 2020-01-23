#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;
using namespace std;

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

bool check()
{
  for (int i = 0; i < 4; i++)
    // The left-hand, right-hand and bottom-hand edge.
    if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
      return 0;
    // If there is tile.
    else if (field[a[i].y][a[i].x])
      return 0;

  return 1;
};

int main()
{
  srand(time(0));
  RenderWindow window(VideoMode(320, 480), "The Game!");

  Texture t1, t2, t3;
  t1.loadFromFile("images/tiles.png");
  t2.loadFromFile("images/background.png");
  t3.loadFromFile("images/frame.png");

  Sprite s(t1), background(t2), frame(t3);

  int colorNum = 1;
  int dx = 0;
  bool rotate = 0;
  float timer = 0, delay = 0.3;

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

      if (e.type == Event::KeyPressed)
      {
        if (e.key.code == Keyboard::Up)
          rotate = true;
        else if (e.key.code == Keyboard::Left)
          dx = -1;
        else if (e.key.code == Keyboard::Right)
          dx = 1;
        else if (e.key.code == Keyboard::Down)
          delay = 0.05;
      }
    }

    // Move
    for (int i = 0; i < 4; i++)
    {
      // 이동하기전에 원래 위치를 b에다가 저장
      b[i] = a[i];
      a[i].x += dx;
    }
    // 막다른 길이라면 원복
    if (!check())
      for (int i = 0; i < 4; i++)
        a[i] = b[i];

    // Rotate
    if (rotate)
    {
      // Center of rotation
      Point p = a[1];
      // TODO: I don't no how
      for (int i = 0; i < 4; i++)
      {
        int x = a[i].y - p.y;
        int y = a[i].x - p.x;
        a[i].x = p.x - x;
        a[i].y = p.y + y;
      }
      // 회전하려고 하는데 막다른 길이면 원복
      if (!check())
        for (int i = 0; i < 4; i++)
          a[i] = b[i];
    }

    // Tick
    if (timer > delay)
    {
      for (int i = 0; i < 4; i++)
      {
        b[i] = a[i];
        a[i].y += 1;
      }

      if (!check())
      {
        // 막다른 길이라면 컬러를 장소에 저장함
        for (int i = 0; i < 4; i++)
          field[b[i].y][b[i].x] = colorNum;

        // Random color 컬러 변경
        colorNum = 1 + rand() % 7;
        // Random shape 모양 변경
        int n = rand() % 7;
        for (int i = 0; i < 4; i++)
        {
          a[i].x = figures[n][i] % 2;
          a[i].y = figures[n][i] / 2;
        }
      }

      timer = 0;
    }

    dx = 0;
    rotate = 0;
    delay = 0.3;

    // Draw
    window.clear(Color::White);
    window.draw(background);

    // 쌓여있는 타일 그려줌
    for (int i = 0; i < M; i++)
      for (int j = 0; j < N; j++)
      {
        // 색이 저장되어있지 않다면 그리지 않음
        if (field[i][j] == 0)
          continue;
        // 저장되어 있는 색을 가져옴
        s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
        // 그려줌
        s.setPosition(j * 18, i * 18);
        s.move(28, 31); //offset
        window.draw(s);
      }

    // 새로운 타일 그려줌
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
