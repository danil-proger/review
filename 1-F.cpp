#include <fstream>
#include <string>
#include <utility>
#include <queue>
#include <algorithm>


using namespace std;
long long ans = 0;


vector<long long> Merge(vector<long long> left, vector<long long> right) {
	int i = 0;
	int j = 0;
	vector<long long> res;
	while ((i < left.size()) && (j < right.size())) {
		if (left[i] > right[j]) {
			res.push_back(right[j]);
			ans += left.size() - i;
			j++;
		}
		else {
			res.push_back(left[i]);
			i++;
		}
	}
	while (i < left.size()) {
		res.push_back(left[i]);
		i++;
	}
	while (j < right.size()) {
		res.push_back(right[j]);
		j++;
	}
	return res;
}


int main() {
	std::ifstream fin("inverse.in");
	std::ofstream fout("inverse.out");
	int n, input;
	fin >> n;
	queue<vector<long long>> merge;
	vector< long long> left, right;
	for (int i = 0; i < n; i++) {
		fin >> input;
		merge.push({ input });
	}
	int step = 1;
	while (step < n) {
		step *= 2;
	}
	for (int i = n; i < step; i++) {
		merge.push({ 10000000000 });
	}
	while (merge.size() > 1) {
		left = merge.front();
		merge.pop();
		right = merge.front();
		merge.pop();
		merge.push(Merge(left, right));
	}
	fout << ans;
}
