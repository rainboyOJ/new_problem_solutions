/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-09 17:35
 * update_at: 2026-11-09 17:35
 */
/*
 * 解法二：DP（覆盖前缀的最少步数）
 *
 * 思路：
 *   把每个 s_i 在 t 中的每次出现看成一个区间 [l, r]（0 起），选它就等价于一步涂红这段。
 *   状态：dp[i] = 把前缀 t[0..i-1] 全部涂红所需的最少步数（dp[0] = 0）。
 *   转移：从已涂红到 i 的状态出发，任一左端点 l <= i 的区间 [l, r] 都能接着用一步，
 *         把已涂红范围推进到 max(i, r+1)，即
 *             dp[max(i, r+1)] = min(dp[max(i, r+1)], dp[i] + 1)
 *   答案：dp[L]，L = |t|；若 dp[L] 仍为 INF 说明涂不满，输出 -1。
 *   用 pre_i / pre_w / pre_p 记下每个状态的转移来源，最后从 L 一路回溯出方案。
 *
 * 与解法一(main.cpp)的关系：
 *   main.cpp 的贪心每步只保留「最远右端点」，相当于把 DP 中「右端点更远的状态一定不劣」
 *   这条性质直接用来合并状态；因为每个区间代价都是 1，两者答案必然相同。
 *   这里保留全部状态，写法更不容易出错，且天然适合回溯方案。
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;

const int maxn = 105;
const int INF = 1e9;

int n;              // 字符串个数
string t;           // 文本
string s[maxn];     // s[1..n]

int dp[maxn];       // dp[i] = 涂红前缀 t[0..i-1] 的最少步数
int pre_i[maxn];    // pre_i[i]：dp[i] 由哪个前缀位置 i' 转移过来
int pre_w[maxn];    // pre_w[i]：这次转移用的字符串编号
int pre_p[maxn];    // pre_p[i]：这次转移的起始位置（0 起）

int ans_w[maxn];    // 回溯出的方案：第 k 步的字符串编号
int ans_p[maxn];    // 回溯出的方案：第 k 步的起始位置（1 起）

void sol(){
    cin >> t;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];

    int L = t.size();
    for (int i = 0; i <= L; i++) dp[i] = INF;
    dp[0] = 0;

    for (int i = 0; i < L; i++) {
        if (dp[i] == INF) continue;
        for (int w = 1; w <= n; w++) {
            int len = s[w].size();
            // 枚举字符串 w 在 t 中的每个出现位置 p（0 起）
            for (int p = 0; p + len <= L; p++) {
                if (p > i) break;                    // 左端点必须落在已涂红前缀内（允许重叠）
                if (t.compare(p, len, s[w]) != 0) continue;
                int r = p + len - 1;
                int np = max(i, r + 1);              // 涂红后推进到的前缀终点
                if (dp[np] > dp[i] + 1) {
                    dp[np] = dp[i] + 1;
                    pre_i[np] = i;
                    pre_w[np] = w;
                    pre_p[np] = p;
                }
            }
        }
    }

    if (dp[L] == INF) {   // 涂不满所有字母
        cout << -1 << "\n";
        return;
    }

    // 从终点 L 沿前驱回溯，倒序收集方案
    int cnt = 0;
    int cur = L;
    while (cur > 0) {
        cnt++;
        ans_w[cnt] = pre_w[cur];
        ans_p[cnt] = pre_p[cur] + 1;   // 转成 1 起位置
        cur = pre_i[cur];
    }

    cout << cnt << "\n";
    for (int k = cnt; k >= 1; k--) {   // 回溯到的顺序是反的，倒着输出
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
