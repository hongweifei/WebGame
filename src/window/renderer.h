

#include <SDL2/SDL.h>

#ifndef RENDERER
#define RENDERER

#define RENDERER_SOFTWARE       SDL_RENDERER_SOFTWARE       //the renderer is a software fallback
#define RENDERER_ACCELERATED    SDL_RENDERER_ACCELERATED    //the renderer uses hardware acceleration
#define RENDERER_PRESENTVSYNC   SDL_RENDERER_PRESENTVSYNC   //present is synchronized with the refresh rate
#define RENDERER_TARGETTEXTURE  SDL_RENDERER_TARGETTEXTURE  //the renderer supports rendering to texture

typedef struct
{
    SDL_Renderer *r;
    Uint32 window_id;
}Renderer;

Renderer *RendererInit(SDL_Window *window,int index,Uint32 flags);//初始化


int SetRenderDrawColor(Renderer *renderer,Uint8 r,Uint8 g,Uint8 b,Uint8 a);//设置颜色


int RenderClear(Renderer *renderer);//清空
void RenderPresent(Renderer *renderer);//交换

int RenderCopy(Renderer *renderer,SDL_Texture *texture,SDL_Rect *src_rect,SDL_Rect *dst_rect);

#endif
