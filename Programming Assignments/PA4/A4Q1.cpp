#include <iostream>
#include <bits/stdc++.h>

#define limits 100
using namespace std;


class triple {
public:
    int a;
    int b;
    int c;

    triple(int a, int b, int c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

class node {
public:
    triple data = triple(0, 0, 0);
    node *next = nullptr;
};

class List {
private:
    node *head, *tail;
public:
    List() {
        head = nullptr;
    }

    void push_back(triple data) {
        node *new_node = new node;
        new_node->data = data;
        if (!head) {
            head = new_node;
        }
        else {
            node* t = head;
            while(t->next != nullptr) t = t->next;
            t->next = new_node;
        }

    }

    bool empty() {
        return !head;
    }

    triple front() {
        return head->data;
    }

    void pop_front() {
        node *t;
        t = head;
        head = head->next;
        delete t;
    }

};


triple generateEdges(int i, int j, triple u, triple li) {
    triple t = u;
    if (i == 1 && j == 2) { //a to b
        if (u.a < li.b - u.b) {
            t.a = 0;
            t.b = u.a + u.b;
            t.c = u.c;
        } else {
            t.a = u.a + u.b - li.b;
            t.b = li.b;
            t.c = u.c;
        }
    } else if (i == 1 && j == 3) { //a to c
        if (u.a < li.c - u.c) {
            t.a = 0;
            t.b = u.b;
            t.c = u.a + u.c;
        } else {
            t.a = u.a + u.c - li.c;
            t.b = u.b;
            t.c = li.c;
        }
    } else if (i == 2 && j == 3) {//b to c
        if (u.b < li.c - u.c) {
            t.a = u.a;
            t.b = 0;
            t.c = u.b + u.c;
        } else {
            t.a = u.a;
            t.b = u.b + u.c - li.c;
            t.c = li.c;
        }
    } else if (i == 2 && j == 1) { //b to a
        if (u.b < li.a - u.a) {
            t.b = 0;
            t.a = u.a + u.b;
            t.c = u.c;
        } else {
            t.b = u.a + u.b - li.a;
            t.a = li.a;
            t.c = u.c;
        }
    } else if (i == 3 && j == 1) { //c to a
        if (u.c < li.a - u.a) {
            t.c = 0;
            t.b = u.b;
            t.a = u.a + u.c;
        } else {
            t.c = u.a + u.c - li.a;
            t.b = u.b;
            t.a = li.a;
        }
    } else if (i == 3 && j == 2) { //c to b
        if (u.c < li.b - u.b) {
            t.a = u.a;
            t.c = 0;
            t.b = u.b + u.c;
        } else {
            t.a = u.a;
            t.c = u.b + u.c - li.b;
            t.b = li.b;
        }
    }
    return t;
}

int DieHardBFS(int(*a)[limits][limits], triple l, triple s, triple d) {
    List q;
    q.push_back(s);
    while (!q.empty()) {
        triple u = q.front();
        if (u.a == d.a && u.b == d.b && u.c == d.c) return a[u.a][u.b][u.c];
        q.pop_front();
        // Generation of new edges
        for (int i = 1; i <= 3; i++) {
            for (int j = 1; j <= 3; j++) {
                if (i == j) continue;
                triple t = generateEdges(i, j, u, l);
                if (a[t.a][t.b][t.c] == 0 && !(t.a == s.a && t.b == s.b && t.c == s.c)) {
                    a[t.a][t.b][t.c] = a[u.a][u.b][u.c] + 1;
                    q.push_back(t);
                }
            }
        }
        //considering case of dropping to ground
        //drop a/b/c
        if (a[0][u.b][u.c] == 0 && !(s.a == 0 && u.b == s.b && u.c == s.c)) {
            a[0][u.b][u.c] = a[u.a][u.b][u.c] + 1;
            q.push_back(triple(0, u.b, u.c));
        }
        if (a[u.a][0][u.c] == 0 && !(u.a == s.a && s.b == 0 && u.c == s.c)) {
            a[u.a][0][u.c] = a[u.a][u.b][u.c] + 1;
            q.push_back(triple(u.a, 0, u.c));
        }
        if (a[u.a][u.b][0] == 0 && !(u.a == s.a && u.b == s.b && s.c == 0)) {
            a[u.a][u.b][0] = a[u.a][u.b][u.c] + 1;
            q.push_back(triple(u.a, u.b, 0));
        }
    }
    return -1;
}


int main() {
    freopen("input.text", "r", stdin);
    int t;
    cin >> t;
    while (t--) {
        int l1, l2, l3, s1, s2, s3, n;
        cin >> l1 >> l2 >> l3 >> s1 >> s2 >> s3 >> n;
        triple l = triple(l1, l2, l3);
        triple s = triple(s1, s2, s3);


        while (n--) {
            auto a = new int[limits][limits][limits];
            int d1, d2, d3;
            cin >> d1 >> d2 >> d3;
            triple d = triple(d1, d2, d3);
            int out = DieHardBFS(a, l, s, d);
            if (out != -1) cout << out + 1 << endl;
            else {
                cout << "IMPOSSIBLE" << endl;
            }
        }

    }
    return 0;
}