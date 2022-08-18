#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <chrono>
#include <iostream>
#include <vector>

#include "Block.h"
#include "Blocks.h"
#include "GameMap.h"
using namespace std;
using namespace std::chrono;

const int   BLOCK_SIZE    = 25;   // 1ブロックの幅・高さ
const float FALL_INTERVAL = 300;  // 下落の時間間隔（ミリ秒）

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
  void  update_vertexes_and_colors();
  float time_after_fall();  // 前回の下落からの経過時間（秒）
  void  fall();             // ブロックを下落させる

 private:
  system_clock::time_point falling_time;
};
