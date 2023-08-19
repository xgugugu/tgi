/**
 * @file tgi.h
 * @author xgugugu
 * @brief Tiny Graphics Interfaces
 * @brief C语言的极简图形库
 * @note 本库支持自动DPI缩放，如无特殊说明，所有坐标（像素）均为逻辑坐标（逻辑像素）
 */

#ifndef TGI_H
#define TGI_H

#include <stdarg.h>

#define TGIAPI __stdcall
#define TGICB TGIAPI

/**
 * @brief 图形后端类型
 * @see TGI_BACKEND_GDI
 */
typedef enum TGI_Backend
{
    /**
     * @brief GDI/GDI+ 图形后端，支持 Windows XP 及以上的操作系统
     */
    TGI_BACKEND_GDI
} TGI_Backend;

/**
 * @brief 文本编码类型
 * @see TGI_ENCODING_UTF8
 * @see TGI_ENCODING_ANSI
 */
typedef enum TGI_Encoding
{
    /**
     * @brief UTF-8 编码
     */
    TGI_ENCODING_UTF8,
    /**
     * @brief ANSI 编码
     * @attention 仅支持 Windows 操作系统
     */
    TGI_ENCODING_ANSI
} TGI_Encoding;

/**
 * @brief 应用对象类型
 * @see tgi_application_create
 * @see tgi_application_free
 * @see tgi_application_exec
 * @see tgi_application_exec_once
 * @see tgi_application_create_window
 * @see tgi_application_create_image
 * @see tgi_application_create_image_from_file
 * @see tgi_application_create_font
 * @see tgi_application_create_timer
 */
typedef struct TGI_Application
{
    const struct vtable_TGI_Application_t *vptr;
} TGI_Application;

/**
 * @brief 窗口对象类型
 * @see tgi_application_create_window
 * @see tgi_window_free
 * @see tgi_window_on_close
 * @see tgi_window_on_paint
 * @see tgi_window_on_size
 * @see tgi_window_on_key
 * @see tgi_window_on_mouse
 * @see tgi_window_is_key_down
 * @see tgi_window_show
 * @see tgi_window_paint
 * @see tgi_window_set_style
 * @see tgi_window_set_size
 * @see tgi_window_get_size
 * @see tgi_window_set_min_size
 * @see tgi_window_set_max_size
 * @see tgi_window_set_title
 * @see tgi_window_create_graphics
 * @see tgi_window_create_image
 */
typedef struct TGI_Window
{
    const struct vtable_TGI_Window_t *vptr;
} TGI_Window;
/**
 * @brief 窗口风格类型
 * @see TGI_WINDOWSTYLE_WINDOW
 * @see TGI_WINDOWSTYLE_BORDER
 * @see TGI_WINDOWSTYLE_CAPTION
 * @see TGI_WINDOWSTYLE_RESIZE
 * @see TGI_WINDOWSTYLE_MINIMIZEBOX
 * @see TGI_WINDOWSTYLE_MAXIMIZEBOX
 * @see TGI_WINDOWSTYLE_DEFAULT
 */
typedef enum TGI_WindowStyle
{
    /**
     * @brief 基础
     */
    TGI_WINDOWSTYLE_WINDOW = 0,
    /**
     * @brief 有边框
     */
    TGI_WINDOWSTYLE_BORDER = 1,
    /**
     * @brief 有标题
     */
    TGI_WINDOWSTYLE_CAPTION = 2,
    /**
     * @brief 可调节大小
     */
    TGI_WINDOWSTYLE_RESIZE = 4,
    /**
     * @brief 有最小化按钮
     */
    TGI_WINDOWSTYLE_MINIMIZEBOX = 8,
    /**
     * @brief 有最大化按钮
     */
    TGI_WINDOWSTYLE_MAXIMIZEBOX = 16,
    /**
     * @brief 默认
     */
    TGI_WINDOWSTYLE_DEFAULT = TGI_WINDOWSTYLE_WINDOW | TGI_WINDOWSTYLE_BORDER | TGI_WINDOWSTYLE_CAPTION |
                              TGI_WINDOWSTYLE_RESIZE | TGI_WINDOWSTYLE_MINIMIZEBOX | TGI_WINDOWSTYLE_MAXIMIZEBOX,
} TGI_WindowStyle;

/**
 * @brief 图形对象类型
 * @see tgi_window_create_graphics
 * @see tgi_image_create_graphics
 * @see tgi_graphics_free
 * @see tgi_graphics_clear
 * @see tgi_graphics_set_color
 * @see tgi_graphics_set_width
 * @see tgi_graphics_draw_line
 * @see tgi_graphics_draw_arc
 * @see tgi_graphics_draw_rect
 * @see tgi_graphics_draw_ellipse
 * @see tgi_graphics_draw_pie
 * @see tgi_graphics_draw_polygon
 * @see tgi_graphics_fill_rect
 * @see tgi_graphics_fill_ellipse
 * @see tgi_graphics_fill_pie
 * @see tgi_graphics_fill_polygon
 * @see tgi_graphics_draw_image
 * @see tgi_graphics_draw_image_rect
 * @see tgi_graphics_draw_image_ex
 * @see tgi_graphics_draw_text
 * @see tgi_graphics_draw_text_rect
 */
typedef struct TGI_Graphics
{
    const struct vtable_TGI_Graphics_t *vptr;
} TGI_Graphics;

/**
 * @brief 图像对象类型
 * @see tgi_application_create_image
 * @see tgi_application_create_image_from_file
 * @see tgi_window_create_image
 * @see tgi_image_free
 * @see tgi_image_clone
 * @see tgi_image_get_size
 * @see tgi_image_create_graphics
 */
typedef struct TGI_Image
{
    const struct vtable_TGI_Image_t *vptr;
} TGI_Image;

/**
 * @brief 字体对象类型
 * @see tgi_application_create_font
 * @see tgi_font_free
 * @see tgi_font_set_align
 * @see tgi_font_set_vertical_align
 */
typedef struct TGI_Font
{
    const struct vtable_TGI_Font_t *vptr;
} TGI_Font;
/**
 * @brief 字体样式类型
 * @see TGI_FONTSTYLE_REGULAR
 * @see TGI_FONTSTYLE_BOLD
 * @see TGI_FONTSTYLE_ITALIC
 * @see TGI_FONTSTYLE_UNDERLINE
 * @see TGI_FONTSTYLE_STRIKEOUT
 */
typedef enum TGI_FontStyle
{
    /**
     * @brief 标准
     */
    TGI_FONTSTYLE_REGULAR = 0,
    /**
     * @brief 加粗
     */
    TGI_FONTSTYLE_BOLD = 1,
    /**
     * @brief 斜体
     */
    TGI_FONTSTYLE_ITALIC = 2,
    /**
     * @brief 下划线
     */
    TGI_FONTSTYLE_UNDERLINE = 4,
    /**
     * @brief 删除线
     */
    TGI_FONTSTYLE_STRIKEOUT = 8
} TGI_FontStyle;
/**
 * @brief 字体对齐方法类型
 * @see TGI_TEXTALIGN_LEFT
 * @see TGI_TEXTALIGN_CENTER
 * @see TGI_TEXTALIGN_RIGHT
 * @see TGI_TEXTALIGN_TOP
 * @see TGI_TEXTALIGN_BOTTOM
 */
typedef enum TGI_TextAlign
{
    /**
     * @brief 靠左
     */
    TGI_TEXTALIGN_LEFT = 0,
    /**
     * @brief 居中
     */
    TGI_TEXTALIGN_CENTER = 1,
    /**
     * @brief 靠右
     */
    TGI_TEXTALIGN_RIGHT = 2,
    /**
     * @brief 靠上
     */
    TGI_TEXTALIGN_TOP = TGI_TEXTALIGN_LEFT,
    /**
     * @brief 靠下
     */
    TGI_TEXTALIGN_BOTTOM = TGI_TEXTALIGN_RIGHT
} TGI_TextAlign;

/**
 * @brief 计时器对象类型
 * @see tgi_application_create_timer
 * @see tgi_timer_free
 */
typedef struct TGI_Timer
{
    const struct vtable_TGI_Timer_t *vptr;
} TGI_Timer;

/**
 * @brief 颜色类型
 * @see TGI_COLOR
 */
typedef unsigned int TGI_Color;
/**
 * @brief 创建一个ARGB颜色
 * @param a 透明度（0-255）
 * @param r 红色（0-255）
 * @param g 绿色（0-255）
 * @param b 蓝色（0-255）
 * @return 所创建的颜色
 */
#define TGI_COLOR(a, r, g, b)                                                                                          \
    ((((TGI_Color)(a)) << 24) | (((TGI_Color)(r)) << 16) | (((TGI_Color)(g)) << 8) | ((TGI_Color)(b)))
/**
 * @brief 创建一个ARGB颜色
 * @see TGI_COLOR
 */
static inline TGI_Color TGIAPI tgi_color(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
{
    return TGI_COLOR(a, r, g, b);
}

/**
 * @brief 点（坐标）类型
 */
typedef struct TGI_Point
{
    float x, y;
} TGI_Point;

/**
 * @brief 矩形类型
 */
typedef struct TGI_Rect
{
    float left, right, top, bottom;
} TGI_Rect;

/**
 * @brief 键盘事件类型
 * @see tgi_window_on_key
 */
typedef struct TGI_KeyEvent
{
    /**
     * @brief 事件类型
     * @attention 输入应当使用 TGI_KEYEVENT_INPUT 事件，
     *            因为 TGI_KEYEVENT_DOWN 和 TGI_KEYEVENT_UP 事件无法接收非ASCII字符
     */
    enum
    {
        /**
         * @brief 按键按下事件
         */
        TGI_KEYEVENT_DOWN,
        /**
         * @brief 按键抬起事件
         */
        TGI_KEYEVENT_UP,
        /**
         * @brief 输入事件
         */
        TGI_KEYEVENT_INPUT,
    } type;
    /**
     * @brief 当事件类型为 TGI_KEYEVENT_DOWN 或 TGI_KEYEVENT_UP 时，指向一个字符，表示按下按键的ASCII码
     * @brief 当事件类型为 TGI_KEYEVENT_INPUT 时，指向一个字符串，表示输入的内容
     */
    char *key;
} TGI_KeyEvent;
/**
 * @brief 鼠标事件类型
 * @see tgi_window_on_mouse
 */
typedef struct TGI_MouseEvent
{
    /**
     * @brief 事件类型
     */
    enum
    {
        /**
         * @brief 按键按下
         */
        TGI_MOUSEEVENT_DOWN,
        /**
         * @brief 按键抬起
         */
        TGI_MOUSEEVENT_UP,
        /**
         * @brief 双击
         */
        TGI_MOUSEEVENT_DOUBLE,
        /**
         * @brief 移动
         */
        TGI_MOUSEEVENT_MOVE,
    } type;
    /**
     * @brief 按键类型
     */
    enum
    {
        /**
         * @brief 左键
         */
        TGI_MOUSEEVENT_LEFT,
        /**
         * @brief 中键
         */
        TGI_MOUSEEVENT_MIDDLE,
        /**
         * @brief 右键
         */
        TGI_MOUSEEVENT_RIGHT,
    } buttom;
    /**
     * @brief 鼠标相对窗口的位置
     */
    float x, y;
} TGI_MouseEvent;

/**
 * @brief 应用对象的虚函数表（正常使用无需了解）
 */
struct vtable_TGI_Application_t
{
    void(TGIAPI *free)(TGI_Application *self);
    void(TGIAPI *exec)(TGI_Application *self);
    int(TGIAPI *exec_once)(TGI_Application *self);
    TGI_Window *(TGIAPI *create_window)(TGI_Application *self);
    TGI_Image *(TGIAPI *create_image)(TGI_Application *self, int width, int height);
    TGI_Image *(TGIAPI *create_image_from_file)(TGI_Application *self, const char *filename);
    TGI_Font *(TGIAPI *create_font)(TGI_Application *self, const char *name, float size, TGI_FontStyle style);
    TGI_Timer *(TGIAPI *create_timer)(TGI_Application *self, unsigned int delay, int type,
                                      void TGIAPI callback(TGI_Timer *timer));
};
/**
 * @brief 关闭应用并释放资源
 * @param self 应用对象指针
 */
static inline void TGIAPI tgi_application_free(TGI_Application *self)
{
    self->vptr->free(self);
}
/**
 * @brief 启动应用的事件循环
 * @param self 应用对象指针
 */
static inline void TGIAPI tgi_application_exec(TGI_Application *self)
{
    self->vptr->exec(self);
}
/**
 * @brief 处理一次应用事件
 * @param self 应用对象指针
 * @return 若函数成功且事件循环未结束，返回非零值；若事件循环结束，返回0；否则，返回-1
 */
static inline int TGIAPI tgi_application_exec_once(TGI_Application *self)
{
    return self->vptr->exec_once(self);
}
/**
 * @brief 创建一个窗口
 * @param self 应用对象指针
 * @return 若函数成功，返回所创建的窗口对象的指针；否则，返回NULL
 * @see TGI_Window
 */
static inline TGI_Window *TGIAPI tgi_application_create_window(TGI_Application *self)
{
    return self->vptr->create_window(self);
}
/**
 * @brief 创建一个图片
 * @param self 应用对象指针
 * @param width 图片的宽度（单位为真实像素）
 * @param height 图片的高度（单位为真实像素）
 * @return 若函数成功，返回所创建的图片对象的指针；否则，返回NULL
 * @attention 该函数创建的图片与当前屏幕缩放无关，操作这个图片始终使用真实像素（坐标）
 * @see TGI_Image
 */
static inline TGI_Image *TGIAPI tgi_application_create_image(TGI_Application *self, int width, int height)
{
    return self->vptr->create_image(self, width, height);
}
/**
 * @brief 从文件创建一个图片
 * @param self 应用对象指针
 * @param width 图片的宽度（单位为真实像素）
 * @param height 图片的高度（单位为真实像素）
 * @return 若函数成功，返回所创建的图片对象的指针；否则，返回NULL
 * @attention 该函数创建的图片与当前屏幕缩放无关，操作这个图片始终使用真实像素（坐标）
 * @see TGI_Image
 */
static inline TGI_Image *TGIAPI tgi_application_create_image_from_file(TGI_Application *self, const char *filename)
{
    return self->vptr->create_image_from_file(self, filename);
}
/**
 * @brief 创建一个字体
 * @param self 应用对象指针
 * @param name 字体名称
 * @param size 字体大小（单位为像素）
 * @return 若函数成功，返回所创建的字体对象的指针；否则，返回NULL
 * @see TGI_Font
 */
static inline TGI_Font *TGIAPI tgi_application_create_font(TGI_Application *self, const char *name, float size,
                                                           TGI_FontStyle style)
{
    return self->vptr->create_font(self, name, size, style);
}
/**
 * @brief 创建一个计时器
 * @param self 应用对象指针
 * @param delay 延时（单位为毫秒）
 * @param type 若为0，则在delay毫秒后调用回调函数；否则，在每隔delay毫秒调用一次回调函数
 * @param callback 回调函数
 * @return 若函数成功，返回所创建的计时器对象的指针；否则，返回NULL
 * @attention 请在合适的时机（如回调函数内），释放返回的计时器对象
 * @see TGI_Timer
 */
static inline TGI_Timer *TGIAPI tgi_application_create_timer(TGI_Application *self, unsigned int delay, int type,
                                                             void TGIAPI callback(TGI_Timer *timer))
{
    return self->vptr->create_timer(self, delay, type, callback);
}

/**
 * @brief 窗口对象的虚函数表（正常使用无需了解）
 */
struct vtable_TGI_Window_t
{
    void(TGIAPI *free)(TGI_Window *self);
    void(TGIAPI *on_close)(TGI_Window *self, int TGIAPI callback(TGI_Window *self));
    void(TGIAPI *on_paint)(TGI_Window *self, void TGIAPI callback(TGI_Window *self));
    void(TGIAPI *on_size)(TGI_Window *self, void TGIAPI callback(TGI_Window *self, float new_width, float new_height));
    void(TGIAPI *on_key)(TGI_Window *self, void TGIAPI callback(TGI_Window *self, TGI_KeyEvent *event));
    void(TGIAPI *on_mouse)(TGI_Window *self, void TGIAPI callback(TGI_Window *self, TGI_MouseEvent *event));
    int(TGIAPI *is_key_down)(TGI_Window *self, char key);
    void(TGIAPI *show)(TGI_Window *self);
    void(TGIAPI *paint)(TGI_Window *self);
    int(TGIAPI *set_style)(TGI_Window *self, TGI_WindowStyle style);
    int(TGIAPI *set_size)(TGI_Window *self, int width, int height);
    int(TGIAPI *get_size)(TGI_Window *self, TGI_Rect *rect);
    int(TGIAPI *set_min_size)(TGI_Window *self, int width, int height);
    int(TGIAPI *set_max_size)(TGI_Window *self, int width, int height);
    int(TGIAPI *set_title)(TGI_Window *self, const char *title);
    TGI_Graphics *(TGIAPI *create_graphics)(TGI_Window *self);
    TGI_Image *(TGIAPI *create_image)(TGI_Window *self);
};
/**
 * @brief 关闭窗口并释放资源
 * @param self 窗口对象指针
 */
static inline void TGIAPI tgi_window_free(TGI_Window *self)
{
    self->vptr->free(self);
}
/**
 * @brief 设置窗口关闭时将会调用的函数
 * @param self 窗口对象指针
 * @param callback 回调函数
 * @note 若回调函数返回0，则阻止窗口关闭；否则，允许窗口关闭
 */
static inline void TGIAPI tgi_window_on_close(TGI_Window *self, int TGIAPI callback(TGI_Window *self))
{
    self->vptr->on_close(self, callback);
}
/**
 * @brief 设置窗口需要绘制时将会调用的函数
 * @param self 窗口对象指针
 * @param callback 回调函数
 */
static inline void TGIAPI tgi_window_on_paint(TGI_Window *self, void TGIAPI callback(TGI_Window *self))
{
    self->vptr->on_paint(self, callback);
}
/**
 * @brief 设置窗口改变大小时将会调用的函数
 * @param self 窗口对象指针
 * @param callback 回调函数
 */
static inline void TGIAPI tgi_window_on_size(TGI_Window *self,
                                             void TGIAPI callback(TGI_Window *self, float new_width, float new_height))
{
    self->vptr->on_size(self, callback);
}
/**
 * @brief 设置出现键盘事件时将会调用的函数
 * @param self 窗口对象指针
 * @param callback 回调函数
 */
static inline void TGIAPI tgi_window_on_key(TGI_Window *self,
                                            void TGIAPI callback(TGI_Window *self, TGI_KeyEvent *event))
{
    self->vptr->on_key(self, callback);
}
/**
 * @brief 设置出现鼠标事件时将会调用的函数
 * @param self 窗口对象指针
 * @param callback 回调函数
 */
static inline void TGIAPI tgi_window_on_mouse(TGI_Window *self,
                                              void TGIAPI callback(TGI_Window *self, TGI_MouseEvent *event))
{
    self->vptr->on_mouse(self, callback);
}
/**
 * @brief 判断键盘按键是否按下
 * @param self 窗口对象指针
 * @param key 表示键盘按键的ASCII码
 * @return 若按键按下，则返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_window_is_key_down(TGI_Window *self, char key)
{
    return self->vptr->is_key_down(self, key);
}
/**
 * @brief 激活窗口并以当前大小和位置显示窗口
 * @param self 窗口对象指针
 */
static inline void TGIAPI tgi_window_show(TGI_Window *self)
{
    self->vptr->show(self);
}
/**
 * @brief 调用设置的 on_paint 回调函数
 * @param self 窗口对象指针
 */
static inline void TGIAPI tgi_window_paint(TGI_Window *self)
{
    self->vptr->paint(self);
}
/**
 * @brief 设置窗口风格
 * @param self 窗口对象指针
 * @param style 窗口风格
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_window_set_style(TGI_Window *self, TGI_WindowStyle style)
{
    return self->vptr->set_style(self, style);
}
/**
 * @brief 设置窗口的大小
 * @param self 窗口对象指针
 * @param width 窗口的新宽度
 * @param height 窗口的新高度
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_window_set_size(TGI_Window *self, int width, int height)
{
    return self->vptr->set_size(self, width, height);
}
/**
 * @brief 获取窗口大小
 * @param self 窗口对象指针
 * @param rect 指向 TGI_Rect 对象的指针
 * @return 若函数成功，返回非零值；否则，返回0
 * @note rect的right成员存放窗口的宽度，bottom成员存放窗口的高度
 */
static inline int TGIAPI tgi_window_get_size(TGI_Window *self, TGI_Rect *rect)
{
    return self->vptr->get_size(self, rect);
}
/**
 * @brief 设置窗口的最大小大小
 * @param self 窗口对象指针
 * @param width 窗口的最小宽度
 * @param height 窗口的最小高度
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_window_set_min_size(TGI_Window *self, int width, int height)
{
    return self->vptr->set_min_size(self, width, height);
}
/**
 * @brief 设置窗口的最大大小
 * @param self 窗口对象指针
 * @param width 窗口的最大宽度
 * @param height 窗口的最大高度
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_window_set_max_size(TGI_Window *self, int width, int height)
{
    return self->vptr->set_max_size(self, width, height);
}
/**
 * @brief 设置窗口的标题
 * @param self 窗口对象指针
 * @param title 窗口的新标题
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_window_set_title(TGI_Window *self, const char *title)
{
    return self->vptr->set_title(self, title);
}
/**
 * @brief 创建绘图对象
 * @param self 窗口对象指针
 * @return 若函数成功，返回所创建绘图对象的指针；否则，返回NULL
 * @attention 不能在释放该对象前创建第二个绘图对象
 * @see TGI_Graphics
 */
static inline TGI_Graphics *TGIAPI tgi_window_create_graphics(TGI_Window *self)
{
    return self->vptr->create_graphics(self);
}
/**
 * @brief 创建与窗口关联的图像对象
 * @param self 窗口对象指针
 * @return 若函数成功，返回所创建图像对象的指针；否则，返回NULL
 * @attention 该函数创建的图片大小与窗口大小相等，且拥有相同的缩放设置
 * @see TGI_Graphics
 */
static inline TGI_Image *TGIAPI tgi_window_create_image(TGI_Window *self)
{
    return self->vptr->create_image(self);
}

/**
 * @brief 图形对象的虚函数表（正常使用无需了解）
 */
struct vtable_TGI_Graphics_t
{
    void(TGIAPI *free)(TGI_Graphics *self);
    int(TGIAPI *clear)(TGI_Graphics *self, TGI_Color color);
    int(TGIAPI *set_color)(TGI_Graphics *self, TGI_Color color);
    int(TGIAPI *set_width)(TGI_Graphics *self, float width);
    int(TGIAPI *draw_line)(TGI_Graphics *self, float x1, float y1, float x2, float y2);
    int(TGIAPI *draw_arc)(TGI_Graphics *self, float x, float y, float width, float height, float start_angle,
                          float sweep_angle);
    int(TGIAPI *draw_rect)(TGI_Graphics *self, float x, float y, float width, float height);
    int(TGIAPI *draw_ellipse)(TGI_Graphics *self, float x, float y, float width, float height);
    int(TGIAPI *draw_pie)(TGI_Graphics *self, float x, float y, float width, float height, float start_angle,
                          float sweep_angle);
    int(TGIAPI *draw_polygon)(TGI_Graphics *self, const TGI_Point *points, int count);
    int(TGIAPI *fill_rect)(TGI_Graphics *self, float x, float y, float width, float height);
    int(TGIAPI *fill_ellipse)(TGI_Graphics *self, float x, float y, float width, float height);
    int(TGIAPI *fill_pie)(TGI_Graphics *self, float x, float y, float width, float height, float start_angle,
                          float sweep_angle);
    int(TGIAPI *fill_polygon)(TGI_Graphics *self, const TGI_Point *points, int count);
    int(TGIAPI *draw_image)(TGI_Graphics *self, const TGI_Image *image, float x, float y);
    int(TGIAPI *draw_image_rect)(TGI_Graphics *self, const TGI_Image *image, float x, float y, float width,
                                 float height);
    int(TGIAPI *draw_image_ex)(TGI_Graphics *self, const TGI_Image *image, float x, float y, float src_x, float src_y,
                               float src_width, float src_height);
    int(TGIAPI *draw_image_rect_ex)(TGI_Graphics *self, const TGI_Image *image, float x, float y, float width,
                                    float height, float src_x, float src_y, float src_width, float src_height);
    int(TGIAPI *draw_text)(TGI_Graphics *self, const char *text, const TGI_Font *font, float x, float y);
    int(TGIAPI *draw_text_rect)(TGI_Graphics *self, const char *text, const TGI_Font *font, float x, float y,
                                float width, float height);
};
/**
 * @brief 结束绘图并释放资源
 * @param self 绘图对象指针
 */
static inline void TGIAPI tgi_graphics_free(TGI_Graphics *self)
{
    self->vptr->free(self);
}
/**
 * @brief 绘制背景颜色
 * @param self 绘图对象指针
 * @param color 颜色
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_clear(TGI_Graphics *self, TGI_Color color)
{
    return self->vptr->clear(self, color);
}
/**
 * @brief 设置画笔颜色
 * @param self 绘图对象指针
 * @param color 颜色
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_set_color(TGI_Graphics *self, TGI_Color color)
{
    return self->vptr->set_color(self, color);
}
/**
 * @brief 设置画笔宽度
 * @param self 绘图对象指针
 * @param width 宽度
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_set_width(TGI_Graphics *self, float width)
{
    return self->vptr->set_width(self, width);
}
/**
 * @brief 绘制一条从(x1, y1)到(x2,y2)的直线
 * @param self 绘图对象指针
 * @param x1 直线起点的x坐标
 * @param y1 直线起点的y坐标
 * @param x2 直线终点的x坐标
 * @param y2 直线终点的y坐标
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_draw_line(TGI_Graphics *self, float x1, float y1, float x2, float y2)
{
    return self->vptr->draw_line(self, x1, y1, x2, y2);
}
/**
 * @brief 绘制一条弧线
 * @param self 绘图对象指针
 * @param x 圆弧所在椭圆的外切矩形的左上角x坐标
 * @param y 圆弧所在椭圆的外切矩形的左上角y坐标
 * @param width 圆弧所在椭圆的外切矩形的宽度
 * @param height 圆弧所在椭圆的外切矩形的高度
 * @param start_angle 圆弧起始角的角度
 * @param sweep_angle 圆弧终止角的角度
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_draw_arc(TGI_Graphics *self, float x, float y, float width, float height,
                                               float start_angle, float sweep_angle)
{
    return self->vptr->draw_arc(self, x, y, width, height, start_angle, sweep_angle);
}
/**
 * @brief 绘制一个矩形
 * @param self 绘图对象指针
 * @param x 矩形的左上角x坐标
 * @param y 矩形的左上角y坐标
 * @param width 矩形的宽度
 * @param height 矩形的高度
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_draw_rect(TGI_Graphics *self, float x, float y, float width, float height)
{
    return self->vptr->draw_rect(self, x, y, width, height);
}
/**
 * @brief 绘制一个椭圆
 * @param self 绘图对象指针
 * @param x 椭圆的外切矩形的左上角x坐标
 * @param y 椭圆的外切矩形的左上角y坐标
 * @param width 椭圆的外切矩形的宽度
 * @param height 椭圆的外切矩形的高度
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_draw_ellipse(TGI_Graphics *self, float x, float y, float width, float height)
{
    return self->vptr->draw_ellipse(self, x, y, width, height);
}
/**
 * @brief 绘制一个扇形
 * @param self 绘图对象指针
 * @param x 扇形所在椭圆的外切矩形的左上角x坐标
 * @param y 扇形所在椭圆的外切矩形的左上角y坐标
 * @param width 扇形所在椭圆的外切矩形的宽度
 * @param height 扇形所在椭圆的外切矩形的高度
 * @param start_angle 扇形起始角的角度
 * @param sweep_angle 扇形终止角的角度
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_draw_pie(TGI_Graphics *self, float x, float y, float width, float height,
                                               float start_angle, float sweep_angle)
{
    return self->vptr->draw_pie(self, x, y, width, height, start_angle, sweep_angle);
}
/**
 * @brief 绘制一个多边形
 * @param self 绘图对象指针
 * @param points 表示多边形顶点的数组
 * @param count 多边形点的数目
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_draw_polygon(TGI_Graphics *self, const TGI_Point *points, int count)
{
    return self->vptr->draw_polygon(self, points, count);
}
/**
 * @brief 填充一个矩形
 * @param self 绘图对象指针
 * @param x 矩形的左上角x坐标
 * @param y 矩形的左上角y坐标
 * @param width 矩形的宽度
 * @param height 矩形的高度
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_fill_rect(TGI_Graphics *self, float x, float y, float width, float height)
{
    return self->vptr->fill_rect(self, x, y, width, height);
}
/**
 * @brief 填充一个椭圆
 * @param self 绘图对象指针
 * @param x 椭圆的外切矩形的左上角x坐标
 * @param y 椭圆的外切矩形的左上角y坐标
 * @param width 椭圆的外切矩形的宽度
 * @param height 椭圆的外切矩形的高度
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_fill_ellipse(TGI_Graphics *self, float x, float y, float width, float height)
{
    return self->vptr->fill_ellipse(self, x, y, width, height);
}
/**
 * @brief 填充一个扇形
 * @param self 绘图对象指针
 * @param x 扇形所在椭圆的外切矩形的左上角x坐标
 * @param y 扇形所在椭圆的外切矩形的左上角y坐标
 * @param width 扇形所在椭圆的外切矩形的宽度
 * @param height 扇形所在椭圆的外切矩形的高度
 * @param start_angle 扇形起始角的角度
 * @param sweep_angle 扇形终止角的角度
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_fill_pie(TGI_Graphics *self, float x, float y, float width, float height,
                                               float start_angle, float sweep_angle)
{
    return self->vptr->fill_pie(self, x, y, width, height, start_angle, sweep_angle);
}
/**
 * @brief 填充一个多边形
 * @param self 绘图对象指针
 * @param points 表示多边形顶点的数组
 * @param count 多边形点的数目
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_fill_polygon(TGI_Graphics *self, const TGI_Point *points, int count)
{
    return self->vptr->fill_polygon(self, points, count);
}
/**
 * @brief 在指定的位置绘制一个图片
 * @param self 绘图对象指针
 * @param image 图片对象指针
 * @param x 表示图片左上角的x坐标
 * @param y 表示图片左上角的y坐标
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_draw_image(TGI_Graphics *self, const TGI_Image *image, float x, float y)
{
    return self->vptr->draw_image(self, image, x, y);
}
/**
 * @brief 在指定的矩形内绘制一个图片
 * @param self 绘图对象指针
 * @param image 图片对象指针
 * @param x 表示图片左上角的x坐标
 * @param y 表示图片左上角的y坐标
 * @param width 表示绘制的宽度
 * @param height 表示绘制的高度
 * @note 若图片大小与矩形的大小不等，则会拉伸图片以适应矩形大小
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_draw_image_rect(TGI_Graphics *self, const TGI_Image *image, float x, float y,
                                                      float width, float height)
{
    return self->vptr->draw_image_rect(self, image, x, y, width, height);
}
/**
 * @brief 在指定的位置绘制图片的部分
 * @param self 绘图对象指针
 * @param image 图片对象指针
 * @param x 表示图片左上角的x坐标（单位为逻辑像素）
 * @param y 表示图片左上角的y坐标（单位为逻辑像素）
 * @param src_x 表示截取图片左上角的x坐标（单位为真实像素）
 * @param src_y 表示截取图片左上角的y坐标（单位为真实像素）
 * @param src_width 表示截取图片的宽度（单位为真实像素）
 * @param src_height 表示截取图片的高度（单位为真实像素）
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_draw_image_ex(TGI_Graphics *self, const TGI_Image *image, float x, float y,
                                                    float src_x, float src_y, float src_width, float src_height)
{
    return self->vptr->draw_image_ex(self, image, x, y, src_x, src_y, src_width, src_height);
}
/**
 * @brief 在指定的位置绘制图片的部分
 * @param self 绘图对象指针
 * @param image 图片对象指针
 * @param x 表示绘制左上角的x坐标（单位为逻辑像素）
 * @param y 表示绘制左上角的y坐标（单位为逻辑像素）
 * @param width 表示绘制的宽度（单位为逻辑像素）
 * @param height 表示绘制的高度（单位为逻辑像素）
 * @param src_x 表示截取图片左上角的x坐标（单位为真实像素）
 * @param src_y 表示截取图片左上角的y坐标（单位为真实像素）
 * @param src_width 表示截取图片的宽度（单位为真实像素）
 * @param src_height 表示截取图片的高度（单位为真实像素）
 * @return 若函数成功，返回非零值；否则，返回0
 * @since v0.2.0
 */
static inline int TGIAPI tgi_graphics_draw_image_rect_ex(TGI_Graphics *self, const TGI_Image *image, float x, float y,
                                                         float width, float height, float src_x, float src_y,
                                                         float src_width, float src_height)
{
    return self->vptr->draw_image_rect_ex(self, image, x, y, width, height, src_x, src_y, src_width, src_height);
}
/**
 * @brief 在指定位置绘制文字
 * @param self 绘图对象指针
 * @param text 要绘制的字符串
 * @param font 绘制的字体
 * @param x 表示绘制位置的x坐标
 * @param y 表示绘制位置的y坐标
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_draw_text(TGI_Graphics *self, const char *text, const TGI_Font *font, float x,
                                                float y)
{
    return self->vptr->draw_text(self, text, font, x, y);
}
/**
 * @brief 在指定矩形绘制文字
 * @param self 绘图对象指针
 * @param text 要绘制的字符串
 * @param font 绘制的字体
 * @param x 表示绘制矩形左上角的x坐标
 * @param y 表示绘制矩形左上角的y坐标
 * @param width 表示绘制矩形的高度
 * @param height 表示绘制矩形的宽度
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_graphics_draw_text_rect(TGI_Graphics *self, const char *text, const TGI_Font *font,
                                                     float x, float y, float width, float height)
{
    return self->vptr->draw_text_rect(self, text, font, x, y, width, height);
}

/**
 * @brief 图片对象的虚函数表（正常使用无需了解）
 */
struct vtable_TGI_Image_t
{
    void(TGIAPI *free)(TGI_Image *self);
    TGI_Image *(TGIAPI *clone)(TGI_Image *self);
    int(TGIAPI *get_size)(TGI_Image *self, TGI_Rect *rect);
    TGI_Graphics *(TGIAPI *create_graphics)(TGI_Image *self);
};
/**
 * @brief 释放图片资源
 * @param self 图片对象指针
 */
static inline void TGIAPI tgi_image_free(TGI_Image *self)
{
    self->vptr->free(self);
}
/**
 * @brief 复制图片
 * @param self 图片对象指针
 * @return 若函数成功，返回复制的图片对象指针；否则，返回NULL
 * @see TGI_Image
 */
static inline TGI_Image *TGIAPI tgi_image_clone(TGI_Image *self)
{
    return self->vptr->clone(self);
}
/**
 * @brief 获取图片大小
 * @param self 图片对象指针
 * @param rect 指向 TGI_Rect 对象的指针
 * @return 若函数成功，返回非零值；否则，返回0
 * @note rect的right成员存放图片的宽度，bottom成员存放图片的高度（单位为真实像素）
 */
static inline int TGIAPI tgi_image_get_size(TGI_Image *self, TGI_Rect *rect)
{
    return self->vptr->get_size(self, rect);
}
/**
 * @brief 开始在图片上绘图
 * @param self 图片对象指针
 * @return 若函数成功，返回创建的绘图对象指针；否则，返回0
 * @attention 绘图对象的缩放设置同图片的缩放设置
 * @see TGI_Graphics
 */
static inline TGI_Graphics *TGIAPI tgi_image_create_graphics(TGI_Image *self)
{
    return self->vptr->create_graphics(self);
}

/**
 * @brief 字体对象的虚函数表（正常使用无需了解）
 */
struct vtable_TGI_Font_t
{
    void(TGIAPI *free)(TGI_Font *self);
    int(TGIAPI *set_align)(TGI_Font *self, TGI_TextAlign align);
    int(TGIAPI *set_vertical_align)(TGI_Font *self, TGI_TextAlign align);
};
/**
 * @brief 释放字体资源
 * @param self 字体对象指针
 */
static inline void TGIAPI tgi_font_free(TGI_Font *self)
{
    self->vptr->free(self);
}
/**
 * @brief 设置横向的文本对齐方式
 * @param self 字体对象指针
 * @param align 文本对齐方式
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_font_set_align(TGI_Font *self, TGI_TextAlign align)
{
    return self->vptr->set_align(self, align);
}
/**
 * @brief 设置竖直方向的文本对齐方式
 * @param self 字体对象指针
 * @param align 文本对齐方式
 * @return 若函数成功，返回非零值；否则，返回0
 */
static inline int TGIAPI tgi_font_set_vertical_align(TGI_Font *self, TGI_TextAlign align)
{
    return self->vptr->set_vertical_align(self, align);
}

/**
 * @brief 计时器对象的虚函数表（正常使用无需了解）
 */
struct vtable_TGI_Timer_t
{
    void(TGIAPI *free)(TGI_Timer *self);
};
/**
 * @brief 关闭计时器并释放资源
 * @param self 计时器对象指针
 */
static inline void tgi_timer_free(TGI_Timer *self)
{
    self->vptr->free(self);
}

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief 创建使用指定绘图后端的应用
     * @param backend 需要使用的图形后端
     * @param encoding 需要使用的编码方式
     * @return 若函数成功，返回所创建应用对象的指针；否则，返回NULL
     * @attention 推荐使用 UTF-8 编码，因为其在所有平台上都将是可用的；
     *            其余编码方式仅适用于不支持 UTF-8 编码的开发环境（如：Dev-C++）
     * @see TGI_Application
     */
    TGI_Application *TGIAPI tgi_application_create(TGI_Backend backend, TGI_Encoding encoding);

#ifdef __cplusplus
}
#endif

#endif