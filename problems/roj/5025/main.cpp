/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:25
 * update_at: 2026-10-08 22:25
 */
// 一本通 2023《【例4.8】数据统计》（ROJ 5025）
// 题意：输入一行若干个整数（个数 <= 100，值是不超过 1000 的整数），
//       输出一行：最小值、最大值、平均值（保留 3 位小数），空格分隔。
//       样例 `1 2 3` -> `1 3 2.000`。
// 关键点：
//   * 个数不定，读入必须读到 EOF（`cin >> x` 在流耗尽时返回 false），不能用「只读一行」。
//   * 题面只声明上界“不超过 1000”，未声明下界（负数在字面上未被禁止），
//     所以 min 初值取 INT_MAX、max 初值取 INT_MIN；写成 min=1001 / max=0
//     这类「依赖数据非负」的初值，遇到全负数据就会给出错误的 min/max。
//   * 求平均必须转 double：`sum / cnt` 会做整数除法丢掉小数。
//     printf("%.3f") 与 Python 的 f-string 都用 IEEE binary64 的
//     「就近舍入 / 平局取偶」（round-half-even），10 个测试点与 80000 个
//     平分点（第 4 位小数 = 5）全部逐字节一致，无需 Decimal 兼容层。
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll sum_all;                  // 所有输入整数之和；n <= 100、值 <= 1000，sum <= 10^5，用 ll 无溢出
ll cnt;                      // 数据个数（读完后即题面的 n）
ll mn = INT_MAX;             // 最小值，初值取类型上界，保证任意首元素都能压低它
ll mx = INT_MIN;             // 最大值，初值取类型下界，保证任意首元素都能抬高它

// 读到 EOF，边读边维护最小值 / 最大值 / 和 / 个数，最后按题面格式输出。
void solve() {
    ll x;
    while (cin >> x) {
        mn = min(mn, x);
        mx = max(mx, x);
        sum_all += x;
        cnt++;
    }

    if (cnt == 0) {  // 题面保证至少有 1 个数；空输入时直接返回，避免 0 除
        return;
    }

    // 1.0 * sum_all 把和抬成 double，先做实数除法，再交给 printf 做 3 位舍入；
    // 直接写 sum_all / cnt 会走整数除法丢掉小数。
    double avg = 1.0 * sum_all / cnt;

    printf("%lld %lld %.3f\n", mn, mx, avg);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
