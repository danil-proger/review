#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

pair<vector<int>, vector<int>> Partition(vector<int> A, long long pivot) {
	pair<vector<int>, vector<int>> part;
	for (int el : A) {
		if (el < pivot) part.first.push_back(el);
		if (el > pivot) part.second.push_back(el);
	}
	return part;
}

int QuickSelect(vector<int> A, int k) {
	if (A.size() == 1) return A[0];
	long long pivot = A[rand() % (A.size())];
	pair<vector<int>, vector<int>> part;
	part = Partition(A, pivot);
	if (k < part.first.size()) return QuickSelect(part.first, k);
	if (k < A.size() - part.second.size()) return pivot;
	return QuickSelect(part.second, k - A.size() + part.second.size());
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
	cout << QuickSelect(A, k);
}
