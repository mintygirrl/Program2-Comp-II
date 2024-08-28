/**********************************************************************
Program: Program 2
Author: Fallon Weiss
Date: 7/8/24
Time spent: One week.
Purpose: The purpose of this program is to run a simulation of two 
doubly linked queues of distinct lengths of cars to simluate a ferry
crossing, starting from the left and moving back and forth, picking up
cars and taking them to the other side of the river.
***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


int simulate_ferry_crossings(int l, int m, int cars[], char banks[][6]);

int main(int argc, char* argv[]) 
{
    FILE* input_file = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w");

    if (!input_file) 
    {
        fprintf(stderr, "Error opening input.txt\n");
        return 1;
    }
    if (!output_file) 
    {
        fprintf(stderr, "Error opening output.txt\n");
        fclose(input_file);
        return 1;
    }

    int num_cases;
    fscanf(input_file, "%d", &num_cases);

    for (int i = 0; i < num_cases; i++) 
    {
        int l, m;
        fscanf(input_file, "%d %d", &l, &m);

        int cars[m];
        char banks[m][6];

        for (int j = 0; j < m; j++) 
        {
            fscanf(input_file, "%d %s", &cars[j], banks[j]);
        }

        int result = simulate_ferry_crossings(l, m, cars, banks);
        fprintf(output_file, "%d\n", result);
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}

int simulate_ferry_crossings(int l, int m, int cars[], char banks[][6]) 
{
    Queue left_queue;
    Queue right_queue;
    init_queue(&left_queue);
    init_queue(&right_queue);
    
    // Enqueue cars into respective queues
    for (int i = 0; i < m; i++) 
    {
        if (banks[i][0] == 'l') 
        {  // Check if the bank is "left"
            enqueue(&left_queue, cars[i]);
        } else 
        {  // Assume it must be "right"
            enqueue(&right_queue, cars[i]);
        }
    }

    int ferry_length = l * 100;  // Convert to centimeters
    int current_load = 0;
    int crossings = 0;
    char current_bank = 'l';  // Start at the left bank

    while (!is_empty(&left_queue) || !is_empty(&right_queue)) 
    {
        current_load = 0;

        if (current_bank == 'l') 
        {
            while (!is_empty(&left_queue) && current_load + left_queue.head->data <= ferry_length) 
            {
                current_load += service(&left_queue);
            }
            current_bank = 'r';  // Switch to the right bank
        } else 
        {
            while (!is_empty(&right_queue) && current_load + right_queue.head->data <= ferry_length) 
            {
                current_load += service(&right_queue);
            }
            current_bank = 'l';  // Switch to the left bank
        }

        crossings++;
    }

    free_queue(&left_queue);
    free_queue(&right_queue);

    return crossings;
}
