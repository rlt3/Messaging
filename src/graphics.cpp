#include "graphics.hpp"
#include <stdio.h>

static SDL_Renderer     *_renderer;
static SDL_Window       *_window;
static SDL_RendererInfo  _renderer_info;
static SDL_Event         _event;

void create_window()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 
      SDL_WINDOW_SHOWN, &_window, &_renderer);
  SDL_GetRendererInfo(_renderer, &_renderer_info);

  SDL_ShowCursor(SDL_DISABLE);
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

SDL_Rect event_location()
{
  /* return 1, 1 because that's the most accurate bounding box for mouse */
  return { _event.motion.x, _event.motion.y, 1, 1 };
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

void set_draw_color(int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

SDL_Texture* load_sprite(const char *filename)
{
  SDL_Texture* s = IMG_LoadTexture(_renderer, filename);

  if (s == NULL)
    printf("error: %s\n", IMG_GetError());

  return s;
}

void draw_sprite(Spritesheet sprite, Rect frame, Rect location)
{
  SDL_RenderCopy(_renderer, sprite, &frame, &location);
}

void draw_sprite(Spritesheet sprite, Rect location)
{
  SDL_RenderCopy(_renderer, sprite, NULL, &location);
}

SDL_Rect rect(int x, int y, int w, int h)
{
  SDL_Rect r = { x, y, w, h };
  return r;
}

void draw_rect(int x, int y, int w, int h)
{
  SDL_Rect r = { x, y, w, h };
  SDL_RenderFillRect(_renderer, &r); 
}

void draw_rect(Rect r)
{
  SDL_RenderFillRect(_renderer, &r); 
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

void destroy_window()
{
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  IMG_Quit();
  SDL_Quit();
}
