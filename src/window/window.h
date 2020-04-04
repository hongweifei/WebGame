

#include <SDL2/SDL.h>
#include "renderer.h"

#ifndef WINDOW
#define WINDOW

#define WINDOWPOS_CENTERED  SDL_WINDOWPOS_CENTERED
#define WINDOWPOS_UNDEFINED SDL_WINDOWPOS_UNDEFINED

#define WINDOW_FULLSCREEN           0x00000001      /**< fullscreen window */
#define WINDOW_OPENGL               0x00000002      /**< window usable with OpenGL context */
#define WINDOW_SHOWN                0x00000004      /**< window is visible */
#define WINDOW_HIDDEN               0x00000008      /**< window is not visible */
#define WINDOW_BORDERLESS           0x00000010      /**< no window decoration */
#define WINDOW_RESIZABLE            0x00000020      /**< window can be resized */
#define WINDOW_MINIMIZED            0x00000040      /**< window is minimized */
#define WINDOW_MAXIMIZED            0x00000080      /**< window is maximized */
#define WINDOW_INPUT_GRABBED        0x00000100      /**< window has grabbed input focus */
#define WINDOW_INPUT_FOCUS          0x00000200      /**< window has input focus */
#define WINDOW_MOUSE_FOCUS          0x00000400      /**< window has mouse focus */
#define WINDOW_FULLSCREEN_DESKTOP   ( SDL_WINDOW_FULLSCREEN | 0x00001000 )
#define WINDOW_FOREIGN              0x00000800      /**< window not created by SDL */

#define WINDOW_ALLOW_HIGHDPI        0x00002000      /**< window should be created in high-DPI mode if supported. */
                                                    /**  On macOS NSHighResolutionCapable must be set true in the */
                                                    /**  application's Info.plist for this to have any effect. */

#define WINDOW_MOUSE_CAPTURE        0x00004000      /**< window has mouse captured (unrelated to INPUT_GRABBED) */
#define WINDOW_ALWAYS_ON_TOP        0x00008000      /**< window should always be above others */
#define WINDOW_SKIP_TASKBAR         0x00010000      /**< window should not be added to the taskbar */
#define WINDOW_UTILITY              0x00020000      /**< window should be treated as a utility window */
#define WINDOW_TOOLTIP              0x00040000      /**< window should be treated as a tooltip */
#define WINDOW_POPUP_MENU           0x00080000      /**< window should be treated as a popup menu */
#define WINDOW_VULKAN               0x10000000      /**< window usable for Vulkan surface */


#define MouseMotion SDL_MouseMotionEvent

typedef void(*RenderEvent)(Renderer*);//渲染事件
typedef void(*Event)(void);//普通事件

typedef void(*MouseMotionEvent)(MouseMotion);//
typedef void(*MouseButtonEvent)(MouseMotion);//鼠标按钮事件
typedef void(*MouseWheelEvent)(MouseMotion);//

typedef struct
{
    const char *title;
    int x,y;
    int width,height;

    SDL_Window *w;

    Renderer *renderer;
    RenderEvent render;

    MouseMotionEvent mouse_motion;
    MouseButtonEvent mouse_button_down;
    MouseButtonEvent mouse_button_up;
    MouseWheelEvent mouse_wheel;

    Event *event;
    int event_n;
}Window;

Window *WindowInit(const char *title,int x,int y,int width,int height);//初始化
void WindowCreate(Window *window,Uint32 flags);//创建窗口
void WindowDestroy(Window *window);//销毁窗口

void SetWindowRenderer(Window *window,Renderer *renderer);//设置窗口渲染器

/*设置窗口各种事件*/
void SetWindowRenderEvent(Window *window,RenderEvent render);//设置窗口渲染事件
void SetMouseMotionEvent(Window *window,MouseMotionEvent mouse_motion);//
void SetMouseButtonDownEvent(Window *window,MouseButtonEvent mouse_button_down);
void SetMouseButtonUpEvent(Window *window,MouseButtonEvent mouse_button_up);
void SetMouseWheelEvent(Window *window,MouseWheelEvent mouse_wheel);

/*添加普通事件*/
void AddWindowEvent(Window *window,Event event);

/*窗口循环*/
void WindowMainLoop(Window *window);
void WindowsMainLoop(int window_n,...);
int WebMainLoop(Window *window);

/*退出*/
void Quit();



#endif
