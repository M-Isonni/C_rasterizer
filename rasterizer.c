#include "rasterizer.h"
#include <string.h>
#include <stdio.h>

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

    vertex_t p[3];
    p[0]=triangle->a;
    p[1]=triangle->b;
    p[2]=triangle->c;

    bubble_sort(p,3);

    float slope_p0_p1= (p[1].raster_x-p[0].raster_x)/(p[1].raster_y-p[0].raster_y);
    float slope_p0_p2= (p[2].raster_x-p[0].raster_x)/(p[2].raster_y-p[0].raster_y);
    if(slope_p0_p1<slope_p0_p2)
    {
        printf("left");
    }
    else
        printf("right");

    int y;
    int x;
    int x1;
    float gradient;
    float gradient1;
    int index;
    int index1;
    int x2;    
    for(y=p[0].raster_y;y<=p[1].raster_y;y++){

        gradient=(float)(y-p[0].raster_y)/(float)(p[1].raster_y-p[0].raster_y);
        x = lerp(p[0].raster_x,p[1].raster_x,gradient); 
        index = (y*ctx->width+x)*4;  
        ctx->framebuffer[index++]=255;
        ctx->framebuffer[index++]=255;
        ctx->framebuffer[index++]=255;
        ctx->framebuffer[index]=255; 
        gradient1=(float)(y-p[0].raster_y)/(p[2].raster_y-p[0].raster_y);
        x1=lerp(p[0].raster_x,p[2].raster_x,gradient1);
        index1 = (y*ctx->width+x1)*4;
        ctx->framebuffer[index1++]=255;
        ctx->framebuffer[index1++]=255;
        ctx->framebuffer[index1++]=255;
        ctx->framebuffer[index1]=255; 
        int index2;
        for(x2=x;x2<x1;x2++){
            index2 = (y*ctx->width+x2)*4;
            ctx->framebuffer[index2++]=255;
            ctx->framebuffer[index2++]=255;
            ctx->framebuffer[index2++]=255;
            ctx->framebuffer[index2]=255; 
        }
    }   
    // y3=y;
    // x3=x2;
    for(y=p[1].raster_y;y<=p[2].raster_y;y++){
        gradient=(float)(y-p[1].raster_y)/(float)(p[2].raster_y-p[1].raster_y);
        x = lerp(p[1].raster_x,p[2].raster_x,gradient); 
        index = (y*ctx->width+x)*4;  
        ctx->framebuffer[index++]=255;
        ctx->framebuffer[index++]=255;
        ctx->framebuffer[index++]=255;
        ctx->framebuffer[index]=255; 
        gradient1=(float)(y-p[0].raster_y)/(p[2].raster_y-p[0].raster_y);
        x1=lerp(p[0].raster_x,p[2].raster_x,gradient1);
        index1 = (y*ctx->width+x1)*4;
        ctx->framebuffer[index1++]=255;
        ctx->framebuffer[index1++]=255;
        ctx->framebuffer[index1++]=255;
        ctx->framebuffer[index1]=255; 
        int index2;
        for(x2=x;x2<x1;x2++){
            index2 = (y*ctx->width+x2)*4;
            ctx->framebuffer[index2++]=255;
            ctx->framebuffer[index2++]=255;
            ctx->framebuffer[index2++]=255;
            ctx->framebuffer[index2]=255; 
        } 
    }
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

void bubble_sort(vertex_t *vertexes, int size){
    int i;
    for(i=0;i<size-1;i++)
    {
        vertex_t temp;
        if(vertexes[i].raster_y>vertexes[i+1].raster_y){
            temp=vertexes[i];
            vertexes[i]=vertexes[i+1];
            vertexes[i+1]=temp;   
        }
    }
}