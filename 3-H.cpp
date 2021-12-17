#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SparseTable {
private:
    vector<int> mas;
public:
    vector<int> deg;
    vector<vector<pair<int, int>> >sparse;
    pair<int, int> GetMin(const pair<int, int> &fir, const pair<int , int> &sec, const vector<int> &mas, int k);

    SparseTable(const vector<int> &mas);

    int answer(int x, int y, const vector<int> &mas);
};

SparseTable::SparseTable(const vector<int> &mas) {
    int n = mas.size();
    int step = 2;
    deg.resize(n + 1);
    for (int i = 2; i < mas.size() + 1; ++i) {
        if (i == step) {
            deg[i] = deg[i - 1] + 1;
            step *= 2;
        } else deg[i] = deg[i - 1];
    }
    sparse.resize(deg[n] + 1, vector < pair < int, int>>(n, { 0, 0 }));
    for (int i = 0; i < n; ++i){
        sparse[0][i] = {i, mas[i]};
    }
    for (int k = 0; k < deg[n]; ++k){
        int st = 1 << k;
        for (int i = 0; i + st < n; ++i){
            int j = i + st;
            sparse[k + 1][i] = GetMin(sparse[k][i], sparse[k][j], mas, k);
        }
    }
}

pair<int, int> SparseTable::GetMin(const pair<int, int> &fir, const pair<int, int> &sec, const vector<int> &mas, int k)  {
    if (k == 0) {
        return {fir.first, sec.first};
    }
    std::vector<pair<int, int>> sorted(4);
    sorted[0] = {mas[fir.first], fir.first};
    sorted[1] = {mas[fir.second], fir.second};
    sorted[2] = {mas[sec.first], sec.first};
    sorted[3] = {mas[sec.second], sec.second};
    sort(sorted.begin(), sorted.end());
    if (sorted[0].second == sorted[1].second) return {sorted[0].second, sorted[2].second};
    else return {sorted[0].second, sorted[1].second};

}

int SparseTable::answer(int x, int y, const vector<int> &mas) {
    int st = deg[y - x + 1];
    int step = 1 << st;
    pair res = GetMin(sparse[st][x - 1], sparse[st][y - step], mas, deg[y - x + 1]);
    return res.second;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> mas(n);
    for (int i = 0; i < n; ++i){
        cin >> mas[i];
    }
    SparseTable sparse1(mas);
    int x, y;
    for (int i = 0; i < m; ++i){
        cin >> x >> y;
        cout << mas[sparse1.answer(x, y, mas)] << '\n';
    }
}

