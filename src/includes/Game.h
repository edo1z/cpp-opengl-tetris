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
  vector<int>&    inputs;
  Blocks          now_blocks;
  Blocks          next_blocks;
  GameMap         gamemap;
  vector<GLfloat> vertexes;
  vector<GLfloat> colors;
  Blocks          random_blocks(int x, int y);
  Game(vector<int>& _inputs);
  void  update_vertexes_and_colors();
  float time_after_fall();  // 前回の下落からの経過時間（秒）
  void  update();
  void  fall();  // ブロックを下落させる
  bool  is_collistion_blocks(vector<vector<int>> indexes, int x_vec, int y_vec);
  bool  is_collistion_rotated_blocks(vector<vector<char>> rotated_map);
  void  fix_blocks(vector<vector<int>> indexes);
  void  next_blocks_to_now_blocks();

 private:
  system_clock::time_point falling_time;
};
