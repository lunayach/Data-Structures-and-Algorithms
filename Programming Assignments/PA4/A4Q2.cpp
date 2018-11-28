#include <iostream>
#include <bits/stdc++.h>

using namespace std;


/*Visited. 0 => white 1 => grey 2 => black*/
class vertex {
public:
    int label;
public:
    explicit vertex(int label) {
        this->label = label;
    }
};

void DFS_Visit(list<vertex> *g, int length, int start, int *status) {
    auto begin = g[start].begin();
    status[(*begin).label] = 1;
    for (auto i = begin; i != g[start].end(); i++) {
        if (status[(*i).label] == 0) DFS_Visit(g, length, (*i).label, status);
    }
    status[(*begin).label] = 2;
}


string Check_Bridge(list<vertex> *g, int n, int a, int b, int *status) {

    auto i = g[a].begin();
    while ((*i).label != b) i++;

    g[a].erase(i);

    auto j = g[b].begin();
    while ((*j).label != a) j++;

    g[b].erase(j);


    DFS_Visit(g, n, a, status);
    if (status[b] == 0) return "Bridge";
    else return "Not Bridge";
}

int main() {
    freopen("input.text", "r", stdin);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        list<vertex> g[n + 1];
        int status[n + 1];
        for (int i = 1; i <= n; i++) status[i] = 0;
        int e;
        cin >> e;
        for (int i = 1; i <= n; i++) {
            vertex v = vertex(i);
            g[i].push_back(v);
        }
        while (e--) {
            int a, b;
            cin >> a >> b;
            vertex vb = vertex(b);
            vertex va = vertex(a);
            g[a].push_back(vb);
            g[b].push_back(va);
        }
        int a, b;
        cin >> a >> b;
        cout << Check_Bridge(g, n, a, b, status) << endl;
    }
    return 0;
}