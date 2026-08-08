#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;

int n;
i128 normal_cost[25], magic_cost[25];
vector<int> spawn[25];
i128 dist_arr[25];

string to_string_i128(i128 x) {
    if (x == 0) {
        return "0";
    }

    bool neg = false;
    if (x < 0) {
        neg = true;
        x = -x;
    }

    string s;
    while (x > 0) {
        int digit = (int) (x % 10);
        s.push_back(char('0' + digit));
        x /= 10;
    }
    if (neg) {
        s.push_back('-');
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        long long s, k;
        int r;
        cin >> s >> k >> r;
        normal_cost[i] = (i128) s;
        magic_cost[i] = (i128) k;
        spawn[i].clear();
        for (int j = 1; j <= r; j++) {
            int child;
            cin >> child;
            spawn[i].push_back(child);
        }
    }

    for (int i = 1; i <= n; i++) {
        dist_arr[i] = magic_cost[i];
    }

    // 更直接的小数据做法：
    // 反复使用方程
    // f[i] = min(法术攻击, 普通攻击 + 生成怪兽的总代价)
    // 直到没有任何值继续下降。
    bool changed = true;
    while (changed) {
        changed = false;

        for (int i = 1; i <= n; i++) {
            i128 cand = normal_cost[i];
            for (size_t j = 0; j < spawn[i].size(); j++) {
                cand += dist_arr[spawn[i][j]];
            }

            if (cand < dist_arr[i]) {
                dist_arr[i] = cand;
                changed = true;
            }
        }
    }

    cout << to_string_i128(dist_arr[1]) << '\n';

    return 0;
}
