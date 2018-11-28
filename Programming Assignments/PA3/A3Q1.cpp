#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class interval {
public:
    float low;
    float high;
};

class node {
public:
    node *parent = nullptr;
    node *left = nullptr;
    node *right = nullptr;
    float max;
    interval intv;
};

node *TRANSPLANT(node *u, node *v) {
    if (u->parent == nullptr) {
        if (v != nullptr) v->parent = nullptr;
        return v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) v->parent = u->parent;
    return v;
}

node *CreateNode(interval i) {
    node *newNode = new node[1];
    newNode->intv.low = i.low;
    newNode->intv.high = i.high;
    newNode->max = i.high;
    return newNode;
}

node *INSERT_L(node *root, interval i) {
    node *z = CreateNode(i);
    node *y = nullptr;
    node *x = root;
    while (x != nullptr) {
        y = x;
        x->max = max(x->max, i.high);
        if (z->intv.low < x->intv.low) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nullptr) root = z;
    else if (z->intv.low < y->intv.low) y->left = z;
    else y->right = z;
    if (y != nullptr)
        y->max = max(y->intv.high,
                     max((y->left ? y->left->max : -1 * 100000), (y->right ? y->right->max : -1 * 100000)));
    return root;
}

node *INSERT_H(node *root, interval i) {
    node *z = CreateNode(i);
    node *y = nullptr;
    node *x = root;
    while (x != nullptr) {
        y = x;
        if (z->intv.high < x->intv.high) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nullptr) root = z;
    else if (z->intv.high < y->intv.high) y->left = z;
    else y->right = z;
    return root;
}

node *MINIMUM_TREE(node *x) {
    while (x->left != nullptr)
        x = x->left;
    return x;
}

node *MAXIMUM_TREE(node *x) {
    while (x->right != nullptr)
        x = x->right;
    return x;
}


tuple<bool, interval> SUCCESSOR_L(node *root, interval intv) {
    while (root != nullptr) {
        if (root->intv.low == intv.low) break;
        else if (root->intv.low < intv.low) root = root->right;
        else root = root->left;
    }
    if (root == nullptr) {
        interval intrv;
        return make_tuple(false, intrv);
    } else {
        node *x = root;
        if (x->right != nullptr)
            return make_tuple(true, MINIMUM_TREE(x->right)->intv);
        node *y = x->parent;
        while (y != nullptr && x == y->right) {
            x = y;
            y = y->parent;
        }
        interval intrv;
        if (y != nullptr) return make_tuple(true, y->intv);
        else return make_tuple(false, intrv);
    }
}

tuple<bool, interval> SUCCESSOR_H(node *root, interval intv) {
    while (root != nullptr) {
        if (root->intv.high == intv.high) break;
        else if (intv.high > root->intv.high) root = root->right;
        else root = root->left;
    }
    if (root == nullptr) {
        interval intrv;
        return make_tuple(false, intrv);
    } else {
        node *x = root;

        if (x->right != nullptr)
            return make_tuple(true, MINIMUM_TREE(x->right)->intv);
        node *y = x->parent;
        while (y != nullptr && x == y->right) {
            x = y;
            y = y->parent;
        }
        interval intrv;
        if (y != nullptr) return make_tuple(true, y->intv);
        else return make_tuple(false, intrv);
    }
}


void TRAVERSAL_L(node *root) {
    if (root != nullptr) {
        TRAVERSAL_L(root->left);
        cout << root->intv.low << endl;
        TRAVERSAL_L(root->right);
    }
}

void TRAVERSAL_H(node *root) {
    if (root != nullptr) {
        TRAVERSAL_H(root->left);
        cout << root->intv.high << endl;
        TRAVERSAL_H(root->right);
    }
}


bool Overlap(interval intv1, interval intv2) {
    return intv1.low <= intv2.high && intv2.low <= intv1.high;
}

bool ExactOverlap(interval intv1, interval intv2) {
    return intv1.low == intv2.low && intv2.high == intv1.high;
}


node *FIND_DELETE_MATCH_L(node *root, interval intv) {
    node *x = root;
    while (x != nullptr && !ExactOverlap(intv, x->intv)) {
        if (intv.high > x->max) {
            x = nullptr;
            break;
        } else if (intv.low < x->intv.low) x = x->left;
        else if (intv.low > x->intv.low) x = x->right;
        else {
            x = nullptr;
            break;
        }
    }
    return x;

}

node *FIND_DELETE_MATCH_H(node *root, interval intv) {
    node *x = root;
    while (x != nullptr && !ExactOverlap(intv, x->intv)) {
        if (intv.high < x->intv.high) x = x->left;
        else if (intv.high > x->intv.high) x = x->right;
        else {
            x = nullptr;
            break;
        }
    }
    return x;
}

int OverlapSearch(node *root, interval intv) {
    node *x = root;
    while (x != nullptr && !(Overlap(intv, x->intv))) {
        if (x->left != nullptr && x->left->max >= intv.low) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    if (x != nullptr) return 1;
    else return 0;
}

node *DELETE(node *root, interval intv, string mode) {
    node *z = (mode == "low") ? FIND_DELETE_MATCH_L(root, intv) : FIND_DELETE_MATCH_H(root, intv);
    node *y = nullptr;
    node *t = nullptr;
    if (z == nullptr) {
        return root;
    }
    if (z->left == nullptr) {
        t = z->parent;
        node *newT = TRANSPLANT(z, z->right);
        delete z;
        if (t == nullptr) {
            return newT;
        }
    } else if (z->right == nullptr) {
        t = z->parent;
        node *newT = TRANSPLANT(z, z->left);
        delete z;
        if (t == nullptr) return newT;
    } else {
        y = MINIMUM_TREE(z->right);
        if (y->parent != z) {
            TRANSPLANT(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        TRANSPLANT(z, y);
        y->left = z->left;
        delete z;
        y->left->parent = y;
        y->max = max(y->intv.high,
                     max((y->left ? y->left->max : -100000), (y->right ? y->right->max : -100000)));
        if (y->right) {
            y->right->max = max(y->right->intv.high, max((y->right->left ? y->right->left->max : -100000),
                                                         (y->right->right ? y->right->right->max : -100000)));
        }
        t = y->parent;
        if (t == nullptr) return y;
    }
    while (t != nullptr) {
        t->max = max(t->intv.high, max((t->left ? t->left->max : -100000), (t->right ? t->right->max : -100000)));
        if (t->parent == nullptr) {
            return t;
        }
        t = t->parent;
    }
    return nullptr;
}

void extract(int begin, string exp, float(&params)[2]) {
    int i = begin;
    string temp;
    while (exp[i] != ' ') {
        temp = temp + exp[i];
        i++;
    }
    float a = stof(temp);
    int j = i + 1;
    temp = "";
    while (j < exp.length()) {
        temp += exp[j];
        j++;
    }
    float b = stof(temp);
    params[0] = a;
    params[1] = b;
}

int main() {
    freopen("input.text", "r", stdin);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        float params[2];
        string newline;
        getline(cin, newline);
        node *rootL = nullptr;
        node *rootH = nullptr;
        while (n--) {
            string exp;
            getline(cin, exp);
            if (exp[0] == '+') {
                extract(2, exp, params);
                interval intv;
                intv.low = params[0];
                intv.high = params[1];
                rootL = INSERT_L(rootL, intv);
                rootH = INSERT_H(rootH, intv);
            } else if (exp[0] == '-') {
                extract(2, exp, params);
                interval intv;
                intv.low = params[0];
                intv.high = params[1];
                rootL = DELETE(rootL, intv, "low");
                rootH = DELETE(rootH, intv, "high");
            } else if (exp == "max") {
                if (rootH == nullptr) cout << "INVALID" << endl;
                else {
                    node *o = MAXIMUM_TREE(rootH);
                    cout << "[" << o->intv.low << " " << o->intv.high << "]" << endl;
                }
            } else if (exp == "min") {
                if (rootL == nullptr) cout << "INVALID" << endl;
                else {
                    node *o = MINIMUM_TREE(rootL);
                    cout << "[" << o->intv.low << " " << o->intv.high << "]" << endl;
                }
            } else if (exp[0] == 'l') {
                extract(6, exp, params);
                interval intv;
                intv.low = params[0];
                intv.high = params[1];
                interval intvn;
                bool booln;
                tie(booln, intvn) = SUCCESSOR_L(rootL, intv);
                if (booln) cout << "[" << intvn.low << " " << intvn.high << "]" << endl;
                else cout << "INVALID" << endl;
            } else if (exp[0] == 'h') {
                extract(6, exp, params);
                interval intv;
                intv.low = params[0];
                intv.high = params[1];
                interval intvn;
                bool booln;
                tie(booln, intvn) = SUCCESSOR_H(rootH, intv);
                if (booln) cout << "[" << intvn.low << " " << intvn.high << "]" << endl;
                else cout << "INVALID" << endl;
            } else if (exp[0] == 'o') {
                extract(8, exp, params);
                interval intv;
                intv.low = params[0];
                intv.high = params[1];
                cout << OverlapSearch(rootL, intv) << endl;
            }
        }
        delete rootH;
        delete rootL;
    }
    return 0;
}