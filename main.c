#define SDL_MAIN_HANDLED
#include "parser.h"

int main(int argc, char **argv){

        context_t ctx;
        ctx.width=600;
        ctx.height=600;  

        array_of_triangles=NULL;
        array_of_triangle_size=0;  
        vertex_array=NULL;
        vertex_array_size=0;    
        
        #define triangle(x0,y0,z0,x1,y1,z1,x2,y2,z2)\
            triangle_new(\
                vertex_new(Vector3_new(x0,y0,z0)),\
                vertex_new(Vector3_new(x1,y1,z1)),\
                vertex_new(Vector3_new(x2,y2,z2))\
                )

        SDL_Init(SDL_INIT_VIDEO);
        Vector3_t *camera=Vector3_new(0,0,-5);

        ctx.framebuffer=NULL; 
        size_t size;
        char* data=read_file("Stormtrooper.obj",&size);
        parse_obj(data,&size);
        parse_obj_faces(data,&size);
        
        
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
                if(event.type==SDL_KEYDOWN){
                    switch(event.key.keysym.scancode){
                        case SDL_SCANCODE_LEFT:
                            camera->x-=0.1;             
                            break;
                        case SDL_SCANCODE_RIGHT:
                            camera->x+=0.1;
                             break;             
                        case SDL_SCANCODE_DOWN:
                            camera->y+=0.1;
                            break;
                        case SDL_SCANCODE_UP:
                            camera->y-=0.1;
                            break; 
                        case SDL_SCANCODE_W:
                            camera->z+=0.1;
                            break; 
                        case SDL_SCANCODE_S:
                            camera->z-=0.1;
                            break; 
                        default:
                            break;
                    }      
                    
                }
            }
            int pitch;
            SDL_LockTexture(texture,NULL,(void **)&ctx.framebuffer,&pitch);
            clear_screen(&ctx);
            for(int i=0;i<array_of_triangle_size;i++){
                rasterize(&ctx,&array_of_triangles[i],camera);
            }
            
            SDL_UnlockTexture(texture);
            SDL_RenderCopy(renderer,texture,NULL,NULL);
            SDL_RenderPresent(renderer);
        }

        return 0;
}