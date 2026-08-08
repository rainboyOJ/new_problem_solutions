#include <bits/stdc++.h>
using namespace std;

int n;
string target_state;

string spread_once(const string &cur) {
    string nxt = cur;
    for (int i = 0; i < n; i++) {
        if (cur[i] == '1') {
            if (i - 1 >= 0) {
                nxt[i - 1] = '1';
            }
            if (i + 1 < n) {
                nxt[i + 1] = '1';
            }
        }
    }
    return nxt;
}

bool can_reach(const string &start) {
    string cur = start;

    // 最多扩散 n 次后一定稳定。
    for (int day = 0; day <= n; day++) {
        if (cur == target_state) {
            return true;
        }
        string nxt = spread_once(cur);
        if (nxt == cur) {
            if (nxt == target_state) {
                return true;
            }
            return false;
        }
        cur = nxt;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> target_state;

    int ans = n;

    // 小数据暴力：枚举所有初始感染状态。
    for (int mask = 1; mask < (1 << n); mask++) {
        string start(n, '0');
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                start[i] = '1';
                cnt++;
            }
        }
        if (cnt >= ans) {
            continue;
        }
        if (can_reach(start)) {
            ans = cnt;
        }
    }

    cout << ans << '\n';
    return 0;
}
