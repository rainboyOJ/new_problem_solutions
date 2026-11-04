/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-03 10:15
 * update_at: 2026-11-04 20:05
 */
/*
 * 解法一(与 main.py 一致)：移项 + map 计数
 *
 * 区间 [i, j] 合法：
 *   s[j] - s[i-1] = j - i + 1
 *   移项成 s[j] - j = s[i-1] - (i-1)
 * 固定右端点 j，答案累加「之前有多少个 k 满足 s[k] - k == s[j] - j」。
 * 用 map 记下每个 s[k] - k 出现过多少次，O(n log n)，不需要知道值域。
 *
 * 解法二(main2.cpp)是同一个量换存储：先对每个元素减 1，
 * 判据变成两个前缀和相等，再把下标平移后用数组当桶，O(n)。
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n;
string s;
int pre[maxn];          // pre[i] = a[1] + ... + a[i]，原数组的前缀和

void sol(){
    cin >> n >> s;

    pre[0] = 0;
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i-1] + (s[i-1] - '0');

    map<int, ll> cnt;   // cnt[v] = s[k] - k 等于 v 的下标 k 出现过多少次
    cnt[0] = 1;         // k = 0，空前缀 s[0] - 0 = 0
    ll ans = 0;
    for (int j = 1; j <= n; j++) {
        int key = pre[j] - j;
        ans += cnt[key];    // 之前有多少个 k 满足 s[k] - k == s[j] - j
        cnt[key]++;
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
