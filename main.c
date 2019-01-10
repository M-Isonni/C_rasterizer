#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "rasterizer.h"

int main(int argc, char **argv){

        context_t ctx;
        ctx.width=600;
        ctx.height=600;        
        
        #define triangle(x0,y0,z0,x1,y1,z1,x2,y2,z2)\
            triangle_new(\
                vertex_new(Vector3_new(x0,y0,z0)),\
                vertex_new(Vector3_new(x1,y1,z1)),\
                vertex_new(Vector3_new(x2,y2,z2))\
                )

        ctx.framebuffer=NULL;

        triangle_t triangle=triangle(0,0.5,0,-0.5,0,0,0.5,-0.2,0);

        SDL_Init(SDL_INIT_VIDEO);
        
        SDL_Window *window=SDL_CreateWindow("window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,600,600,0);

        if(!window)
        {
            return -1;
        }

        SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if(!renderer)
        {
            return -1;
        }

        SDL_Texture *texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,600,600);

        int running=1;

        while(running){
            SDL_Event event;
            while(SDL_PollEvent(&event)){
                if(event.type==SDL_QUIT){
                    running=0;
                }
            }
            int pitch;
            SDL_LockTexture(texture,NULL,(void **)&ctx.framebuffer,&pitch);
            clear_screen(&ctx);
            rasterize(&ctx,&triangle);
            put_pixel(&ctx,&triangle);
            SDL_UnlockTexture(texture);
            SDL_RenderCopy(renderer,texture,NULL,NULL);
            SDL_RenderPresent(renderer);
        }

        return 0;
}