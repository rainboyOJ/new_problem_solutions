/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:07
 * update_at: 2026-07-11 16:08
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, start_pos;
int q_type[MAXN];
int value_arr[MAXN];
bool broken[MAXN];
set<tuple<long long, int, long long> > seen_state;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> start_pos;
    for (int i = 1; i <= n; i++) {
        cin >> q_type[i] >> value_arr[i];
    }

    long long pos = start_pos;
    long long power = 1;
    int dir = 1;
    int ans = 0;

    // 小数据暴力：不断模拟，遇到完全相同的状态就说明之后会循环。
    while (1 <= pos && pos <= n) {
        tuple<long long, int, long long> state = make_tuple(pos, dir, power);
        if (seen_state.count(state)) break;
        seen_state.insert(state);

        int x = (int)pos;
        if (q_type[x] == 1) {
            if (!broken[x] && power >= value_arr[x]) {
                broken[x] = true;
                ans++;
            }
        } else {
            dir = -dir;
            power += value_arr[x];
        }

        pos += dir * power;
    }

    cout << ans << '\n';

    return 0;
}
