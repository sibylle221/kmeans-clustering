/*
    System Programming 2021
    Project 2

    Team 3
    2019073681 Sophie Nugent
    2019067574 Janae Fariñas
    2019041349 Joshua O'Leary
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define INPUT_FILE "data_set_1" // Enter file name here

int main() {

    FILE* input_file;
    input_file = fopen(INPUT_FILE".txt", "r");

    int no_of_clusters = 0; // K
    int dimension = 0; // d
    int no_of_data = 0; // n

    int cursor; //cursor storage
    int element = 0; //element cursor

    fscanf(input_file, "%d", &no_of_clusters); //retrieves k
    rewind(input_file); //reset eof

    // Retrieve dimension
    while(!feof(input_file)) //while not at end of file
    {
        fscanf(input_file,"%d", &cursor); //gets integer value of step
        if(cursor != NULL)
        {
            element++; //increments element count
        }

        if(element == 1)
        {
            fscanf(input_file, "%d", &dimension);
        }
    }

    rewind(input_file);//reset eof

    //reset element cursor
    element = 0;

    // Retrieves no_of_data
    while(!feof(input_file)) //while not at end of file
    {
        fscanf(input_file,"%d", &cursor); //gets integer value of step
        if(cursor != NULL)
        {
            element++; //increments element count
        }

        if(element == 2)
        {
            fscanf(input_file, "%d", &no_of_data);
        }
    }

    rewind(input_file);//reset eof

    int row = no_of_data; //arrays start from 0 so subtract from actual value
    int col = dimension;
    int data[row][col]; //create array to hold txt file info
    fscanf(input_file, "%*[^\n]\n"); //skips first line of file

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(!feof(input_file)) //if not at end of file
            {
                fscanf(input_file,"%d", &cursor); //gets integer value of step
                data[i][j] = cursor; //places i into step of 2d array
            }
        }
    }

    // Print out data
    /*
    printf("DATA VALUES\n");
    for (int i = 0; i < no_of_data; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    */

    rewind(input_file);//reset eof

    float centroids[no_of_clusters][dimension];
    int distance[no_of_clusters][no_of_data];
    int cluster[no_of_data];
    int prev_cluster[no_of_data];
    
    // Set random points for each centroid
    for (int i = 0; i < no_of_clusters; i++)
    {
        int random_num = rand() % (no_of_data);

        for (int j = 0; j < dimension; j++)
        {
            centroids[i][j] =  data[random_num][j];
        }
    }

    // Centroid values
    /*
    printf("CENTROID VALUES\n");
    for (int i = 0; i < no_of_clusters; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            printf("%.2f ", centroids[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    */

    int iteration = 0;
    float total_dist;
    bool clusters_equal = false;

    do {
        iteration++;

        // Skip the first interation
        if (iteration > 1) {
            for (int i = 0; i < no_of_data; i++)
            {
                prev_cluster[i] = cluster[i];
            }

            // Print contents of previous array
            /*
            printf("\nPREVIOUS CLUSTER ARRAY\n");
            for (int i = 0; i < no_of_data; i++)
            {
                printf("%d ", prev_cluster[i]);
            }
            */
        }

        // Calculate the distance of each data from each centroid
        //printf("\nDISTANCE VALUES\n");
        for (int i = 0; i < no_of_data; i++)
        {
            int min = INT_MAX;

            for (int j = 0; j < no_of_clusters; j++)
            {
                total_dist = 0;

                for (int k = 0; k < dimension; k++)
                {
                    total_dist = total_dist + abs(centroids[j][k] - data[i][k]);
                }

                if (total_dist < min)
                {
                    min = total_dist;
                    cluster[i] = j;
                }
                // printf("%.2f ", total_dist);
            }

            // printf("\n");
        }

        // Print cluster array
        /*
        printf("\nCLUSTER ARRAY\n");
        for (int i = 0; i < no_of_data; i++)
        {
            printf("%d ", cluster[i]);
        }

        printf("\n\n");
        */

        int length;

        // Calculate the new centroids
        //printf("CALCULATIONS\n");
        for (int k = 0; k < dimension; k++)
        {
            for (int i = 0; i < no_of_clusters; i++)
            {
                total_dist = 0;
                length = 0;
    
                for (int j = 0; j < no_of_data; j++)
                {
                    if (cluster[j] == i)
                    {
                        length++;

                        total_dist = total_dist + data[j][k];

                        //printf("%d ", data[j][k]);
                    }
                }
                //printf("= %.2f\n", total_dist);
                centroids[i][k] = total_dist / length;
            }
        }
        //printf("\n");

        // New centroid values
        /*
        printf("NEW CENTROID VALUES\n");
        for (int i = 0; i < no_of_clusters; i++)
        {
            for (int j = 0; j < dimension; j++)
            {
                printf("%.2f ", centroids[i][j]);
            }
            printf("\n");
        }
        */

        int count = 0;

        // Check if cluster is the same as previous interation
        for (int i = 0; i < no_of_data; i++)
        {
            if (prev_cluster[i] == cluster[i])
            {
                count++;
            }
        }

        // If cluster is the same as previous iteration then break out of the while loop
        if (count == no_of_data)
        {
            clusters_equal = true;
        }
        else
        {
            // Print out results
            printf("%d\n", iteration);
            for (int i = 0; i < no_of_clusters; i++)
            {
                for (int j = 0; j < no_of_data; j++)
                {
                    if (cluster[j] == i)
                    {
                        printf("%d ", j + 1);
                    }
                }
                printf("\n");
            }
        }
    } while(!clusters_equal);
}