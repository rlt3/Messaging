#include "window.hpp"
#include "graphics.hpp"

#include <stdio.h>

static SDL_Renderer     *_renderer;
static SDL_Window       *_window;
static SDL_RendererInfo  _renderer_info;
static SDL_Event         _event;

static SDL_Texture *sprite_sheet[TOTAL_ENTITIES];
static SDL_Rect     sprite_dimen[TOTAL_ENTITIES];

/* internal (private) functions declared here */
void sprites_init();
void sprites_destroy();

void destroy_texture(SDL_Texture* texture);
int  texture_width(SDL_Texture* texture);

SDL_Texture* load_sprite(const char *filename);
SDL_Rect     make_offset(int x, int y, int id);


void create_window()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 
      SDL_WINDOW_SHOWN, &_window, &_renderer);
  SDL_GetRendererInfo(_renderer, &_renderer_info);

  //SDL_ShowCursor(SDL_DISABLE);

  sprites_init();
}

void clear_window()
{
  SDL_SetRenderDrawColor(_renderer, 122, 139, 140, 255);
  SDL_RenderClear(_renderer);
}

void render_window()
{
  SDL_RenderPresent(_renderer);
}

void destroy_window()
{
  sprites_destroy();
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  IMG_Quit();
  SDL_Quit();
}

int window_event()
{
  while (SDL_PollEvent(&_event)) {
    switch (_event.type) {
      case SDL_KEYDOWN:
        return KEYDOWN_EVENT;

      case SDL_KEYUP:
        return KEYUP_EVENT;

      case SDL_MOUSEMOTION:
        return MOUSEMOVE_EVENT;

      case SDL_MOUSEBUTTONDOWN:
        return MOUSECLICK_EVENT;

      case SDL_MOUSEBUTTONUP:
        return MOUSEUNCLICK_EVENT;

      default:
        break;
    }
  }

  return 0;
}

int key_event()
{
  switch(_event.key.keysym.sym) {
    case SDLK_ESCAPE: case SDL_QUIT:
      return QUIT_KEY;

    case SDLK_w:
      return W_KEY;

    case SDLK_a:
      return A_KEY;

    case SDLK_s:
      return S_KEY;

    case SDLK_d:
      return D_KEY;

    case SDLK_UP:
      return UP_KEY;

    case SDLK_LEFT:
      return LEFT_KEY;

    case SDLK_DOWN:
      return DOWN_KEY;

    case SDLK_RIGHT:
      return RIGHT_KEY;

    case SDLK_SPACE:
      return SPACE_KEY;

    default:
      break;
  }

  return 0;
}

Rect event_location()
{
  return { _event.motion.x, _event.motion.y, 1, 1 };
}

void draw_sprite(int id, int state, int frame, Point location)
{
  if (sprite_sheet[id] == NULL)
    return;

  int x_offset = sprite_dimen[id].x;
  int y_offset = sprite_dimen[id].y;
  int width    = sprite_dimen[id].w;
  int height   = sprite_dimen[id].h;

  SDL_Rect l = { location.x + x_offset, location.y + y_offset, width, height };
  SDL_Rect f = { frame * width, state * height, width, height };

  SDL_RenderCopy(_renderer, sprite_sheet[id], &f, &l);
}

void draw_sprite(int id, Point location)
{
  draw_sprite(id, 0, 0, location);
}

int num_sprite_frames(int id)
{
  if (!sprite_sheet[id])
    return 0;
  else
    return texture_width(sprite_sheet[id]) / sprite_dimen[id].w;
}

Rect sprite_size(int id)
{
  Rect r = { 0, 0, sprite_dimen[id].w, sprite_dimen[id].h };
  return r;
}

void set_draw_color(int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void draw_rect(int x, int y, int w, int h)
{
  SDL_Rect r = { x, y, w, h };
  SDL_RenderFillRect(_renderer, &r); 
}

void draw_rect(SDL_Rect r)
{
  SDL_RenderFillRect(_renderer, &r); 
}

SDL_Texture* load_sprite(const char *filename)
{
  SDL_Texture* s = IMG_LoadTexture(_renderer, filename);

  if (s == NULL)
    printf("error: %s\n", IMG_GetError());

  return s;
}

int texture_width(SDL_Texture* texture)
{
  int w;
  SDL_QueryTexture(texture, NULL, NULL, &w, NULL);
  return w;
}

void destroy_texture(SDL_Texture* texture)
{
  SDL_DestroyTexture(texture);
}

SDL_Rect make_offset(int x, int y, int id)
{
  Rect r = entity_body_at(x, y, id);
  return { r.x, r.y, r.w, r.h };
}

void sprites_init()
{
  /* 
   * make_offset combines an x, y point and the w, h of the entity_id passed
   * and translates it to a Rect: { x, y, w, h }.  Here the x, y represent the
   * x, y offsets for where the sprite should be drawn.  w, h represent normal
   * width and height.
   */

  sprite_sheet[PLAYER]      = load_sprite("player.png");
  sprite_dimen[PLAYER]      = make_offset(0, 0, PLAYER);

  sprite_sheet[MONSTER]     = load_sprite("enemy.png");
  sprite_dimen[MONSTER]     = make_offset(0, 0, MONSTER);

  sprite_sheet[FISTS]       = NULL;
  sprite_dimen[FISTS]       = make_offset(0, 0, FISTS);

  sprite_sheet[DAGGER]   = load_sprite("dagger.png");
  sprite_dimen[DAGGER]   = make_offset(0, 0, DAGGER);

  sprite_sheet[LONGSWORD]   = load_sprite("longsword.png");
  sprite_dimen[LONGSWORD]   = make_offset(-64, -64, LONGSWORD);

  sprite_sheet[SPEAR]   = load_sprite("spear.png");
  sprite_dimen[SPEAR]   = make_offset(-64, -64, SPEAR);

  sprite_sheet[TILE_FLOOR]  = load_sprite("floor.png");
  sprite_dimen[TILE_FLOOR]  = make_offset(0, 0, TILE_FLOOR);

  sprite_sheet[TILE_TOP_LEFT]   = load_sprite("wall-top-left.png");
  sprite_dimen[TILE_TOP_LEFT]   = make_offset(0, 0, TILE_TOP_LEFT);

  sprite_sheet[TILE_TOP_RIGHT]  = load_sprite("wall-top-right.png");
  sprite_dimen[TILE_TOP_RIGHT]  = make_offset(0, 0, TILE_TOP_RIGHT);

  sprite_sheet[TILE_MID_TOP]    = load_sprite("wall-top-middle.png");
  sprite_dimen[TILE_MID_TOP]    = make_offset(0, 0, TILE_MID_TOP);

  sprite_sheet[TILE_MID_LEFT]   = load_sprite("wall-middle-left.png");
  sprite_dimen[TILE_MID_LEFT]   = make_offset(0, 0, TILE_MID_LEFT);

  sprite_sheet[TILE_MID_RIGHT]  = load_sprite("wall-middle-right.png");
  sprite_dimen[TILE_MID_RIGHT]  = make_offset(0, 0, TILE_MID_RIGHT);

  sprite_sheet[MENU_BUTTON]     = load_sprite("start.png");
  sprite_dimen[MENU_BUTTON]     = make_offset(0, 0, MENU_BUTTON);
}

void sprites_destroy()
{
  int i;
  for (i = 0; i < TOTAL_ENTITIES; i++)
  {
    destroy_texture(sprite_sheet[i]);
    sprite_sheet[i] = NULL;
  }
}
