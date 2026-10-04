/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:36
 * update_at: 2026-10-03 11:36
 */
// main.cpp：正解。
// 每条记录 (A_i, B_i) 等价于不等式组 B_i <= A_i / V < B_i + 1，
// 解出 V 的取值区间 [A_i/(B_i+1)+1, A_i/B_i]，答案是所有区间的交。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MAXV = 1000000000000000000LL; // 上界初值，取一个比 1e9 大的数

int n;
ll min_v; // 所有记录下界的最大值：V 不能比它更小
ll max_v; // 所有记录上界的最小值：V 不能比它更大

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    min_v = 1;
    max_v = MAXV;
    for (int i = 1; i <= n; i++) {
        ll a, b;
        cin >> a >> b;

        // 由 B = A / V（整除）反推：
        // B <= A/V < B+1  =>  A/(B+1) < V <= A/B
        // V 是整数，所以左边界取 A/(B+1)+1，右边界取 A/B。
        ll lo = a / (b + 1) + 1;
        ll hi = a / b;

        // V 必须同时落在每一条记录给出的区间里，于是取交集。
        if (lo > min_v) min_v = lo;
        if (hi < max_v) max_v = hi;
    }

    cout << min_v << " " << max_v << "\n";
    return 0;
}
