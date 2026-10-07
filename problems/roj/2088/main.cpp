/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:33
 * update_at: 2026-10-06 12:33
 */
#include <bits/stdc++.h>
typedef long long ll;

const ll MAXN = 1205;   // 输入行数上限（N < 1200）
const ll INF = 1e9;
const ll NUMC = 27;     // 字符集大小：空格 + 26 个小写字母

ll f_cnt;                                 // 字体文件行数（540）
ll n;                                     // 待识别图像的行数
ll font[NUMC][20];                        // font[c][r]：字符 c 的字模第 r 行压缩成的整数
ll inp[MAXN];                             // inp[i]：输入第 i 行压缩成的整数
ll diff[MAXN][NUMC][20];                  // diff[i][c][r]：输入第 i 行与字符 c 第 r 行的汉明距离
ll dp[MAXN];                              // dp[i]：匹配完前 i 行图像的最小总错误位代价
ll pre[MAXN];                             // pre[i]：dp[i] 的最优前驱状态
char ch[MAXN];                            // ch[i]：转移到状态 i 时识别出的字符
char ans[MAXN];                           // 回溯得到的结果串
ll ans_len;

char CHARS[NUMC + 1] = " abcdefghijklmnopqrstuvwxyz";

// 从字符串 s 读一个 20 位 01 串，压缩成整数
ll to_bits(char *s) {
    ll v = 0;
    for (ll i = 0; i < 20; ++i) {
        v = v * 2 + (s[i] - '0');
    }
    return v;
}

// 当前字符占 20 行：一一对应匹配，返回最优代价和字符编号
ll calc20(ll st, ll &best_c) {
    ll best = INF;
    for (ll c = 0; c < NUMC; ++c) {
        ll cost = 0;
        for (ll r = 0; r < 20; ++r) cost += diff[st + r][c][r];
        if (cost < best) {
            best = cost;
            best_c = c;
        }
    }
    return best;
}

// 当前字符占 19 行：枚举字模中被遗漏的行号 k，滑动增量更新求最小代价
ll calc19(ll st, ll &best_c) {
    ll best = INF;
    for (ll c = 0; c < NUMC; ++c) {
        // 初始 k=0：输入前 19 行对应字模第 1..19 行
        ll cost = 0;
        for (ll r = 0; r < 19; ++r) cost += diff[st + r][c][r + 1];
        ll min_c = cost;
        // k 从 0 增到 18：输入第 k 行改为对应字模第 k 行（原来对应第 k+1 行）
        for (ll k = 0; k < 19; ++k) {
            cost += diff[st + k][c][k] - diff[st + k][c][k + 1];
            if (cost < min_c) min_c = cost;
        }
        if (min_c < best) {
            best = min_c;
            best_c = c;
        }
    }
    return best;
}

// 当前字符占 21 行：枚举字模中被复制的行号 k，用前后缀和 O(1) 求每种 k 的代价
ll calc21(ll st, ll &best_c) {
    ll best = INF;
    for (ll c = 0; c < NUMC; ++c) {
        ll pref[22], suff[22];
        // pref[k] = 输入前 k 行与字模前 k 行的差异和
        pref[0] = 0;
        for (ll r = 0; r < 20; ++r) pref[r + 1] = pref[r] + diff[st + r][c][r];
        // suff[k] = 输入第 k..20 行与字模第 k-1..19 行的差异和
        suff[21] = 0;
        for (ll r = 20; r >= 1; --r) suff[r] = suff[r + 1] + diff[st + r][c][r - 1];
        ll min_c = INF;
        for (ll k = 0; k < 20; ++k) {
            // 第 k、k+1 行都来自字模第 k 行，只算损坏较小的一行
            ll cost = pref[k] + std::min(diff[st + k][c][k], diff[st + k + 1][c][k]) + suff[k + 2];
            if (cost < min_c) min_c = cost;
        }
        if (min_c < best) {
            best = min_c;
            best_c = c;
        }
    }
    return best;
}

void solve() {
    std::cin >> f_cnt;
    static char s[64];
    for (ll i = 0; i < f_cnt; ++i) {
        std::cin >> s;
        // 字体共 541 行 = 1 行 N + 540 行图案，每 20 行是一个字符的字模
        if (i < NUMC * 20) font[i / 20][i % 20] = to_bits(s);
    }
    std::cin >> n;
    for (ll i = 0; i < n; ++i) {
        std::cin >> s;
        inp[i] = to_bits(s);
    }

    // 预处理每行与每个字模行的汉明距离：异或后数 1 的个数
    for (ll i = 0; i < n; ++i) {
        for (ll c = 0; c < NUMC; ++c) {
            for (ll r = 0; r < 20; ++r) {
                diff[i][c][r] = __builtin_popcountll(inp[i] ^ font[c][r]);
            }
        }
    }

    // 线性划分 DP：dp[i] 由 dp[i-19]、dp[i-20]、dp[i-21] 转移而来
    for (ll i = 1; i <= n; ++i) dp[i] = INF;
    dp[0] = 0;
    for (ll i = 0; i < n; ++i) {
        if (dp[i] >= INF) continue;
        ll c;
        if (i + 19 <= n) {
            ll cost = calc19(i, c);
            if (dp[i] + cost < dp[i + 19]) {
                dp[i + 19] = dp[i] + cost;
                pre[i + 19] = i;
                ch[i + 19] = CHARS[c];
            }
        }
        if (i + 20 <= n) {
            ll cost = calc20(i, c);
            if (dp[i] + cost < dp[i + 20]) {
                dp[i + 20] = dp[i] + cost;
                pre[i + 20] = i;
                ch[i + 20] = CHARS[c];
            }
        }
        if (i + 21 <= n) {
            ll cost = calc21(i, c);
            if (dp[i] + cost < dp[i + 21]) {
                dp[i + 21] = dp[i] + cost;
                pre[i + 21] = i;
                ch[i + 21] = CHARS[c];
            }
        }
    }

    // 从 n 逆序回溯，再把首部多余空格剥离后正序输出
    ll rev_len = 0;
    static char rev[MAXN];
    for (ll i = n; i > 0; i = pre[i]) {
        rev[rev_len++] = ch[i];
    }
    // ans[st..ans_len-1] 为正序文本，st 跳过开头的空格字符
    ll ans_len = 0;
    for (ll i = rev_len - 1; i >= 0; --i) ans[ans_len++] = rev[i];
    ll st = 0;
    while (st < ans_len - 1 && ans[st] == ' ') ++st;
    for (ll i = ans_len - 1; i >= st; --i) std::cout << ans[i];
    std::cout << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    solve();
    return 0;
}
