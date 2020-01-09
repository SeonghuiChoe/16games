# How to compile
You have to install sfml and pkg-config.

```bash
brew install sfml pkg-config
g++ main.cpp $(pkg-config --libs --cflags sfml-window sfml-system sfml-graphics) -o main
```
