#include <bits/stdc++.h>
using namespace std;

long long n, m;
vector<long long> cur, best;
long long best_product = -1;

void dfs(int idx, long long last, long long left_sum, long long product) {
    if (idx == m) {
        if (left_sum != 0) return;
        if (product > best_product || (product == best_product && cur < best)) {
            best_product = product;
            best = cur;
        }
        return;
    }

    long long remain = m - idx;
    for (long long x = last; x <= left_sum / remain; x++) {
        cur.push_back(x);
        dfs(idx + 1, x, left_sum - x, product * x);
        cur.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    dfs(0, 1, n, 1);

    for (int i = 0; i < (int) best.size(); i++) {
        if (i) cout << ' ';
        cout << best[i];
    }
    cout << '\n';

    return 0;
}
