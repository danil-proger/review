#include <fstream>
#include <string>
#include <utility>
#include <queue>
#include <algorithm>


using namespace std;
long long answer = 0;


vector<long long> Merge(vector<long long> left, vector<long long> right) {
    long long i = 0;
    long long j = 0;
    vector<long long> result;

    while ((i < left.size()) && (j < right.size())) {
        if (left[i] > right[j]) {
            result.push_back(right[j]);
            j++;
        }
        else {
            result.push_back(left[i]);
            i++;
            answer += j;
        }
    }

    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }

    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
        answer += j;
    }

    return result;
}


vector<long long> alg(vector<long long> &sort) {
    if (sort.size() == 1) return sort;
    unsigned long size = sort.size();
    vector<long long> left;
    vector<long long> right;

    for (long long i = 0; i < (size + 1) / 2; ++i) {
        left.push_back(sort[i]);
    }

    for(unsigned long i = (size + 1) / 2; i < size; ++i) {
        right.push_back(sort[i]);
    }

    return Merge(alg(left), alg(right));
}


int main() {
    ifstream fin("inverse.in");
    ofstream fout("inverse.out");
    long long n, input;
    fin >> n;
    vector<long long> merge(n);

    for (long long i = 0; i < n; i++) {
        fin >> merge[i];
    }

    if (merge.size() == 1) fout << 0;
    else {
        alg(merge);
        fout << answer;
    }
    return 0;
}
