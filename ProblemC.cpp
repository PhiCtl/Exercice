//
// Created by descourt@INTRANET.EPFL.CH on 15.12.20.
//

#include <iostream>
#include <vector>
#include<limits>
#include <queue>
#include<utility>

using namespace std;
const int MAX = numeric_limits<int>::max();

typedef pair<int, int> Edge; //weight, node
typedef vector<vector<Edge>> Adjacency_list;
typedef vector<int> Path;


int Dijkstra_modified(Adjacency_list& E, int s, int t)
{
    //bottleneck values along paths
    Path dist(E.size(), MAX);
    //push in
    priority_queue<Edge> Q;
    //dist defined as bottleneck edge value on the path from s
    dist[s] = 0;
    Q.emplace(dist[s], s);

    while(!Q.empty())
    {
        //extract min element from priority queue
        pair<int,int> p = Q.top(); //dist, node u
        Q.pop();

        //if the current distance of u
        // is less than the min, skip the code below
        if( dist[p.second] < -p.first)
            continue;


        for(pair<int,int>& q: E[p.second]) //for all adjacent nodes q.second to u
        {
            //find path of min bottleneck between s and current node q.second
            if(dist[q.second] > max(dist[p.second], q.first))
            {
                //current value is max of predecessor value and current edge value
                dist[q.second] = max(dist[p.second],q.first);
                Q.emplace(-dist[q.second], q.second);
            }
        }

    }
    return dist[t];
}

Adjacency_list Reader()
{
    //get size of graph
    int m(0);
    int n(0);
    int count(0);
    cin >> n >> m;
    //initialize nodes
    int x(0);
    int y(0);
    int w(0);

    //initialize adjacency list
    Adjacency_list E(n);
    for(count; count < m; ++ count)
    {
        cin >> x >> y >> w;
        E[x-1].push_back(make_pair(w,y-1));
        E[y-1].push_back(make_pair(w,x-1));

    }

    return E;
}
int main()
{
    Adjacency_list E(Reader());
    int n = E.size();
    int max = Dijkstra_modified(E,0,n-1);
    cout << max;
    return 0;
}


