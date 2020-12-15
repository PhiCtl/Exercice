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

typedef pair<int, int> Edge;
typedef vector<vector<Edge>> Adjacency_list;
typedef vector<int> Path;


int Dijkstra_modified(Adjacency_list& E, int s, int t)
{
    Path dist(E.size(), MAX);
    //push in
    priority_queue<Edge> Q;
    dist[s] = 0;
    Q.emplace(dist[s], s);

    while(!Q.empty())
    {
        //extract min element from priority queue
        auto [d, u] = Q.top();
        Q.pop();

        //if the current distance of u
        // is less than the min, skip the code below
        if( dist[u] < -d )
            continue;

        //if min element is the destination then we can return
        //its distance
        if (t == u)
            return dist[t];
        for(auto& [w, v]: E[u])
        {
            if(dist[v] > max(dist[u], w))
            {
                dist[v] = max(dist[u],w);
                Q.emplace(-dist[v], v);
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


