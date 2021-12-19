#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int Partition(vector<int> &A, int l, int r) {
    int value = A[(l + r) / 2];
    swap(A[(l + r) / 2], A[r]);
    int i = l;
    int j = r-1;
    while (i <= j) {
        while (A[i] < value) ++i;
        while (A[j] >= value) --j;
        if (i >= j) break ;
        swap(A[i++], A[j--]);
    }
    swap(A[i], A[r]);
    return i;
}

int QuickSelect(vector<int> &A, int k, int l, int r) {
    if (A.size() == 1) return A[0];
    int part = Partition(A, l, r);
    if (k < part) return QuickSelect(A, k, l, part-1);
    if (k == part) return A[part];
    if (k > part) return QuickSelect(A, k, part+1, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    cout << QuickSelect(A, k, 0, n - 1);
}
