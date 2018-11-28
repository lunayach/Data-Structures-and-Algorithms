#include <iostream>

using namespace std;
#define MAX 1000005


// Using STL Stack
class Stack {
    int t;
public:
    int a[MAX];

    Stack() { t = -1; }

    bool push(int x) {
        if (t >= MAX) return false;
        else {
            t++;
            a[t] = x;
            return true;
        }
    }

    int pop() {
        if (t == -1) return -1;
        else {
            int value = a[t];
            t--;
            return value;
        }
    }

    int top() {
        if (t == -1) return -1;
        else {
            return a[t];
        }
    }

    bool empty() {
        return (t <= -1);
    }
};


int main() {

    freopen("input.text", "r", stdin);
//    freopen("output.text", "w", stdout);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int s[n];
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }
        // Storing the indexes
        int Min[n];
        Min[n - 1] = n - 1;

        // O(n)
        for (int i = n - 2; i >= 0; i--) {
            if (s[i] < s[Min[i + 1]]) {
                Min[i] = i;
            } else {
                Min[i] = Min[i + 1];
            }
        }

        // Min[i] : Minimum^index of array from 'i' to 'n-1'th index



        Stack t, u;


        int start = 0;
        while (start <= n - 1) {
            if (!t.empty() && t.top() <= s[Min[start]]) {
                u.push(t.top());
                t.pop();
            } else {
                if (s[Min[start]] == s[start]) {
                    u.push(s[start]);
                    start++;
                } else {
                    t.push(s[start]);
                    start++;
                }
            }
        }
        while (!t.empty()) {
            u.push(t.top());
            t.pop();
        }
        int result[n];
        for (int x = 0; x < n; x++) {
            result[n - x - 1] = u.top();
            u.pop();
        }
        for (int x = 0; x < n; x++) {
            cout << "v" << result[x];
        }
        cout << endl;
    }
    return 0;
}