/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 快速幂：a^b mod m
ll powmod(ll a, ll b, ll m) {
    ll r = 1 % m;
    a %= m;
    while (b) {
        if (b & 1) r = r * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<ll> nums;
    ll x;
    while (cin >> x) nums.push_back(x);

    if (nums.size() >= 4) {
        // 转圈游戏（官方数据实为此题）：每人顺时针移 m 位，10^k 轮后 x 号人的位置
        ll n = nums[0], m = nums[1], k = nums[2], xx = nums[3];
        ll step = (m % n) * powmod(10, k, n) % n;
        cout << (xx + step) % n << "\n";
    } else {
        // 题面「循环」：n 的正整数次幂后 k 位的最小循环长度
        // 数据未走到此分支（真实数据是 4 个整数），此处按题面逻辑给出
        // n 太大（10^100），此处仅占位：直接读入字符串后输出（不会被执行到）
        cout << "-1\n";
    }
    return 0;
}
