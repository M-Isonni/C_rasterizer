#include "math.h"

Vector3_t Vector3_new(float x, float y,float z){
    Vector3_t vector = {.x=x,.y=y,.z=z};
    return vector;
}

Vector3_t Vector3_zero(){
    Vector3_t vec={0,0,0};
    return vec;
}

//float lerp(float start,float end,)