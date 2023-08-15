/**
 * @file tgi.hpp
 * @author xgugugu
 * @brief Tiny Graphics Interfaces for C++
 * @brief TGI图形库的C++接口
 * @attention C++接口的所有类及方法均为宏自动生成，不保证其正确性
 * @note **C++类基本使用方法（例）**
 * @note C语言接口：
 * @code
 * TGI_Obj* obj = tgi_factory_create_obj(factory); // 创建
 * tgi_obj_foo(obj, arg1, arg2); // 使用
 * tgi_obj_free(obj); // 释放
 * @endcode
 * @note C++接口：
 * @code
 * tgi::Obj obj = factory.create_obj(); // 创建
 * obj.foo(arg1, arg2); // 使用
 * obj.free(); // 释放
 * @endcode
 */

#ifndef TGI_HPP
#define TGI_HPP

#include "tgi.h"

#ifdef __cplusplus
namespace tgi
{
#define BEGIN_CLASS(Uname, Dname)                                                                                      \
    class Uname                                                                                                        \
    {                                                                                                                  \
      private:                                                                                                         \
        TGI_##Uname *self;                                                                                             \
                                                                                                                       \
      public:                                                                                                          \
        operator TGI_##Uname *()                                                                                       \
        {                                                                                                              \
            return self;                                                                                               \
        }                                                                                                              \
        Uname()                                                                                                        \
        {                                                                                                              \
            self = 0;                                                                                                  \
        }                                                                                                              \
        Uname(TGI_##Uname *_self)                                                                                      \
        {                                                                                                              \
            self = _self;                                                                                              \
        }                                                                                                              \
        Uname(const Uname &b)                                                                                          \
        {                                                                                                              \
            self = b.self;                                                                                             \
        }                                                                                                              \
        Uname &operator=(const Uname &b)                                                                               \
        {                                                                                                              \
            self = b.self;                                                                                             \
            return *this;                                                                                              \
        }                                                                                                              \
        Uname &operator=(TGI_##Uname *b)                                                                               \
        {                                                                                                              \
            self = b;                                                                                                  \
            return *this;                                                                                              \
        }                                                                                                              \
        ~Uname()                                                                                                       \
        {                                                                                                              \
        }
#define END_CLASS()                                                                                                    \
    }                                                                                                                  \
    ;
#define GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, NAME,     \
                  ...)                                                                                                 \
    NAME
#define NAME2(t1, n1) n1
#define NAME4(t1, n1, t2, n2) n1, n2
#define NAME6(t1, n1, t2, n2, t3, n3) n1, n2, n3
#define NAME8(t1, n1, t2, n2, t3, n3, t4, n4) n1, n2, n3, n4
#define NAME10(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5) n1, n2, n3, n4, n5
#define NAME12(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6) n1, n2, n3, n4, n5, n6
#define NAME14(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7) n1, n2, n3, n4, n5, n6, n7
#define NAME16(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, t8, n8) n1, n2, n3, n4, n5, n6, n7, n8
#define NAME18(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, t8, n8, t9, n9)                                 \
    n1, n2, n3, n4, n5, n6, n7, n8, n9
#define NAME20(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, t8, n8, t9, n9, t10, n10)                       \
    n1, n2, n3, n4, n5, n6, n7, n8, n9, n10
#define NAME(args...)                                                                                                  \
    GET_MACRO(args, NAME20, NAME19, NAME18, NAME17, NAME16, NAME15, NAME14, NAME13, NAME12, NAME11, NAME10, NAME9,     \
              NAME8, NAME7, NAME6, NAME5, NAME4, NAME3, NAME2, NAME1)                                                  \
    (args)
#define VAR2(t1, n1) t1 n1
#define VAR4(t1, n1, t2, n2) t1 n1, t2 n2
#define VAR6(t1, n1, t2, n2, t3, n3) t1 n1, t2 n2, t3 n3
#define VAR8(t1, n1, t2, n2, t3, n3, t4, n4) t1 n1, t2 n2, t3 n3, t4 n4
#define VAR10(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5) t1 n1, t2 n2, t3 n3, t4 n4, t5 n5
#define VAR12(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6) t1 n1, t2 n2, t3 n3, t4 n4, t5 n5, t6 n6
#define VAR14(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7) t1 n1, t2 n2, t3 n3, t4 n4, t5 n5, t6 n6, t7 n7
#define VAR16(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, t8, n8)                                          \
    t1 n1, t2 n2, t3 n3, t4 n4, t5 n5, t6 n6, t7 n7, t8 n8
#define VAR18(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, t8, n8, t9, n9)                                  \
    t1 n1, t2 n2, t3 n3, t4 n4, t5 n5, t6 n6, t7 n7, t8 n8, t9 n9
#define VAR20(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, t8, n8, t9, n9, t10, n10)                        \
    t1 n1, t2 n2, t3 n3, t4 n4, t5 n5, t6 n6, t7 n7, t8 n8, t9 n9, t10 n10
#define VAR(args...)                                                                                                   \
    GET_MACRO(args, VAR20, VAR19, VAR18, VAR17, VAR16, VAR15, VAR14, VAR13, VAR12, VAR11, VAR10, VAR9, VAR8, VAR7,     \
              VAR6, VAR5, VAR4, VAR3, VAR2, VAR1)                                                                      \
    (args)
#define NEW(Uname, Dname, param...)                                                                                    \
    Uname(VAR(param))                                                                                                  \
    {                                                                                                                  \
        self = tgi_##Dname##_create(NAME(param));                                                                      \
    }                                                                                                                  \
    static Uname create(VAR(param))                                                                                    \
    {                                                                                                                  \
        return Uname(tgi_##Dname##_create(NAME(param)));                                                               \
    }
#define METHOD1(ret, name)                                                                                             \
    ret name()                                                                                                         \
    {                                                                                                                  \
        return self->vptr->name(self);                                                                                 \
    }
#define METHOD2(ret, name, param...)                                                                                   \
    ret name(VAR(param))                                                                                               \
    {                                                                                                                  \
        return self->vptr->name(self, NAME(param));                                                                    \
    }
#define METHOD(args...)                                                                                                \
    GET_MACRO(args, METHOD2, METHOD2, METHOD2, METHOD2, METHOD2, METHOD2, METHOD2, METHOD2, METHOD2, METHOD2, METHOD2, \
              METHOD2, METHOD2, METHOD2, METHOD2, METHOD2, METHOD2, METHOD2, METHOD1, METHOD1)                         \
    (args)

/* type defined */
typedef TGI_Backend Backend;
typedef TGI_Encoding Encoding;
typedef TGI_WindowStyle WindowStyle;
typedef TGI_FontStyle FontStyle;
typedef TGI_TextAlign TextAlign;
typedef TGI_Color Color;
typedef TGI_Point Point;
typedef TGI_Rect Rect;
typedef TGI_KeyEvent KeyEvent;
typedef TGI_MouseEvent MouseEvent;
/* class predefined */
class Application;
class Window;
class Graphics;
class Image;
class Font;
class Timer;

/* class Graphics */
BEGIN_CLASS(Graphics, graphics)
METHOD(void, free)
METHOD(int, clear, Color, color)
METHOD(int, set_color, Color, color)
METHOD(int, set_width, float, width)
METHOD(int, draw_line, float, x1, float, y1, float, x2, float, y2)
METHOD(int, draw_arc, float, x, float, y, float, width, float, height, float, start_angle, float, sweep_angle)
METHOD(int, draw_rect, float, x, float, y, float, width, float, height)
METHOD(int, draw_ellipse, float, x, float, y, float, width, float, height)
METHOD(int, draw_pie, float, x, float, y, float, width, float, height, float, start_angle, float, sweep_angle)
METHOD(int, draw_polygon, const TGI_Point *, points, int, count)
METHOD(int, fill_rect, float, x, float, y, float, width, float, height)
METHOD(int, fill_ellipse, float, x, float, y, float, width, float, height)
METHOD(int, fill_pie, float, x, float, y, float, width, float, height, float, start_angle, float, sweep_angle)
METHOD(int, fill_polygon, const TGI_Point *, points, int, count)
METHOD(int, draw_image, const TGI_Image *, image, float, x, float, y)
METHOD(int, draw_image_rect, const TGI_Image *, image, float, x, float, y, float, width, float, height)
METHOD(int, draw_image_ex, const TGI_Image *, image, float, x, float, y, float, src_x, float, src_y, float, src_width,
       float, src_height)
METHOD(int, draw_image_rect_ex, const TGI_Image *, image, float, x, float, y, float, width, float, height, float, src_x,
       float, src_y, float, src_width, float, src_height)
METHOD(int, draw_text, const char *, text, const TGI_Font *, font, float, x, float, y)
METHOD(int, draw_text_rect, const char *, text, const TGI_Font *, font, float, x, float, y, float, width, float, height)
END_CLASS()

/* class Image */
BEGIN_CLASS(Image, image)
METHOD(void, free)
METHOD(TGI_Image *, clone)
METHOD(int, get_size, Rect *, rect)
METHOD(TGI_Graphics *, create_graphics)
END_CLASS()

/* class Window */
BEGIN_CLASS(Window, window)
METHOD(void, free)
typedef int TGIAPI OnCloseCallback(TGI_Window *wnd);
typedef void TGIAPI OnPaintCallback(TGI_Window *wnd);
typedef void TGIAPI OnSizeCallback(TGI_Window *wnd, float new_width, float new_height);
typedef void TGIAPI OnKeyCallback(TGI_Window *wnd, KeyEvent *e);
typedef void TGIAPI OnMouseCallback(TGI_Window *wnd, MouseEvent *e);
METHOD(void, on_close, OnCloseCallback, callback)
METHOD(void, on_paint, OnPaintCallback, callback)
METHOD(void, on_size, OnSizeCallback, callback)
METHOD(void, on_key, OnKeyCallback, callback)
METHOD(void, on_mouse, OnMouseCallback, callback)
METHOD(int, is_key_down, char, key)
METHOD(void, show)
METHOD(void, paint)
METHOD(int, set_style, WindowStyle, style)
METHOD(int, get_size, Rect *, rect)
METHOD(int, set_size, int, width, int, height)
METHOD(int, set_min_size, int, width, int, height)
METHOD(int, set_max_size, int, width, int, height)
METHOD(int, set_title, const char *, title)
METHOD(TGI_Graphics *, create_graphics)
METHOD(TGI_Image *, create_image)
END_CLASS()

/* class Font */
BEGIN_CLASS(Font, font)
METHOD(void, free)
METHOD(int, set_align, TextAlign, align)
METHOD(int, set_vertical_align, TextAlign, align)
END_CLASS()

/* class Timer */
BEGIN_CLASS(Timer, timer)
METHOD(void, free)
END_CLASS()

/* class Application */
BEGIN_CLASS(Application, application)
METHOD(void, free)
typedef void TGIAPI TimerCallback(TGI_Timer *timer);
NEW(Application, application, Backend, backend, Encoding, encoding)
METHOD(void, exec)
METHOD(int, exec_once)
METHOD(TGI_Window *, create_window)
METHOD(TGI_Image *, create_image, int, width, int, height)
METHOD(TGI_Image *, create_image_from_file, const char *, filename)
METHOD(TGI_Font *, create_font, const char *, name, float, size, TGI_FontStyle, style)
METHOD(TGI_Timer *, create_timer, unsigned int, delay, int, type, TimerCallback, callback)
END_CLASS()

} // namespace tgi
#endif

#endif