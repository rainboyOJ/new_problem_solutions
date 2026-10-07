/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:14
 * update_at: 2026-10-06 16:14
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAX_SCORE = 600; // 成绩值域 0..600

int cnt[MAX_SCORE + 1];    // cnt[s] 表示成绩为 s 的人数

// 从高分往低分累加，找到第 need 名所在的成绩
int cutoff(int need) {
    int got = 0;
    for (int s = MAX_SCORE; s >= 0; --s) {
        got += cnt[s];
        if (got >= need) return s;
    }
    return 0; // 不可达
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, w;
    cin >> n >> w;

    for (int p = 1; p <= n; ++p) {
        int x;
        cin >> x;
        cnt[x]++;
        int need = max(1, p * w / 100); // 计划获奖人数，整数运算避浮点误差
        cout << cutoff(need);
        if (p < n) cout << ' ';
    }
    cout << '\n';
    return 0;
}
