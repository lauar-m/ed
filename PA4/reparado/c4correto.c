#include <stdlib.h>

struct Matrix{
  int rows, cols;
  int** data;
};

struct Matrix* rotation3D = 0;

int main(){
  int i;
  char * text;
  struct Matrix * rotation3D;

  text = (char*) malloc(100);
  if (!text) return -1;

  rotation3D = (struct Matrix*) malloc(sizeof(struct Matrix));
  if (!rotation3D) return -1; 

  rotation3D->rows=4;
  rotation3D->cols=4;

  rotation3D->data=(int**) malloc(sizeof(int*)*rotation3D->rows);
  if (!rotation3D->data) {
        free(rotation3D);
        return -1;
  } 

  for(i=0;i<rotation3D->rows;i++){
    rotation3D->data[i]=(int*) malloc(sizeof(int)*rotation3D->cols);
    if(!rotation3D->data[i]){
      while (i > 0) {
                free(rotation3D->data[--i]);
            }
      free(rotation3D->data);
      free(rotation3D);
      return -1;
    }
  }
  
  free(text);
  
  for (i = 0; i < rotation3D->rows; i++) {
        free(rotation3D->data[i]);
  }
  
  free(rotation3D->data);
  free(rotation3D);
  return 0;
}
