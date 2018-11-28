#include <iostream>
#include <bits/stdc++.h>


using namespace std;

class edge {
public:
    int a;
    int b;
public:
    edge(int a, int b) {
        this->a = a;
        this->b = b;
    }
};

// Initialise global variables => Important to pass last 5 cases!
int times = 0;
unsigned int nv;
vector<int> disc, Min, parent;
vector<bool> Visited;
vector<vector<int>> adj;
vector<edge> Edges;
vector<int> APoints;

void
DFS_Bridge_Edges_Articulate_Points(int vertex) {
    Visited[vertex] = true;
    disc[vertex] = Min[vertex] = times++;
    int c = 0;
    for (int i : adj[vertex]) {
        if (!Visited[i]) {
            c++;
            parent[i] = vertex;
            DFS_Bridge_Edges_Articulate_Points(i);
            Min[vertex] = min(Min[vertex], Min[i]);
            if (parent[vertex] == -1 && c > 1) APoints.push_back(vertex);
            if (parent[vertex] != -1 && Min[i] >= disc[vertex]) APoints.push_back(vertex);
            if (Min[i] > disc[vertex]) {
                if (vertex < i) Edges.emplace_back(vertex, i);
                else Edges.emplace_back(i, vertex);
            }
        } else if (parent[vertex] != i) Min[vertex] = min(Min[vertex], disc[i]);
    }
}
// order edges in ascending order such that e = (u, v) ordered wrt to u first and then v
bool compare(edge u, edge v) {
    if (u.a < v.a) return true;
    else if (u.a > v.a) return false;
    else {
        return u.b < v.b;
    }
}

int main() {
    freopen("input.text", "r", stdin);
    cin >> nv;
    int e;
    cin >> e;

    adj = vector<vector<int>>(nv);
    while (e--) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    disc = vector<int>(nv, 0);
    Min = vector<int>(nv, 0);
    Visited = vector<bool>(nv, false);
    parent = vector<int>(nv, -1);

    //Graph is connected, one call shall suffice
    DFS_Bridge_Edges_Articulate_Points(0);


    sort(APoints.begin(), APoints.end());
    for (int i : APoints) cout << i << " ";
    if (APoints.empty()) cout << "EMPTY";

    cout << endl;

    sort(Edges.begin(), Edges.end(), compare);

    auto item = Edges.begin();
    while (item != Edges.end()) {
        cout << (*item).a << " " << (*item).b << endl;
        item++;
    }
    return 0;
}