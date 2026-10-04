/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:36
 * update_at: 2026-10-03 11:36
 */
// P9244 [蓝桥杯 2023 省 B] 子串简写
// 正解：枚举右端点 j，用变量 cnt 维护“左侧所有满足 c1 且 j - i + 1 >= K 的起点 i 的个数”。
//         每当 j 右移一位，就新允许一个起点，把它加入 cnt。
//         若 S[j] == c2，则这 cnt 个起点各对应一个合法子串，累加进答案。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int maxn = 5e5 + 5;

int K;          // 子串长度下限：长度 >= K 才可以使用简写
int n;          // 字符串长度
char s[maxn];   // 原字符串，下标从 1 开始
char c1, c2;    // 要求的首字符与尾字符

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> K;
    cin >> (s + 1) >> c1 >> c2;
    n = (int)strlen(s + 1);

    ll ans = 0;
    ll cnt = 0; // 在当前右端点 j 下，左侧可作为起点的位置个数

    // j = K 是长度刚好等于 K 的最小右端点；j < K 时任何子串都不够长
    for (int j = K; j <= n; j++) {
        // 右端点从 j-1 变成 j 时，起点 i = j - K + 1 的长度由 K-1 变成 K，
        // 正好刚刚够长，于是它被“解锁”，加入可选起点集合
        if (s[j - K + 1] == c1) {
            cnt++;
        }
        // 现在 cnt 里恰好是 [1, j-K+1] 中所有值为 c1 的位置，且全部满足长度条件
        if (s[j] == c2) {
            ans += cnt;
        }
    }

    cout << ans << "\n";
    return 0;
}
