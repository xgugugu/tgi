#include "tgi.hpp"

using namespace tgi;

Application app;
Window wnd;
Font font;

void TGICB on_paint(TGI_Window *_wnd)
{
    Window wnd(_wnd);
    Graphics g(wnd.create_graphics());
    g.clear(TGI_COLOR(255, 255, 255, 255));
    g.set_color(TGI_COLOR(255, 0, 255, 0));
    font.set_align(TGI_TEXTALIGN_CENTER);
    font.set_vertical_align(TGI_TEXTALIGN_CENTER);
    g.draw_text("ÄãºÃ£¬ÊÀ½ç£¡", font, 300, 300);
    g.free();
}

int main()
{
    app = Application::create(TGI_BACKEND_GDI, TGI_ENCODING_ANSI);
    wnd = app.create_window();
    font = app.create_font("Î¢ÈíÑÅºÚ", 64, TGI_FONTSTYLE_BOLD);
    wnd.set_size(600, 600);
    wnd.on_paint(on_paint);
    wnd.show();
    app.exec();
    wnd.free();
    app.free();
    return 0;
}