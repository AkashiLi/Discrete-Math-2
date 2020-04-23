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

int main() {
    int n;
    int m;
    cin >> n >> m;
    double graph[n][n];
    memset(graph, 0.0, sizeof(graph[0][0])*n*n);
    int x = 0, y = 0;
    for(int i = 0; i < m; ++i) {
        cin >> x >> y;
        cin >> graph[x-1][y-1];
        graph[y-1][x-1] = graph[x-1][y-1];
    }
  
    int src = 0;
    int fin_min;
    int largest_paths[n]; //store all the largest shortest route paths
    while(src < n) {
        //Set all distance to INF and source to false
        int dist[n];
        for(int i = 0; i < n; ++i) dist[i] = INF;
        bool srcSet[n];
        memset(srcSet, false, sizeof(srcSet));
        
        dist[src] = 0;
        
        for(int i = 0; i < n - 1; ++i) //Go through all vertices {
            //pick minimum distance vertex from non processed 
            int min = INF;
            int min_index;
            for(int j = 0; j < n; ++j) {
                if(srcSet[j] == false && dist[j] <= min) {
                    min = dist[j], min_index = j;
                }
            }
            //set picked vertex as processed
            srcSet[min_index] = true;
            //Updated dist val of adjacent verties of picked vertex
            for(int j = 0; j < n; ++j) {
                //update dist[j] only if not in srcSet, there is an edge from min_index to j,
                // and if total weight path is smaller than the current value of  d[j]
                if(!srcSet[j] && graph[min_index][j] && dist[min_index] != INF && dist[min_index] + graph[min_index][j] < dist[j]) {
                    dist[j] = dist[min_index] + graph[min_index][j];
                }
            }
        }
        int max_of_spr = 0; //max of shortest route paths
        for(int i = 0; i < n; i++) {
            if(dist[i] > max_of_spr) {
                max_of_spr = dist[i];
            }
        }
    
        largest_paths[src] = max_of_spr;
        src++;
    }

    int min_of_max = INF; //find shortest of the longest shortest path
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

