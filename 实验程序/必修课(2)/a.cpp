#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <set>

#define MAX_N 1010
#define INF 2147483647
#define MAX(a,b) (a) > (b) ? (a) : (b)
#define MIN(a,b) (a) > (b) ? (b) : (a)

std::vector<int> graph[MAX_N];
std::queue<int> q;

int in[MAX_N];
int ans[MAX_N];
int acc[MAX_N][MAX_N];
int MF[MAX_N][MAX_N];
int path[MAX_N];
int flow[MAX_N];
int n, startNode, endNode;


struct Course
{
    int c;
    int max = 0;
    std::vector<int> pre;
};

int findMax(int index, Course *courses)
{
    if (courses[index].c == 0)
    {
        courses[index].max = 1;
        return courses[index].max;
    }
    int max = 0;
    for (int i = 0; i < courses[index].c; i++) //loops all the prereqs
    {
        if (courses[index].max == 0)
            max = MAX(max, 1 + findMax(courses[index].pre[i], courses));
        else
            max = MAX(max, courses[index].max);
    }
    courses[index].max = max;
    return max;
}

void Cov(int i, int j)
{
    for(int k = 1; k <= n; k ++)
    {
        acc[j][k] = acc[i][k];
    }
}

void Union(int i, int j) 
{
    for(int k = 1; k <= n; k ++) 
    {
        acc[j][k] = acc[i][k] | acc[j][k];
    }
}

int findLongest() 
{
    std::queue<int> q;
    for(int i = 1; i <= n; i ++) {
        if(in[i] == 0) {
            q.push(i);
            ans[i] = 1;
            acc[i][i] = 1;
            MF[0][i] = 1;
        }
    }
    while(!q.empty()) {
        int work = q.front();
        q.pop();
        for(int i = 0; i < graph[work].size(); i ++) {
            int j = graph[work][i];
            in[j] --;
            if(ans[j] < ans[work] + 1) {
                ans[j] = ans[work] + 1;
                Cov(work, j);
            }
            else {
                Union(work, j);
            }
            if(in[j] == 0)
                q.push(j);
        }
    }
    
    int ret = -1;
    for(int i = 1; i <= n; i ++) 
    {
        ret = MAX(ret, ans[i]);
    }
    //cout << endl;
    return ret;
}

int BFSStep() {
    while(!q.empty())
        q.pop();
    memset(path, -1, sizeof(path));
    flow[startNode] = INF;
    q.push(startNode);
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        if(cur == endNode)
            break;
        for(int i = 1; i <= n + 1; i ++) {
            if(path[i] == -1 && MF[cur][i] == 1) {
                flow[i] = MIN(flow[cur], MF[cur][i]);
                path[i] = cur;
                q.push(i); 
            }
        }
    }
    if(path[endNode] == -1)
        return -1;
    return flow[n + 1];
}

int findNum(int longest) 
{
    for(int i = 1; i <= n; i ++) 
    {
        if(ans[i] == longest) 
        {
            MF[i][n + 1] = 1;
            for(int j = 1; j <= n; j ++) 
            {
                if(acc[i][j]) 
                {
                    MF[j][i] = 1;
                }
            }
        }
    }
   
    int maxFlow = 0;
    int pre;
    int now;
    int stepin;
    while((stepin = BFSStep()) != -1)
    {
        maxFlow += stepin;
        now = endNode;
        while(now != startNode) 
        {
            pre = path[now];
            MF[pre][now] -= stepin;
            MF[now][pre] += stepin;
            now = pre;
        }
    }
    return maxFlow;
}

int main() 
{
    std::cin >> n;
    Course courses[n];
    for(int i = 1; i <= n; i++) 
    {
        int num;
        std::cin >> num;
        courses[i-1].c = num;
        in[i] = num;
        for(int j = 1; j <= num; j ++) 
        {
            int pre;
            std::cin >> pre;
            courses[i-1].pre.push_back(pre - 1);
            graph[pre].push_back(i);
        }
    }
    startNode = 0, endNode = n + 1;
    int index = 0;
    findMax(0, courses);
    for (int i = 1; i < n; i++)
    {
        findMax(i, courses);
        if (courses[i].max > courses[index].max)
        {
            index = i;
        }
    }
    int longest = findLongest();
    courses[index].max = longest;
    std::cout << longest  << " " << findNum(longest) << '\n';
    return 0;
}
