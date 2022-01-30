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
    int N = rand()% 78 + 1;
    int S = rand()% 78 + 1;
    int E = rand()% 19 + 1;
    int W = rand()% 19 + 1;
    //Make sure the bounds of ranX and Y are properly defined so that it does not go of the map 
    int ranX = rand()% 78 + 1;
    int ranY = rand()% 19 + 1;
    int x_diff = E - W;
    int x_t_diff = E - W;
    int y_diff= N - S;
    int y_t_diff = N - S;
    printf("X difference: %d, Y difference: %d\n",x_diff,y_diff);
    printf("N:%d, S:%d\n",N,S);
    printf("E:%d, W:%d, ranY: %d\n",E,W,ranY);
    map[0][N] = '#';
    map[20][S] = '#';
    map[E][0] = '#';
    map[W][79] = '#';
    int k = 79;

    //Makes path along East to West
    
    for(i = 0; i < 21; i++){
        for(j = 0; j < 80; j++){
            if(i == E && j < ranX && j > 0){
                map[E][j] = '#';
            }
            if(E > W &&  x_diff>= 0){
                map[E-x_diff][ranX] = '#';
                x_diff--;
            }else if(E < W && x_diff <= 0){
                map[E-x_diff][ranX] = '#';
                x_diff++;
            }
            if(k > ranX)
            {
                map[W][k] = '#';
                k--;
            }
        }
    }

    //makes path along West to East
int f = 20;
for(i = 0; i < 21; i++){
    for(j = 0; j < 80; j++){
        if(j == N && i <= ranY && i > 0){
            map[i][N] = '#';
        }

        if(N > S && y_diff > 0){
               map[ranY][N-y_diff] = '#';
               y_diff--;

           }else if(N < S && y_diff < 0){
               map[ranY][N-y_diff] = '#';
               y_diff++;
           }

        if(f > ranY)
             map[f][S] = '#';
             f--;
    }
}



    for(i = 0; i < 21; i++){
        for(j = 0; j < 80; j++){
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}