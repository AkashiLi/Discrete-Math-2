#include <iostream>
using namespace std;
#include <limits>
#include <vector>
#include <stdio.h>
#include <string.h>
#define INF 2147483647

//Shortest Route Problem 
//1. Find the shortest path from first node to every other node
//2. Find the values of those paths, and save the largest.
//3. Repeat for each node, store each largest
//4. Print out the smallest of those. 

//Dijkstra’s
int main()
{
    int n;
    int m;
    cin >> n >> m;
    double graph[n][n];
    memset(graph, 0.0, sizeof(graph[0][0])*n*n); //Set everything to 0
    int x = 0, y = 0;
    for(int i = 0; i < m; ++i) //Make adjacency graph
    {
        cin >> x >> y;
        cin >> graph[x-1][y-1];
        graph[y-1][x-1] = graph[x-1][y-1];
    }
 
    int src = 0;
    int fin_min;
    double largest_paths[n]; //store all the largest shortest route paths
    while(src < n)
    {
        //Set all distance to INF and source to false
        int dist[n];
        
        for(int i = 0; i < n; ++i) dist[i] = INF;
        bool srcSet[n];
        memset(srcSet, false, sizeof(srcSet));
        
        dist[src] = 0;
        
        for(int i = 0; i < n - 1; ++i) //Go through all vertices
        {
            //pick minimum distance vertex from non processed vertex
            int min = INF;
            int min_index;
            for(int j = 0; j < n; ++j)
            {
                if(srcSet[j] == false && dist[j] <= min)
                {
                    min = dist[j], min_index = j;
                }
            }
            //set picked vertex as processed
            srcSet[min_index] = true;
            //Updated dist val of adjacent verties of picked vertex
            for(int j = 0; j < n; ++j)
            {
                //update dist[j] only if not in srcSet, there is an edge from min_index to j,
                // and if total weight path is smaller than the current value of  d[j]
                if(!srcSet[j] && graph[min_index][j] && dist[min_index] != INF && dist[min_index] + graph[min_index][j] < dist[j])
                {
                    dist[j] = dist[min_index] + graph[min_index][j];
                }
            }
        }        
        double max_of_spr = 0; //max of shortest route paths
        double max_of_spr2 = 0; //second max //use the average of the two to find the max

        for(int i = 0; i < n; i++)
        {
           // cout << dist[i] << "\n";
            if(dist[i] > max_of_spr)
            {
                max_of_spr = dist[i];
            }
        }
        for(int i = 0; i < n; ++i)
        {
            if(dist[i] == max_of_spr) 
            {
                dist[i] = 0;
                break;
            }
        }
        for(int i = 0; i < n; i++)
        {
            
            if((dist[i] > max_of_spr2) && (max_of_spr2 < max_of_spr))
            {   
                max_of_spr2 = dist[i];
            }
        }   
        largest_paths[src] = (.5)*(max_of_spr2 + max_of_spr);
        src++;
    }
    double min_of_max = INF; //find average shortest of the longest shortest paths
    for(int i = 0; i < n; ++i)
    {
        //cout << largest_paths[i] << endl;
        if(min_of_max > largest_paths[i])
        {
            min_of_max = largest_paths[i];
        }
    }
    cout << min_of_max;
}
