/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:09
 * update_at: 2026-10-08 22:09
 */
// 一本通 2020【例4.5】第几项（ROJ 5022）
// 题意：s = 1 + 2 + 3 + ... + n，求「加到第几项时 s 首次超过 m」的项数 n，输出 n。
// 关键：题面是「超过 m」，即严格大于；m 恰为三角数（如 m = 1、990、39903）时，
//       必须再多加一项（m = 1 答案是 2，m = 990 答案是 45），不能停在 s == m。
// 范围：1 <= m <= 40000，S_282 = 39903，S_283 = 40186，
//       所以循环至多 283 次，答案恒 >= 2。
#include <cstdio>

typedef long long ll;

ll m;    // 题目输入的阈值
ll sum;  // 当前累加和 s = 1 + 2 + ... + n，最大只到 S_283 = 40186，用 ll 更保险
ll n;    // 已加进去的项数，也就是当前累加到第 n 项

void solve() {
    // s 还没「超过」m 就一直加下一项；循环结束时 n 就是首次 s > m 的项数
    while (sum <= m) {
        n++;
        sum += n;
    }
}

int main() {
    if (scanf("%lld", &m) != 1) return 0;  // 题面保证有输入，读失败直接结束
    solve();
    printf("%lld\n", n);
    return 0;
}
