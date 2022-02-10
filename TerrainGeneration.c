#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct table_t{
char map[21][80];
}table_t;
void mapbuilder(table_t *m){
  int i,j;
  for(i = 0; i < 21; i++){
      for(j = 0; j < 80; j++){
          if(i == 0|| i == 20 || j == 0|| j == 79)
          {
              m->map[i][j] = '%';

          }else{
              m->map[i][j] = ' ';
          }
      }
  }
}

void pathbuilder(table_t *m,int N,int S,int E,int W,int ranX,int ranY){

  int x_diff = E - W;
  int y_diff= N - S;
  //printf("X difference: %d, Y difference: %d\n",x_diff,y_diff);
  //printf("N:%d, S:%d\n",N,S);
  //printf("E:%d, W:%d, ranY: %d\n",E,W,ranY);
  m ->map[0][N] = '#';
  m ->map[20][S] = '#';
  m ->map[E][0] = '#';
  m ->map[W][79] = '#';
  int k = 79;
  int i,j;
  for(i = 0; i < 21; i++){
      for(j = 0; j < 80; j++){
          if(i == E && j <= ranX && j > 0){
              m->map[E][j] = '#';
          }
          if(E > W &&  x_diff>= 0){
              m ->map[E-x_diff][ranX] = '#';
              x_diff--;
          }else if(E < W && x_diff <= 0){
              m ->map[E-x_diff][ranX] = '#';
              x_diff++;
          }
          if(k > ranX)
          {
              m ->map[W][k] = '#';
              k--;
          }
      }
  }
  int f = 20;
  for(i = 0; i < 21; i++){
      for(j = 0; j < 80; j++){
          if(j == N && i <= ranY && i > 0){
               m ->map[i][N] = '#';
          }

          if(N > S && y_diff > 0){
               m ->map[ranY][N-y_diff] = '#';
                 y_diff--;

             }else if(N < S && y_diff < 0){
               m ->map[ranY][N-y_diff] = '#';
                 y_diff++;
             }

          if(f > ranY){
            m ->map[f][S] = '#';
            f--;
          }
      }
  }
}

void buildingadd(table_t *m,int N,int S,int E,int W,int ranX,int ranY){
  int i;
  srand(time(NULL));
  //Pokemon center will be on N S road and Pokemon mart will be on E W road
  //Check to see if building is being added to path.
  //also allow the marts to be added to other sides.
  int cloc = rand()%(ranX-2)+1;
  
  if(cloc == E|| cloc == W||m ->map[E+2][cloc] != ' '||m ->map[E+1][cloc+1] != ' ')
  {
    cloc += 4;
  }else if((cloc -1) == E|| (cloc - 1) == W)
  {
    cloc += 4;
  }


  int mloc = rand()%(ranY-2)+1;
  
  if(mloc == S || m ->map[mloc][N+2] != ' '||m ->map[mloc+1][N+1] != ' '){
    mloc -= 4; 
  }else if((mloc - 1) == S || (mloc - 1) == N )
  {
    mloc-= 4;
  }
  /*
  else if(mloc+1 == S){
    mloc -= 2;
  }else if(ranX == m->map[mloc][N+2])
  {
    mloc++;
  }
*/
  

  //printf("Center Location: %d\n Mart Location: %d\n",cloc,mloc);
//finds location for center
for(i = 0; i < 2; i++){
  m ->map[mloc+i][N+2] = 'C';
  m ->map[mloc+i][N+1] = 'C';
}
for(i = 0; i < 2; i++){
  m ->map[E+2][cloc+i] = 'M';
  m ->map[E+1][cloc+i] = 'M';
}
}

void grass_add(table_t *m){
  srand(time(NULL));
  int k;
  int tall_grass_x = rand()%3+28;
  int tall_grass_y = rand()%3+10;

  //printf("tall_grass_x %d, tall_grass_y %d\n",tall_grass_x,tall_grass_y);
  k = rand()% 2;
  //Adds tall grass region 1 which is top left corner
  while(tall_grass_y > 0 && tall_grass_x > 0)
  {
      if(m ->map[tall_grass_y][k] == ' ')
      {
        m ->map[tall_grass_y][k] = ':';
      }
      if(k == tall_grass_x){
        tall_grass_y--;
        tall_grass_x = rand()%21+40;
        k = rand() % 2;
      }
    k++;
  }
  //Adds tall grass region 2 which is bottom right corner
  tall_grass_y = 19;
  tall_grass_x = 79;
  //printf("second tall_grass_x %d, second tall_grass_y %d\n",tall_grass_x,tall_grass_y);
  k = 45;
  while(tall_grass_y >= 10 && tall_grass_x > 40)
  {
      if(m ->map[tall_grass_y][k] == ' ')
      {
        m ->map[tall_grass_y][k] = ':';
      }
      if(k == tall_grass_x){
        tall_grass_y--;
        tall_grass_x = 78;
        k = rand()%5+45;
      }
    k++;
  }
}

void clearing_builder(table_t *m){
  srand(time(NULL));
  int k;
  int x_clearing = rand()%3+28;
  int y_clearing = rand()%2+17;

  //printf("x_clearing %d, y_clearing %d\n",x_clearing,y_clearing);
  k = rand()% 2;
  //Adds clearing to bottom left corner
  while(y_clearing > 0 && x_clearing > 0)
  {
      if(m ->map[y_clearing][k] == ' ')
      {
        m ->map[y_clearing][k] = '.';
      }
      if(k == x_clearing){
        y_clearing--;
        x_clearing = rand()%21+40;
        k = rand() % 2;
      }
    k++;
  }
  y_clearing = rand()%3+10;
  x_clearing = 79;
  //printf("second x_clearing %d, second y_clearing %d\n",x_clearing,y_clearing);
  k = 45;
  while(y_clearing >= 0 && x_clearing > 40)
  {
      if(m ->map[y_clearing][k] == ' ')
      {
        m ->map[y_clearing][k] = '.';
      }
      if(k == x_clearing){
        y_clearing--;
        x_clearing = rand()%3+75;
        k = rand()%5+45;
      }
    k++;
  }

}

void trees_boulders(table_t *m){
  int i,j;
  srand(time(NULL));
  int ranNum = rand()%1;
  for(i = 0; i < 21; i++){
    for(j = 0; j < 80; j++){
      if(m ->map[i][j] == ' ')
      {
        if(ranNum == 0){
            m ->map[i][j] = '^';
        }else{
            m ->map[i][j] = '%';
        }
      }
      ranNum = rand()%2;
    }
  }
}

int main(int argc, char *argv[]){
  srand(time(NULL));
  //make sure that the roads have a 4x4 distance between them so that the buidlings have space between them.
  //prevent the roads from being close to the walls
  int N = rand()% 34+40;
  int S = rand()% 74 + 5;
  int E = rand()% 13 + 5;
  int W = rand()% 13 + 5;
  //Make sure the bounds of ranX and Y are properly defined so that it does not go of the map
  int ranX = rand()% 69 + 10;
  int ranY = rand()% 12 + 5;
  printf("RanY: %d E: %d",ranY,E);
  if(ranY-E < 3)
  {
    ranY+=4;
  }
  if(abs(N - ranX) <= 2){
    ranX+=2;
  }
  if(abs(E-W)|| abs(W-E) <= 2)
  {
    W++;
  }
   printf(" POST RanY: %d E: %d\n",ranY,E);
    //intitialize 2d array struct
    table_t* map = malloc(sizeof(table_t));
    int i,j;
    mapbuilder(map);
    pathbuilder(map,N,S,E,W,ranX,ranY);
    buildingadd(map,N,S,E,W,ranX,ranY);
    grass_add(map);
    clearing_builder(map);
    trees_boulders(map);
    for(i = 0; i < 21; i++){
        for(j = 0; j < 80; j++){
            printf("%c", map->map[i][j]);
        }
        printf("\n");
    }
}
