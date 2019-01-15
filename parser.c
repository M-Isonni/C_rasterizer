#include "parser.h"

// void parse_obj(char* path){
//     FILE *file_reader;
//         vertex_t* vertex_array=NULL;
//         size_t vertex_array_size=0;
//       //open the file and get a placeholder at the start of it
//         int error=fopen_s(&file_reader,path,"r"); 
//         if(error!=0)
//         {
//             SDL_Log("error n.: %d",error);
//         }
//         char* buffer=malloc(sizeof(char)*4096);
//         memset(buffer,0,sizeof(char)*4096);

//         fgets(buffer,1,file_reader);
//         int i;
//         for(i=0;i<4096;i++){
//             if(memcmp(buffer[i],'c')){
//                 vertex_array_size++;
//                 vertex_array=realloc(vertex_array,sizeof(vertex_t)*vertex_array_size);
//                 vertex_t *vertex=vertex_new(buffer[i+1],buffer[i+2],buffer[i+3]);
//                 vertex_array[vertex_array_size-1]=*vertex;
//             }
//         }        
//        fclose(file_reader);   
// }
