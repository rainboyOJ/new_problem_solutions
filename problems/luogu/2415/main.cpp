/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int a[35]; // 集合元素
int n;     // 元素个数

int main() {
    int x;
    while (cin >> x) a[++n] = x;
    // 每个元素在 2^(n-1) 个子集中出现
    long long sum = 0;
    for (int i = 1; i <= n; i++) sum += a[i];
    long long ans = sum * (1LL << (n - 1)); // 等价于 sum * 2^(n-1)
    cout << ans;
    return 0;
}
