#include <iostream>

using namespace std;
#define MAX 10000

// Opcodes
/*
 * + : 0
 * - : 1
 * * : 2
 * % : 3
 * / : 4
 * ^ : 5
 * ~ : 6
*/

// Parenthesis
/*
 * (: 7
 * ) : 8
*/

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

    bool pop() {
        if (t == -1) return false;
        else {
            t--;
            return true;
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


void handleToken(Stack &st, int token, char const Operators[], char const Associativity[], int const Precedence[]) {
    if (st.empty() || token == 7) {
        st.push(token);
        return;
    } else if (token == 8) {
        while (st.top() != 7) {

            cout << Operators[st.top()] << ' ';
            st.pop();
        }
        st.pop();
        return;
    } else {
        int top = st.top();
        while (Precedence[top] > Precedence[token]) {
            cout << Operators[top] << ' ';
            st.pop();
            if (st.empty()) break;
            top = st.top();
        }
        if (st.empty()) st.push(token);
        else {
            if (Precedence[top] == Precedence[token]) {
                if (Associativity[top] == 'l') {
                    cout << Operators[top] << ' ';
                    st.pop();
                    st.push(token);
                } else {
                    st.push(token);
                }
            } else {
                st.push(token);
            }
        }
    }
}


int main() {
    // Precedence Array
    int Precedence[] = {1, 1, 2, 3, 3, 4, 5};
    // Associativity Array
    char Associativity[] = {'l', 'l', 'l', 'l', 'l', 'r', 'r'};
    // Operators Array
    char Operators[] = {'+', '-', '*', '%', '/', '^', '~'};

    int t;
    cin >> t;
    char *newline = new char[1];
    scanf("%c", newline);
    while (t--) {
        Stack bracketFlag;
        /*For '(' : -1 and ')' : 1*/
        char **output = new char *[MAX];
        for (int i = 0; i < MAX; i++) {
            output[i] = new char[MAX];
        }
        int index = 0;
        int stringIndex = 0;
        bool operatorFlag = false;
        bool valid = true;
        bool unary;
        while (true) {
            unary = false;
            char *newChar = new char[1];
            scanf("%c", newChar);
            if (*newChar == '\n' || !*newChar) {
                if (output[index][0] == ')') {
                    operatorFlag = false;
                }
                break;
            } else if (*newChar == ' ') {
                index++;
                stringIndex = 0;
                continue;
            } else if ((*newChar == '+' || *newChar == '-' || *newChar == '*' || *newChar == '%' || *newChar == '/' ||
                        *newChar == '^' ||
                        *newChar == '%' || *newChar == '(' || *newChar == ')') && valid) {
                if (operatorFlag || !index) {
                    valid = false;
                    if (!(index - 1 >= 0 && output[index - 1][0] == ')') && *newChar == '(') {
                        valid = true;
                    }
                    if (index - 1 >= 0 && output[index - 1][0] == ')') {
                        if (*newChar != '(') valid = true;
                    }
                    if ((index - 1 >= 0 && output[index - 1][0] != ')') || index == 0) {
                        if (*newChar == '-') {
                            valid = true;
                            unary = true;
                            if ((index - 1 >= 0) && (output[index - 1][0] == '~') && (index - 2 >= 0) &&
                                (output[index - 2][0] == '-')) {
                                valid = false;
                            }
                        }
                    }
                }
                if (*newChar == '(') {
                    bracketFlag.push(-1);
                    if ((index - 1 >= 0 && output[index - 1][0] >= 48 && output[index - 1][0] <= 57)) {
                        valid = false;
                    }
                }
                if (*newChar == ')') {
                    if (!bracketFlag.empty() && bracketFlag.top() == -1) {
                        bracketFlag.pop();
                    } else {
                        valid = false;
                    }
                }
                operatorFlag = true;
            } else {
                if (valid) {
                    operatorFlag = false;
                    if (index - 1 >= 0 && output[index - 1][0] >= 48 && output[index - 1][0] <= 57) {
                        valid = false;
                    }
                    if (index - 1 >= 0 && output[index - 1][0] == ')') {
                        valid = false;
                    }
                }
            }
            output[index][stringIndex] = (unary) ? '~' : *newChar;
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
//        }
//        cout<< endl <<p;
        int p = 0;
        Stack st;
        if (!operatorFlag && valid && bracketFlag.empty()) {
            while (output[p][0]) {
                switch (output[p][0]) {
                    case '+':
                        handleToken(st, 0, Operators, Associativity, Precedence);
                        break;
                    case '-':
                        handleToken(st, 1, Operators, Associativity, Precedence);
                        break;
                    case '*':
                        handleToken(st, 2, Operators, Associativity, Precedence);

                        break;
                    case '%':
                        handleToken(st, 3, Operators, Associativity, Precedence);

                        break;
                    case '/':
                        handleToken(st, 4, Operators, Associativity, Precedence);

                        break;
                    case '^':
                        handleToken(st, 5, Operators, Associativity, Precedence);

                        break;
                    case '~':
                        handleToken(st, 6, Operators, Associativity, Precedence);

                        break;
                    case '(':
                        handleToken(st, 7, Operators, Associativity, Precedence);

                        break;
                    case ')':
                        handleToken(st, 8, Operators, Associativity, Precedence);

                        break;


                    default: {
                        int m = 0;
                        while (output[p][m]) {
                            cout << output[p][m];
                            m++;
                        }
                        cout << " ";
                    }
                }
                p++;
            }
            while (!st.empty()) {
                cout << Operators[st.top()] << ' ';
                st.pop();
            }
        } else {
            cout << "INVALID";
        }
        cout << endl;
    }
    return 0;
}