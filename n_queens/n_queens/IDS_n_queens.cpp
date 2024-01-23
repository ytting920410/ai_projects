#include <stdio.h>
#include <ctime>
#define N 8

int q[N];
//int count;
int place(int row);

void show()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(q[i] == j) printf("@");
            else printf("-");
        }
        printf("\n");
    }
    printf("===========\n");
}

int main()
{
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    place(0);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double execution_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("%lf sec\n", execution_time);
    return 0;
}

int valid(int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        if(q[i] == col) return 0;
        if(row-i == col-q[i]) return 0;
        if(i-row == col-q[i]) return 0;
    }
    return 1;
}

int place(int row)
{
    if(row >= N)
    {
        //count++;
        //show();
        return 1;
    }
    else
    {
        for(int j = 0; j < N; j++)
        {
            if(valid(row, j))
            {
                q[row] = j;
                if(place(row+1)){
                    return 1;
                }
            }
        }
    }
}
