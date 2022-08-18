#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <vector>

#include "Block.h"
#include "Blocks.h"
#include "GameMap.h"
using namespace std;

const int BLOCK_SIZE = 25;  // 1ブロックの幅・高さ

class Game
{
 public:
  Blocks          now_blocks;
  Blocks          next_blocks;
  GameMap         gamemap;
  vector<GLfloat> vertexes;
  vector<GLfloat> colors;
  Blocks          random_blocks(int x, int y);
  Game();
  void update_vertexes_and_colors();
};
