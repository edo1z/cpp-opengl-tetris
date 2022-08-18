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
  int                  w, h;             // ブロックの個数
  int                  block_size;       // 1ブロックの幅・高さ
  vector<vector<char>> game_map;         // 現在のゲームマップ
  vector<GLfloat>      vertexes;         // シェーダに渡す用の頂点データ
  vector<GLfloat>      colors;           // シェーダに渡す用の色データ
  void                 init_game_map();  // ゲームマップの初期化
  int                  screen_w();       // ウインドウの幅を返す
  int                  screen_h();       // ウインドウの高さを返す
  void                 insert_vertexes_and_colors(
                      int x_idx, int y_idx, char c, vector<GLfloat>& vertexes, vector<GLfloat>& colors);
  void            update_vertexes_and_colors();
  vector<GLfloat> position(int x_idx, int y_idx);
  bool is_collision(int x_idx, int y_idx, int x_vec, int y_vec);  // 衝突しているか？
  GameMap(int block_size);
};
