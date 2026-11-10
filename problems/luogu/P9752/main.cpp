/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:41
 * update_at: 2026-11-10 19:53
 */
// main.cpp：正难则反——由每个记录状态反向生成它能一步到达的全部 81 种合法前驱状态并计数。
#include <bits/stdc++.h>
using namespace std;

int n;
int a[5];
int cnt[100000]; // cnt[s] 表示状态 s 能够一步变成多少个记录状态

// 将 5 位拨圈状态编码为 00000~99999 的整数
int encode(const int state[5]) {
    return state[0] * 10000 + state[1] * 1000 + state[2] * 100 + state[3] * 10 + state[4];
}

// 统计当前记录能一步变出的所有 81 种候选状态（转 1 个轮子 45 种 + 转 2 个相邻轮子 36 种）
void add_record(const int state[5]) {
    int b[5];

    // 1. 转动 1 个拨圈（5 * 9 = 45 种）
    for (int i = 0; i < 5; i++) {
        for (int step = 1; step <= 9; step++) {
            for (int k = 0; k < 5; k++) b[k] = state[k];
            b[i] = (state[i] + step) % 10;
            cnt[encode(b)]++;
        }
    }

    // 2. 同时转动 2 个相邻拨圈（4 * 9 = 36 种）
    for (int i = 0; i < 4; i++) {
        for (int step = 1; step <= 9; step++) {
            for (int k = 0; k < 5; k++) b[k] = state[k];
            b[i] = (state[i] + step) % 10;
            b[i + 1] = (state[i + 1] + step) % 10;
            cnt[encode(b)]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> a[j];
        }
        add_record(a);
    }

    int ans = 0;
    for (int s = 0; s < 100000; s++) {
        if (cnt[s] == n) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
