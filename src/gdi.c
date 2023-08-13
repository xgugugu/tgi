#include "gdi.h"

#include "tgi.h"

#ifdef __WIN32

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>

#include <gdiplus.h>
#include <versionhelpers.h>

wchar_t *tgi_gdi_codecvt(TGI_Encoding encoding, const char *in_str)
{
    int ec = (encoding == TGI_ENCODING_ANSI ? CP_ACP : CP_UTF8);
    int len = MultiByteToWideChar(ec, 0, in_str, -1, NULL, 0);
    wchar_t *wstr = malloc((len + 1) * sizeof(wchar_t));
    MultiByteToWideChar(ec, 0, in_str, -1, wstr, len + 1);
    return wstr;
}
char *tgi_gdi_codecvt2(TGI_Encoding encoding, const wchar_t *in_str)
{
    int ec = (encoding == TGI_ENCODING_ANSI ? CP_ACP : CP_UTF8);
    int len = WideCharToMultiByte(ec, 0, in_str, -1, NULL, 0, NULL, NULL);
    char *str = malloc((len + 1) * sizeof(char));
    WideCharToMultiByte(ec, 0, in_str, -1, str, len + 1, NULL, NULL);
    return str;
}

typedef struct TGI_Application_GDI TGI_Application_GDI;
typedef struct TGI_Window_GDI TGI_Window_GDI;
typedef struct TGI_Graphics_GDI TGI_Graphics_GDI;
typedef struct TGI_Image_GDI TGI_Image_GDI;
typedef struct TGI_Font_GDI TGI_Font_GDI;
typedef struct TGI_Timer_GDI TGI_Timer_GDI;
struct TGI_Application_GDI
{
    TGI_Application base;
    TGI_Encoding encoding;
    double scaling;
    ULONG_PTR gdiplusToken;
};
extern const struct vtable_TGI_Application_t vtable_TGI_Application_GDI;
struct TGI_Window_GDI
{
    TGI_Window base;
    TGI_Application_GDI *app;
    HWND hwnd;
    double scaling;
    void(TGIAPI *callback_on_create)(TGI_Window *self);
    int(TGIAPI *callback_on_close)(TGI_Window *self);
    void(TGIAPI *callback_on_paint)(TGI_Window *self);
    void(TGIAPI *callback_on_size)(TGI_Window *self, float new_width, float new_height);
    void(TGIAPI *callback_on_key)(TGI_Window *self, TGI_KeyEvent *event);
    void(TGIAPI *callback_on_mouse)(TGI_Window *self, TGI_MouseEvent *event);
    wchar_t *classname;
    RECT sizeinfo;
};
extern const struct vtable_TGI_Window_t vtable_TGI_Window_GDI;
struct TGI_Graphics_GDI
{
    TGI_Graphics base;
    TGI_Application_GDI *app;
    double scaling;
    GpGraphics *g;
    GpPen *pen;
    GpSolidFill *brush;
};
extern const struct vtable_TGI_Graphics_t vtable_TGI_Graphics_GDI;
struct TGI_Image_GDI
{
    TGI_Image base;
    TGI_Application_GDI *app;
    GpImage *img;
    double scaling;
};
extern const struct vtable_TGI_Image_t vtable_TGI_Image_GDI;
struct TGI_Font_GDI
{
    TGI_Font base;
    GpFontFamily *family;
    GpFont *font;
    GpStringFormat *sfmt;
};
extern const struct vtable_TGI_Font_t vtable_TGI_Font_GDI;
struct TGI_Timer_GDI
{
    TGI_Timer base;
    MMRESULT id;
    void(TGIAPI *callback)(TGI_Timer *self);
};
extern const struct vtable_TGI_Timer_t vtable_TGI_Timer_GDI;

void TGIAPI tgi_graphics_gdi_free(TGI_Graphics *_self)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    GdipDeleteBrush(self->brush);
    GdipDeletePen(self->pen);
    GdipDeleteGraphics(self->g);
    free(self);
}
int TGIAPI tgi_graphics_gdi_clear(TGI_Graphics *_self, TGI_Color color)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    return !GdipGraphicsClear(self->g, color);
}
int TGIAPI tgi_graphics_gdi_set_color(TGI_Graphics *_self, TGI_Color color)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    return !GdipSetPenColor(self->pen, color) && !GdipSetSolidFillColor(self->brush, color);
}
int TGIAPI tgi_graphics_gdi_set_width(TGI_Graphics *_self, float width)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    return !GdipSetPenWidth(self->pen, width * self->scaling);
}
int TGIAPI tgi_graphics_gdi_draw_line(TGI_Graphics *_self, float x1, float y1, float x2, float y2)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    double s = self->scaling;
    return !GdipDrawLine(self->g, self->pen, x1 * s, y1 * s, x2 * s, y2 * s);
}
int TGIAPI tgi_graphics_gdi_draw_arc(TGI_Graphics *_self, float x, float y, float width, float height,
                                     float start_angle, float sweep_angle)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    double s = self->scaling;
    return !GdipDrawArc(self->g, self->pen, x * s, y * s, width * s, height * s, start_angle, sweep_angle);
}
int TGIAPI tgi_graphics_gdi_draw_rect(TGI_Graphics *_self, float x, float y, float width, float height)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    double s = self->scaling;
    return !GdipDrawRectangle(self->g, self->pen, x * s, y * s, width * s, height * s);
}
int TGIAPI tgi_graphics_gdi_draw_ellipse(TGI_Graphics *_self, float x, float y, float width, float height)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    double s = self->scaling;
    return !GdipDrawEllipse(self->g, self->pen, x * s, y * s, width * s, height * s);
}
int TGIAPI tgi_graphics_gdi_draw_pie(TGI_Graphics *_self, float x, float y, float width, float height,
                                     float start_angle, float sweep_angle)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    double s = self->scaling;
    return !GdipDrawPie(self->g, self->pen, x * s, y * s, width * s, height * s, start_angle, sweep_angle);
}
int TGIAPI tgi_graphics_gdi_draw_polygon(TGI_Graphics *_self, const TGI_Point *points, int count)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    PointF p[count];
    for (int i = 0; i < count; i++)
    {
        p[i].X = points[i].x * self->scaling;
        p[i].Y = points[i].y * self->scaling;
    }
    return !GdipDrawPolygon(self->g, self->pen, p, count);
}
int TGIAPI tgi_graphics_gdi_fill_rect(TGI_Graphics *_self, float x, float y, float width, float height)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    double s = self->scaling;
    return !GdipFillRectangle(self->g, self->brush, x * s, y * s, width * s, height * s);
}
int TGIAPI tgi_graphics_gdi_fill_ellipse(TGI_Graphics *_self, float x, float y, float width, float height)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    double s = self->scaling;
    return !GdipFillEllipse(self->g, self->brush, x * s, y * s, width * s, height * s);
}
int TGIAPI tgi_graphics_gdi_fill_pie(TGI_Graphics *_self, float x, float y, float width, float height,
                                     float start_angle, float sweep_angle)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    double s = self->scaling;
    return !GdipFillPie(self->g, self->brush, x * s, y * s, width * s, height * s, start_angle, sweep_angle);
}
int TGIAPI tgi_graphics_gdi_fill_polygon(TGI_Graphics *_self, const TGI_Point *points, int count)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    PointF p[count];
    for (int i = 0; i < count; i++)
    {
        p[i].X = points[i].x * self->scaling;
        p[i].Y = points[i].y * self->scaling;
    }
    return !GdipFillPolygon2(self->g, self->brush, p, count);
}
int TGIAPI tgi_graphics_gdi_draw_image(TGI_Graphics *_self, const TGI_Image *image, float x, float y)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    TGI_Rect rect;
    tgi_image_get_size((TGI_Image *)image, &rect);
    return !GdipDrawImageRect(self->g, ((TGI_Image_GDI *)image)->img, x * self->scaling, y * self->scaling, rect.right,
                              rect.bottom);
}
int TGIAPI tgi_graphics_gdi_draw_image_rect(TGI_Graphics *_self, const TGI_Image *image, float x, float y, float width,
                                            float height)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    return !GdipDrawImageRect(self->g, ((TGI_Image_GDI *)image)->img, x * self->scaling, y * self->scaling,
                              width * self->scaling, height * self->scaling);
}
int TGIAPI tgi_graphics_gdi_draw_image_ex(TGI_Graphics *_self, const TGI_Image *image, float x, float y, float src_x,
                                          float src_y, float src_width, float src_height)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    return !GdipDrawImagePointRect(self->g, ((TGI_Image_GDI *)image)->img, x * self->scaling, y * self->scaling, src_x,
                                   src_y, src_width, src_height, UnitPixel);
}
int TGIAPI tgi_graphics_gdi_draw_text(TGI_Graphics *_self, const char *text, const TGI_Font *_font, float x, float y)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    TGI_Font_GDI *font = (TGI_Font_GDI *)_font;
    wchar_t *ws = tgi_gdi_codecvt(self->app->encoding, text);
    RectF rect = {x * self->scaling, y * self->scaling, 0, 0};
    int ret = GdipDrawString(self->g, ws, -1, font->font, &rect, font->sfmt, self->brush);
    free(ws);
    return !ret;
}
int TGIAPI tgi_graphics_gdi_draw_text_rect(TGI_Graphics *_self, const char *text, const TGI_Font *_font, float x,
                                           float y, float width, float height)
{
    TGI_Graphics_GDI *self = (TGI_Graphics_GDI *)_self;
    TGI_Font_GDI *font = (TGI_Font_GDI *)_font;
    wchar_t *ws = tgi_gdi_codecvt(self->app->encoding, text);
    RectF rect = {x * self->scaling, y * self->scaling, width * self->scaling, height * self->scaling};
    int ret = GdipDrawString(self->g, ws, -1, font->font, &rect, font->sfmt, self->brush);
    free(ws);
    return !ret;
}
const struct vtable_TGI_Graphics_t vtable_TGI_Graphics_GDI = {
    .free = tgi_graphics_gdi_free,
    .clear = tgi_graphics_gdi_clear,
    .set_color = tgi_graphics_gdi_set_color,
    .set_width = tgi_graphics_gdi_set_width,
    .draw_line = tgi_graphics_gdi_draw_line,
    .draw_arc = tgi_graphics_gdi_draw_arc,
    .draw_rect = tgi_graphics_gdi_draw_rect,
    .draw_ellipse = tgi_graphics_gdi_draw_ellipse,
    .draw_pie = tgi_graphics_gdi_draw_pie,
    .draw_polygon = tgi_graphics_gdi_draw_polygon,
    .fill_rect = tgi_graphics_gdi_fill_rect,
    .fill_ellipse = tgi_graphics_gdi_fill_ellipse,
    .fill_pie = tgi_graphics_gdi_fill_pie,
    .fill_polygon = tgi_graphics_gdi_fill_polygon,
    .draw_image = tgi_graphics_gdi_draw_image,
    .draw_image_rect = tgi_graphics_gdi_draw_image_rect,
    .draw_image_ex = tgi_graphics_gdi_draw_image_ex,
    .draw_text = tgi_graphics_gdi_draw_text,
    .draw_text_rect = tgi_graphics_gdi_draw_text_rect,
};

void tgi_window_gdi_wnd_vinfo(HWND hwnd)
{
    HMENU nmenu = CreatePopupMenu();
    AppendMenuW(nmenu, MF_STRING | MF_DISABLED, 0x1141, L"This window is built by TGI");
    AppendMenuW(nmenu, MF_SEPARATOR, 0, L"");
    AppendMenuW(nmenu, MF_STRING, 0x1145, L"Github repository");
    HMENU hmenu = GetSystemMenu(hwnd, FALSE);
    AppendMenuW(hmenu, MF_SEPARATOR, 0, L"");
    AppendMenuW(hmenu, MF_POPUP, (UINT_PTR)nmenu, L"About");
}
static int tgi_window_gdi_count = 0;
LRESULT CALLBACK tgi_window_gdi_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
    static PAINTSTRUCT ps;
    switch (uMsg)
    {
    case WM_CREATE:
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT *)lParam)->lpCreateParams);
        tgi_window_gdi_wnd_vinfo(hwnd);
        return 0;
    case WM_CLOSE:
        if (self->callback_on_close)
        {
            if (self->callback_on_close((TGI_Window *)self) == 0)
            {
                return 0;
            }
        }
        DestroyWindow(hwnd);
        return 0;
    case WM_PAINT:
        BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        if (self->callback_on_paint)
        {
            self->callback_on_paint((TGI_Window *)self);
        }
        return 0;
    case WM_SIZE:
        if (self->callback_on_size)
        {
            float width = LOWORD(lParam) / self->scaling;
            float height = HIWORD(lParam) / self->scaling;
            self->callback_on_size((TGI_Window *)self, width, height);
        }
        return 0;
    case WM_GETMINMAXINFO:
        if (self != NULL)
        {
            if (self->sizeinfo.left != -1 && self->sizeinfo.top != -1)
            {
                MINMAXINFO *mmi = (MINMAXINFO *)lParam;
                mmi->ptMinTrackSize.x = self->sizeinfo.left;
                mmi->ptMinTrackSize.y = self->sizeinfo.top;
            }
            if (self->sizeinfo.right != -1 && self->sizeinfo.bottom != -1)
            {
                MINMAXINFO *mmi = (MINMAXINFO *)lParam;
                mmi->ptMaxTrackSize.x = self->sizeinfo.right;
                mmi->ptMaxTrackSize.y = self->sizeinfo.bottom;
            }
        }
        return 0;
#define KE(msg, e_type, e_sys)                                                                                         \
    case msg:                                                                                                          \
        if (self->callback_on_key)                                                                                     \
        {                                                                                                              \
            char key = LOWORD(MapVirtualKeyW(wParam, MAPVK_VK_TO_CHAR));                                               \
            TGI_KeyEvent e;                                                                                            \
            e.type = e_type, e.key = &key;                                                                             \
            self->callback_on_key((TGI_Window *)self, &e);                                                             \
        }                                                                                                              \
        if (e_sys)                                                                                                     \
        {                                                                                                              \
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);                                                         \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            return 0;                                                                                                  \
        }
        KE(WM_SYSKEYDOWN, TGI_KEYEVENT_DOWN, 1)
        KE(WM_KEYDOWN, TGI_KEYEVENT_DOWN, 0)
        KE(WM_SYSKEYUP, TGI_KEYEVENT_UP, 1)
        KE(WM_KEYUP, TGI_KEYEVENT_UP, 0)
#undef KE
    case WM_CHAR:
        if (self->callback_on_key)
        {
            wchar_t ws[] = {wParam, 0};
            char *str = tgi_gdi_codecvt2(self->app->encoding, ws);
            TGI_KeyEvent e;
            e.type = TGI_KEYEVENT_INPUT, e.key = str;
            self->callback_on_key((TGI_Window *)self, &e);
            free(str);
        }
        return 0;
#define ME(msg, e_type, e_buttom)                                                                                      \
    case msg:                                                                                                          \
        if (self->callback_on_mouse)                                                                                   \
        {                                                                                                              \
            TGI_MouseEvent e;                                                                                          \
            e.type = e_type, e.buttom = e_buttom;                                                                      \
            e.x = GET_X_LPARAM(lParam) / self->scaling, e.y = GET_Y_LPARAM(lParam) / self->scaling;                    \
            self->callback_on_mouse((TGI_Window *)self, &e);                                                           \
        }                                                                                                              \
        return 0;
        ME(WM_LBUTTONDOWN, TGI_MOUSEEVENT_DOWN, TGI_MOUSEEVENT_LEFT)
        ME(WM_LBUTTONUP, TGI_MOUSEEVENT_UP, TGI_MOUSEEVENT_LEFT)
        ME(WM_LBUTTONDBLCLK, TGI_MOUSEEVENT_DOUBLE, TGI_MOUSEEVENT_LEFT)
        ME(WM_MBUTTONDOWN, TGI_MOUSEEVENT_DOWN, TGI_MOUSEEVENT_MIDDLE)
        ME(WM_MBUTTONUP, TGI_MOUSEEVENT_UP, TGI_MOUSEEVENT_MIDDLE)
        ME(WM_MBUTTONDBLCLK, TGI_MOUSEEVENT_DOUBLE, TGI_MOUSEEVENT_MIDDLE)
        ME(WM_RBUTTONDOWN, TGI_MOUSEEVENT_DOWN, TGI_MOUSEEVENT_RIGHT)
        ME(WM_RBUTTONUP, TGI_MOUSEEVENT_UP, TGI_MOUSEEVENT_RIGHT)
        ME(WM_RBUTTONDBLCLK, TGI_MOUSEEVENT_DOUBLE, TGI_MOUSEEVENT_RIGHT)
        ME(WM_MOUSEMOVE, TGI_MOUSEEVENT_MOVE, -1)
#undef ME
    /* 展示一波 */
    case WM_SYSCOMMAND:
        switch (LOWORD(wParam))
        {
        case 0x1145:
            ShellExecute(NULL, "open", "https://github.com/xgugugu/tgi", NULL, NULL, SW_SHOWNORMAL);
            return 0;
        }
        break;
    /* 展示结束 */
    case WM_DESTROY:
        tgi_window_gdi_count--;
        if (tgi_window_gdi_count == 0)
        {
            PostQuitMessage(0);
        }
        return 0;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}
void TGIAPI tgi_window_gdi_free(TGI_Window *self)
{
    DestroyWindow(((TGI_Window_GDI *)self)->hwnd);
    UnregisterClassW(((TGI_Window_GDI *)self)->classname, GetModuleHandleW(NULL));
    free(((TGI_Window_GDI *)self)->classname);
    free(self);
}
void TGIAPI tgi_window_gdi_on_close(TGI_Window *_self, int TGIAPI callback(TGI_Window *self))
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    self->callback_on_close = callback;
}
void TGIAPI tgi_window_gdi_on_paint(TGI_Window *_self, void TGIAPI callback(TGI_Window *self))
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    self->callback_on_paint = callback;
}
void TGIAPI tgi_window_gdi_on_size(TGI_Window *_self,
                                   void TGIAPI callback(TGI_Window *self, float new_width, float new_height))
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    self->callback_on_size = callback;
}
void TGIAPI tgi_window_gdi_on_key(TGI_Window *_self, void TGIAPI callback(TGI_Window *self, TGI_KeyEvent *event))
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    self->callback_on_key = callback;
}
void TGIAPI tgi_window_gdi_on_mouse(TGI_Window *_self, void TGIAPI callback(TGI_Window *self, TGI_MouseEvent *event))
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    self->callback_on_mouse = callback;
}
int TGIAPI tgi_window_gdi_is_key_down(TGI_Window *self, char key)
{
    return GetKeyState(VkKeyScanA(key)) & 0x8000;
}
void TGIAPI tgi_window_gdi_show(TGI_Window *_self)
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    ShowWindow(self->hwnd, SW_SHOW);
}
void TGIAPI tgi_window_gdi_paint(TGI_Window *_self)
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    InvalidateRect(self->hwnd, NULL, FALSE);
}
int TGIAPI tgi_window_gdi_set_style(TGI_Window *_self, TGI_WindowStyle style)
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    DWORD s = WS_OVERLAPPED;
    if (style & TGI_WINDOWSTYLE_BORDER)
    {
        s |= WS_BORDER;
    }
    if (style & TGI_WINDOWSTYLE_CAPTION)
    {
        s |= WS_CAPTION | WS_SYSMENU;
    }
    if (style & TGI_WINDOWSTYLE_RESIZE)
    {
        s |= WS_SIZEBOX;
    }
    if (style & TGI_WINDOWSTYLE_MAXIMIZEBOX)
    {
        s |= WS_MAXIMIZEBOX;
    }
    if (style & TGI_WINDOWSTYLE_MINIMIZEBOX)
    {
        s |= WS_MINIMIZEBOX;
    }
    int ret = SetWindowLongPtrW(self->hwnd, GWL_STYLE, s);
    TGI_Rect rect;
    tgi_window_get_size((TGI_Window *)self, &rect);
    tgi_window_set_size((TGI_Window *)self, round(rect.right), round(rect.bottom));
    return ret;
}
int TGIAPI tgi_window_gdi_set_size(TGI_Window *_self, int width, int height)
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    RECT rect = {0, 0, round(width * self->scaling), round(height * self->scaling)};
    if (!AdjustWindowRectEx(&rect, GetWindowLongPtrW(self->hwnd, GWL_STYLE), GetMenu(self->hwnd) != NULL,
                            GetWindowLongPtrW(self->hwnd, GWL_EXSTYLE)))
    {
        goto exit;
    }
    return SetWindowPos(self->hwnd, 0, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
exit:
    return 0;
}
int TGIAPI tgi_window_gdi_get_size(TGI_Window *_self, TGI_Rect *rect)
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    RECT rc;
    int ret = GetClientRect(self->hwnd, &rc);
    rect->right = rc.right / self->scaling;
    rect->bottom = rc.bottom / self->scaling;
    rect->left = rect->top = 0;
    return ret;
}
int TGIAPI tgi_window_gdi_set_min_size(TGI_Window *_self, int width, int height)
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    self->sizeinfo.left = round(width * self->scaling), self->sizeinfo.top = round(height * self->scaling);
    return 1;
}
int TGIAPI tgi_window_gdi_set_max_size(TGI_Window *_self, int width, int height)
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    self->sizeinfo.right = round(width * self->scaling), self->sizeinfo.bottom = round(height * self->scaling);
    return 1;
}
int TGIAPI tgi_window_gdi_set_title(TGI_Window *_self, const char *title)
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    wchar_t *ws = tgi_gdi_codecvt(self->app->encoding, title);
    int ret = SetWindowTextW(self->hwnd, ws);
    free(ws);
    return ret;
}
TGI_Graphics *TGIAPI tgi_window_gdi_create_graphics(TGI_Window *_self)
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    TGI_Graphics_GDI *gg = malloc(sizeof(TGI_Graphics_GDI));
    gg->base.vptr = &vtable_TGI_Graphics_GDI;
    gg->scaling = self->scaling;
    gg->app = self->app;
    if (GdipCreateFromHWND(self->hwnd, &gg->g) != Ok)
    {
        goto exit1;
    }
    if (GdipSetSmoothingMode(gg->g, SmoothingModeAntiAlias) != Ok)
    {
        puts("Warning: GdipSetSmoothingMode failed!");
    }
    if (GdipCreatePen1(TGI_COLOR(255, 255, 255, 255), 1.0 * gg->scaling, UnitPixel, &gg->pen) != Ok)
    {
        goto exit2;
    }
    if (GdipCreateSolidFill(TGI_COLOR(255, 255, 255, 255), &gg->brush) != Ok)
    {
        goto exit3;
    }
    return (TGI_Graphics *)gg;
exit3:
    GdipDeletePen(gg->pen);
exit2:
    GdipDeleteGraphics(gg->g);
exit1:
    free(self);
    return NULL;
}
TGI_Image *TGIAPI tgi_window_gdi_create_image(TGI_Window *_self)
{
    TGI_Window_GDI *self = (TGI_Window_GDI *)_self;
    TGI_Image_GDI *img = malloc(sizeof(TGI_Image_GDI));
    img->base.vptr = &vtable_TGI_Image_GDI;
    img->app = self->app;
    img->scaling = self->scaling;
    RECT rc;
    if (!GetClientRect(self->hwnd, &rc))
    {
        goto exit1;
    }
    if (GdipCreateBitmapFromScan0(max(rc.right, 1), max(rc.bottom, 1), 0, PixelFormat32bppARGB, NULL, &img->img) != Ok)
    {
        goto exit1;
    }
    return (TGI_Image *)img;
exit1:
    free(img);
    return NULL;
}
const struct vtable_TGI_Window_t vtable_TGI_Window_GDI = {
    .free = tgi_window_gdi_free,
    .on_close = tgi_window_gdi_on_close,
    .on_paint = tgi_window_gdi_on_paint,
    .on_size = tgi_window_gdi_on_size,
    .on_key = tgi_window_gdi_on_key,
    .on_mouse = tgi_window_gdi_on_mouse,
    .show = tgi_window_gdi_show,
    .paint = tgi_window_gdi_paint,
    .set_style = tgi_window_gdi_set_style,
    .set_size = tgi_window_gdi_set_size,
    .get_size = tgi_window_gdi_get_size,
    .set_min_size = tgi_window_gdi_set_min_size,
    .set_max_size = tgi_window_gdi_set_max_size,
    .set_title = tgi_window_gdi_set_title,
    .create_graphics = tgi_window_gdi_create_graphics,
    .create_image = tgi_window_gdi_create_image,
};

void TGIAPI tgi_image_gdi_free(TGI_Image *_self)
{
    TGI_Image_GDI *self = (TGI_Image_GDI *)_self;
    GdipDisposeImage(self->img);
    free(self);
}
TGI_Image *TGIAPI tgi_image_gdi_clone(TGI_Image *_self)
{
    TGI_Image_GDI *self = (TGI_Image_GDI *)_self;
    TGI_Image_GDI *one = malloc(sizeof(TGI_Image_GDI));
    one->base = self->base;
    one->app = self->app;
    one->scaling = self->scaling;
    if (GdipCloneImage(self->img, &one->img) != Ok)
    {
        goto exit1;
    }
    return (TGI_Image *)one;
exit1:
    free(one);
    return NULL;
}
TGI_Graphics *TGIAPI tgi_image_create_gdi_graphics(TGI_Image *_self)
{
    TGI_Image_GDI *self = (TGI_Image_GDI *)_self;
    TGI_Graphics_GDI *g = malloc(sizeof(TGI_Graphics_GDI));
    g->base.vptr = &vtable_TGI_Graphics_GDI;
    g->scaling = self->scaling;
    g->app = self->app;
    if (GdipGetImageGraphicsContext(self->img, &g->g) != Ok)
    {
        goto exit1;
    }
    if (GdipSetSmoothingMode(g->g, SmoothingModeAntiAlias) != Ok)
    {
        puts("Warning: GdipSetSmoothingMode failed!");
    }
    if (GdipCreatePen1(TGI_COLOR(255, 255, 255, 255), 1.0 * g->scaling, UnitPixel, &g->pen) != Ok)
    {
        goto exit2;
    }
    if (GdipCreateSolidFill(TGI_COLOR(255, 255, 255, 255), &g->brush) != Ok)
    {
        goto exit3;
    }
    return (TGI_Graphics *)g;
exit3:
    GdipDeletePen(g->pen);
exit2:
    GdipDeleteGraphics(g->g);
exit1:
    free(self);
    return NULL;
}
static inline int TGIAPI tgi_image_gdi_get_size(TGI_Image *_self, TGI_Rect *rect)
{
    TGI_Image_GDI *self = (TGI_Image_GDI *)_self;
    return !GdipGetImageDimension(self->img, &rect->right, &rect->bottom);
}
const struct vtable_TGI_Image_t vtable_TGI_Image_GDI = {
    .free = tgi_image_gdi_free,
    .clone = tgi_image_gdi_clone,
    .create_graphics = tgi_image_create_gdi_graphics,
    .get_size = tgi_image_gdi_get_size,
};

void TGIAPI tgi_font_gdi_free(TGI_Font *_self)
{
    TGI_Font_GDI *self = (TGI_Font_GDI *)_self;
    GdipDeleteStringFormat(self->sfmt);
    GdipDeleteFont(self->font);
    GdipDeleteFontFamily(self->family);
    free(self);
}
int TGIAPI tgi_font_gdi_set_align(TGI_Font *_self, TGI_TextAlign align)
{
    TGI_Font_GDI *self = (TGI_Font_GDI *)_self;
    return !GdipSetStringFormatAlign(self->sfmt, (StringAlignment)align);
}
int TGIAPI tgi_font_gdi_set_vertical_align(TGI_Font *_self, TGI_TextAlign align)
{
    TGI_Font_GDI *self = (TGI_Font_GDI *)_self;
    return !GdipSetStringFormatLineAlign(self->sfmt, (StringAlignment)align);
}
const struct vtable_TGI_Font_t vtable_TGI_Font_GDI = {
    .free = tgi_font_gdi_free,
    .set_align = tgi_font_gdi_set_align,
    .set_vertical_align = tgi_font_gdi_set_vertical_align,
};

void CALLBACK tgi_timer_gdi_Callback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    TGI_Timer_GDI *self = (TGI_Timer_GDI *)dwUser;
    self->callback((TGI_Timer *)self);
}
void TGIAPI tgi_timer_gdi_free(TGI_Timer *_self)
{
    TGI_Timer_GDI *self = (TGI_Timer_GDI *)_self;
    timeKillEvent(self->id);
    free(self);
}
const struct vtable_TGI_Timer_t vtable_TGI_Timer_GDI = {
    .free = tgi_timer_gdi_free,
};

static int wnd_classnameid = 0;
wchar_t *tgi_window_gdi_wnd_classname()
{
    static char cn[256];
    sprintf(cn, "TGI_Window_%d", wnd_classnameid);
    wchar_t *ws = tgi_gdi_codecvt(TGI_ENCODING_UTF8, cn);
    wnd_classnameid++;
    return ws;
}
void TGIAPI tgi_window_gdi_exec(TGI_Application *_self)
{
    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}
int TGIAPI tgi_window_gdi_exec_once(TGI_Application *_self)
{
    MSG msg;
    BOOL ret = GetMessageW(&msg, NULL, 0, 0);
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
    return ret;
}
TGI_Window *TGIAPI tgi_window_gdi_create(TGI_Application *app)
{
    TGI_Window_GDI *self = malloc(sizeof(TGI_Window_GDI));
    self->base.vptr = &vtable_TGI_Window_GDI;
    self->app = (TGI_Application_GDI *)app;
    self->callback_on_create = NULL;
    self->callback_on_close = NULL;
    self->callback_on_paint = NULL;
    self->callback_on_size = NULL;
    self->callback_on_key = NULL;
    self->callback_on_mouse = NULL;
    self->scaling = ((TGI_Application_GDI *)app)->scaling;
    memset(&self->sizeinfo, -1, sizeof(self->sizeinfo));
    // 注册窗口类
    self->classname = tgi_window_gdi_wnd_classname();
    WNDCLASSW wndclass = {};
    wndclass.lpfnWndProc = tgi_window_gdi_WndProc;
    wndclass.hInstance = GetModuleHandleW(NULL);
    wndclass.lpszClassName = self->classname;
    wndclass.style = CS_DBLCLKS;
    wndclass.hCursor = LoadCursorA(NULL, IDC_ARROW);
    RegisterClassW(&wndclass);
    // 创建窗口
    self->hwnd = CreateWindowExW(0, self->classname, L"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                 CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, wndclass.hInstance, self);
    if (self->hwnd == NULL)
    {
        goto exit;
    }
    tgi_window_gdi_count++;
    return (TGI_Window *)self;
exit:
    free(self);
    return NULL;
}
void TGIAPI tgi_application_gdi_free(TGI_Application *_self)
{
    TGI_Application_GDI *self = (TGI_Application_GDI *)_self;
    GdiplusShutdown(self->gdiplusToken);
    free(self);
}
TGI_Image *TGIAPI tgi_application_gdi_create_image(TGI_Application *_self, int width, int height)
{
    TGI_Application_GDI *self = (TGI_Application_GDI *)_self;
    TGI_Image_GDI *img = malloc(sizeof(TGI_Image_GDI));
    img->base.vptr = &vtable_TGI_Image_GDI;
    img->app = self;
    img->scaling = 1.0;
    if (GdipCreateBitmapFromScan0(width, height, 0, PixelFormat32bppARGB, NULL, &img->img) != Ok)
    {
        goto exit1;
    }
    return (TGI_Image *)img;
exit1:
    free(img);
    return NULL;
}
TGI_Image *TGIAPI tgi_application_gdi_create_image_from_file(TGI_Application *_self, const char *filename)
{
    TGI_Application_GDI *self = (TGI_Application_GDI *)_self;
    TGI_Image_GDI *img = malloc(sizeof(TGI_Image_GDI));
    img->base.vptr = &vtable_TGI_Image_GDI;
    img->app = self;
    img->scaling = 1.0;
    wchar_t *ws = tgi_gdi_codecvt(self->encoding, filename);
    if (GdipCreateBitmapFromFile(ws, &img->img) != Ok)
    {
        goto exit1;
    }
    free(ws);
    return (TGI_Image *)img;
exit1:
    free(ws);
    free(img);
    return NULL;
}
TGI_Font *TGIAPI tgi_application_gdi_create_font(TGI_Application *_self, const char *name, float size,
                                                 TGI_FontStyle style)
{
    TGI_Application_GDI *self = (TGI_Application_GDI *)_self;
    TGI_Font_GDI *font = malloc(sizeof(TGI_Font_GDI));
    font->base.vptr = &vtable_TGI_Font_GDI;
    wchar_t *ws = tgi_gdi_codecvt(self->encoding, name);
    if (GdipCreateFontFamilyFromName(ws, NULL, &font->family) != Ok)
    {
        goto exit1;
    }
    if (GdipCreateFont(font->family, size * self->scaling, style, UnitPixel, &font->font) != Ok)
    {
        goto exit2;
    }
    if (GdipStringFormatGetGenericDefault(&font->sfmt) != Ok)
    {
        goto exit3;
    }
    free(ws);
    return (TGI_Font *)font;
exit3:
    GdipDeleteStringFormat(font->sfmt);
exit2:
    GdipDeleteFontFamily(font->family);
exit1:
    free(ws);
    free(font);
    return NULL;
}
TGI_Timer *TGIAPI tgi_application_gdi_create_timer(TGI_Application *_self, unsigned int delay, int type,
                                                   void callback(TGI_Timer *timer))
{
    TGI_Timer_GDI *self = malloc(sizeof(TGI_Timer_GDI));
    self->base.vptr = &vtable_TGI_Timer_GDI;
    self->callback = callback;
    if (!(self->id = timeSetEvent(delay, 1, tgi_timer_gdi_Callback, (DWORD_PTR)self,
                                  type == 0 ? TIME_ONESHOT : TIME_PERIODIC)))
    {
        goto exit1;
    }
    return (TGI_Timer *)self;
exit1:
    free(self);
    return NULL;
}
const struct vtable_TGI_Application_t vtable_TGI_Application_GDI = {
    .free = tgi_application_gdi_free,
    .exec = tgi_window_gdi_exec,
    .exec_once = tgi_window_gdi_exec_once,
    .create_window = tgi_window_gdi_create,
    .create_image = tgi_application_gdi_create_image,
    .create_image_from_file = tgi_application_gdi_create_image_from_file,
    .create_font = tgi_application_gdi_create_font,
    .create_timer = tgi_application_gdi_create_timer,
};
double tgi_window_gdi_get_scaling()
{
    HDC hdc = GetDC(NULL);
    double width = GetDeviceCaps(hdc, LOGPIXELSX) / 96.0;
    double height = GetDeviceCaps(hdc, LOGPIXELSY) / 96.0;
    ReleaseDC(NULL, hdc);
    if (width != height)
    {
        puts("Unsupported scaling method!");
        exit(1);
    }
    return width;
}
void tgi_window_gdi_set_scaling()
{
    if (IsWindowsVistaOrGreater())
    {
        HMODULE user32 = LoadLibrary("user32.dll");
        typedef BOOL(WINAPI * Func)();
        Func SetProcessDPIAware = (Func)GetProcAddress(user32, "SetProcessDPIAware");
        SetProcessDPIAware();
        FreeLibrary(user32);
    }
}
TGI_Application *tgi_application_gdi_create(TGI_Encoding encoding)
{
    tgi_window_gdi_set_scaling();
    TGI_Application_GDI *self = malloc(sizeof(TGI_Application_GDI));
    self->base.vptr = &vtable_TGI_Application_GDI;
    self->encoding = encoding;
    self->scaling = tgi_window_gdi_get_scaling();
    static GdiplusStartupInput gdiplusStartupInput = {
        1,
        NULL,
        FALSE,
        FALSE,
    };
    if (GdiplusStartup(&self->gdiplusToken, &gdiplusStartupInput, NULL) != Ok)
    {
        goto exit1;
    }
    return (TGI_Application *)self;
exit1:
    free(self);
    return NULL;
}

#else
TGI_Application_GDI *tgi_application_gdi_create(TGI_Encoding _)
{
    return NULL;
}
#endif