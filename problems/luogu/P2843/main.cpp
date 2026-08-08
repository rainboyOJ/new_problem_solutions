#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXK = 30;

int n, k;
int a[MAXN];
int cnt[MAXK + 1];

struct State {
    int d[MAXK];

    bool operator==(const State &other) const {
        for (int i = 0; i < MAXK; i++) {
            if (d[i] != other.d[i]) {
                return false;
            }
        }
        return true;
    }
};

struct StateHash {
    size_t operator()(const State &s) const {
        unsigned long long h = 1469598103934665603ULL;
        for (int i = 0; i < MAXK; i++) {
            unsigned long long x = static_cast<unsigned int>(s.d[i] + 100000);
            h ^= x + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
        }
        return static_cast<size_t>(h);
    }
};

// 根据当前前缀计数，构造“相对第 1 种特性的差分状态”。
State build_state() {
    State s;
    for (int i = 0; i < MAXK; i++) {
        s.d[i] = 0;
    }

    for (int i = 2; i <= k; i++) {
        s.d[i - 2] = cnt[i] - cnt[1];
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    unordered_map<State, int, StateHash> first_pos;
    first_pos.reserve(n * 2 + 5);

    State zero = build_state();
    first_pos[zero] = 0;

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int bit = 0; bit < k; bit++) {
            if ((a[i] >> bit) & 1) {
                cnt[bit + 1]++;
            }
        }

        State now = build_state();

        unordered_map<State, int, StateHash>::iterator it = first_pos.find(now);
        if (it == first_pos.end()) {
            first_pos[now] = i;
        } else {
            ans = max(ans, i - it->second);
        }
    }

    cout << ans << '\n';
    return 0;
}
