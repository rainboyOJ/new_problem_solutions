/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 16:05
 * update_at: 2026-10-07 16:05
 */
// main.cpp：石环（ROJ 1699）。
// 题意：n 个石头围成环，可以有 0 个石头（n=1 时）以外的任意情况；
//       对每个 k（0 <= k <= n-1）判断能否拿走恰好 k 个连续石头（k=0 表示不拿），
//       使剩下的环中任意相邻两个石头颜色都不同。
//
// 算法（KMP 前缀函数 + 断点切段）：
//   1. 把环展成 s2 = s + s（长度 2n）。拿走 k 个连续石头等价于在 s2 上取一段
//      长度 m = n - k 的连续子串当作剩下的环；因为 m <= n，子串起点可以落在
//      [0, n-1] 内且不越出 s2。
//   2. s2 中 s2[i] == s2[i-1] 的位置是"断点"，把 s2 切成若干极大段，段内任意
//      相邻字符都不同。于是段内长度为 m 的子串只需要再检查"首尾字符是否相同"。
//   3. 段 T（长 L）内所有长度为 m 的子串都首尾相同，等价于 T 有周期 m-1，
//      也等价于 T 有长度 L-m+1 的 border。T 的全部 border 长度就是 KMP
//      前缀函数的 border 链，于是这些坏的 m 只有 O(L) 个，可以逐个扣掉。
//   4. 每个段先把 m <= min(L, n) 的计数整体 +1，再对每条真 border 把
//      m = L - b + 1 减 1；最终 res[m] > 0 即表示"剩 m 个石头"可行。
//      注意 m = 1 时环里只有 1 个石头，没有相邻对，恒为美丽，不会被扣掉。
//   5. 输出第 k 位对应 m = n - k。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1000005; // n 的上限为 10^6，多留几个位置给 1-indexed 的下标

ll n;                      // 当前这组数据的环长 |s|
char s2[2 * MAXN + 5];     // 环展开得到的 2n 长串 s + s，字符值域小，用 char 省内存
int pi_arr[2 * MAXN + 5];  // KMP 前缀函数数组，处理每个段时复用：pi_arr[i] 是段内
                           // 前 i 个字符的最长真 border 长度（段内下标从 0 起）
int res[MAXN];             // res[m] 表示"能取出合法的长度为 m 的弧"的段数，>0 即可行

// 处理 s2 上的一段 [l, r]（闭区间），它满足段内任意相邻字符都不同。
// 段内每个长度为 m 的子串只剩"首尾字符是否相同"这一个约束，
// 本函数把"本段对长度 m 可行 / 不可行"记进 res。
void process_segment(ll l, ll r) {
    ll L = r - l + 1;

    // 段内的 KMP 前缀函数：pi_arr[i] 是最长真 border 长度
    pi_arr[0] = 0;
    pi_arr[1] = 0;
    int j = 0;
    for (ll i = 2; i <= L; i++) {
        j = pi_arr[i - 1];
        while (j > 0 && s2[l + i - 1] != s2[l + j]) {
            j = pi_arr[j]; // 失配就沿 border 链往回跳
        }
        if (s2[l + i - 1] == s2[l + j]) {
            j++; // 接上了，border 长度加一
        }
        pi_arr[i] = j;
    }

    // 段内长为 m 的子串共有 L-m+1 个，只要 m <= min(L, n)，本段就能提供长度 m 的弧。
    // 这里只关心"是否存在"，所以先用整体 +1 表示"本段可以提供"，坏长度稍后逐条扣掉。
    ll cap = min(L, n);
    for (ll m = 1; m <= cap; m++) {
        res[m]++;
    }

    // 段 T 有长度 b 的 border <=> T 有周期 L-b <=> 段内所有长度为 L-b+1 的
    // 子串首尾相同，也就是长度 m = L-b+1 在本段完全不可行，扣掉它。
    // border 链上的 b 恰是全部真 border 长度，故坏长度只有这么多。
    j = pi_arr[L];
    while (j > 0) {
        ll m = L - j + 1;
        if (m <= n) {
            res[m]--;
        }
        j = pi_arr[j];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int case_no = 0;
    while (cin >> s) { // 多组数据，读到 EOF 结束
        case_no++;
        n = s.size();
        for (ll i = 0; i < 2 * n; i++) {
            s2[i] = s[i % n]; // 环展开
        }
        for (ll m = 0; m <= n; m++) {
            res[m] = 0; // 只清本组实际用到的范围
        }

        // 按"相邻字符相同"的断点把 s2 切成极大段
        ll l = 0;
        for (ll i = 1; i < 2 * n; i++) {
            if (s2[i] == s2[i - 1]) {
                process_segment(l, i - 1);
                l = i;
            }
        }
        process_segment(l, 2 * n - 1);

        cout << "Case " << case_no << ": ";
        for (ll k = 0; k < n; k++) {
            cout << (res[n - k] > 0 ? '1' : '0'); // 拿走 k 个后剩 m = n-k 个
        }
        cout << '\n';
    }

    return 0;
}
