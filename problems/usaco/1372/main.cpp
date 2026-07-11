/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:07
 * update_at: 2026-07-11 16:08
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAX_STEP = 5000000;

int n, start_pos;
int q_type[MAXN];      // 0 表示跳板，1 表示炮击目标
int value_arr[MAXN];   // 跳板增加能量，目标表示击破所需能量
bool broken[MAXN];     // 目标是否已经被击破

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

    for (int step = 0; step < MAX_STEP && 1 <= pos && pos <= n; step++) {
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
