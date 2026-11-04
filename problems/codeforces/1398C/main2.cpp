/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-03 10:15
 * update_at: 2026-11-04 20:05
 */
/*
 * 解法二(与 main2.py 一致)：元素减 1 + 平移数组当桶
 *
 * 思路：
 *   数出 sum(a[l..r]) == r-l+1 的子段个数。
 *   把每个元素减 1，条件变成 sum(a'[l..r]) == 0，
 *   也就是「前缀和相等的两个下标之间」构成一个合法子段。
 *   扫一遍，用桶记下每个前缀和出现过多少次，答案累加历史出现次数。
 *
 * 与解法一(main.cpp)的关系：
 *   解法一里的 s[k] - k 正好等于「减 1 后的前缀和」，
 *   两种解法统计的是同一个量；这里把 map 换成值域平移后的数组，O(n log n) -> O(n)。
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 1e6+5;
int n;
string s;
int cnt[maxn];          // cnt[pre + base] = 前缀和 pre 出现过的次数

void sol(){
    cin >> n >> s;

    int base = n;                       // 前缀和最小能到 -n，平移成非负下标
    for (int i = 0; i <= 9*n+5; i++)    // 清桶(每个用例自己清，别跨用例串味)
        cnt[i] = 0;

    int pre = 0;
    ll ans = 0;
    cnt[base] = 1;                      // 空前缀，前缀和 0 出现过一次
    for (int i = 0; i < n; i++) {
        pre += (s[i] - '0') - 1;        // 关键是减掉 1
        ans += cnt[pre + base];         // 相同前缀和的历史次数就是子段个数
        cnt[pre + base]++;
    }
    cout << ans << "\n";
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    int t;
    cin >> t;
    while (t--)
        sol();
    return 0;
}
