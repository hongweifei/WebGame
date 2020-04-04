


#include "renderer.h"

Renderer *RendererInit(SDL_Window *window,int index,Uint32 flags)//渲染器初始化
{
    Renderer *renderer = (Renderer*)calloc(1,sizeof(Renderer));
    renderer->r = SDL_CreateRenderer(window,index,flags);//创建SDL渲染器
    renderer->window_id = SDL_GetWindowID(window);//获取窗口id
    return renderer;
}

//设置渲染颜色
int SetRenderDrawColor(Renderer *renderer,Uint8 r,Uint8 g,Uint8 b,Uint8 a){return SDL_SetRenderDrawColor(renderer->r, r, g, b, a);}

//用渲染颜色清空
int RenderClear(Renderer *renderer){return SDL_RenderClear(renderer->r);}
//交换
void RenderPresent(Renderer *renderer){SDL_RenderPresent(renderer->r);}

int RenderCopy(Renderer *renderer,SDL_Texture *texture,SDL_Rect *src_rect,SDL_Rect *dst_rect)
{return SDL_RenderCopy(renderer->r,texture,src_rect,dst_rect);}

