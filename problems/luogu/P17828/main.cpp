/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-11-02 22:22
 */
// main.cpp：答案等于「字符不同的对称位置对数」。
// 左右指针 l, r 分别从两端向中间走，每次取两端段长的较小值 take 配对。
// 当 l == r 时，剩余未配对字符全在同一段内，字符必然相同，修改代价为 0，直接结束。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 5;
int n;
ll a[maxn];    // 第 i 段的长度，跑的过程中会被减掉已经配掉的字符数
char c[maxn];  // 第 i 段全是字符 c[i]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> c[i];
    }

    ll ans = 0;
    int l = 0, r = n - 1;

    while (l < r) {
        ll take = min(a[l], a[r]);
        if (c[l] != c[r]) ans += take;
        a[l] -= take;
        a[r] -= take;
        if (a[l] == 0) ++l;
        if (a[r] == 0) --r;
    }

    cout << ans << '\n';
    return 0;
}
