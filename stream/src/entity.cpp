#include "entity.hpp"

static Point entities[TOTAL_ENTITIES] =
{
  {  64,  64 },  // player
  {  64,  64 },  // monster
  {   0,   0 },  // fists
  {  64,  64 },  // dagger
  { 192, 192 },  // longsword
  { 192, 192 },  // spear
  {  64,  64 },  // 
  {  64,  64 },  //  
  {  64,  64 },  // tiles
  {  64,  64 },  //  
  {  64,  64 },  //  
  {  64,  64 },  //
  { 190,  49 }   // menu_button
};

Rect entity_body_at(int x, int y, int id)
{
  return entity_body_at(point(x, y), id);
}

Rect entity_body_at(Point p, int id)
{
  return { p.x, p.y, entity_width(id), entity_height(id) };
}

int  entity_width(int id)
{
  return entities[id].x;
}

int entity_height(int id)
{
  return entities[id].y;
}
