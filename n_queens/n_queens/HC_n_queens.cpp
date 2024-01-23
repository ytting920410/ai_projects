#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <time.h>

#define N 50

void random_board(int board[][N], int* state)
{
    srand(time(0));
    for(int i = 0; i < N; i++){
        state[i] = rand() % N;
        board[state[i]][i] = 1;
    }
}

void print_board(int board[][N])
{

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

void fill(int board[][N], int value)
{
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = value;
        }
    }
}

int calculate_objective(int board[][N], int* state)
{
    int attacking = 0;
    int row, col;
    for(int i = 0; i < N; i++){
        row = state[i], col = i - 1;
        while(col >= 0 && board[row][col] != 1){
            col--;
        }
        if(col >= 0 && board[row][col] == 1){
            attacking++;
        }
        row = state[i], col = i + 1;
        while(col < N && board[row][col] != 1){
            col++;
        }
        if(col < N && board[row][col] == 1){
            attacking++;
        }
        row = state[i] - 1, col = i - 1;
        while(col >= 0 && row >= 0 && board[row][col] != 1){
            col--;
            row--;
        }
        if(col >= 0 && row >= 0 && board[row][col] == 1){
            attacking++;
        }
        row = state[i] + 1, col = i + 1;
        while(col < N && row < N && board[row][col] != 1){
            col++;
            row++;
        }
        if(col < N && row < N && board[row][col] == 1){
            attacking++;
        }
        row = state[i] + 1, col = i - 1;
        while(col >= 0 && row < N && board[row][col] != 1){
            col--;
            row++;
        }
        if(col >= 0 && row < N && board[row][col] == 1){
            attacking++;
        }
        row = state[i] - 1, col = i + 1;
        while(col < N && row >= 0 && board[row][col] != 1){
            col++;
            row--;
        }
        if(col < N && row >= 0 && board[row][col] == 1){
            attacking++;
        }
    }
    return (int)(attacking/2);
}

void generate_board(int board[][N], int* state)
{
    fill(board, 0);
    for(int i = 0; i < N; i++){
        board[state[i]][i] = 1;
    }
}

void copy_state(int* state1, int* state2)
{

    for(int i = 0; i < N; i++){
        state1[i] = state2[i];
    }
}

void get_neighbor(int board[][N], int* state)
{
    int opti_board[N][N];
    int opti_state[N];
    copy_state(opti_state, state);
    generate_board(opti_board, opti_state);
    int opti_objective = calculate_objective(opti_board, opti_state);
    int neighbor_board[N][N];
    int neighbor_state[N];
    copy_state(neighbor_state, state);
    generate_board(neighbor_board, neighbor_state);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j != state[i]){
                neighbor_state[i] = j;
                neighbor_board[neighbor_state[i]][i] = 1;
                neighbor_board[state[i]][i] = 0;
                int temp = calculate_objective(neighbor_board, neighbor_state);
                if(temp <= opti_objective){
                    opti_objective = temp;
                    copy_state(opti_state, neighbor_state);
                    generate_board(opti_board, opti_state);
                }
                neighbor_board[neighbor_state[i]][i] = 0;
                neighbor_state[i] = state[i];
                neighbor_board[state[i]][i] = 1;
            }
        }
    }
    copy_state(state, opti_state);
    fill(board, 0);
    generate_board(board, state);
}

void hill_climbing(int board[][N], int* state)
{
    int neighbour_board[N][N] = {};
    int neighbour_state[N];
    copy_state(neighbour_state, state);
    generate_board(neighbour_board, neighbour_state);
    while(1){
        copy_state(state, neighbour_state);
        generate_board(board, state);
        get_neighbor(neighbour_board, neighbour_state);
        if (calculate_objective(board, state) == calculate_objective(neighbour_board, neighbour_state)){
            //print_board(board);
            printf("%d\n", calculate_objective(board, state));
            break;
        }
    }
}

int main()
{
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    int state[N] = {};
    int board[N][N] = {};
    random_board(board, state);
    hill_climbing(board, state);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double execution_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("%lf sec\n", execution_time);
    return 0;
}
