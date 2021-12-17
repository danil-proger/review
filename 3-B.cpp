#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Bitree {
private:
    vector<int> tree;
    static int f(int pos);
    static int g(int pos);

public:
    Bitree(const vector<int> &mas);
    int Getsum(int l, int r);
    void update(int pos, int value);
    int prefixSum(int pos);
};

int Bitree::f(int pos) {
    return pos & (pos + 1);
}

int Bitree::g(int pos) {
    return pos | (pos + 1);
}

Bitree::Bitree(const vector<int> &mas) {
    tree.resize(mas.size());
    for (int i = 0; i < mas.size(); ++i){
        for (int j = f(i); j < i + 1; ++j){
            tree[i] += mas[j];
        }
    }
}
int Bitree::Getsum(int l, int r) {
    if (l == 0) {
        return prefixSum(r);
    }
    if (l % 2 == 0) {
        return prefixSum(r) - prefixSum(l - 1);
    }
    return prefixSum(l - 1) - prefixSum(r);
}

void Bitree::update(int pos, int value) {
    for (int i = pos; i < tree.size(); i = g(i)) {
        tree[i] += value;
    }
}

int Bitree::prefixSum(int pos) {
    int sum = 0;
    for (int i = pos; i >= 0; i = f(i) - 1){
        sum += tree[i];
    }
    return sum;
}

int main(){
    int n, el;
    cin >> n;
    vector<int> mas(n);
    for (int i = 0; i < n; ++i){
        cin >> el;
        if (i % 2 == 0) mas[i] = el;
        else mas[i] = -el;
    }
    Bitree fen(mas);
    int m;
    cin >> m;
    int ind, l, r;
    for (int i = 0; i < m; ++i){
        cin >> ind >> l >> r;
        if (ind == 0) {
            if ((l - 1) % 2 == 1) r = -r;
            fen.update(l - 1, r - mas[l-1]);
            mas[l-1] = r;
        }
        else{
            cout << (int)fen.Getsum(l - 1, r - 1) << '\n';
        }
    }
}
