#ifndef ENTITY_HPP
#define ENTITY_HPP

#define TOTAL_ENTITIES 13

#include "data_structs.hpp"

/*
 * Holds all the basic information about a particular entity. 
 */

Rect entity_body_at(int id, int x, int y);
Rect entity_body_at(Point p, int y);
int  entity_width(int id);
int  entity_height(int id);

enum Entity
{
  /* entities */
  PLAYER = 0,
  MONSTER,

  /* weapons */
  FISTS,
  DAGGER,
  LONGSWORD,
  SPEAR,

  /* tiles */
  TILE_FLOOR,
  TILE_TOP_LEFT,
  TILE_TOP_RIGHT,
  TILE_MID_TOP,
  TILE_MID_LEFT,
  TILE_MID_RIGHT,

  /* misc stuff */
  MENU_BUTTON
};

enum State
{
  UP     = 0,
  LEFT,
  DOWN,
  RIGHT,
  COMBAT = 4,
  DIE    = 8,
};

#endif
