#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <time.h>

#define N 50
#define POPULATION_SIZE 500
#define MUTATION_RATE 0.01
#define TOTAL_GENERATION 500

void create_population(int population[][N], int size)
{
    srand(time(0));
    for(int q0=0; q0<size; q0++){
        int q1 = 0;
        while(q1<N){
            int pop = rand()%N, dont_do = 0;
            for(int q2=0; q2<q1; q2++){
                if(pop == population[q0][q2]){
                    dont_do = 1;
                }
            }
            if(!dont_do){
                population[q0][q1] = pop;
                q1++;
            }
        }
    }
}

int fitness_func(int state[])
{
    int attacking = 0;
    for(int q0=0; q0<N; q0++){
        int row = state[q0], col = q0 - 1;
        while(col >= 0 && state[col] != row){
            col--;
        }
        if(col >= 0 && state[col] == row){
            attacking++;
        }
        row = state[q0], col = q0 + 1;
        while(col < N && state[col] != row){
            col++;
        }
        if(col < N && state[col] == row){
            attacking++;
        }
        row = state[q0] - 1, col = q0 - 1;
        while(col >= 0 && row >= 0 && state[col] != row){
            col--;
            row--;
        }
        if(col >= 0 && row >= 0 && state[col] == row){
            attacking++;
        }
        row = state[q0] + 1, col = q0 + 1;
        while(col < N && row < N && state[col] != row){
            col++;
            row++;
        }
        if(col < N && row < N && state[col] == row){
            attacking++;
        }
        row = state[q0] + 1, col = q0 - 1;
        while(col >= 0 && row < N && state[col] != row){
            col--;
            row++;
        }
        if(col >= 0 && row < N && state[col] == row){
            attacking++;
        }
        row = state[q0] - 1, col = q0 + 1;
        while(col < N && row >= 0 && state[col] == row){
            col++;
            row--;
        }
        if(col < N && row >= 0 && state[col] == row){
            attacking++;
        }
    }
    return attacking/2;
}

void crossover(int* parent1, int* parent2, int* child)
{
    int crossoverPoint = rand() % N;
    for (int i = 0; i < crossoverPoint; i++) {
        child[i] = parent1[i];
    }
    for (int i = crossoverPoint; i < N; i++) {
        child[i] = parent2[i];
    }
}

void partially_mapped_crossover(int* parent1, int* parent2, int* child)
{
    int l = rand() % N, r = rand() % N;
    if(l>r){
        int temp = r;
        r = l;
        l = temp;
    }
    int check[N];
    for(int q0=0; q0<N; q0++){
        check[q0] = N;
    }
    for(int q0=l; q0<=r; q0++){
        check[parent1[q0]] = parent2[q0];
        child[q0] = parent1[q0];
    }
    for(int q0=0; q0<l; q0++){
        int gene = parent2[q0];
        while(check[gene] != N){
            gene = check[gene];
        }
        if(check[gene] == N){
            child[q0] = gene;
        }
    }
    for(int q0=r+1; q0<N; q0++){
        int gene = parent2[q0];
        while(check[gene] != N){
            gene = check[gene];
        }
        if(check[gene] == N){
            child[q0] = gene;
        }
    }
}

void mutation(int* child) //inversion
{
    if((rand()/(double)RAND_MAX) < MUTATION_RATE){
        int l = rand() % N, r = rand() % N;
        if(l>r){
            int temp = r;
            r = l;
            l = temp;
        }
        for(int q0=l; q0<=(l+r)/2; q0++){
            int temp = child[r+l-q0];
            child[r+l-q0] = child[q0];
            child[q0] = temp;
        }
    }
}

int main()
{
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    srand(time(NULL));
    int population[POPULATION_SIZE][N];
    int fitness[POPULATION_SIZE] = {0};
    create_population(population, POPULATION_SIZE);
    for(int q0=0; q0<POPULATION_SIZE; q0++){
        fitness[q0] = fitness_func(population[q0]);
    }
    int generation = 0, biggest_fitness = N*(N-1)/2;
    while(generation < TOTAL_GENERATION){
        for(int q0=0; q0<POPULATION_SIZE; q0++){
            int* parents[2];
            parents[0] = population[rand() % POPULATION_SIZE];
            parents[1] = population[rand() % POPULATION_SIZE];
            int child[N];
            //crossover(parents[0], parents[1], child);
            partially_mapped_crossover(parents[0], parents[1], child);
            mutation(child);
            int child_fitness = fitness_func(child);
            if(child_fitness < fitness[q0]){
                for(int q1=0; q1<N; q1++){
                    population[q0][q1] = child[q1];
                }
                fitness[q0] = child_fitness;
            }
        }
        generation++;
        int breaker = 0;
        biggest_fitness = N*(N-1)/2;
        for(int q0=0; q0<POPULATION_SIZE; q0++){
            if(fitness[q0] == 0){
                breaker = 1;
            }
            if(fitness[q0] < biggest_fitness){
                biggest_fitness = fitness[q0];
            }
        }
        //printf("generation %d best fitness: %d\n", generation, biggest_fitness);
        if(breaker){
            break;
        }
    }
    printf("%d\n", biggest_fitness);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double execution_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("%lf sec\n", execution_time);
    return 0;
}
