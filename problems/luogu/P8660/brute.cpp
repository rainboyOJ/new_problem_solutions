#include <bits/stdc++.h>
using namespace std;

const int MAXN = 18;
const int TARGET = 20000; // 坐标统一乘 2。

int n;
int a[MAXN], b[MAXN];

struct Interval {
    int need_left;
    int dead;
    int len;
};

Interval seg[MAXN];
unordered_map<long long, int> memo;

long long encode_state(int mask, int covered) {
    return (static_cast<long long>(mask) << 20) | covered;
}

// 小数据暴力：枚举当前还能接上的所有区间，求最远能覆盖到哪里。
int dfs(int mask, int covered) {
    long long key = encode_state(mask, covered);
    unordered_map<long long, int>::iterator it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }

    int best = covered;

    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) {
            continue;
        }
        if (seg[i].need_left > covered) {
            continue;
        }
        if (seg[i].dead <= covered) {
            continue;
        }

        int next_covered = min(covered + seg[i].len, seg[i].dead);
        int value = dfs(mask | (1 << i), next_covered);
        if (value > best) {
            best = value;
        }
    }

    memo[key] = best;
    return best;
}

bool check(int lim2) {
    for (int i = 0; i < n; i++) {
        seg[i].need_left = a[i] - lim2;
        seg[i].dead = b[i] + lim2;
        seg[i].len = b[i] - a[i];
    }

    memo.clear();
    return dfs(0, 0) >= TARGET;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        a[i] *= 2;
        b[i] *= 2;
    }

    int left = 0;
    int right = TARGET;
    while (left < right) {
        int mid = (left + right) >> 1;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    if ((left & 1) == 0) {
        cout << left / 2 << '\n';
    } else {
        cout << left / 2 << ".5\n";
    }

    return 0;
}
