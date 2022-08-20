#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <vector>

#include "Block.h"
#include "Blocks.h"
#include "Game.h"
using namespace std;
using namespace std::chrono;

Game::Game(vector<int>& _inputs)
    : inputs(_inputs)
    , now_blocks(random_blocks(6, 0))
    , next_blocks(random_blocks(0, 0))
    , gamemap(GameMap(BLOCK_SIZE))
    , falling_time(system_clock::now())
{}

float Game::time_after_fall()
{
  system_clock::time_point now = system_clock::now();
  return duration_cast<milliseconds>(now - falling_time).count();
}

void Game::update()
{
  if (inputs[GLFW_KEY_A] > 0 && inputs[GLFW_KEY_D] > 0) {
    inputs[GLFW_KEY_A] = 0;
    inputs[GLFW_KEY_D] = 0;
  } else if (inputs[GLFW_KEY_A] > 0) {
    inputs[GLFW_KEY_A]          = 0;
    vector<vector<int>> indexes = now_blocks.block_indexes();
    if (! is_collistion_blocks(indexes, -1, 0)) {
      now_blocks.go_left();
    }
  } else if (inputs[GLFW_KEY_D] > 0) {
    inputs[GLFW_KEY_D]          = 0;
    vector<vector<int>> indexes = now_blocks.block_indexes();
    if (! is_collistion_blocks(indexes, 1, 0)) {
      now_blocks.go_right();
    }
  }
  if (time_after_fall() < FALL_INTERVAL) {
    if (inputs[GLFW_KEY_S] > 0) {
      inputs[GLFW_KEY_S]          = 0;
      vector<vector<int>> indexes = now_blocks.block_indexes();
      if (! is_collistion_blocks(indexes, 0, 1)) {
        now_blocks.fall();
      }
    }
  } else {
    fall();
    return;
  }

  if (inputs[GLFW_KEY_Q] > 0 && inputs[GLFW_KEY_E] > 0) {
    inputs[GLFW_KEY_Q] = 0;
    inputs[GLFW_KEY_E] = 0;
  } else if (inputs[GLFW_KEY_Q] > 0 || inputs[GLFW_KEY_E] > 0) {
    inputs[GLFW_KEY_Q]               = 0;
    inputs[GLFW_KEY_E]               = 0;
    int                  vec         = inputs[GLFW_KEY_Q] > 0 ? -1 : 1;
    vector<vector<char>> rotated_map = now_blocks.rotated_map(vec);
    if (! is_collistion_rotated_blocks(rotated_map)) {
      now_blocks.rotate(rotated_map);
    }
  }
}

void Game::delete_block_lines()
{
  vector<int> deletable_rows = gamemap.deletable_rows();
  int         row_num        = deletable_rows.size();
  if (row_num == 0) return;
  cout << row_num << "deleted!" << endl;
  gamemap.delete_rows(deletable_rows);
}

void Game::fall()
{
  inputs[GLFW_KEY_S]          = 0;
  vector<vector<int>> indexes = now_blocks.block_indexes();
  if (is_collistion_blocks(indexes, 0, 1)) {
    fix_blocks(indexes);
    next_blocks_to_now_blocks();
    delete_block_lines();
  } else {
    now_blocks.fall();
  }
  falling_time = system_clock::now();
}

bool Game::is_collistion_rotated_blocks(vector<vector<char>> rotated_map)
{
  for (int y_idx = 0; y_idx < rotated_map.size(); y_idx++) {
    for (int x_idx = 0; x_idx < rotated_map[0].size(); x_idx++) {
      if (rotated_map[y_idx][x_idx] != '.') {
        if (gamemap.is_collision(x_idx + now_blocks.x, y_idx + now_blocks.y, 0, 0)) return true;
      }
    }
  }
  return false;
}

bool Game::is_collistion_blocks(vector<vector<int>> indexes, int x_vec, int y_vec)
{
  for (vector<int> xy : indexes) {
    if (gamemap.is_collision(xy[0], xy[1], x_vec, y_vec)) return true;
  }
  return false;
}

void Game::fix_blocks(vector<vector<int>> indexes)
{
  for (int i = 0; i < indexes.size(); i++) {
    int  x_idx = indexes[i][0];
    int  y_idx = indexes[i][1];
    char c     = now_blocks.blocks_type.blocks_map[y_idx - now_blocks.y][x_idx - now_blocks.x];
    gamemap.game_map[y_idx][x_idx] = c;
  }
}

void Game::next_blocks_to_now_blocks()
{
  next_blocks.x = 6;
  now_blocks    = next_blocks;
  next_blocks   = random_blocks(0, 0);
}

Blocks Game::random_blocks(int x, int y)
{
  random_device rnd;
  return Blocks(x, y, rnd() % 5);
}

map<string, vector<GLfloat>> Game::update_vertexes_and_colors()
{
  vector<GLfloat> _vertexes;
  vector<GLfloat> _colors;
  gamemap.update_vertexes_and_colors();
  _vertexes = gamemap.vertexes;
  _colors   = gamemap.colors;
  int                   y_idx, x_idx, _x_idx, _y_idx;
  char                  c;
  vector<vector<char>>& now_map  = now_blocks.blocks_type.blocks_map;
  vector<vector<char>>& next_map = next_blocks.blocks_type.blocks_map;
  for (_y_idx = 0; _y_idx < now_map.size(); _y_idx++) {
    for (_x_idx = 0; _x_idx < now_map[0].size(); _x_idx++) {
      c     = now_map[_y_idx][_x_idx];
      x_idx = _x_idx + now_blocks.x;
      y_idx = _y_idx + now_blocks.y;
      gamemap.insert_vertexes_and_colors(x_idx, y_idx, c, _vertexes, _colors);
    }
  }
  for (_y_idx = 0; _y_idx < next_map.size(); _y_idx++) {
    for (_x_idx = 0; _x_idx < next_map[0].size(); _x_idx++) {
      c     = next_map[_y_idx][_x_idx];
      x_idx = _x_idx + next_blocks.x;
      y_idx = _y_idx + next_blocks.y;
      gamemap.insert_vertexes_and_colors(x_idx, y_idx, c, _vertexes, _colors);
    }
  }
  return map<string, vector<GLfloat>> {
    {"vertexes", _vertexes},
    {  "colors",   _colors},
  };
}

void Game::display_map_in_terminal()
{
  system("clear");
  for (int i = 0; i < gamemap.game_map.size(); i++) {
    for (int j = 0; j < gamemap.game_map[0].size(); j++) {
      cout << gamemap.game_map[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}
