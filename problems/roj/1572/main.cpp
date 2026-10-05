/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:17
 * update_at: 2026-10-05 09:17
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;
const ll INF = 0x3f3f3f3f3f3f3f3fLL; // 转移中的无穷大，表示当前无法匹配

char s[MAXN];    // 输入的括号串，下标从 0 开始
ll n;            // 括号串长度
ll dp[MAXN][MAXN]; // dp[i][j] 表示把子串 s[i..j] 补齐为合法括号序列所需添加的最少字符数

// 判断左右两个字符能否配成一对括号。
bool matched(char left, char right) {
    if (left == '(' && right == ')') return true;
    if (left == '[' && right == ']') return true;
    return false;
}

void solve() {
    if (n == 0) {
        cout << 0 << "\n";
        return;
    }

    // 长度为 1 的区间自己无法配对，必须补一个括号
    for (ll i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    // 按区间长度从小到大递推，保证子区间已算好
    for (ll len = 2; len <= n; len++) {
        for (ll i = 0; i + len - 1 < n; i++) {
            ll j = i + len - 1;
            ll best = INF;

            // 两端匹配：用 s[i]、s[j] 作最外层括号，代价等于内部子串的代价
            if (matched(s[i], s[j])) {
                best = dp[i + 1][j - 1]; // i >= j-1 时该位置没算过，全局默认为 0，正好是空串代价
            }

            // 枚举分割点，把区间拆成 s[i..k] 与 s[k+1..j] 两段分别补齐再拼接
            for (ll k = i; k < j; k++) {
                ll candidate = dp[i][k] + dp[k + 1][j];
                if (candidate < best) {
                    best = candidate;
                }
            }

            dp[i][j] = best;
        }
    }

    cout << dp[0][n - 1] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    n = strlen(s);

    solve();

    return 0;
}
