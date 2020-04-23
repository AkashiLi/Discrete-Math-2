#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N; 
struct Course
{
   
    int time; //time for class
    int pre_count; //number of prerequisits
    int max = 0; 
    vector<int>pre;
};


int min_(int a, int b)
{
    if (a > b) return b;
    return a;
}
int max_(int a, int b)
{
    if (a > b) return a;
    return b;
}

void store_classes(Course* course)
{
    int i = 0;
    while(i < N)
    {
        cin >> course[i].time >> course[i].pre_count;
        int j = 0;
        while(j < course[i].pre_count)
        {
            int p;
            cin >> p;
            course[i].pre.push_back(p-1);
            ++j;
        }
        ++i;
    }
}





int findMax(int index, Course *courses)
{
    if(courses[index].pre_count == 0)
    {
        courses[index].max = courses[index].time;
        return courses[index].max;
    }
    int max = 0;
    for(int i = 0; i < courses[index].pre_count; ++i)
    {
        if(courses[index].max == 0)
        {
            max = max_(max, courses[index].time + findMax(courses[index].pre[i], courses));
        }
        else
        {
            max = max_(max, courses[index].max);
        }
    }
    courses[index].max = max;
    return max;
}

int main()
{
    cin >> N;
    Course courses[N];
    store_classes(courses);
    
    int index = 0;
    findMax(0, courses);
    for(int i = 1; i < N; ++i)
    {
        findMax(i, courses);
        if(courses[i].max > courses[index].max)
        {
            index = i;
        }
    }


    int next = index;
    vector<int> taken;
    taken.push_back(next);

    while(courses[next].pre_count != 0)
    {
        int maxIndex = courses[next].pre[0];
        int max = courses[courses[next].pre[0]].max;
        for(int i = 1; i < courses[next].pre_count; ++i)
        {
            if(max < courses[courses[next].pre[i]].max)
            {
                max = courses[courses[next].pre[i]].max;
                maxIndex = courses[next].pre[i];
            }

        }
        taken.push_back(maxIndex);
        next = maxIndex;
    }
    sort(taken.begin(), taken.end());
    index = 0;
    for(int i = 0; i < N; i++)
    {
        cout << courses[i].max << " ";
        if(index < taken.size() && i == taken[index])
        {
            index++;
            cout << 1;
        }
        else 
            cout << 0;
        cout << "\n";
    }   
}

