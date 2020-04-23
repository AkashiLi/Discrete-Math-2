#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX_N 10
#define INF 2147483647
#define MIN(a, b) ((a) > (b) ? (b) : (a))

int gra[MAX_N][MAX_N];
int cun[MAX_N][MAX_N];
int counts[MAX_N];
int res = INF;
int N, M;
void solve(int id, int num)
{
    if(num>=res){
        return;
    }
    if(id>N){
        res=MIN(res,num);
        return;
    }
    for(int i=1;i<=num;i++)
    {
        int sz=counts[i];
        int jishu=0;
        for(int j=1;j<=sz;j++)
        {
            if(gra[id][cun[i][j]]==0)
            {
                jishu++;
            }
        }
        if(jishu==sz)
        {
            cun[i][++counts[i]]=id;
            solve(id+1,num);
            counts[i]--;
        }
    }
    cun[num+1][++counts[num+1]]=id;
    solve(id+1,num+1);
    --counts[num+1];
}

int main()
{
    cin >> N >> M;
    memset(gra,0,sizeof(gra));
    memset(counts,0,sizeof(counts));
     while(M--)
     {
        int a,b;
        cin >> a >> b;
        gra[a][b]= gra[b][a]= 1;
    }
     if (M == 0) //no edges = 1 color
    {
        printf("1\n");
        return 0;
    }
    else if (M == N * (N - 1) / 2) //complete graph = N clr
    {
        printf("%d\n", N);
        return 0;
    }
    else if (M + 1 == N * (N - 1) / 2) //complete graph - 1 = N - 1 clr
    {
        printf("%d\n", N - 1);
        return 0;
    }
    else if (N <= MAX_N)
    {
        solve(1,0);
    }
    cout << res;
    return 0;    
}
