#include "tgi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TGI_Application *app;
TGI_Window *wnd;
TGI_Font *font;

void TGICB on_paint(TGI_Window *)
{
    TGI_Graphics *g = tgi_window_create_graphics(wnd);
    tgi_graphics_clear(g, TGI_COLOR(255, 255, 255, 255));
    tgi_graphics_set_color(g, TGI_COLOR(255, 0, 255, 0));
    tgi_font_set_align(font, TGI_TEXTALIGN_CENTER);
    tgi_font_set_vertical_align(font, TGI_TEXTALIGN_CENTER);
    tgi_graphics_draw_text(g, "你好，世界！", font, 300, 300);
}

int main()
{
    app = tgi_application_create(TGI_BACKEND_GDI, TGI_ENCODING_ANSI);
    wnd = tgi_application_create_window(app);
    font = tgi_application_create_font(app, "微软雅黑", 64, TGI_FONTSTYLE_BOLD);

    tgi_window_set_title(wnd, "你好");
    tgi_window_set_size(wnd, 600, 600);
    tgi_window_set_style(wnd, TGI_WindowStyle(TGI_WINDOWSTYLE_DEFAULT & ~TGI_WINDOWSTYLE_RESIZE & ~TGI_WINDOWSTYLE_MAXIMIZEBOX));
    tgi_window_on_paint(wnd, on_paint); 
    tgi_window_show(wnd);
    tgi_application_exec(app);

    tgi_font_free(font);
    tgi_window_free(wnd);
    tgi_application_free(app);
    return 0;
}
