// brute.cpp：小数据搜索所有攻击顺序，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

int n;
int r[MAXN];
map<long long, int> memo;

int count_bits(int x) {
    int cnt = 0;
    while (x > 0) {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}

int dfs(int alive, int used) {
    long long key = ((long long)alive << n) | used;
    auto it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }

    int can_attack = 0;
    for (int i = 0; i < n; i++) {
        if ((alive & (1 << i)) && !(used & (1 << i))) {
            can_attack = 1;
        }
    }

    if (!can_attack) {
        int ret = count_bits(alive);
        memo[key] = ret;
        return ret;
    }

    int ans = count_bits(alive);

    for (int i = 0; i < n; i++) {
        if (!(alive & (1 << i)) || (used & (1 << i))) {
            continue;
        }

        for (int j = 0; j < n; j++) {
            if (i == j || !(alive & (1 << j))) {
                continue;
            }

            int next_alive = alive;
            int next_used = used | (1 << i);
            if (r[i] > r[j]) {
                next_alive &= ~(1 << j);
            }

            ans = min(ans, dfs(next_alive, next_used));
        }
    }

    memo[key] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    memo.clear();
    cout << dfs((1 << n) - 1, 0) << '\n';

    return 0;
}
