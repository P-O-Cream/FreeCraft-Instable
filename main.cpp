/*
Copyright(c) 2023 P.O Cream(田陈啸) and all contributors
All right Reserved
    
    Distributed under GPL license
    See copy at https://opensource.org/licenses/GPL-3.0
*/
/**
 * FreeCraft Instable -  sandbox based on C plus plus
 * From FreeWorld(The same writer) based on Python
**/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <locale>
#include <clocale>
#include <cwchar>
#include <typeinfo>
#include <algorithm>
#include <climits>
#include <sstream>
#include <queue>
#include <set>
#include <map>
#include <iomanip>
#include <unistd.h>
#include <termios.h>
#include <cstdio>
#include <cstring>
#include <random>

/* Copyright(c) 2021 Xinrui Zhang,JiaCheng Pan and all contributors
All right Reserved
    
    Distributed under GPL license
    See copy at https://opensource.org/licenses/GPL-3.0
*/

#define __hasPrintSpeedLimit
const bool online_xes = true;

namespace stdcolor_256{
    const std::string red    = "\033[48;5;1m";//红色
    const std::string yellow = "\033[48;5;3m";//黄色
    const std::string green  = "\033[48;5;2m";//绿色
    const std::string blue   = "\033[48;5;4m";//蓝色
    const std::string cyan   = "\033[48;5;5m";//青色
    const std::string purple = "\033[48;5;6m";//紫色
    const std::string white  = "\033[48;5;255m";//白色
    const std::string gray   = "\033[48;5;8m";//灰色
    const std::string black  = "\033[48;5;0m";//黑色
    const std::string darkgray = "\033[48;5;235m";//暗灰色
    const std::string light_red    = "\033[48;5;9m";//亮红色
    const std::string light_yellow = "\033[48;5;11m";//亮黄色
    const std::string light_green  = "\033[48;5;10m";//亮绿色
    const std::string light_blue   = "\033[48;5;12m";//亮蓝色
    const std::string light_cyan   = "\033[48;5;13m";//亮青色
    const std::string light_purple = "\033[48;5;14m";//亮紫色
    const std::string light_white  = "\033[48;5;15m";//亮白色
    const std::string dark_black  = "\033[48;5;16m";//纯黑色
    inline std::string to256color(int incolor){
        return "\033[48;5;"+std::to_string(std::abs(incolor%256))+"m";
    }//数字直接转换至256色字符串
    const std::string code_background = stdcolor_256::darkgray;//代码背景色
};//标准256背景色
namespace stdcolor_RGB{
    const std::string pure_red =    "\033[48;2;255;0;0m";//      颜色#FF0000
    const std::string pure_green =  "\033[48;2;0;255;0m";//      颜色#00FF00
    const std::string pure_blue  =  "\033[48;2;0;0;255m";//      颜色#0000FF
    const std::string pure_black =  "\033[48;2;0;0;0m";//        颜色#000000
    const std::string pure_white =  "\0333[48;2;255;255;255m";// 颜色#FFFFFF
    const std::string pure_yellow = "\033[48;2;255;255;0m";//    颜色#FFFF00
    const std::string pure_violet = "\033[48;2;255;0;255m";//    颜色#FF00FF
    const std::string pure_cyan   = "\033[48;2;0;255;255m";//    颜色#00FFFF
    inline std::string torgbcolor(unsigned char inred,
                                   unsigned char ingreen,
                                   unsigned char inblue){
        return "\033[48;2;" + std::to_string(inred) + ";" +
                               std::to_string(ingreen) + ";" +
                               std::to_string(inblue) + "m";
    }//数字直接转换至RGB字符串
};//RGB标准颜色库
namespace stdtext{
    const std::string text_white = "\033[38;5;255m";//文字纯白
    const std::string text_red = "\033[38;5;9m";//文字红色
    const std::string text_orange = "\033[38;5;208m";//文字橙色
    const std::string text_yellow = "\033[33m";//文字黄色
    const std::string text_green = "\033[32m";//文字绿色
    const std::string text_blue = "\033[34m";//文字蓝色
    const std::string text_cyan = "\033[38;2;0;255;255m";//文字靛色
    const std::string text_violet = "\033[38;2;255;0;255m";//文字紫色
    const std::string text_dark = "\033[38;5;232m";//文字纯黑
    const std::string text_darkgray = "\033[38;5;234m";
    const std::string text_gray = "\033[38;5;242m";//文字灰色
    const std::string text_darkblue = "\033[38;5;27m";//文字深蓝
    const std::string text_lightblue = "\033[38;5;39m";//文字亮蓝
    const std::string text_lightgreen = "\033[38;5;10m";//文字亮绿
    const std::string text_lightyellow = "\033[38;2;255;255;0m";
    const std::string italic = "\033[003m";//文字斜体
    const std::string text_underline = "\033[004m";//文字下划线
    const std::string text_lightviolet = "\033[38;2;216;160;233m";//文字淡紫
};//文字格式标准库

namespace CUIL_std{
    using namespace stdcolor_256;
    using namespace stdcolor_RGB;
    using namespace stdtext;
    #ifndef EXTERNED_UNISTDH
        extern "C" unsigned int sleep (unsigned int __seconds);
        extern "C" int usleep (__useconds_t __useconds);
        #define EXTERNED_UNISTDH
    #endif
    #define _EN_UK_DEFAULT_WARNING "Warning,error occured because of wrong parameter or incorrect use."//默认反馈信息——英语
    #define _ZH_CN_DEFAULT_WARNING "警告：错误的参数或不正当使用导致了一个错误"//默认反馈信息——中文
    #ifdef __linux
	    #define CLEARSCREEN_CMDCOMMMAND "\033c\033[1;1H"
	#endif
    int WCHAR_T_INIT(){
        try{
            std::locale lc("zh_CN.UTF-8");
    	    std::locale::global(lc);
    	    return 1;
        }catch(...){
            return 0;
        }
    }
    const int SUPPORT_WCHAR_T = WCHAR_T_INIT();//常量——系统是否支持中文宽字符（unicode字符集）
    
	//清除屏幕的system指令
    const std::string VOID_PARAMETER = "NONE";//默认空参数
    const std::string _DEFAULT_LANGUAGE = "zh-CN";//默认语言
    const std::string _NOW_DEFAULT_WARNING = _ZH_CN_DEFAULT_WARNING;//现在的默认警告（可随时更改）
    const std::string _CLEAREFFECT_STR = "\033[m";//清除效果
    const std::string CUIL_VERSIONINFO = "CUIL v0.0.9";//CUIL的版本
    
    //CUIL基础结构
    
    //衍生功能库
    
    enum RGB{
        RED,
        GREEN,
        BLUE,
    };
    const std::string warning_color_type[] = {stdcolor_256::yellow,stdcolor_256::light_red,stdcolor_256::red};
    //0级警告：黄，1级警告：亮红，2级（最高）警告：暗红
    //基础类
    struct warning{
        int warn_type;
        std::string content;
    };
    std::queue<warning> warning_queue;//警告队列
    inline int warn_if(bool statement,const std::string show,int type_warning = 1);//警告
    class format{
        protected:
            bool formatlock;//格式锁
        private:
            std::string text_color;//文字颜色 
            std::string background_color;//背景颜色
            bool useitalic;//是否启用斜体
        public:
            void settextcolor(const std::string& input){
                if(!warn_if(formatlock,"此类的格式锁已启用，无法通过set进行修改"))
                    text_color = input;
            }
            void setbgcolor(const std::string& input){
                if(!warn_if(formatlock,"此类的格式锁已启用，无法通过set进行修改"))
                    background_color = input;
            }
            void setitalic(bool input){
                if(!warn_if(formatlock,"此类的格式锁已启用，无法通过set进行修改"))
                    useitalic = input;
            }
            void lock(){
                formatlock=true;    
            }
            void unlock(){
                formatlock=false;
            }
            void clear(){
                formatlock = false;
                useitalic=false;
                text_color="";
                background_color="";
            }//清除效果
            format(bool a,bool b,const std::string& c,const std::string& d){
                formatlock = a;
                useitalic = b;
                text_color = c;
                background_color = d;
            }
            format(){}
            ~format(){}
        friend void print(const std::string& content,const format& formatin,bool step,double char_per_sec,bool end);
        friend     void printcode(const std::string& code,const std::string& lang,int min_line_length);
        friend std::ostream& operator<<(std::ostream& wis,const format& c);
    }publicformat = {false,false,"",""},
    default_printformat = {false,false,"",""},
    default_codeformat = {false,false,"",code_background};
    format printformat = default_printformat;
    format codeformat = default_codeformat;    
    std::ostream& operator<<(std::ostream& wis,const format& c){
        std::string s = c.text_color + c.background_color + (c.useitalic?italic:"");
        wis << s;
        return wis;
    
    }
    class element{
        public:
            std::string content;//模板化内容
            format buildin_format;//内置格式
        public:
            void show() const{ std::cout << buildin_format << content; /* 内容 */ }
            element(){
                content = "";
                buildin_format = default_printformat;
            }//默认构造
            explicit element(const std::string& input,const format& formatin = printformat){
                content = input;
                buildin_format = formatin;
            }//输入元素内容
            explicit element(const long long input,const format& formatin = printformat){
                content = std::to_string(input);
                buildin_format = formatin;
            }//对整型数据的重载
            explicit element(const char input,const format& formatin = printformat){
                content += input;
                buildin_format = formatin;
            }//对宽字符数据的重载
            explicit element(const long double input,const format& formatin = printformat){
                content = std::to_string(input);
                buildin_format = formatin;
            }
    }voidelement{"",default_printformat};//元素类
    
    int count_showlen(const element& input){
        int count_t = input.content.length();
        for(auto&& i:input.content){
            if(int(i) > 127)
                count_t++;
        }
        return count_t;
    }
    int count_showlen(const std::string& input){
        int count_t = input.length();
        for(auto&& i:input){
            if(int(i) > 127)
                count_t++;
        }
        return count_t;
    }
    std::string wstrcpy(const std::string& cpystr,int cpynum);
    class label_line{
        public:
            element left;//左元素
            element mid;//中元素
            element right;//右元素
            int line_len;//当前对齐长度
        public:
            int minshowlen() const{
                int show_len_left = count_showlen(left),
                    show_len_mid  = count_showlen(mid),
                    show_len_right = count_showlen(right);
                int line_len = show_len_left + show_len_mid + show_len_right + 2;
                return line_len;
            }
            void editleft(const element& in){
                left = in;
            }
            void editright(const element& in){
                right = in;
            }
            void editmid(const element& in){
                mid = in;
            }
            void show(int line_len_min = 20){
                int now_len = minshowlen();
                if(now_len > line_len_min){
                    left.show();
                    std::cout << " ";
                    mid.show();
                    std::cout << " ";
                    right.show();
                    line_len = now_len;
                }//拓展长度
                else{
                    int space_left = (line_len_min - now_len + 2)/2,
                        space_right = line_len_min - now_len + 2 - space_left;
                    left.show();
                    std::cout << wstrcpy(" ",space_left);
                    mid.show();
                    std::cout << wstrcpy(" ",space_right);
                    right.show();
                    line_len = line_len_min;
                }
            }//展示标签行
            label_line(){
                left = element();
                mid = element();
                right = element();
            }
            explicit label_line(const element& l,const element& m = voidelement,const element& r = voidelement){
                left = l;
                mid = m;
                right = r;
                
            }
    };//标签行类
    class label{
        public:
            std::vector<label_line>content;
        public:
            void add_line(const label_line& in){
                content.push_back(in);
            }
            void delete_line(){
                content.pop_back();
            }
            void show(int show_len = 20){
                int max_len = -1;
                for(auto&&i:content){
                    int tmp_len = i.minshowlen();
                    max_len = tmp_len>max_len?tmp_len:max_len;
                }//检索最大长度
                show_len = max_len>=show_len?max_len:show_len;//如果最大长度超过定义，则换为最大长度
                std::cout << "┌"<<wstrcpy("─",show_len-1)<<"┐"<<std::endl;
                for(auto&&i:content){
                    std::cout << "│";
                    i.show(show_len);
                    std::cout << "│"<<std::endl;
                }
                std::cout << "└"<<wstrcpy("─",show_len-1)<<"┘"<<std::endl;
            }
    };//标签总类
    double half_precision(double a){
        return fabs(a - floor(a))<fabs(ceil(a)-a)?floor(a):ceil(a);
    }
    template<class T>class matrix{
        private:
            std::vector<std::vector<T>>content;
        public:
            void edit(int x,int y,const T& v){
                if(warn_if(!(0<=x&&x<content[0].size()&&0<=y&&y<content.size()),"尝试访问不存在的矩阵元素["+std::to_string(x)+","+std::to_string(y)+"]"))
                    return ;
                else
                    content[y][x]=v;
            }
            T get(int x,int y)const{
                if(0<=x&&x<content[0].size()&&0<=y&&y<content.size())
                    return content[y][x];
                return T();
            }
            matrix<T>(int h,int w,const T& set_as = T()){
                std::vector<std::vector<T> >tmp(h,std::vector<T>(w,set_as));
                content = tmp;
            }
            matrix<T>(const std::vector<std::vector<T>>& inmatrix = {{}}){
                for(auto&&i:inmatrix){
                    content.emplace_back();
                    for(auto&&j:i)
                        content[content.size() - 1].push_back(j);
                }
            }
            int geth()const{
                return content.size();
            }
            int getw()const{
                return content[0].size();
            }
            void seth(int newh,const T& set_as = T()){
                if(newh<content.size()){
                    while(content.size()>newh&&(!content.empty()))
                        content.pop_back();
                }else{
                    std::vector<T>tmp;
                    while(tmp.size()<content[0].size())
                        tmp.push_back(set_as);
                    while(content.size()<newh)
                        content.push_back(tmp);
                }
            }
            void setw(int neww,const T& set_as = T()){
                if(neww<content[0].size()){
                    for(auto&&i:content){
                        while(i.size()>neww)
                            i.pop_back();
                    }
                }else{
                    for(auto&&i:content){
                        while(i.size()<neww)
                            i.push_back(set_as);
                    }
                }
            }
            void recover(const T& input){
                for(int i = 0;i<content.size();++i){
                    for(int j = 0;j<content[i].size();++j)
                        content[i][j] = input;
                }
            }
            void cover(int sx,int sy,int ex,int ey,const T& input){
                if(0<=sx&&sx<content[0].size()){
                    if(0<=sy&&sy<content.size()){
                        
                    }else
                        sy = sy<0?0:content.size()-1;
                        warn_if(true,"开始的y坐标超出范围，已自动调整",0);    
                }//开始坐标在范围内
                else{
                    sx = sx<0?0:content[0].size()-1;
                    warn_if(true,"开始的x坐标超出范围，已自动调整",0);
                }
                if(0<=ex&&ex<content[0].size()){
                    if(0<=ey&&ey<content.size()){
                        
                    }else
                        ey = ey<0?0:content.size()-1;
                        warn_if(true,"结束的y坐标超出范围，已自动调整",0);    
                }//开始坐标在范围内
                else{
                    ex = ex<0?0:content[0].size()-1;
                    warn_if(true,"结束的x坐标超出范围，已自动调整",0);
                }
                int tmp = sx;
                sx = std::min(tmp,ex);
                ex = std::max(tmp,ex);
                tmp=sy;
                sy = std::min(tmp,ey);
                ey = std::max(tmp,ey);
                for(int i = sx;i<=ex;++i){
                    for(int j = sy;j<=ey;++j)
                        content[j][i] = input;
                }
            }
            void matrixcover(const matrix<T>& inmat,int x,int y){
                for(int i = (x < 0?0:x);i < ((x + inmat.getw()) < getw()?(x + inmat.getw()):getw());++i){
                    for(int j = (y < 0?0:y);j < ((y + inmat.geth()) < geth()?(y + inmat.geth()):geth());++j)
                        edit(i,j,inmat.get(i - x,j - y));
                }
            }
            void print()const{
                for(int i = 0;i<content.size();++i){
                    for(int j = 0;j<content[i].size();++j)
                        std::cout << content[i][j]<<",";
                    std::cout << std::endl;
                }
            }
            void line(int sx,int sy,int ex,int ey,const T& input){
                long double k = (sx!=ex)?(ey-sy-0.0)/(ex-sx-0.0):(1e+308);
                long double b = sy - sx*k;
                if(sx>ex){
                    for(long double i = ex;i<=sx;i+=0.1){
                        long double nx = i,ny = k*i+b;
                        if(0<=nx&&nx<=content[0].size()&&0<=ny&&ny<=content.size())
                            content[half_precision(ny)][half_precision(nx)] = input;
                    }
                }else if(sx<ex){
                    for(long double i = sx;i<=ex;i+=0.1){
                        long double nx = i,ny = k*i+b;
                        if(0<=nx&&nx<=content[0].size()&&0<=ny&&ny<=content.size())
                            content[half_precision(ny)][half_precision(nx)] = input;
                    }
                }else{
                    int nsy = std::min(sy,ey),ney = std::max(sy,ey);
                    for(int i = nsy;i<=ney;++i){
                        if((0<=i&i<=content.size()&&0<=sx&&sx<=content[0].size()))
                            content[i][sx] = input;
                    }
                }
            }
            void circle(int x,int y,int r,const T& input){
                for(int i = x-r;i<=x+r;++i){
                    for(int j = y-r;j<=y+r;++j){
                        if(0<=i&i<=content[0].size()&&0<=j&&j<=content.size()){
                            if((i-x)*(i-x)+(j-y)*(j-y)<r*r)
                                content[j][i] = input;
                        }
                    }
                }
            }
    };
    const std::vector<std::string> img_type = {"rgb","256","grey"};
    bool intype(const std::string& typein){
        for(auto && i : img_type){
            if(typein == i)
                return true;
        }
        return false;
    }
    inline int chartohex(char inchar){
        return isdigit(inchar)?inchar - '0':(isalpha(inchar)?(toupper(inchar) > 'F'?0:toupper(inchar) - '7'):0);
    }
    class pixel{
        public:
            unsigned char red;//红
            unsigned char green;//绿
            unsigned char blue;//蓝
        public:
            std::string make_show_RGB()const{
                return "\033[48;2;"+std::to_string(red)+";"+
                                     std::to_string(green)+";"+
                                     std::to_string(blue)+"m";
            }
            std::string make_show_RGB_text()const{
                return "\033[38;2;"+std::to_string(red)+";"+
                                     std::to_string(green)+";"+
                                     std::to_string(blue)+"m";
            }
            pixel(int r = 255,int g = 255,int b = 255){
                red = r;
                green = g;
                blue = b;
            }
            unsigned char getred() const{ return red; };
            unsigned char getgreen() const{ return green; };
            unsigned char getblue() const{ return blue; };
            pixel(const std::string& rgb){
                if(rgb[0] == '#' && rgb.length() == 7){
                    red =   chartohex(rgb[1]) * 16 + chartohex(rgb[2]);
                    green = chartohex(rgb[3]) * 16 + chartohex(rgb[4]);
                    blue =  chartohex(rgb[5]) * 16 + chartohex(rgb[6]);
                }else if(rgb.length() == 6){
                    red =   chartohex(rgb[0]) * 16 + chartohex(rgb[1]);
                    green = chartohex(rgb[2]) * 16 + chartohex(rgb[3]);
                    blue =  chartohex(rgb[4]) * 16 + chartohex(rgb[5]);
                }else{
                    warn_if(true,"不合法的RGB值表示: "+rgb);
                    red = 255;
                    green = 255;
                    blue = 255;
                }
            }
            pixel(const char* trgb){
                std::string rgb = trgb;
                if(rgb[0] == '#' && rgb.length() == 7){
                    red =   chartohex(rgb[1]) * 16 + chartohex(rgb[2]);
                    green = chartohex(rgb[3]) * 16 + chartohex(rgb[4]);
                    blue =  chartohex(rgb[5]) * 16 + chartohex(rgb[6]);
                }else if(rgb.length() == 6){
                    red =   chartohex(rgb[0]) * 16 + chartohex(rgb[1]);
                    green = chartohex(rgb[2]) * 16 + chartohex(rgb[3]);
                    blue =  chartohex(rgb[4]) * 16 + chartohex(rgb[5]);
                }else{
                    warn_if(true,"不合法的RGB值表示: "+rgb);
                    red = 255;
                    green = 255;
                    blue = 255;
                }
            }
            bool not_equal(const pixel& pix)const{
                return pix.red != red || pix.green != green || pix.blue != blue;
            }
            bool operator==(const pixel& pix2)const{
                return red == pix2.red && green == pix2.green && blue == pix2.blue;
            }
            bool operator!=(const pixel& pix2)const{
                return !(*this == pix2);
            }
            pixel reverse_color(){
                return pixel(255 - red,255 - green,255 - blue);   
            }
            void show(const pixel& last = pixel(0,0,0),bool at_front = false)const{
                if(last != *this || at_front)
                    std::cout << make_show_RGB();
                std::cout << "  ";
            }
            friend inline std::string torgbcolor(const pixel& inpixel);
            friend std::ostream& operator<<(std::ostream& wis,const pixel& c);
    }
    pixel_red(255,0,0),//纯红像素
    pixel_green(0,255,0),//纯绿像素
    pixel_blue(0,0,255),//纯蓝像素
    pixel_white(255,255,255),//纯白像素
    pixel_cyan(0,255,255),//纯靛像素
    pixel_violet(255,0,255),//纯紫像素
    pixel_yellow(255,255,0),//纯黄像素
    pixel_black(0,0,0);//纯黑像素
    class pixel_hsv{
        private:
            float hue;
            float saturation;
            float value;
        public:
            pixel_hsv(float h = 0.0,float s = 1.0,float v = 1.0){
                hue = h;
                saturation = s;
                value = v;
            }
            pixel_hsv(const pixel& inpix){
                int red = inpix.getred(),green = inpix.getgreen(),blue = inpix.getblue();
                int Pmax = std::max(red,std::max(green,blue)),Pmin=std::min(red,std::min(green,blue));
                if(Pmax == Pmin)
                    hue = 0.0;
                else if(red == Pmax)
                    hue = (green - blue)*1.0 /(Pmax - Pmin);
                else if(green == Pmax)
                    hue = 2.0 + (blue - red)*1.0/(Pmax - Pmin);
                else if(blue == Pmax)
                    hue = 4.0 + (red - green)*1.0/(Pmax - Pmin);
                else
                    hue = 0.0;
                hue *= 60.0;
                while(hue < 0.0)
                    hue+=360.0;
                while(hue >= 360.0)
                    hue-=360.0;
                value = Pmax*1.0/255;
                saturation = (Pmax - Pmin) * 1.0 / Pmax;
            }
            pixel torgbpix() const{
                int h = 2 * (floor(hue)/2);
                double c = value * saturation,
                       x = c * (1 - std::fabs(hue-h - 1.0)),
                       m = value - c;
                int int_hue = (int(hue/60))%6;
                double R,G,B;
                switch(int_hue){
                    case 0:R = c,G = x,B = 0.0;break;
                    case 1:R = x,G = c,B = 0.0;break;
                    case 2:R = 0.0,G = c,B = x;break;   
                    case 3:R = 0.0,G = x,B = c;break;   
                    case 4:R = x,G = 0.0,B = c;break;   
                    case 5:R = c,G = 0.0,B = x;break;   
                }
                return pixel(int((R+m)*255),int((G+m)*255),int((B+m)*255));
            }
            pixel_hsv reverse_color() const{
                return pixel_hsv(360.0 - hue,1.0 - saturation,1.0 - value);
            }
            std::string make_show_RGB() const{
                return torgbpix().make_show_RGB();
            }
            bool operator==(const pixel_hsv& pix2)const{
                return hue == pix2.hue && saturation == pix2.saturation && value == pix2.value;
            }
            bool operator!=(const pixel_hsv& pix2)const{
                return !(*this == pix2);
            }
            void show(const pixel_hsv& last,bool at_front = false)const{
                if(last != *this || at_front)
                    std::cout << make_show_RGB();
                std::cout << "  ";
            }
    };
   
    inline std::string torgbcolor(const pixel& inpixel){
        return "\033[48;2;"+std::to_string(inpixel.red)+";"+
                             std::to_string(inpixel.green)+";"+
                             std::to_string(inpixel.blue)+"m";
    }//数字直接转换至RGB字符串
    inline std::string torgbcolor(const pixel_hsv& inpixel){
        return torgbcolor(inpixel.torgbpix());
    }
    std::ostream& operator<<(std::ostream& wis,const pixel& c){
        std::string s = "["+std::to_string(c.red)+","+std::to_string(c.green)+","+std::to_string(c.blue)+"]";
        wis<<s;
        return wis;
    }
    class grey{
        public:unsigned char vgrey;
        public:
            std::string make_show_RGB() const{
                return "\033[48;2;"+std::to_string(vgrey)+";"+
                                     std::to_string(vgrey)+";"+
                                     std::to_string(vgrey)+"m";
            }
            std::string make_show_RGB_text() const{
                return "\033[38;2;"+std::to_string(vgrey)+";"+
                                     std::to_string(vgrey)+";"+
                                     std::to_string(vgrey)+"m";
            }
            void edit(unsigned char a){
                vgrey = a;
            }
            grey(unsigned char a = 255){
                vgrey = a;
            }
            grey(const pixel& pix,double vRed = 0.30,double vGreen = 0.59,double vBlue = 0.11){
                vgrey = pix.red * vRed + pix.green * vGreen + pix.blue * vBlue;
            }
            bool not_equal(const grey& ing)const{
                return ing.vgrey != vgrey;
            }
            grey reverse_color()const{
                return grey(255 - vgrey);
            }
            unsigned char getgrey()const{
                return vgrey;
            }
            bool operator==(const grey& pix2)const{
                return vgrey == pix2.vgrey;
            }
            bool operator!=(const grey& pix2)const{
                return !(*this == pix2);
            }
            void show(const grey& last,bool at_front = false)const{
                if(last != *this || at_front)
                    std::cout << make_show_RGB();
                std::cout << "  ";
            }
            friend inline std::string torgbcolor(const grey& ingrey);
            friend std::ostream& operator<<(std::ostream& wis,const grey& c);
    }grey_white(255),grey_black(0);
    inline std::string torgbcolor(const grey& ingrey){
        return "\033[48;2;"+std::to_string(ingrey.vgrey)+";"+
                             std::to_string(ingrey.vgrey)+";"+
                             std::to_string(ingrey.vgrey)+"m";
    }//数字直接转换至RGB字符串
    std::ostream& operator<<(std::ostream& wis,const grey& c){
        std::string s = "["+std::to_string(c.vgrey)+"]";
        wis<<s;
        return wis;
    }
    template<class T>
    class basic_image{
        public:
            int height;//图像高
            int width;//图像宽
            matrix<T>pmap;//像素矩阵
            double speed;//速度
        public:
            basic_image(const int h = 16,const int w = 16,const T& set_as = T()){
                height = h;
                width = w;
                pmap = matrix<T>(h,w,set_as);
                speed = 100;
            }
            basic_image(const std::vector<std::vector<T>>& mapin){
                height = mapin.size();
                width = mapin.at(0).size();
                pmap = matrix<T>(mapin);
                speed = 100;
            }
            void setspeed(double a){
                speed = a;
            }
            void show()const{
                for(int i = 0;i<pmap.geth();++i){
                    for(int j = 0;j<pmap.getw();++j){
                        pmap.get(j,i).show(pmap.get(j - 1,i),j == 0);
                        usleep(500000/speed);
                    }
                    std::cout << _CLEAREFFECT_STR;
                    std::cout << std::endl;
                }
                std::cout << _CLEAREFFECT_STR;
            }
            void recover(const T& input){
                pmap.recover(input);
            }
            void cover(int sx,int sy,int ex,int ey,const T& input){
                pmap.cover(sx,sy,ex,ey,input);
            }
            void edit(int x,int y,const T& input){
                pmap.edit(x,y,input);
            }
            void line(int sx,int sy,int ex,int ey,const T& input){
                pmap.line(sx,sy,ex,ey,input);
            }
            void circle(int x,int y,int r,const T& input){
                pmap.circle(x,y,r,input);
            }
            void seth(int newh,const T& set_as = pixel_white){
                if(warn_if(newh<0,"设置的图像高无法小于0",1))
                    return ;
                else
                    pmap.seth(newh,set_as);
                height = newh;
            }
            void setw(int neww,const T& set_as = pixel_white){
                if(warn_if(neww<0,"设置的图像宽无法小于0",1))
                    return ;
                else
                    pmap.setw(neww,set_as);
                width = neww;
            }
            std::string to_wstr()const{
                std::string output;
                pixel tmp;
                for(int i = 0;i<pmap.geth();++i){
                    T last = pixel(255,255,255);
                    for(int j = 0;j<pmap.getw();++j){
                        tmp = pmap.get(j,i);
                        if(last != tmp || j == 0){
                            output += tmp.make_show_RGB();
                            last = tmp;
                        }
                        output += "  ";
                    }
                    output+=_CLEAREFFECT_STR+"\n";
                }
                return output;
            }
            T get(int x,int y)const{
                return pmap.get(x,y);
            }
            basic_image intercept(int x1,int y1,int x2,int y2)const{
                basic_image out(std::max(x1,x2) - std::min(x1,x2),std::max(y1,y2) - std::min(y1,y2));
                int sx = std::min(x1,x2),sy = std::min(y1,y2);
                for(int i = 0;i < out.height;++i){
                    for(int j = 0;j < out.width;++j)
                        out.edit(j,i,get(sx + j,sy + i));
                }
                return out;
            }
            basic_image rotate_clockwise()const{
                basic_image out(width,height);
                for(int x = 0;x < width;++x){
                    for(int y = 0;y < height;++y){
                        out.edit(int(height - y - 0.5),int(x + 0.5),get(x,y));
                    }
                }
                return out;
            }//顺时针旋转
            basic_image rotate_anticlockwise()const{
                basic_image out(width,height);
                for(int x = 0;x < width;++x){
                    for(int y = 0;y < height;++y)
                        out.edit(int(y + 0.5),int(width - x - 0.5),get(x,y));
                }
                return out;
            }//逆时针旋转
            basic_image overturn_x()const{
                basic_image out(height,width);
                for(int x = 0;x < width;++x){
                    for(int y = 0;y < height;++y)
                        out.edit(x,floor(height - y - 0.5),get(x,y));
                }
                return out;
            }//绕x轴旋转
            basic_image overturn_y()const{
                basic_image out(height,width);
                for(int x = 0;x < width;++x){
                    for(int y = 0;y < height;++y)
                        out.edit(floor(width - x - 0.5),y,get(x,y));
                }
                return out;
            }//绕y轴旋转
            basic_image reverse_color()const{
                basic_image out(height,width);
                for(int x = 0;x < width;++x){
                    for(int y = 0;y < height;++y)
                        out.edit(x,y,get(x,y).reverse_color());
                }
                return out;
            }
            void imgcover(const basic_image<T>& img,int x,int y){
                for(int i = (x < 0?0:x);i < ((x + img.width) < width?(x + img.width):width);++i){
                    for(int j = (y < 0?0:y);j < ((y + img.height) < height?(y + img.height):height);++j)
                        edit(i,j,img.get(i - x,j - y));
                    
                }
            }
            friend std::wostream& operator<<(std::wostream& wis,const basic_image& c);
    };
    template<class T>
    std::wostream& operator<<(std::wostream& wis,const basic_image<T>& c){
        wis<<c.to_wstr();
        return wis;
    }
    typedef basic_image<pixel>             image;
    typedef basic_image<char>      image_char;
    typedef basic_image<grey>         image_grey;
    typedef basic_image<pixel_hsv>     image_hsv;
    
    class hyperpixel{
        private:
            pixel m1;
            pixel m2;
            pixel m3;
            pixel m4;
        public:
            hyperpixel(const pixel& a = pixel(),const pixel& b = pixel(),
                       const pixel& c = pixel(),const pixel& d = pixel()){
                m1 = a;
                m2 = b;
                m3 = c;
                m4 = d;
            }
            void show(const hyperpixel& last = hyperpixel(),bool at_front = false){
                if(last.m2.not_equal(m1) || at_front)
                    std::cout << m1.make_show_RGB();
                if((last.m4.not_equal(m3) && m1 != m3) || at_front){
                    std::cout << m3.make_show_RGB_text();
                    std::cout << "▄";
                }else
                    std::cout << " ";
                if(m1.not_equal(m2) || at_front)
                    std::cout <<  m2.make_show_RGB();
                if((m3.not_equal(m4) && m2 != m4) || at_front){
                    std::cout << m4.make_show_RGB_text();
                    std::cout << "▄";
                }else
                    std::cout << " ";
            }
    };
    const std::vector<std::string> map_dotmatrix = {
    "\u2800","\u2801","\u2802","\u2803","\u2804","\u2805","\u2806","\u2807","\u2808","\u2809","\u280A","\u280B","\u280C","\u280D","\u280E","\u280F",
    "\u2810","\u2811","\u2812","\u2813","\u2814","\u2815","\u2816","\u2817","\u2818","\u2819","\u281A","\u281B","\u281C","\u281D","\u281E","\u281F",
    "\u2820","\u2821","\u2822","\u2823","\u2824","\u2825","\u2826","\u2827","\u2828","\u2829","\u282A","\u282B","\u282C","\u282D","\u282E","\u282F",
    "\u2830","\u2831","\u2832","\u2833","\u2834","\u2835","\u2836","\u2837","\u2838","\u2839","\u283A","\u283B","\u283C","\u283D","\u283E","\u283F",
    "\u2840","\u2841","\u2842","\u2843","\u2844","\u2845","\u2846","\u2847","\u2848","\u2849","\u284A","\u284B","\u284C","\u284D","\u284E","\u284F",
    "\u2850","\u2851","\u2852","\u2853","\u2854","\u2855","\u2856","\u2857","\u2858","\u2859","\u285A","\u285B","\u285C","\u285D","\u285E","\u285F",
    "\u2860","\u2861","\u2862","\u2863","\u2864","\u2865","\u2866","\u2867","\u2868","\u2869","\u286A","\u286B","\u286C","\u286D","\u286E","\u286F",
    "\u2870","\u2871","\u2872","\u2873","\u2874","\u2875","\u2876","\u2877","\u2878","\u2879","\u287A","\u287B","\u287C","\u287D","\u287E","\u287F",
    "\u2880","\u2881","\u2882","\u2883","\u2884","\u2885","\u2886","\u2887","\u2888","\u2889","\u288A","\u288B","\u288C","\u288D","\u288E","\u288F",
    "\u2890","\u2891","\u2892","\u2893","\u2894","\u2895","\u2896","\u2897","\u2898","\u2899","\u289A","\u289B","\u289C","\u289D","\u289E","\u289F",
    "\u28A0","\u28A1","\u28A2","\u28A3","\u28A4","\u28A5","\u28A6","\u28A7","\u28A8","\u28A9","\u28AA","\u28AB","\u28AC","\u28AD","\u28AE","\u28AF",
    "\u28B0","\u28B1","\u28B2","\u28B3","\u28B4","\u28B5","\u28B6","\u28B7","\u28B8","\u28B9","\u28BA","\u28BB","\u28BC","\u28BD","\u28BE","\u28BF",
    "\u28C0","\u28C1","\u28C2","\u28C3","\u28C4","\u28C5","\u28C6","\u28C7","\u28C8","\u28C9","\u28CA","\u28CB","\u28CC","\u28CD","\u28CE","\u28CF",
    "\u28D0","\u28D1","\u28D2","\u28D3","\u28D4","\u28D5","\u28D6","\u28D7","\u28D8","\u28D9","\u28DA","\u28DB","\u28DC","\u28DD","\u28DE","\u28DF",
    "\u28E0","\u28E1","\u28E2","\u28E3","\u28E4","\u28E5","\u28E6","\u28E7","\u28E8","\u28E9","\u28EA","\u28EB","\u28EC","\u28ED","\u28EE","\u28EF",
    "\u28F0","\u28F1","\u28F2","\u28F3","\u28F4","\u28F5","\u28F6","\u28F7","\u28F8","\u28F9","\u28FA","\u28FB","\u28FC","\u28FD","\u28FE","\u28FF",
    };
    pixel t256[256] = {
        pixel("#000000"),pixel("#800000"),pixel("#008000"),pixel("#808000"),pixel("#000080"),pixel("#800080"),pixel("#008080"),pixel("#c0c0c0"),
        pixel("#808080"),pixel("#ff0000"),pixel("#ffff00"),pixel("#00ff00"),pixel("#0000ff"),pixel("#ff00ff"),pixel("#00ffff"),pixel("#ffffff"),
        pixel("#000000"),pixel("#00005f"),pixel("#000087"),pixel("#0000af"),pixel("#0000d7"),pixel("#0000ff"),pixel("#005f00"),pixel("#005f5f"),
        pixel("#005f87"),pixel("#005faf"),pixel("#005fd7"),pixel("#005fff"),pixel("#008700"),pixel("#00875f"),pixel("#008787"),pixel("#0087af"),
        pixel("#0087d7"),pixel("#0087ff"),pixel("#00af00"),pixel("#00af5f"),pixel("#00af87"),pixel("#00afaf"),pixel("#00afd7"),pixel("#00afff"),
        pixel("#00d700"),pixel("#00d75f"),pixel("#00d787"),pixel("#00d7af"),pixel("#00d7d7"),pixel("#00d7ff"),pixel("#00ff00"),pixel("#00ff5f"),
        pixel("#00ff87"),pixel("#00ffaf"),pixel("#00ffd7"),pixel("#00ffff"),pixel("#5f0000"),pixel("#5f005f"),pixel("#5f0087"),pixel("#5f00af"),
        pixel("#5f00d7"),pixel("#5f00ff"),pixel("#5f5f00"),pixel("#5f5f5f"),pixel("#5f5f87"),pixel("#5f5faf"),pixel("#5f5fd7"),pixel("#5f5fff"),
        pixel("#5f8700"),pixel("#5f875f"),pixel("#5f8787"),pixel("#5f87af"),pixel("#5f87d7"),pixel("#5f87ff"),pixel("#5faf00"),pixel("#5faf5f"),
        pixel("#5faf87"),pixel("#5fafaf"),pixel("#5fafd7"),pixel("#5fafff"),pixel("#5fd700"),pixel("#5fd75f"),pixel("#5fd787"),pixel("#5fd7af"),
        pixel("#5fd7d7"),pixel("#5fd7ff"),pixel("#5fff00"),pixel("#5fff5f"),pixel("#5fff87"),pixel("#5fffaf"),pixel("#5fffd7"),pixel("#5fffff"),
        pixel("#870000"),pixel("#87005f"),pixel("#870087"),pixel("#8700af"),pixel("#8700d7"),pixel("#8700ff"),pixel("#875f00"),pixel("#875f5f"),
        pixel("#875f87"),pixel("#875faf"),pixel("#875fd7"),pixel("#875fff"),pixel("#878700"),pixel("#87875f"),pixel("#878787"),pixel("#8787af"),
        pixel("#8787d7"),pixel("#8787ff"),pixel("#87af00"),pixel("#87af5f"),pixel("#87af87"),pixel("#87afaf"),pixel("#87afd7"),pixel("#87afff"),
        pixel("#87d700"),pixel("#87d75f"),pixel("#87d787"),pixel("#87d7af"),pixel("#87d7d7"),pixel("#87d7ff"),pixel("#87ff00"),pixel("#87ff5f"),
        pixel("#87ff87"),pixel("#87ffaf"),pixel("#87ffd7"),pixel("#87ffff"),pixel("#af0000"),pixel("#af005f"),pixel("#af0087"),pixel("#af00af"),
        pixel("#af00d7"),pixel("#af00ff"),pixel("#af5f00"),pixel("#af5f5f"),pixel("#af5f87"),pixel("#af5faf"),pixel("#af5fd7"),pixel("#af5fff"),
        pixel("#af8700"),pixel("#af875f"),pixel("#af8787"),pixel("#af87af"),pixel("#af87d7"),pixel("#af87ff"),pixel("#afaf00"),pixel("#afaf5f"),
        pixel("#afaf87"),pixel("#afafaf"),pixel("#afafd7"),pixel("#afafff"),pixel("#afd700"),pixel("#afd75f"),pixel("#afd787"),pixel("#afd7af"),
        pixel("#afd7d7"),pixel("#afd7ff"),pixel("#afff00"),pixel("#afff5f"),pixel("#afff87"),pixel("#afffaf"),pixel("#afffd7"),pixel("#afffff"),
        pixel("#d70000"),pixel("#d7005f"),pixel("#d70087"),pixel("#d700af"),pixel("#d700d7"),pixel("#d700ff"),pixel("#d75f00"),pixel("#d75f5f"),
        pixel("#d75f87"),pixel("#d75faf"),pixel("#d75fd7"),pixel("#d75fff"),pixel("#d78700"),pixel("#d7875f"),pixel("#d78787"),pixel("#d787af"),
        pixel("#d787d7"),pixel("#d787ff"),pixel("#d7af00"),pixel("#d7af5f"),pixel("#d7af87"),pixel("#d7afaf"),pixel("#d7afd7"),pixel("#d7afff"),
        pixel("#d7d700"),pixel("#d7d75f"),pixel("#d7d787"),pixel("#d7d7af"),pixel("#d7d7d7"),pixel("#d7d7ff"),pixel("#d7ff00"),pixel("#d7ff5f"),
        pixel("#d7ff87"),pixel("#d7ffaf"),pixel("#d7ffd7"),pixel("#d7ffff"),pixel("#ff0000"),pixel("#ff005f"),pixel("#ff0087"),pixel("#ff00af"),
        pixel("#ff00d7"),pixel("#ff00ff"),pixel("#ff5f00"),pixel("#ff5f5f"),pixel("#ff5f87"),pixel("#ff5faf"),pixel("#ff5fd7"),pixel("#ff5fff"),
        pixel("#ff8700"),pixel("#ff875f"),pixel("#ff8787"),pixel("#ff87af"),pixel("#ff87d7"),pixel("#ff87ff"),pixel("#ffaf00"),pixel("#ffaf5f"),
        pixel("#ffaf87"),pixel("#ffafaf"),pixel("#ffafd7"),pixel("#ffafff"),pixel("#ffd700"),pixel("#ffd75f"),pixel("#ffd787"),pixel("#ffd7af"),
        pixel("#ffd7d7"),pixel("#ffd7ff"),pixel("#ffff00"),pixel("#ffff5f"),pixel("#ffff87"),pixel("#ffffaf"),pixel("#ffffd7"),pixel("#ffffff"),
        pixel("#080808"),pixel("#121212"),pixel("#1c1c1c"),pixel("#262626"),pixel("#303030"),pixel("#3a3a3a"),pixel("#444444"),pixel("#4e4e4e"),
        pixel("#585858"),pixel("#626262"),pixel("#6c6c6c"),pixel("#767676"),pixel("#808080"),pixel("#8a8a8a"),pixel("#949494"),pixel("#9e9e9e"),
        pixel("#a8a8a8"),pixel("#b2b2b2"),pixel("#bcbcbc"),pixel("#c6c6c6"),pixel("#d0d0d0"),pixel("#dadada"),pixel("#e4e4e4"),pixel("#eeeeee"),
    };
    enum GREY_MODE{
    GREY,    
    BINARY,
    C256,
    };
    class hyper_greypixel{
        public:
            bool pix[4][2];
            grey grey_info;
            GREY_MODE mode;
        public:
            bool operator==(const hyper_greypixel& op2)const{
                return op2.grey_info == grey_info;
            }
            bool operator!=(const hyper_greypixel& op2)const{
                return !(op2 == *this);
            }
            hyper_greypixel(const std::vector<grey>& grey_list = {8,grey()},
                            const grey& sgrey = grey(0),
                            GREY_MODE inmode = GREY){
                if(warn_if(grey_list.size() != 8,"为hyper_greypixel复制的列表项数不符合要求"))
                    return ;
                int sum = 0;
                for(int i = 0;i < 8;++i){
                    sum += grey_list[i].vgrey;
                    pix[i/2][i%2] = (inmode == C256?(grey(t256[sgrey.vgrey]).vgrey > 16):(grey_list[i].vgrey > 128));
                }
                if(sgrey == grey(0))
                    grey_info = grey(sum/8);
                else
                    grey_info = sgrey;
                mode = inmode;
            }
            void show(const hyper_greypixel& last,bool at_front = false)const{
                bool tmp[8] = {pix[0][0],pix[1][0],pix[2][0],pix[0][1],pix[1][1],pix[2][1],pix[3][0],pix[3][1]};
                int res = tmp[0] + tmp[1] * 2 + tmp[2] * 4 + tmp[3] * 8 +
                          tmp[4] * 16 + tmp[5] * 32 + tmp[6] * 64 + tmp[7] * 128;
                if(grey_info.vgrey < 240 || (last.grey_info != grey_info) || at_front){
                    switch(mode){
                        case BINARY:break;
                        case GREY:std::cout << grey_info.make_show_RGB_text();break;
                        case C256:std::cout << t256[grey_info.vgrey].make_show_RGB_text();break;
                        default:std::cout << grey_info.make_show_RGB_text();break;
                    }
                }
                std::cout << map_dotmatrix[res];
            }
    };
    typedef basic_image<hyperpixel> hyper_image;
    hyper_image tohyperimg(const image& img){
        hyper_image outimg(img.height / 2 + img.height%2,img.width / 2 + img.width%2,hyperpixel());
        for(int y = 0;y < outimg.height;++y){
            for(int x= 0;x < outimg.width;++x)
                outimg.edit(x,y,hyperpixel(img.get(x * 2,y * 2),img.get(x * 2 + 1,y * 2),img.get(x * 2,y * 2 + 1),img.get(x * 2 + 1,y * 2 + 1)));
        }
        return outimg;
    }
    typedef basic_image<hyper_greypixel> hyper_greyimage;
    pixel search_256pix(const pixel& inpix){
        long long distance = LONG_LONG_MAX;
        int ret = 0;
        for(int i = 0;i < 256;i++){
            long long t1 = (inpix.getred() - t256[i].getred()),
                   t2 = (inpix.getgreen() - t256[i].getgreen()),
                   t3 = (inpix.getblue() - t256[i].getblue()),
                   d = t1*t1 + t2*t2 + t3*t3;
            if(d < distance){
                distance = d;
                ret = i;
            }
        }
        return t256[ret];
    }
    int search_256pix_id(const pixel& inpix){
        long long distance = LONG_LONG_MAX;
        int ret = 0;
        for(int i = 0;i < 256;i++){
            long long t1 = (inpix.getred() - t256[i].getred()),
                   t2 = (inpix.getgreen() - t256[i].getgreen()),
                   t3 = (inpix.getblue() - t256[i].getblue()),
                   d = t1*t1 + t2*t2 + t3*t3;
            if(d < distance){
                distance = d;
                ret = i;
            }
        }
        return ret;
    }
    image reset256(const image& img){
        image tmpimg(img.height,img.width);
        for(int i = 0;i < img.height;++i){
            for(int j = 0;j < img.width;++j)
                tmpimg.edit(j,i,search_256pix(img.get(j,i)));
        }
        return tmpimg;
    }
    hyper_greyimage tohypergreyimg(const image_grey& img,GREY_MODE grey_mode = GREY,bool AUTO = true,const image& c256_img = image()){
        hyper_greyimage outimg(img.height / 4 + (img.height%4 > 0),img.width / 2 + img.width%2);
        for(int y = 0;y < outimg.height;++y){
            for(int x= 0;x < outimg.width;++x){
                outimg.edit(x,y,hyper_greypixel({
                    img.get(x * 2,y * 4)    ,img.get(x * 2 + 1,y * 4),
                    img.get(x * 2,y * 4 + 1),img.get(x * 2 + 1,y * 4 + 1),
                    img.get(x * 2,y * 4 + 2),img.get(x * 2 + 1,y * 4 + 2),
                    img.get(x * 2,y * 4 + 3),img.get(x * 2 + 1,y * 4 + 3)},
                    AUTO?0:search_256pix_id(c256_img.get(x,y)),grey_mode)
                );
            }
        }
        return outimg;
    }
    image_grey getPassage(const image& img,const RGB passage){
        image_grey out(img.height,img.width);
        for(int x = 0;x < img.width;++x){
            for(int y = 0;y < img.height;++y){
                switch(passage){
                    case   RED:    out.edit(x,y,grey(img.get(x,y).getred()));break;
                    case GREEN:  out.edit(x,y,grey(img.get(x,y).getgreen()));break;
                    case  BLUE:   out.edit(x,y,grey(img.get(x,y).getblue()));break;
                }
            }
        }
        return out;
    }
    image_grey ImgtoGrey(const image& img,double vRed = 0.30,double vGreen = 0.59,double vBlue = 0.11){
        image_grey out(img.height,img.width);
        for(int x = 0;x < img.width;++x){
            for(int y = 0;y < img.height;++y){
                pixel tmp = img.get(x,y);
                out.edit(x,y,grey(vRed * tmp.getred() + vGreen * tmp.getgreen() + vBlue * tmp.getblue()));
            }
        }
        return out;
    }
    image GreytoImg(const image_grey& img){
        image out(img.height,img.width);
        for(int x = 0;x < img.width;++x){
            for(int y = 0;y < img.height;++y){
                grey tmp = img.get(x,y);
                out.edit(x,y,pixel(tmp.getgrey(),tmp.getgrey(),tmp.getgrey()));
            }
        }
        return out;
    }
    image combinePassage(const image_grey& img_R,const image_grey& img_G,const image_grey& img_B){
        image out(std::min(img_R.height,std::min(img_G.height,img_B.height)),
                  std::min(img_R.width,std::min(img_G.width,img_B.width)));        
        for(int x = 0;x < out.width;++x){
            for(int y = 0;y < out.height;++y)
                out.edit(x,y,pixel(img_R.get(x,y).getgrey(),
                                   img_G.get(x,y).getgrey(),
                                   img_B.get(x,y).getgrey())
                        );
        }
        return out;
    }
    image averageNoise(const image& img,unsigned char differ = 16){
        const int dx[8] = {-1,0,1,-1,1,-1,0,1},dy[8] = {-1,-1,-1,0,0,1,1,1};
        image out(img.height,img.width);
        for(int x = 0;x < img.width;++x){
            for(int y = 0;y < img.height;++y){
                pixel pix = img.get(x,y);
                int dR = 0,dG = 0,dB = 0;
                for(int i = 0;i < 8;++i){
                    pixel tmp = img.get(x + dx[i],y + dy[i]);
                    dR += tmp.getred();
                    dG += tmp.getgreen();
                    dB += tmp.getblue();
                }
                if(abs(dR + dG + dB - 8 * (pix.getred() + pix.getgreen() + pix.getblue())) >= 3 * differ)
                    out.edit(x,y,pixel(dR / 8,dG / 8,dB / 8));
                else
                    out.edit(x,y,pix);
            }
        }
        return out;
    }
    
    class windows{
        private:
            int height;
            int width;
            
    };
    int doclear(){
        try{
            std::cout << CLEARSCREEN_CMDCOMMMAND;
            return 1;
        }catch(...){
            return 0;
        }//或许永远不会发生？
    }//调用系统cmd清屏
    
    char getch(){  
        char Input;
        struct termios a;
        struct termios b;
        int ret;
        tcgetattr(STDIN_FILENO,&a);
        memcpy(&b,&a,sizeof(b));
        b.c_lflag &= ~(ICANON);
        b.c_cc[VMIN] = 1;
        b.c_cc[VTIME] = 0;
        ret=tcsetattr(STDIN_FILENO,TCSANOW,&b);
        fflush(stdout);
        ret = read(STDIN_FILENO,&Input,1);
        tcsetattr(STDIN_FILENO,TCSANOW,&a);
        return Input;
    }  
    char datain(bool end = true){
        char tmp_c = getch();
        if(end)
            std::cout << std::endl << "\r";
        return tmp_c;
    }//获取单个字符
    
    int digitin(){
        char tmpin = datain(true);
        return isdigit(tmpin)?(tmpin-'0'):1;
    }
    const std::vector<std::string> key_word = {
    "alignas","alignof","and","and_eq","asm","__asm__",
    "auto","bitand","bitor","bool","break","_Bool",
    "case","catch","char","char16_t","char32_t","class",
    "const","compl","const_cast","constexpr","decltype","default",
    "delete","do","double","dynamic_cast","else","enum",
    "explicit","export","extern","false","FALSE","float",
    "for","friend","global","goto","if","include",
    "inline","int","iostream","iterator","_Imaginary",
    "long","mutable","new","namespace","noexcept","not",
    "not_eq","NULL","nullptr","operator","or","or_eq",
    "private","protected","public","_Pragma","register","reinterpret_cast",
    "restrict","return","short","signed","size","sizeof",
    "static","static_cast","struct","switch","template",
    "this","thread_local","throw","true","TRUE","try",
    "typedef","typeid","typename","union","unsigned","using",
    "virtual","void","volatile","wchar_t","while","xor",
    "xor_eq",
    "std","string","wstring","vector","map","list","multimap","set","multiset",
    };//关键词   
    const std::vector<std::string> key_word_color = {
    text_lightblue,text_lightblue,text_gray,text_gray,text_lightblue,text_lightblue,
    text_lightblue,text_gray,text_gray,text_lightblue,text_lightviolet,text_lightblue,
    text_lightviolet,text_lightviolet,text_lightblue,text_lightblue,text_lightblue,text_lightblue,
    text_lightblue,text_gray,text_lightblue,text_lightblue,text_lightblue,text_lightviolet,
    text_lightblue,text_lightviolet,text_lightblue,text_gray,text_lightviolet,text_lightblue,
    text_lightblue,text_lightblue,text_lightblue,text_cyan,text_cyan,text_lightblue,
    text_lightviolet,text_lightblue,text_lightblue,text_lightviolet,text_lightviolet,text_lightblue,
    text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_lightblue,
    text_lightblue,text_lightblue,text_lightblue,text_gray,text_lightblue,text_gray,
    text_gray,text_cyan,text_cyan,text_lightblue,text_gray,text_gray,
    text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_gray,
    text_lightblue,text_lightviolet,text_lightblue,text_lightblue,text_lightblue,text_gray,
    text_lightblue,text_gray,text_lightblue,text_lightviolet,text_lightblue,
    text_green,text_lightblue,text_lightviolet,text_cyan,text_cyan,text_lightviolet,
    text_lightblue,text_gray,text_lightblue,text_lightblue,text_lightblue,text_lightblue,
    text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_lightviolet,text_gray,
    text_gray,
    text_violet,text_cyan,text_cyan,text_cyan,text_cyan,text_cyan,text_cyan,text_cyan,text_cyan,
    };//关键字标色
    const std::vector<char> key_char = {
    '!','%','^','&','-','=','+','|','<','>','/','~',':','(',')','[',']','{','}',',',        
    };
    const std::vector<std::string> key_macro = {
    "#include","#define","#if","#else","#endif","#ifdef","#ifndef","#pragma","#elif"
    };
    const std::vector<std::string> key_char_color = {
        text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_violet,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,
    };
    
    int find_keyword(const std::string& input){
        for(int i = 0;i< key_word.size();++i){
            if(input == key_word[i])
                return i;
        }
        return -1;
    }
    int find_macro(const std::string& input){
        for(int i = 0;i< key_macro.size();++i){
            if(input == key_macro[i])
                return i;
        }
        return -1;
    }
    int find_keychar(const char input){
        for(int i = 0;i<key_char.size();++i){
            if(input == key_char[i])
                return i;
        }
        return -1;
    }
    bool isnoncoloredchar(const char input){
        return (isalpha(input)||isdigit(input)||input=='_'||input=='#'||input=='\"'||input=='\'');
    }
    bool issimulatechar(const char front,const char input){
        if( (isalpha(front)&&isalpha(input))||
            (isalpha(front)&&isdigit(input))||
            (isdigit(front)&&isalpha(input))||
            (isdigit(front)&&isdigit(input))||
            (front=='_'&&(isdigit(input)||isalpha(input)||input=='_'))||
            (input=='_'&&(isdigit(front)||isalpha(front)||front=='_'))||
            (front=='#'&&(isdigit(input)||isalpha(input)||input=='#'))||
            (input=='#'&&(isdigit(front)||isalpha(front)||front=='#'))||
            (find_keychar(front)!=-1 && find_keychar(input)!=-1 && !(front != '/' && input == '/'))||
            (front==input&&front!='\"'&&front!='\''&&input!='\"'&&input!='\'')
        )
            return true;
        else
            return false;
    }
    std::vector<std::string> sep_bykeychar(const std::string& input){
        std::vector<std::string> out;
        for(int a = 0;a<input.length();a++){
            std::string put_newstr;
            put_newstr+=input[a];
            a++;
            while(issimulatechar(input[a-1],input[a])&&input[a-1]!='\n'&&a<input.length())
                put_newstr+=input[a++];
            a--;
            out.push_back(put_newstr);
        }
        return out;
    }
    bool contain_onlydigit(std::string input){
        for(auto&&i:input){
            if(!isdigit(i))
                return false;
        }
        return true;
    }
    bool is_hex_num(std::string input){
        if(input.size()<=1)
            return false;
        if(input[0]=='0'&&(input[1]=='x'||input[1]=='X')){
            for(int i = 2;i<input.length();++i){
                if(!isdigit(input[i]))
                    return false;
            }    
            return true;
        }else
            return false;
    }
    bool is_long_num(std::string input){
        if(input.size()<=1)
            return false;
        if(input[input.size()-1]=='l'||input[input.size()-1]=='L'){
            for(int i = 0;i<input.size()-1;++i){
                if(!isdigit(input[i]))
                    return false;
            }    
            return true;
        }else
            return false;
    }
    bool is_longhex_num(std::string input){
        if(input.size()<=1)
            return false;
        if(input[input.size()-1]=='l'||input[input.size()-1]=='L'){
            if(input[0]=='0'&&(input[1]=='x'||input[1]=='X')){
                for(int i = 2;i<input.length()-1;++i){
                    if(!isdigit(input[i]))
                        return false;
                }    
                return true;
            }else
                return false;
        }else
            return false;
    }
    bool is_float_num(std::string input){
        if(input.size()<=1)
            return false;
        if(input[input.size()-1]=='f'||input[input.size()-1]=='F'){
            for(int i = 0;i<input.size()-1;++i){
                if(!isdigit(input[i]))
                    return false;
            }    
            return true;
        }else
            return false;
    }
    
    inline int warn_if(bool statement,const std::string show,int type_warning){
        if(statement){
            if(show != VOID_PARAMETER)//非空串
                CUIL_std::warning_queue.push({type_warning,show+CUIL_std::_CLEAREFFECT_STR});
            else
                CUIL_std::warning_queue.push({type_warning,_NOW_DEFAULT_WARNING+CUIL_std::_CLEAREFFECT_STR});
        }
        return statement;
    }//如果表达式为真，进行警告
    
    std::vector<std::string> split(std::string input,char sep = ','){
        std::vector<std::string>input_units;
        for(long long spliti=0;spliti<input.length();++spliti){
            if(input[spliti]!=sep){
                input_units.push_back("");
                while(input[spliti]!=sep&&spliti<input.length())
                    input_units[input_units.size()-1]+=input[spliti++];
            }
        }
        return input_units;
    }//分割字符串
    
    std::string wstrcpy(const std::string& cpystr,int cpynum){
        std::string out_wstrcpy;
        for(int i = 1;i<cpynum;++i)
            out_wstrcpy+=cpystr;
        return out_wstrcpy;
    }//复写字符串
    
    std::string wstrcpy(char cpystr,int cpynum){
        std::string out_wstrcpy;
        for(int i = 1;i<=cpynum;++i)
            out_wstrcpy+=cpystr;
        return out_wstrcpy;
    }//对char的重载
    void clear_warning(){
        while(!warning_queue.empty())
            CUIL_std::warning_queue.pop();
        return ;
    }//清除警告
    void updwarning(){
        while(!CUIL_std::warning_queue.empty()){
            std::cout  << "|"<<warning_color_type[CUIL_std::warning_queue.front().warn_type]<<"  "<<_CLEAREFFECT_STR<<"|"
                        <<CUIL_std::warning_queue.front().content<<"\n";
            CUIL_std::warning_queue.pop();
        }
        std::cout<<std::endl;
    }//清空并输出警告队列
    void PAUSE(){
        char tmp;
        std::cout<<"按任意键继续>>>";
        tmp = datain(true);
    }
    std::string make_shapebool(bool input){
        return input?("是|"+green+"  "+_CLEAREFFECT_STR):("否|"+red+"  "+_CLEAREFFECT_STR);
    }
    std::string formin(const std::string show = "输入：",int line_len = 10){
        std::cout << show;
        std::string line = wstrcpy("_",line_len);
        std::string back = wstrcpy("\b",line_len);
        std::cout << line<<back;
        std::string input;
        getline(std::cin,input);
        return input;
    }
    
    //复合组件原型
    template<class T>int uniselect(const std::vector<T>choice_list,std::string title="",char last_sign='w',char next_sign='s',char end_sign='y',int choice_first=1);//一元选择器
    template<class T>std::vector<int> multiselect(const std::vector<T> choice_list,std::string title="",char last_sign='w',char next_sign='s',char choice_sign='y',char cancel_sign='c',char end_sign='z',int choice_first=1);
    void dot_linerary_load(double wait_time,int width = 10,int height = 1,bool has_boarder = true,bool has_progress = true,char show_char = 'O',char blank_char = ' ');//点型加载
    void shape_linerary_load(double wait_time,int width = 10,int height = 1,bool has_border = true,bool has_progress = true,std::string format_pass = _CLEAREFFECT_STR,std::string format_border = _CLEAREFFECT_STR,char pass_char = '#',char show_char = '#',char blank_char = ' ');//线性加载 
    void ring_linerary_load();//环形加载动效
    void print(const std::string& content,const format& formatin = printformat,bool step = true,double char_per_sec = 4.0,bool end = true);//打印
    void printcode(const std::string& code,const std::string& lang = "cpp",int min_line_length = 40);
    //复合组件实现

    
    
    template<class T>
    int uniselect(const std::vector<T> choice_list,std::string title,char last_sign,char next_sign,char end_sign,int choice_first){
        std::set<char>sign_list = {last_sign,next_sign,end_sign};
        if(warn_if(sign_list.size()<3,"uniselect组件不得有相同的操作字符"))
            return 0;
        char tmp_listchoice=' ';
        int choice_now = choice_first;
        while(tmp_listchoice!=end_sign){
            doclear();
            if(title.length()<30)
                std::cout <<title<<std::endl;
            else
                print(title,printformat,true,500.0);
            std::cout<<"选择："<<std::endl;
            for(int choice_i = 1;choice_i<=choice_list.size();++choice_i)
                std::cout<<(choice_now==choice_i?">  "+text_lightgreen:"   ")<<choice_i<<"." << choice_list.at(choice_i-1) << _CLEAREFFECT_STR<< std::endl;
            std::cout<<"（"<<last_sign<<","<<next_sign<<"上下切换选项,"<<end_sign<<"确定）"<<std::endl;
            std::cout<<">>>";
            tmp_listchoice=datain(true);
            if(tmp_listchoice==last_sign)
                choice_now=(choice_now>1?choice_now-1:choice_list.size());
            if(tmp_listchoice==next_sign)
                choice_now=(choice_now<choice_list.size()?choice_now+1:1);
        }
        return choice_now;
    }
    template<class T>
    std::vector<int> multiselect(const std::vector<T> choice_list,std::string title,char last_sign,char next_sign,char choice_sign,char cancel_sign,char end_sign,int choice_first){
        std::set<char>sign_list = {last_sign,next_sign,end_sign,choice_sign,cancel_sign};
        if(warn_if(sign_list.size()<5,"multiselect组件不得有相同的操作字符"))
            return {0};
        char tmp_listchoice=' ';
        int choice_now = choice_first;
        std::set<int> select_list;
        std::vector<int> ret_list;
        while(tmp_listchoice!=end_sign){
            doclear();
            if(title.length()<30)
                std::cout <<title<<std::endl;
            else
                print(title,printformat,true,500.0);
            std::cout<<"选择："<<std::endl;
            for(int choice_i = 1;choice_i<=choice_list.size();++choice_i)
                std::cout<<(choice_now==choice_i?"> ":"  ")<<((select_list.find(choice_i)!=select_list.end())?"O "+text_lightgreen:"  ")<<choice_i<<"." << choice_list.at(choice_i-1) << _CLEAREFFECT_STR << std::endl;
            std::cout<<"（"<<last_sign<<","<<next_sign<<"上下切换选项,"<<choice_sign<<"选择,"<<cancel_sign<<"取消,"<<end_sign<<"结束）"<<std::endl<<">>>";
            tmp_listchoice=datain(true);
            if(tmp_listchoice==last_sign)
                choice_now=(choice_now>1?choice_now-1:choice_list.size());
            if(tmp_listchoice==next_sign)
                choice_now=(choice_now<choice_list.size()?choice_now+1:1);
            if(tmp_listchoice==choice_sign)
                select_list.insert(choice_now);
            if(tmp_listchoice==cancel_sign){
                if(select_list.find(choice_now) != select_list.end())
                    select_list.erase(select_list.find(choice_now));
            }
        }
        for(auto&&i:select_list)
            ret_list.push_back(i);
        return ret_list;
    }
    template<class T>
    int uniselect_extend(const std::vector<T> choice_list,std::string title,char last_sign,char next_sign,char end_sign,int choice_first){
        std::set<char>sign_list = {last_sign,next_sign,end_sign};
        if(warn_if(sign_list.size()<3,"uniselect组件不得有相同的操作字符"))
            return 0;
        char tmp_listchoice=' ';
        int choice_now = choice_first;
        while(tmp_listchoice!=end_sign){
            doclear();
            if(title.length()<30)
                std::cout <<title<<std::endl;
            else
                print(title,printformat,true,500.0);
            std::cout<<"选择："<<std::endl;
            for(int choice_i = 1;choice_i<=choice_list.size();++choice_i)
                std::cout<<(choice_now==choice_i?">  "+text_lightgreen:"   ")<<choice_i<<"." << choice_list.at(choice_i-1) << _CLEAREFFECT_STR<< std::endl;
            std::cout<<"（"<<last_sign<<","<<next_sign<<"上下切换选项,"<<end_sign<<"确定）"<<std::endl;
            std::cout<<">>>";
            tmp_listchoice=datain(true);
            if(tmp_listchoice==last_sign)
                choice_now=(choice_now>1?choice_now-1:choice_list.size());
            if(tmp_listchoice==next_sign)
                choice_now=(choice_now<choice_list.size()?choice_now+1:1);
        }
        return choice_now;
    }
    void dot_linerary_load(double wait_time,int width,int height,bool has_border,bool has_progress,char show_char,char blank_char){
        if(warn_if(wait_time<0.0,"dot_linerary_load组件参数错误：时间参数不得小于0",1))
            return ;
        if(warn_if(width<0,"dot_linerary_load组件参数错误：长度参数不得小于0",1))
            return ;
        if(warn_if(height<0,"dot_linerary_load组件参数错误：高度参数不得小于0",1))
            return ;
        doclear();
        std::string up_border_str = "┌" + wstrcpy("─",width+1) + "┐\n",
                     down_border_str = "└" + wstrcpy("─",width+1) + "┘\n";
        for(int i = 1;i<=width;++i){
            doclear();
            if(height == 1){
                std::cout << (has_border?"[":"");
                for(int j = 0;j<width;++j){
                    if(j==i-1)
                        std::cout << show_char;
                    else
                        std::cout << blank_char;
                }
                std::cout << (has_border?"]":"") << _CLEAREFFECT_STR;
                if(has_progress)
                    std::cout << int(100*i/width) <<"%"<<_CLEAREFFECT_STR;//文字颜色自行添加
                std::cout << std::endl;
            }
            else{
                std::string mid_content_str = (has_border?"│":"") + wstrcpy(blank_char,i-1) + show_char + wstrcpy(blank_char,width-i) + (has_border?"│":""); 
                if(has_border)
                    std::cout << up_border_str;
                for(int k = 0;k<height;k++){
                    std::cout << mid_content_str;
                    if(k==(height+1)/2){
                        if(has_progress)
                        std::cout << int(100*i/width) <<"%"<<_CLEAREFFECT_STR;//文字颜色自行添加
                    }
                    std::cout << "\n"; 
                }
                if(has_border)
                    std::cout << down_border_str;
            }
            usleep(int(wait_time*1000000)/width);
        }//线性加载动效
    }
    void shape_linerary_load(double wait_time,int width,int height,bool has_border,bool has_progress,std::string format_pass,std::string format_border,char pass_char,char show_char,char blank_char){
        if(warn_if(wait_time<0.0,"shape_linerary_load组件参数错误：时间参数不得小于0",1))
            return ;
        if(warn_if(width<0,"shape_linerary_load组件参数错误：长度参数不得小于0",1))
            return ;
        if(warn_if(height<0,"shape_linerary_load组件参数错误：高度参数不得小于0",1))
            return ;
        std::string up_border_str = format_border + "┌" + wstrcpy("─",width+1) + "┐\n"+_CLEAREFFECT_STR,
                     down_border_str = format_border + "└" + wstrcpy("─",width+1) + "┘\n"+_CLEAREFFECT_STR;
        for(int i = 1;i<=width;++i){
            doclear();
            if(height == 1){
                std::cout << format_border << (has_border?"[":"") << _CLEAREFFECT_STR;
                std::cout << format_pass;
                for(int j = 0;j<width;++j){
                    if(j<i-1)
                        std::cout << pass_char;
                    else if(j==i-1)
                        std::cout <<show_char<<_CLEAREFFECT_STR;
                    else
                        std::cout << blank_char;
                }
                std::cout << format_border << (has_border?"]":"") << _CLEAREFFECT_STR;
                if(has_progress)
                    std::cout << int(100*i/width) <<"%"<<_CLEAREFFECT_STR;//文字颜色自行添加
                std::cout << std::endl;
            }
            else{
                std::string mid_content_str = format_border + (has_border?"│":"") + _CLEAREFFECT_STR + format_pass + wstrcpy(pass_char,i-1) + show_char + _CLEAREFFECT_STR + wstrcpy(blank_char,width-i) + _CLEAREFFECT_STR + format_border + (has_border?"│":"")+_CLEAREFFECT_STR; 
                if(has_border)
                    std::cout << up_border_str;
                for(int k = 0;k<height;k++){
                    std::cout << mid_content_str;
                    if(k==(height+1)/2){
                        if(has_progress)
                        std::cout << int(100*i/width) <<"%"<<_CLEAREFFECT_STR;//文字颜色自行添加
                    }
                    std::cout << "\n"; 
                }
                if(has_border)
                    std::cout << down_border_str;
            }
            usleep(int(wait_time*1000000)/width);
        }//图形化加载动效
    }
    void print(const std::string& content,const format& formatin,bool step,double char_per_sec,bool end){
        if(warn_if(char_per_sec<0.0,"print组件参数错误：速度参数不得小于0",1))
            return ;
        std::cout << formatin.text_color<<
                      formatin.background_color<<
                      (formatin.useitalic?italic:"");
        if(!step || char_per_sec == 0.0)
            std::cout<<content;//无延迟，直接输出
        else{
            for(auto&&i:content){
                std::cout<<i;
                if(isascii(i))
                    usleep(1000000.0/(3 * char_per_sec));
                else
                    usleep(1000000.0/(9* char_per_sec));
            }
            
        }
        std::cout<<_CLEAREFFECT_STR;
        if(end)
            std::cout << std::endl;
        
    }
    template<typename T>
    void printvec(std::vector<T>input){
        std::cout<<"{"<<std::endl;
        for(auto&&i:input)
            std::cout<<"["<<i<<"]"<<std::endl;
        std::cout<<"}"<<std::endl;
    }
    void printcode(const std::string& code,const std::string& lang,int min_line_length){
        std::cout << codeformat.background_color << (codeformat.useitalic?italic:"");
        std::string out_print,code_t;
        int code_start = 0;
        while(code[code_start] == ' ' && code_start < code.length())
            out_print+=code[code_start++];
        code_t = code.substr(code_start);
        std::vector<std::string>first_word = sep_bykeychar(code_t);
        for(int i = 0;i<first_word.size();++i){
            out_print += codeformat.background_color;
            std::string j = first_word[i];
            if (contain_onlydigit(j) || is_hex_num(j) ||
                is_long_num(j) || is_longhex_num(j) ||
                is_float_num(j)
            ){
                out_print += text_lightblue + j + _CLEAREFFECT_STR;
                continue;//对于16进制数字，长整型数字与浮点数字的判定
            }
            else{
                if(j==";"){
                    out_print+=codeformat.background_color+text_white+j;
                    continue;
                }
                else if(j == "\n"){
                    out_print+=_CLEAREFFECT_STR + "\n";
                    continue;
                }
                else if(j=="/" && first_word[i + 1] == "*"){
                    out_print+=codeformat.background_color+text_green + "/*";
                    i+=2;
                    while(i + 1 < first_word.size() && !(first_word[i] == "*" && first_word[i+1] == "/"))
                        out_print+=first_word[i++];
                    //注释一律标绿
                    ++i;
                    out_print+="*/"+_CLEAREFFECT_STR;
                    continue;
                }//行间注释
                else if(j=="\""){
                    out_print+=text_lightgreen+codeformat.background_color+j;
                    ++i;
                    while(first_word[i]!="\""&&i<first_word.size()){
                        if(first_word[i]=="\\"){
                            out_print+=text_lightblue+codeformat.background_color;
                            out_print+=first_word[i]+first_word[i+1];//转义字符本身
                            out_print+=_CLEAREFFECT_STR+codeformat.background_color;
                            i+=2;//跳过两个字符
                            continue;
                        }//转义字符判定
                        out_print+=first_word.at(i++);
                    }
                    out_print+=text_lightgreen+first_word[i]+_CLEAREFFECT_STR+codeformat.background_color;
                    continue;
                }//字符串判定
                else if(j=="\'"){
                    out_print+=text_lightgreen+codeformat.background_color;
                    if(i+2<first_word.size() && first_word[i+2]=="\'" && first_word[i+1].size() < 2)
                        out_print+="\'" + first_word[i+1]+"\'";
                    else
                        out_print+=text_white + "\'" + first_word[i+1] + "\'";
                    out_print+=_CLEAREFFECT_STR+codeformat.background_color;
                    i+=2;
                    continue;
                }//字符判定
                else if(first_word[i]=="\\"){
                    out_print+=text_lightblue+codeformat.background_color;
                    out_print+=first_word[i]+first_word[i+1];//转义字符本身
                    out_print+=_CLEAREFFECT_STR+codeformat.background_color;
                    i+=2;//跳过两个字符
                    continue;
                }//转义字符判定
                
                int id_keyword = find_keyword(j),
                    id_macro   = find_macro(j),
                    id_keychar = find_keychar(j[0]);
                if(id_keyword!=-1)
                    out_print+=(key_word_color[id_keyword]+j+_CLEAREFFECT_STR);
                //关键字    
                else if(j=="//"){
                    out_print+=codeformat.background_color+text_green;
                    for(;i<first_word.size();++i){
                        if(first_word[i] == "\n")
                            break;
                        out_print+=first_word[i];
                    }
                    //注释一律标绿
                    out_print+=_CLEAREFFECT_STR + "\n";
                    continue;
                }
                else if(id_macro!=-1){
                    //非关键字，但为宏类型关键词
                    out_print+=(text_lightblue+j+" "+codeformat.background_color);
                    for(i += 1;i < first_word.size();i++){
                        if(first_word[i] == "\n" || find_macro(first_word[i]) != -1 || (i < first_word.size() - 1 && first_word[i] == "\n" && find_macro(first_word[i + 1]) != -1)){
                            out_print+="\n";
                            break;
                        }
                        out_print+=text_red+first_word[i];
                    }
                    //宏关键词一律标红
                    out_print+=_CLEAREFFECT_STR;
                    continue;
                }
                else if(id_keychar != -1)
                    out_print+=key_char_color[id_keychar]+j;
                //关键字符
                else
                    out_print+="\033[38;2;255;255;234m" +j;
                
                //用户自定义标识符或未知，默认为白色
            }//关键字，宏定义等其他情况
        }
        print(out_print + _CLEAREFFECT_STR + "\n",printformat,true,1000.0,false);
    }
};

using namespace CUIL_std;
namespace FreeCraft{
    const std::string FreecraftVersion = "FreeCraft 1.3.5 Instable"; // 游戏目前版本
    const std::string RequireCuilVersion = "CUIL v0.0.9"; // CUIL运行需要版本
    
    #define sleep(x) for(long long n = 0;n<44444444*x;++n){} // 按照秒数停止程序
    std::string answer = "None";
    
    int seed;
    
    int randnum(int a,int b){
        srand(seed);
        return rand()%a+b;
    }
    void sc(){
        srand(seed);//我用8作为种子
        int x1,y1,randsc;
        x1=0;
        y1=0;
        randsc=5;
        for(int q=0;q<mp_x;q++)
        {
            y1=0;
            randsc+=rand()%3-1;
            for(int w=0;w<randsc-3;w++)
            {
                if(randnum(15,1)==1)
                {
                    mp[x1][y1]=4;
                }
                else
                {
                    mp[x1][y1]=1;
                }
                y1++;
                seed++;
            }
            for(int e=0;e<2;e++)
            {
                mp[x1][y1]=5;
                y1++;
            }
            mp[x1][y1]=6;
            y1++;
            
            for(int r=0;r<12-randsc;r++)
            {
                mp[x1][y1]=0;
            }
            x1++;
            seed++;//造成更快的"伪伪随机数",且输入相同的种子生成的地形不会改变
    }
}

    void GameBegin(){
        std::cout << "欢迎来到FreeCraft Instable！" << std::endl;
        sleep(200);PAUSE();doclear();
        std::cout << R"(FreeCraft Instable - 起点
FreeCraft Instable是本人(P.O Cream)第一个正式C++项目

使用ParseY Pasy CUIL String拓展库
这个游戏会继续迭代下去，期待FreeCraft Instable的更多玩法

P.S 不会与FreeWorld有任何关联)" << std::endl;
        PAUSE();doclear();
        int main_choose = uniselect<std::string>(split("种子,结束"));
        switch(main_choose){
            case 1:
                std::cout << "请输入种子：";
                std::cin << seed;
        }
        
    }
    
    void Debug(){
        std::cout << "FreeCraft Instable因异常退出！";
    }
    
    int PlayerXCoordinate = 1;
    int PlayerYCoordinate = 1;
    
};

int main()
{
    try{
        FreeCraft::GameBegin();
    }catch(...){
        FreeCraft::Debug();
    }
    return 0;
}
