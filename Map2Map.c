#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "TerrainGeneration.h"

typedef struct worldmap_t{
  table_t* world[399][399];
}worldmap_t;


int neighborCheck(worldmap_t *worldmap,int rows,int cols, char dir){


  srand(time(NULL));
  switch(dir){
    case 'n':
      if(worldmap->world[rows + 1][cols] != NULL){
        //takes in neighboring south as north
          return return_exits(worldmap->world[rows + 1][cols],'s');
      }else{
          return (rand()% 34+40);
      }
    case 's':
        if(worldmap->world[rows - 1][cols] != NULL){
      //takes neighboring north as south
          return return_exits(worldmap->world[rows - 1][cols],'n');
        }else{
          return (rand()% 74 + 5);
        }
    case 'e':
    if(worldmap->world[rows][cols + 1] != NULL){
      //takes neighboring west exit as east exit
          return return_exits(worldmap->world[rows][cols + 1],'w');
    }else{
      //randomize east exit
          return (rand()% 13 + 5);
    }
    case 'w':
    if(worldmap->world[rows][cols - 1] != NULL){
      //takes neighboring east as west exit
      return return_exits(worldmap->world[rows][cols - 1],'e');
    }else{
      //randomize west exit
      return (rand()% 13 + 5);
    }

  }



}
//this function will parse the integers out of input. first space is x second space is y
int parseX(char x[4]){
  printf("\n");
  int parsedX;
  sscanf(x, "%04d", &parsedX);
  return parsedX;
}
int parseY(char input[20],int second){
  int i;
  char posy[4];
   int count = 0;
  for(i = second; i < 20; i++)
  {
    if((isdigit(input[i]) || input[i] == '-')){
      posy[count] = input[i];

      count++;
    }
  }
  int parsed;
  sscanf(posy, "%04d", &parsed);
  return parsed;
}




void print_map(table_t* m, int x, int y){
  int i,j;
  for(i = 0; i < 21; i++){
        for(j = 0; j < 80; j++){
            printf("%c", m->map[i][j]);
        }
        printf("\n");
    }
    printf("(%d,%d)\n",x,y);
}
//checks if a neighbor exists and matches exits with current map. if it doesn't exist returns random exit


//make function called border which will take in cardinal direction map and will erase exit based on direction
table_t* border(table_t *b, char dir,int rows,int cols){
  int i,j;

  //BUG DOUBLE CHECK RANGES
  if(dir == 'n'){
    for(i = 0; i < 80; i++){
      b->map[0][i] = '%';
      if(cols == 0){
        b->map[i][80] = '%';
      }else if(cols = 399){
          b->map[i][0] = '%';
      }
    }
    }

  if(dir == 's'){
    for(i = 0; i < 80; i++){
      b->map[21][i] = '%';
      if(cols == 0){
        b->map[i][80] = '%';
      }else if(cols == 399){
        b->map[i][0] = '%';
      }
  }

  if(dir == 'e'){
    for(i = 0; i < 21; i++){
      b->map[i][0] = '%';
      if(rows == 0){
        b->map[0][i] = '%';
      }else if(rows == 399){
        b->map[21][i] = '%';
      }
    }
  }
  if(dir == 'w'){
    for(i = 0; i < 21; i++){
      b->map[i][80] = '%';
      if(rows == 0){
        b->map[0][i] = '%';
      }else if(rows == 399){
          b->map[21][i] = '%';
      }
    }
  }
}

  return b;
}

int main(int argc, char *argv[]){
  int i,j;
  srand(time(NULL));
  worldmap_t* worldmap = malloc(sizeof(worldmap_t));
  for( i = 0; i < 399; i++){
    for(j = 0; j < 399; j++){
      worldmap->world[i][j] = NULL;
    }
  }
  table_t* map = malloc(sizeof(table_t));

  int N = rand()% 34+40;
  int S = rand()% 74 + 5;
  int E = rand()% 13 + 5;
  int W = rand()% 13 + 5;
  //printf("E before mapgen %d\n",E);
  int xCoord = 0;
  int yCoord = 0;
  worldmap->world[199][199] = mapgen(map,N,S,E,W,199,199);
  print_map( worldmap->world[199][199],xCoord,yCoord);

  char exit = 0;
  int rows = 199;
  int cols = 199;
  int prevS = N;
  int prevN = S;
  int prevE = E;
  int prevW = W;
  //printf("returning exit %d\n",return_exits(worldmap->world[199][199],'w'));
  //printf("PREV W %d\n",prevW);





while(1)
{
    char c[20];
    fgets(c, 20, stdin);
    int count = 2;
    //use spaces as a buffer. when spaces == 1 count into x char string //Possibly use site bro gave me

    if(c[0] == 'q')
    {

        break;
    }


    if(c[0] == 'f'){


      char posx[4];
      char posy[4];

      int count = 0;
      int spaces = 0;
      int secondSpace = 0;
      for(i = 0; i < 20; i++)
      {
        if(c[i] == ' '){
          spaces++;
          if(spaces == 2){
            secondSpace = i;
          }
        }

        if(spaces == 1 && (c[i] == '-'||isdigit(c[i]))){
          posx[count] = c[i];
          count++;
        }

      }
    int X = parseX(posx);
    int Y = parseY(c,secondSpace);

    if(X > 199)
    {
      X = 199;
    }
    if(Y > 199){
      Y = 199;
    }
    if(X < 0){
      X = 0;
    }
    if(Y < 0){
      Y = 0;
    }
    rows = rows + Y;
    cols = cols + X;
    xCoord = X;
    yCoord = Y;
     //printf("%d , %d",parse(c,1),parse(c,2));
    if(worldmap->world[rows][cols] == NULL){
      N = neighborCheck(worldmap,rows,cols,'n');
      S = neighborCheck(worldmap,rows,cols,'s');
      E = neighborCheck(worldmap,rows,cols,'e');
      W = neighborCheck(worldmap,rows,cols,'w');
      table_t* map2 = malloc(sizeof(table_t));
      //check if it is teleported to a border on a side
      if(rows == 0 || cols == 0 || rows == 399 || cols == 399){
        worldmap->world[rows][cols] = border(mapgen(map2,N,prevS,E,W,rows,cols),'n',rows,cols);
      }else{
        worldmap->world[rows][cols] = mapgen(map2,N,prevS,E,W,rows,cols);
      }
      print_map(worldmap->world[rows][cols],xCoord,yCoord);
    }else{
      print_map( worldmap->world[rows][cols],xCoord,yCoord);
    }
    }





    //BUG switch south and north variable names because north is negative y coordinate direction but goes towards row == 399 while south is positive coording y direction but goes towards zero in 2d array
    if(c[0] == 's'){
      if(rows < 399){
        rows++;
        yCoord--;
      }
      //current issue is that for some reason, the value of north is being changed every iteration
      if(worldmap->world[rows][cols] == NULL && rows >= 0){
        //check neigbors and set current exit based on neighboring exit.

        //given south randomize east west and north
        N = neighborCheck(worldmap,rows,cols,'n');
        E = neighborCheck(worldmap,rows,cols,'e');
        W = neighborCheck(worldmap,rows,cols,'w');




        table_t* map2 = malloc(sizeof(table_t));
        if(rows == 0 || rows == 399){
          worldmap->world[rows][cols] = border(mapgen(map2,N,prevS,E,W,rows,cols),'s',rows,cols);
        }else{
          worldmap->world[rows][cols] = mapgen(map2,N,prevS,E,W,rows,cols);
        }
        prevS = N;
        prevN = prevS;
        prevE = E;
        prevW = W;
        print_map( worldmap->world[rows][cols],xCoord,yCoord);

      }else{

        print_map( worldmap->world[rows][cols],xCoord,yCoord);

      }

    }else if(c[0] == 'n'){
      //given north randomize west east and south.
      if(rows > 0){
        rows--;
        yCoord++;
      }
      if(worldmap->world[rows][cols] == NULL && rows != 399){

        S = neighborCheck(worldmap,rows,cols,'s');
        E = neighborCheck(worldmap,rows,cols,'e');
        W = neighborCheck(worldmap,rows,cols,'w');
        //later bug to be fixed

        table_t* map2 = malloc(sizeof(table_t));
        if(rows == 0 || rows == 399){
          worldmap->world[rows][cols] = border(mapgen(map2,prevN,S,E,W,rows,cols),'n',rows,cols);
        }else{
          worldmap->world[rows][cols] = mapgen(map2,prevN,S,E,W,rows,cols);
        }
        prevN = S;
        prevS = N;
        prevE = E;
        prevW = W;
        print_map( worldmap->world[rows][cols],xCoord,yCoord);
      }else{
        print_map( worldmap->world[rows][cols],xCoord,yCoord);
      }
    }else if(c[0] == 'e'){
      cols++;
      xCoord++;
      if(worldmap->world[rows][cols] == NULL){
        N = neighborCheck(worldmap,rows,cols,'n');
        S = neighborCheck(worldmap,rows,cols,'s');
        W = neighborCheck(worldmap,rows,cols,'w');

        //printf("PREV W %d\n",prevW);
        table_t* map2 = malloc(sizeof(table_t));
        if(cols == 399){
          worldmap->world[rows][cols] = border(mapgen(map2,N,S,prevW,W,rows,cols),'e',rows,cols);
        }else{
          worldmap->world[rows][cols] = mapgen(map2,N,S,prevW,W,rows,cols );
        }

        prevW = W;
        prevS = N;
        prevN = S;
        print_map( worldmap->world[rows][cols],xCoord,yCoord);
      }else{
        print_map( worldmap->world[rows][cols],xCoord,yCoord);
      }
    }else if(c[0] == 'w'){
      if(cols > 0){
        cols--;
        xCoord--;
      }
      if(worldmap->world[rows][cols] == NULL){
        N = neighborCheck(worldmap,rows,cols,'n');
        S = neighborCheck(worldmap,rows,cols,'s');
        E = neighborCheck(worldmap,rows,cols,'e');



        table_t* map2 = malloc(sizeof(table_t));
        if(cols == 0){
          worldmap->world[rows][cols] = border(mapgen(map2,N,S,E,prevE,rows,cols),'w',rows,cols);
        }else{
            worldmap->world[rows][cols] = mapgen(map2,N,S,E,prevE,rows,cols);
        }
        prevE = E;
        prevS = N;
        prevN = S;
        print_map( worldmap->world[rows][cols],xCoord,yCoord);
      }else{
        print_map( worldmap->world[rows][cols],xCoord,yCoord);
      }



    }
    //printf("Prev N: %d Prev S: %d Prev E: %d Prev W: %d\n",prevN,prevS,prevE,prevW);

    exit = c[0];
}

    free(map);
    free(worldmap);

}
