#include <bits/stdc++.h>
using namespace std;

const int MAXN = 18;

struct State {
    int rides;
    int weight;
};

int n, limit_w;
int w[MAXN + 1];
State dp[1 << MAXN];

bool better(const State &a, const State &b) {
    if (a.rides != b.rides) {
        return a.rides < b.rides;
    }
    return a.weight < b.weight;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> limit_w;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    int full = 1 << n;
    for (int i = 0; i < full; i++) {
        dp[i] = {n + 1, 0};
    }
    dp[0] = {1, 0};

    for (int mask = 0; mask < full; mask++) {
        for (int i = 1; i <= n; i++) {
            if (mask & (1 << (i - 1))) {
                continue;
            }
            State nxt = dp[mask];
            if (nxt.weight + w[i] <= limit_w) {
                nxt.weight += w[i];
            } else {
                nxt.rides++;
                nxt.weight = w[i];
            }

            int to = mask | (1 << (i - 1));
            if (better(nxt, dp[to])) {
                dp[to] = nxt;
            }
        }
    }

    cout << dp[full - 1].rides << '\n';
    return 0;
}
