#include <iostream>

using namespace std;
#define MAX 10000

int round(double a) {
    int I = int(a);
    double Q = a - I;
    int R = (Q >= 0.5) ? I + 1 : I;
    return R;
}


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
        return (t == -1);
    }
};


int main() {

    freopen("input.text", "r", stdin);
    //freopen("output.text", "w", stdout);
    int t;
    cin >> t;
    char *newline = new char[1];
    scanf("%c", newline);
    while (t--) {
        char **output = new char *[MAX];
        for (int i = 0; i < MAX; i++) {
            output[i] = new char[MAX];
        }
        int index = 0;
        int stringIndex = 0;
        while (true) {
            char *newChar = new char[1];
            scanf("%c", newChar);
            if (*newChar == '\n' || !*newChar) {
                break;
            } else if (*newChar == ' ') {
                index++;
                stringIndex = 0;
                continue;
            }
            output[index][stringIndex] = *newChar;
            stringIndex++;
        }

        // Input check
//        int p = 0;
//        while (output[p][0]) {
//            int m = 0;
//            while (output[p][m]) {
//                cout << output[p][m];
//                m++;
//            }
//            p++;
//        }cout<<endl<<output[8][1];
//        cout<< endl <<p;
        int p = 0;
        Stack st;
        while (output[p][0]) {
            switch (output[p][0]) {
                case '+': {
                    int a = st.pop();
                    int b = st.pop();
                    st.push(a + b);
                    break;
                }
                case '-': {
                    int a = st.pop();
                    int b = st.pop();
                    st.push(b - a);
                    break;
                }
                case '*': {
                    int a = st.pop();
                    int b = st.pop();
                    st.push(a * b);
                    break;
                }
                case '%': {
                    int a = st.pop();
                    int b = st.pop();
                    st.push(b % a);
                    break;
                }

                case '/': {
                    int a = st.pop();
                    int b = st.pop();
                    st.push(round((b + 0.0) / (a + 0.0)));
                    break;
                }

                case '^': {
                    int a = st.pop();
                    int b = st.pop();
                    int temp = b;
                    a-=1;
                    while (a--) b *= temp;
                    st.push(b);
                    break;
                }

                case '~': {
                    int a = st.pop();
                    st.push(a * (-1));
                    break;
                }
                default: {
                    int m = 0;
                    int next = 0;
                    while (output[p][m]) {
                        m++;
                    }
                    for (int i = m - 1; i >= 0; i--) {
                        int z = (i - m) * (-1) - 1;
                        int current = int(output[p][z]) - 48;
                        int temp = i;
                        while (temp--) {
                            current *= 10;
                        }
                        next += current;
                    }
                    st.push(next);
                }
            }
            p++;
        }
        cout << st.pop() << endl;
    }
    return 0;
}