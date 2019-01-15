#include "math.h"

typedef struct context{
    int width;
    int height;

    unsigned char *framebuffer;

}context_t;

typedef struct vertex{
    Vector3_t position;
    Vector3_t normal;
    Vector3_t color;

    int raster_x;
    int raster_y;
}vertex_t;

vertex_t *vertex_new(Vector3_t *vec);

typedef struct triangle{
    vertex_t a;
    vertex_t b;
    vertex_t c;
}triangle_t;

triangle_t *array_of_triangles;
size_t array_of_triangle_size;

triangle_t *triangle_new(vertex_t *a,vertex_t *b, vertex_t *c);
void rasterize(context_t *ctx,triangle_t *triangle);
void put_pixel(context_t *ctx,triangle_t *triangle);
void clear_screen(context_t *ctx);
void bubble_sort(vertex_t *vertexes, int size);
void append_triangle(triangle_t* value);
//void append_triangle(triangle_t *array_of_triangles[],size_t* array_of_triangle_size, triangle_t *triangle_to_append);