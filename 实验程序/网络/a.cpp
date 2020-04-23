#include <iostream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <cstring>
#define INT_MAX 2147483647
#define MAX(a, b) ((a) > (b) ? (a) : (b))
using namespace std;
int N;
vector<int> answer;


int traverse(int s, int t, int **mst, bool *visited)
{
    int band = -1; //-1 if nowhere to go
    for (int i = 0; i < N; i++)
    {
        if (mst[s][i] != 0 && !visited[i])
        {
            if (i == t)
                return mst[s][t];
            visited[i] = true;
            int temp = traverse(i, t, mst, visited);
            if (temp != -1)
                band = MAX(mst[s][i], temp);
        }
    }
    return band;
}

int minKey(int *key, bool *mstSet)
{
    int min = INT_MAX;
    int min_index;
    for (int v = 0; v < N; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

int main()
{
    cin >> N;
    int x[N], y[N];
    int **dist = new int *[N];
    for (int i = 0; i < N; i++)
        dist[i] = new int[N];
    for (int i = 0; i < N; i++)
         cin >> x[i] >> y[i];
    for (int i = 0; i < N - 1; i++)
    {
        dist[i][i] = 0;
        for (int j = i; j < N; j++)
        {
            dist[i][j] = ((x[i] - x[j]) * (x[i] - x[j])) + ((y[i] - y[j]) * (y[i] - y[j]));
            dist[j][i] = dist[i][j];
        }
    }
#pragma region prim
    int parent[N];
    int key[N];
    bool mstSet[N];
    for (int i = 0; i < N; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < N - 1; count++)
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < N; v++)
            if (dist[u][v] && mstSet[v] == false && dist[u][v] < key[v])
                parent[v] = u, key[v] = dist[u][v];
    }
#pragma endregion
    int **mst;
    mst = new int *[N];
    for (int j = 0; j < N; j++)
        mst[j] = new int[N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mst[i][j] = 0;
    for (int i = 1; i < N; i++)
    {
        mst[parent[i]][i] = dist[i][parent[i]];
        mst[i][parent[i]] = mst[parent[i]][i];
    }
    int q;
    cin >> q;
    bool visited[N];
    for (int i = 0; i < q; i++)
    {
        int s, t;
        cin >> s >> t;
        memset(visited, 0, sizeof(visited));
        visited[--s] = true;
        int temp = traverse(s, --t, mst, visited);
        //cout << temp << "\n";
        answer.push_back(temp);
    }

    for(int i = 0; i < answer.size(); i++)
    {
        cout << answer[i] << endl;
    }
