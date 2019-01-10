#include "rasterizer.h"
#include <string.h>

vertex_t vertex_new(Vector3_t position){
    vertex_t vertex;
    memset(&vertex,0,sizeof(vertex_t));
    vertex.position=position;
    return vertex;
}

triangle_t triangle_new(vertex_t a,vertex_t b, vertex_t c){
    triangle_t triangle={.a=a,.b=b,.c=c};
    return triangle;
}

void rasterize(context_t *ctx,triangle_t *triangle){
    triangle->a.raster_x=(ctx->width*(triangle->a.position.x+1)/2);
    triangle->a.raster_y=ctx->height-(ctx->height*(triangle->a.position.y+1)/2);
    triangle->b.raster_x=(ctx->width*(triangle->b.position.x+1)/2);
    triangle->b.raster_y=ctx->height-(ctx->height*(triangle->b.position.y+1)/2);
    triangle->c.raster_x=(ctx->width*(triangle->c.position.x+1)/2);
    triangle->c.raster_y=ctx->height-(ctx->height*(triangle->c.position.y+1)/2);
}

void put_pixel(context_t *ctx,triangle_t *triangle){
    int index_a = (triangle->a.raster_y*ctx->width+triangle->a.raster_x)*4;
    int index_b =(triangle->b.raster_y*ctx->width+triangle->b.raster_x)*4;
    int index_c = (triangle->c.raster_y*ctx->width+triangle->c.raster_x)*4;

    ctx->framebuffer[index_a++]=255;
    ctx->framebuffer[index_a++]=255;
    ctx->framebuffer[index_a++]=255;
    ctx->framebuffer[index_a]=255;
    ctx->framebuffer[index_b++]=255;
    ctx->framebuffer[index_b++]=255;
    ctx->framebuffer[index_b++]=255;
    ctx->framebuffer[index_b]=255;
    ctx->framebuffer[index_c++]=255;
    ctx->framebuffer[index_c++]=255;
    ctx->framebuffer[index_c++]=255;
    ctx->framebuffer[index_c]=255;
}

void clear_screen(context_t *ctx){
    memset(ctx->framebuffer,0,ctx->width*ctx->height*4);
}