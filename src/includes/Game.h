#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <chrono>
#include <iostream>
#include <map>
#include <vector>

#include "Block.h"
#include "Blocks.h"
#include "GameMap.h"
using namespace std;
using namespace std::chrono;

const int   BLOCK_SIZE    = 25;   // 1ブロックの幅・高さ
const float FALL_INTERVAL = 200;  // 下落の時間間隔（ミリ秒）

class Game
{
 public:
  vector<int>& inputs;
  Blocks       now_blocks;
  Blocks       next_blocks;
  GameMap      gamemap;
  Blocks       random_blocks(int x, int y);
  Game(vector<int>& _inputs);
  vector<vector<char>> merged_map();
  vector<GLfloat>      vertexes(vector<vector<char>>& merged_map);
  vector<GLfloat>      colors(vector<vector<char>>& merged_map);
  void                 display_map_in_terminal(vector<vector<char>>& merged_map);
  float                time_after_fall();  // 前回の下落からの経過時間（秒）
  void                 update();
  void                 delete_block_lines();
  void                 fall();  // ブロックを下落させる
  bool                 is_collistion_blocks(vector<vector<int>> indexes, int x_vec, int y_vec);
  bool                 is_collistion_rotated_blocks(vector<vector<char>> rotated_map);
  void                 fix_blocks(vector<vector<int>> indexes);
  void                 next_blocks_to_now_blocks();

 private:
  system_clock::time_point falling_time;
};
