#pragma once
#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <string>
#include <vector>

class GameMap
{
 public:
  int               w, h;              // ブロックの個数
  int               size();            // マップ全体のブロック数
  std::vector<char> default_game_map;  // 初期状態のゲームマップ
  std::vector<char> game_map;          // 現在のゲームマップ
  GameMap(int _w, int _h, std::string _game_map);
  std::vector<GLfloat> position(int idx);
  void                 init_game_map();  // ゲームマップの初期化
  std::vector<GLfloat> vertexes;  // シェーダに渡す用の頂点データ
  std::vector<GLfloat> colors;    // シェーダに渡す用の色データ
  void                 update_vertexes_and_colors();
};
