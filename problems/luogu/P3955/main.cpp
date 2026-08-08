#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXL = 8;

int n, q;
int a[MAXN];
int pw10[MAXL + 1];
map<int, int> best[MAXL + 1];

void init_pow10() {
    pw10[0] = 1;
    for (int i = 1; i <= MAXL; i++) {
        pw10[i] = pw10[i - 1] * 10;
    }
}

void build_answer() {
    for (int i = 1; i <= n; i++) {
        for (int len = 1; len <= MAXL; len++) {
            int suffix = a[i] % pw10[len];
            if (best[len].count(suffix) == 0 || a[i] < best[len][suffix]) {
                best[len][suffix] = a[i];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_pow10();

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build_answer();

    for (int i = 1; i <= q; i++) {
        int len, need;
        cin >> len >> need;
        if (best[len].count(need)) {
            cout << best[len][need] << '\n';
        }
        else {
            cout << -1 << '\n';
        }
    }

    return 0;
}
