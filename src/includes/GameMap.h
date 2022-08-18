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
  int             w, h;              // ブロックの個数
  vector<char>    default_game_map;  // 初期状態のゲームマップ
  vector<char>    game_map;          // 現在のゲームマップ
  vector<GLfloat> vertexes;  // シェーダに渡す用の頂点データ
  vector<GLfloat> colors;    // シェーダに渡す用の色データ
  void            update_vertexes_and_colors();
  int             size();  // マップ全体のブロック数
  vector<GLfloat> position(int idx);
  void            init_game_map();  // ゲームマップの初期化
  GameMap(int _w, int _h, string _game_map);
};
