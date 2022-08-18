#pragma once
#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GameMap
{
 public:
  int                  w, h;        // ブロックの個数
  int                  block_size;  // 1ブロックの幅・高さ
  vector<vector<char>> game_map;    // 現在のゲームマップ
  vector<GLfloat>      vertexes;  // シェーダに渡す用の頂点データ
  vector<GLfloat>      colors;    // シェーダに渡す用の色データ
  void                 update_vertexes_and_colors();
  vector<GLfloat>      position(int x_idx, int y_idx);
  void                 init_game_map();  // ゲームマップの初期化
  int                  screen_w();       // ウインドウの幅を返す
  int                  screen_h();       // ウインドウの高さを返す
  GameMap(int block_size);
};
