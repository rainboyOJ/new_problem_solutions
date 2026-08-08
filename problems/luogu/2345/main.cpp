/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 14:30
 * update_at: 2026-08-05 14:30
 */
// 按 v 排序后，处理第 i 头牛时它和之前牛的贡献 max(v) 就是 v[i]，
// 用两个树状数组维护前面牛的坐标数量与坐标和，O(n log n) 统计。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005;

int n;
struct Cow {
    int v, x;
};
Cow cows[MAXN];

long long bit_cnt[MAXN];   // 坐标出现次数
long long bit_sum[MAXN];   // 坐标值之和

bool cmp_v(const Cow& a, const Cow& b) {
    return a.v < b.v;
}

void add(long long* bit, int idx, long long val) {
    for (; idx <= MAXN; idx += idx & -idx) bit[idx] += val;
}

long long query(long long* bit, int idx) {
    long long res = 0;
    for (; idx > 0; idx -= idx & -idx) res += bit[idx];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> cows[i].v >> cows[i].x;

    sort(cows + 1, cows + n + 1, cmp_v);   // 按听力升序

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int x = cows[i].x;
        int v = cows[i].v;

        // 前面（v 更小）的牛中，x 小于当前坐标的数量与坐标和
        long long cnt_less = query(bit_cnt, x - 1);
        long long sum_less = query(bit_sum, x - 1);
        // 全部前面牛的数量与坐标和
        long long cnt_all = i - 1;
        long long sum_all = query(bit_sum, MAXN);
        // 剩下的就是 x 大于当前坐标的部分
        long long cnt_greater = cnt_all - cnt_less;
        long long sum_greater = sum_all - sum_less;

        // 贡献 = v * (x*数量 - 坐标和 + 坐标和 - x*数量)，绝对值拆成左右两边
        ans += 1LL * v * (x * cnt_less - sum_less + sum_greater - x * cnt_greater);

        // 把当前牛插入 BIT
        add(bit_cnt, x, 1);
        add(bit_sum, x, x);
    }

    cout << ans << '\n';

    return 0;
}
