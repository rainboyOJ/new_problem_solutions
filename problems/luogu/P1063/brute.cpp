#include <bits/stdc++.h>
using namespace std;

long long dfs(vector<long long> v) {
    if ((int)v.size() == 1) {
        return 0;
    }

    long long best = 0;
    int m = (int)v.size();
    for (int i = 0; i < m; ++i) {
        int j = (i + 1) % m;
        int k = (i + 2) % m;
        long long gain = v[i] * v[j] * v[k];

        vector<long long> next;
        next.reserve(m - 1);
        for (int t = 0; t < m; ++t) {
            if (t != j) {
                next.push_back(v[t]);
            }
        }

        best = max(best, gain + dfs(next));
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    cout << dfs(v) << '\n';
    return 0;
}
