/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-09 17:35
 * update_at: 2026-11-09 17:35
 */
/*
 * 解法一：贪心（最少区间覆盖整段）
 *
 * 思路：
 *   每个 s_i 在 t 中每出现一次，就是一个「一步就能涂红」的区间 [l, r]。
 *   把 t 全部涂红 = 用最少的区间覆盖 [1, |t|]，每个区间代价都是 1，
 *   这就是经典的「最少线段覆盖整段」贪心。
 *
 * 贪心选择标准：
 *   设已经涂红了前缀 t[0..covered-1]（covered 是第一个还没涂红的位置，0 起）。
 *   在所有左端点 l <= covered 的区间里，选右端点 r 最远的那个涂上，
 *   一步把 covered 推到 r+1。为什么对：任何可行解都必须有一个区间跨过
 *   covered，换成能跨得最远的那个不会让之后的覆盖变差（最优子结构）。
 *   若没有任何区间能越过 covered，说明有位置永远涂不到，输出 -1。
 *
 * 与解法二(main2.cpp)的关系：
 *   main2.cpp 用 DP 保留所有可能的前缀终点，本质仍是同一个覆盖模型：
 *   由于每个区间代价都是 1、取最远右端点不劣，贪心和 DP 答案必然相同。
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;

const int maxn = 105;

int n;              // 字符串个数
string t;           // 文本
string s[maxn];     // s[1..n]

// 记录方案：第 k 步用第 ans_w[k] 个字符串，从 1 起位置 ans_p[k] 开始涂红
int ans_w[maxn];
int ans_p[maxn];

void sol(){
    cin >> t;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];

    int L = t.size();
    int covered = 0;    // 已涂红 t[0..covered-1]，covered 为第一个还没涂红的位置（0 起）
    int cnt = 0;

    while (covered < L) {
        int best_r = -1;    // 本步能涂到的最远右端点（0 起）
        int best_w = 0;     // 达到 best_r 的字符串编号
        int best_l = 0;     // 达到 best_r 的起始位置（0 起）
        for (int i = 1; i <= n; i++) {
            int len = s[i].size();
            // p 是 s[i] 在 t 中的起始位置（0 起），左端点必须落在已涂红前缀内（允许重叠）
            for (int p = 0; p + len <= L; p++) {
                if (p > covered) break;              // 起点更靠后的区间留给后面
                if (t.compare(p, len, s[i]) != 0) continue;
                int r = p + len - 1;
                if (r > best_r) {
                    best_r = r;
                    best_w = i;
                    best_l = p;
                }
            }
        }
        if (best_r < covered) {   // 没有区间能越过 covered，说明有位置涂不到
            cout << -1 << "\n";
            return;
        }
        cnt++;
        ans_w[cnt] = best_w;
        ans_p[cnt] = best_l + 1;  // 转成 1 起位置
        covered = best_r + 1;
    }

    cout << cnt << "\n";
    for (int k = 1; k <= cnt; k++) {
        cout << ans_w[k] << " " << ans_p[k] << "\n";
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    int q;
    cin >> q;
    while (q--) sol();
    return 0;
}
