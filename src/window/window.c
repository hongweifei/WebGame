


#include "window.h"


Window *WindowInit(const char *title,int x,int y,int width,int height)
{
    Window *window = (Window*)calloc(1,sizeof(Window));
    window->title = title;
    window->x = x;
    window->y = y;
    window->width = width;
    window->height = height;

    window->event = (Event*)calloc(0,sizeof(Event));
    window->event_n = 0;

    return window;
}

void WindowCreate(Window *window,Uint32 flags)//创建窗口
{
    window->w = SDL_CreateWindow(window->title,window->x,window->y,window->width,window->height,flags);
    window->renderer = RendererInit(window->w,-1,RENDERER_ACCELERATED);//初始化窗口渲染器
}

//销毁窗口
void WindowDestroy(Window *window)
{
    SDL_DestroyWindow(window->w);//销毁SDL窗口
    SDL_DestroyRenderer(window->renderer->r);//销毁SDL窗口SDL渲染器
    free(window->renderer);//释放窗口渲染器
    free(window);//释放窗口
}


void SetWindowRenderer(Window *window,Renderer *renderer){window->renderer = renderer;}//设置渲染器
void SetWindowRenderEvent(Window *window,RenderEvent render){window->render = render;}//设置渲染事件

/*设置各种事件*/
void SetMouseMotionEvent(Window *window,MouseMotionEvent mouse_motion){window->mouse_motion = mouse_motion;}
void SetMouseButtonDownEvent(Window *window,MouseButtonEvent mouse_button_down){window->mouse_button_down = mouse_button_down;}
void SetMouseButtonUpEvent(Window *window,MouseButtonEvent mouse_button_up){window->mouse_button_up = mouse_button_up;}
void SetMouseWheelEvent(Window *window,MouseWheelEvent mouse_wheel){window->mouse_wheel = mouse_wheel;}

/*添加普通事件*/
void AddWindowEvent(Window *window,Event event)
{
    window->event = (Event*)realloc(window->event,sizeof(window->event) + sizeof(event));
    window->event[window->event_n] = event;
    window->event_n++;
}

/*窗口循环*/
void WindowMainLoop(Window *window)
{
    int quit = 0;//退出为假

    while (!quit)//假则循环
        quit = WebMainLoop(window);//循环

    Quit();//退出
}

void WindowsMainLoop(int window_n,...) //window_n为窗口数量  窗口类型为 Window*
{
    #define WINDOWS_MAIN_LOOP

    int i;
    int quit = 0;                                       //退出真假
    int *destroy = (int*)calloc(window_n,sizeof(int));  //window销毁记录
    int destroy_n = 0;                                  //windows销毁数量

    Window *window[window_n];//各个窗口数据
    //SDL_Thread *window_thread[window_n];//各个窗口事件线程

    va_list window_list;//窗口列表
    va_start(window_list,window_n);

    for (i = 0; i < window_n; i++)
    {
        window[i] = va_arg(window_list,Window*);//将各个窗口的数据取出
    }

    va_end(window_list);

    while (!quit)//未退出
    {
        for (i = 0; i < window_n; i++)
        {
            if(!destroy[i])//窗口未销毁
            {
                //window_thread[i] = SDL_CreateThread(WebMainLoop,NULL,window[i]);//创建事件窗口线程

                destroy[i] = WebMainLoop(window[i]);//执行程序循环，并取得窗口销毁与否
                if(destroy[i])//窗口被销毁
                {
                    destroy_n++;//销毁窗口数++
                }
            }
        }
        if(destroy_n == window_n)//销毁窗口数等于总窗口数
            quit = 1;//退出为真
    }

    free(destroy);//释放销毁信息

    Quit();//退出
}

int WebMainLoop(Window *window)
{
    int quit = 0;//退出
    SDL_Event event;//事件

    if (SDL_PollEvent(&event))//获取事件
    {
        switch(event.type)//判断事件类型
        {
        case SDL_QUIT://退出事件
            SDL_Log("Program quit after %i ticks", event.quit.timestamp);
            quit = 1;//退出为真
            break;
        case SDL_USEREVENT:
            break;
        case SDL_WINDOWEVENT://窗口事件
            if(event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window->w))//窗口关闭，且id等于执行事件的窗口
            {
                WindowDestroy(window);//销毁窗口
                quit = 1;//退出
                return quit;//返回窗口已销毁，函数结束
            }

            #ifdef WINDOWS_MAIN_LOOP
            
            #endif
            break;
        /*鼠标事件*/
        case SDL_MOUSEMOTION:
            if(window->mouse_motion)
                window->mouse_motion(event.motion);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(window->mouse_button_down)
                window->mouse_button_down(event.motion);
            break;
        case SDL_MOUSEBUTTONUP:
            if(window->mouse_button_up)
                window->mouse_button_up(event.motion);
            break;
        case SDL_MOUSEWHEEL:
            if(window->mouse_wheel)
                window->mouse_wheel(event.motion);
            break;
        }
    }

    /*获取执行事件的窗口的坐标与大小*/
    SDL_GetWindowPosition(window->w,&window->x,&window->y);
    SDL_GetWindowSize(window->w,&window->width,&window->height);
        
    int i;
    for (i = 0; i < window->event_n; i++)
        window->event[i]();//执行窗口所有普通事件

    RenderClear(window->renderer);
    if(window->render)//渲染事件不为空
        window->render(window->renderer);//执行窗口渲染事件
    RenderPresent(window->renderer);//交换

    return quit;//返回程序是否结束，函数结束
}

/*退出*/
void Quit()
{
    SDL_Quit();
}