#pragma once
#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <string>
#include <vector>

#include "Block.h"

using namespace std;
const int BOTTOM_ROWS   = 1;  // 底の行数
const int GAMEOVER_LINE = 4;  // ゲームオーバになる行（yのindex）

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
  int                  map_w();          // マップの横のvector要素数
  int                  map_h();          // マップの縦のvector要素数
  vector<GLfloat>      position(int x_idx, int y_idx);
  Block                block_from_index_and_char(int x, int y, char c);
  vector<GLfloat>      vertexes_of_map(vector<vector<char>>& m);
  vector<GLfloat>      colors_of_map(vector<vector<char>>& m);
  bool                 is_collision(int x_idx, int y_idx, int x_vec, int y_vec);
  vector<int>          deletable_rows();  // 削除可能な行のindexを返す
  void                 delete_rows(vector<int> deletable_rows);
  GameMap(int block_size);
};
