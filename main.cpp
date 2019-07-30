#include<iostream>
#include<string>
#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<math.h>

int _WIDTH =960;
int _HEIGHT =640;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
int    rmask = 0xff000000;
int    gmask = 0x00ff0000;
int    bmask = 0x0000ff00;
int    amask = 0x000000ff;
#else
int    rmask = 0x000000ff;
int    gmask = 0x0000ff00;
int    bmask = 0x00ff0000;
int    amask = 0xff000000;
#endif

#include"src/base.h"
#include"src/block.h"
#include"src/person.h"
#include"src/box.h"
#include"src/content.h"


#include"SDLdraw/palette.h"
#include"SDLdraw/drawlist.h"

palette global_palette;
SDL_Window* global_w; 

#include"src/_maps.h"
int main(int argc,char* agrv[]) {
    char flag[100]={0};
    int isq = false;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    drawlist_init_img();
    FILE *f = fopen("data.sav","rb+");
    if(f){
        fread(flag,sizeof(flag),1,f);
        fclose(f);
    }

    SDL_Window* w = SDL_CreateWindow("hello,world",
                                    SDL_UNSUPPORTED,SDLK_UNDERSCORE,
                                    _WIDTH,_HEIGHT,
                                    SDL_WINDOW_RESIZABLE|SDL_WINDOW_SHOWN);
    global_w = w;

    SDL_Surface* win_surface = SDL_GetWindowSurface(w);
    std::string title;            
    SDL_Event event;
    int leve = 0;
    int hleve = 0;
    int mleve  = sizeof(_MAPS_def)/(_SIZE*sizeof(int));
    map m;   
    m.read(_MAPS_def[leve]);
    palette p(m._w(),m._h(),_WIDTH/m._w(),_HEIGHT/m._h());
    global_palette  = p;
    title = "Level :"+std::to_string(leve+1)+"|autor:liubailin src:https://github.com/liubailin2017/box/tree/graph|"+flag[leve];
    SDL_SetWindowTitle(w,title.c_str());
    content c(&m);

    c.display();
    int cwid,chei;
    while (!isq)
    {
        while(SDL_PollEvent(&event)) {
            
                SDL_GetWindowSize(w,&_WIDTH,&_HEIGHT);
                if( !(cwid == _WIDTH && _HEIGHT == chei)) {
                    global_palette.setsize(_WIDTH/m._w(),_HEIGHT/m._h());
                    cwid = _WIDTH;
                    chei =_HEIGHT;
                    std::cout<<"resize"<<std::endl;
                }
            switch (event.type)
            {
            
          
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    c.actinput(UP);
                    break;
                case SDLK_LEFT:
                    c.actinput(LEFT);
                    break;
                case SDLK_RIGHT:
                    c.actinput(RIGHT);
                    break;
                case SDLK_DOWN:
                    c.actinput(DOWN);
                    break;
                case SDLK_SPACE:
                    c.back();
                    break;
                case SDLK_PAGEUP:
                        if(leve < mleve-1) { 
                            leve++;
                            m.read(_MAPS_def[leve]);
                            palette p(m._w(),m._h(),_WIDTH/m._w(),_HEIGHT/m._h());
                            global_palette = p;
                            c.init();
                            title = "level:"+std::to_string(leve+1)+"    "+flag[leve];
                            SDL_SetWindowTitle(w,title.c_str());
                        }
                break;
                case SDLK_PAGEDOWN:
                        if(leve>0) {
                            leve--;
                            m.read(_MAPS_def[leve]);
                            palette p(m._w(),m._h(),_WIDTH/m._w(),_HEIGHT/m._h());
                            global_palette = p;
                            c.init();
                            title = "level:"+std::to_string(leve+1)+"    "+flag[leve];
                            SDL_SetWindowTitle(w,title.c_str());
                        }

                break;
                default:
                    break;
                }
                if(c.isfinsh()){
                        flag[leve] = '*';
                        leve++;
                        hleve = hleve>leve? hleve:leve;
                        m.read(_MAPS_def[leve]);
                        palette p(m._w(),m._h(),_WIDTH/m._w(),_HEIGHT/m._h());
                        global_palette = p;
                        c.init();
                        title = "level:"+std::to_string(leve+1)+"    "+flag[leve];
                        SDL_SetWindowTitle(w,title.c_str());
                }

                global_palette.reset();
                c.display();

                break;
            case SDL_QUIT: 
                isq =true;
                break;
            default:
                break;
            }
        }
      SDLdraw_updateWindow();
    }
    
    SDL_DestroyWindow(w);
    
    f = fopen("data.sav","wb+");

    if(f){
        fwrite(flag,sizeof(flag),1,f);
        fclose(f);
    }
    return 0;
}