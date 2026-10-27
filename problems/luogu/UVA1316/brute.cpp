/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-27 21:05
 * update_at: 2026-10-27 21:05
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 把"选哪些商品卖"看成 01 选择序列，枚举所有 2^n 种子集，逐个检查能否按期卖出，取利润最大者。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 12;

int n;
int profit[MAXN];   // profit[i]：第 i 个商品的利润
int deadline[MAXN]; // deadline[i]：第 i 个商品的截止日期
int choose[MAXN];   // choose[i]：第 i 个商品卖（1）还是不卖（0）

// 检查当前 choose[] 选出的商品能否全部按期卖出
// 判定方法：把选中的商品按截止日期排序后，第 k 个必须满足 d >= k
bool can_schedule() {
    vector<pair<int, int> > picked; // (截止日期, 利润)，只要截止日期
    for (int i = 0; i < n; i++) {
        if (choose[i]) picked.push_back(make_pair(deadline[i], profit[i]));
    }
    sort(picked.begin(), picked.end());
    for (int k = 0; k < (int)picked.size(); k++) {
        if (picked[k].first < k + 1) return false; // 前 k+1 个商品挤不进 k+1 天内
    }
    return true;
}

// 分别枚举所有子集，可行就更新答案
ll solve() {
    ll best = 0;
    int total = 1 << n;
    for (int mask = 0; mask < total; mask++) {
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            choose[i] = (mask >> i) & 1;
            if (choose[i]) sum += profit[i];
        }
        if (sum <= best) continue;       // 利润已经不可能更优，省掉可行性检查
        if (can_schedule()) best = sum;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 本题是多组输入，读到 EOF 为止
    while (cin >> n) {
        for (int i = 0; i < n; i++) cin >> profit[i] >> deadline[i];
        cout << solve() << '\n';
    }

    return 0;
}
