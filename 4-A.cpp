#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>

using namespace std;

class AVL {
private:
    struct node {
        int key;
        int height;
        node* left;
        node* right;
        node(int k) {
            key = k;
            left = right = nullptr;
            height = 1;
        }
        ~node();
    };

    node* first = nullptr;

    node* ins(node* tree, int k);

    node* removemin(node * p);

    int pred(node * first, int x, int& max);

    int Next(node* first, int x, int &min);

    bool find(node* first, int x);

    node* remove(node*p, int k);

public:
    AVL();

    ~AVL();

    long long h(node* tree);

    int balancef(node* tree);

    void fix(node* tree);

    node* rotright(node* tree);

    node* rotleft(node* tree);

    node* balance(node* tree);

    void insert(int x);

    node* findmin(node* p);

    void removeminimum();

    void del(int k);

    bool exist(int x);

    int prev(int x, int& ans);

    int next(int x, int &ans);
};

AVL::node::~node() {
    delete left;
    delete right;

}

int AVL::balancef(AVL::node *tree) {
    return h(tree->right) - h(tree->left);
}

long long AVL::h(AVL::node *tree) {
    if (tree == nullptr) return 0;
    return tree->height;
}

void AVL::fix(AVL::node *tree) {
    int hl = h(tree->left);
    int hr = h(tree->right);
    if (hl > hr) tree->height = hl + 1;
    else tree->height = hr + 1;
}

AVL::node *AVL::rotright(AVL::node *tree) {
    node* copy = tree->left;
    tree->left = copy->right;
    copy->right = tree;
    fix(tree);
    fix(copy);
    return copy;
}

AVL::node *AVL::rotleft(AVL::node *tree) {
    node* copy = tree->right;
    tree->right = copy->left;
    copy->left = tree;
    fix(tree);
    fix(copy);
    return copy;
}

AVL::node *AVL::balance(AVL::node *tree) {
    fix(tree);
    if (balancef(tree) == 2) {
        if (balancef(tree->right) < 0) {
            tree->right = rotright(tree->right);
        }
        return rotleft(tree);
    }
    if (balancef(tree) == -2) {
        if (balancef(tree->left) > 0) {
            tree->left = rotleft(tree->left);
        }
        return rotright(tree);
    }
    return tree;
}

AVL::node *AVL::ins(AVL::node *tree, int k) {
    if (!tree) return new node(k);
    if (k < tree->key) {
        tree->left = ins(tree->left, k);
    }
    else tree->right = ins(tree->right, k);
    return balance(tree);
}

AVL::node *AVL::findmin(AVL::node *p) {
    if (p->left) return findmin(p->left);
    return p;
}

AVL::node *AVL::removemin(AVL::node *p) {
    if (p->left == nullptr) return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

AVL::node *AVL::remove(AVL::node *p, int k) {
    if (!p) return nullptr;
    if (k < p->key) p->left  = remove(p->left, k);
    else if (k > p->key) p->right = remove(p->right, k);
    else {
        node* q = p->left;
        node* r = p->right;
        p->left = nullptr;
        p->right = nullptr;
        delete p;
        if (!r) return q;
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void AVL::insert(int x) {
    if (find(first , x))  return;
    first = ins(first, x);
}

void AVL::removeminimum() {
    first = removemin(first);
}

int AVL::pred(AVL::node *tree, int x, int& ans) {
    if (!tree) return false;
    if (tree->key >= x) {
        return pred(tree->left, x, ans);
    }
    else {
        if (!pred(tree->right, x, ans))
            ans = tree->key;
        return true;
    }
}

bool AVL::exist(int x) {
    return find(first, x);
}

bool AVL::find(AVL::node *tree, int x) {
    if (tree == nullptr) return false;
    if (x == tree->key) return true;
    if (x > tree->key) {
        if (tree->right) return find(tree->right, x);
        else return false;
    }
    if (tree->left) return find(tree->left, x);
    return false;
}

int AVL::prev(int x, int& ans) {
    return pred(first, x, ans);
}

void AVL::del(int k) {
    first = remove(first, k);
}

int AVL::next(int x, int &ans) {
    return Next(first, x , ans);
}

int AVL::Next(AVL::node *tree, int x, int &ans) {
    if (!tree) return false;
    if (tree->key <= x) return Next(tree->right, x, ans);
    if (!Next(tree->left, x, ans)) ans = tree->key;
    return true;
}

AVL::AVL() {
    first = nullptr;
}

AVL::~AVL() {
    delete first;
}


int main() {
    AVL tree;
    string s;
    int k;
    while (cin >> s) {
        cin >> k;
        if (s == "insert") tree.insert(k);
        else if (s == "delete") tree.del(k);
        else if (s == "exists") {
            if (tree.exist(k)) cout << "true" << '\n';
            else cout << "false" << '\n';
        }
        else if (s == "prev") {
            int ans;
            if (!tree.prev(k, ans)) cout << "none" << '\n';
            else cout << ans << '\n';
        }
        else if (s == "next") {
            int ans;
            if (!tree.next(k, ans)) cout << "none" << '\n';
            else cout << ans << '\n';
        }

    }
}
