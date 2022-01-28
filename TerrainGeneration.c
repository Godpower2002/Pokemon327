#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){

    srand(time(NULL));
    char map[21][80];
    int i,j;
    for(i = 0; i < 21; i++){
        for(j = 0; j < 80; j++){
            if(i == 0|| i == 20 || j == 0|| j == 79)
            {
                map[i][j] = '%';
              
            }else{
                map[i][j] = ' ';
            }
            
        }
    }
    //possible bug if one of the random values are within
    int N = rand()% 80 + 1;
    int S = rand()% 80 + 1;
    int E = rand()% 19 + 1;
    int W = rand()% 19 + 1;
    int ranX = rand()% 80 + 1;
    int ranY = rand()% 21 + 1;
    int x_diff,x_t_diff= E - W;
    int y_diff,y_t_diff = N - S;
    printf("N:%d, S:%d, diffpos: %d, diffneg: %d\n",N,S,x_diff,x_t_diff);
    printf("E:%d, W:%d, ranY: %d\n",E,W,ranY);
    map[0][N] = '#';
    map[20][S] = '#';
    map[E][0] = '#';
    map[W][79] = '#';
    

    //Makes path along East to West
    /*
    for(i = 0; i < 21; i++){
        for(j = 0; j < 80; j++){
            if(i == E && j < ranX && j > 0){
                map[E][j] = 'P';
            }
        }
    }

    for(i = 0; i < 21; i++){
        for(j = 0; j < 80; j++){ 
            if(E > W &&  x_diff>= 0){
                map[E-x_diff][ranX - 1] = '*';
                x_diff--;
            }else if(E < W && x_diff <= 0){
                map[E-x_diff][ranX - 1] = '*';
                x_diff++;
            }
        }
    }

  
    for(i = 0; i < 21; i++){
        for(j = 0; j < 80; j++){
            if(j < 79 && ranX < 79)
            {
                map[E-x_t_diff][ranX] = '*';
                ranX++;
            }
            
        }
    }*/
    //makes path along West to East
    for(i = 0; i < 20; i++){
        for(j = 0; j < 80; j++){
            if(j == N && i < ranY && i > 0){
                 map[i][N] = 'P';
            }
        }
    }
//Stuck on connecting with north and south axis
  //  map[N+y_diff][ranY] = '*';
/*
    for(i = 0; i < 21; i++){
        for(j = 0; j < 80; j++){ 
            if(N > S &&  y_diff>= 0){
                map[N-y_diff][ranY - 1] = '*';
                y_diff--;
            }else if(N < S && y_diff <= 0){
                map[N-y_diff][ranY - 1] = '*';
                y_diff++;
            }
        }
    }

  /*
    for(i = 0; i < 21; i++){
        for(j = 0; j < 80; j++){
            if(j < 79 && ranX < 79)
            {
                map[E-x_t_diff][ranX] = '*';
                ranX++;
            }
            
        }
    }

*/


    for(i = 0; i < 21; i++){
        for(j = 0; j < 80; j++){
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}