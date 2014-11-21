#include "Graphics.hpp"

SDL_Renderer     * Graphics::_renderer;
SDL_Window       * Graphics::_window;
SDL_RendererInfo   Graphics::_renderer_info;

Graphics::Graphics(Messageable *g) : _game(g)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, 
      &Graphics::_window, &Graphics::_renderer);
  SDL_GetRendererInfo(Graphics::_renderer, &Graphics::_renderer_info);
}

Graphics::~Graphics()
{
  SDL_DestroyWindow(Graphics::_window);
  SDL_Quit();
}

void Graphics::message(const Message &msg)
{
  switch (msg.type) {
    case RENDER: 
      /* clear the screen, go `up the stack', and then present */
      _clear();
      notify(msg.sender, Message(this, DRAW));
      _render();

    default:
      break;
  }
}

void Graphics::_clear()
{
  SDL_SetRenderDrawColor(Graphics::_renderer, 128, 128, 128, 255);
  SDL_RenderClear(Graphics::_renderer);
}

void Graphics::_render()
{
  SDL_RenderPresent(Graphics::_renderer);
}
