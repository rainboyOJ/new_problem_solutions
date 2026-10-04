/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:49
 * update_at: 2026-10-04 23:49
 */
// roj 1062 最高的分数
// 打擂台扫描：初值 0，读到一个成绩就更新当前最高分；n = 0 时无人考试，输出 0。

#include <cstdio>

typedef long long ll;

ll n;         // 参加考试的人数，可以为 0
ll cur_score; // 当前读到的成绩
ll best;      // 打擂台变量：到目前为止的最高分，初值 0（成绩非负，不会被真实成绩超过）

void solve() {
    scanf("%lld", &n);
    best = 0;
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &cur_score);
        if (cur_score > best) { // 只有遇到更高的成绩才更新擂台
            best = cur_score;
        }
    }
    printf("%lld\n", best);
}

int main() {
    solve();
    return 0;
}
