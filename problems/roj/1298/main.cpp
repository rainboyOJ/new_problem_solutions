/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:25
 * update_at: 2026-10-05 08:25
 */
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXL = 1006; // 字符串长度 ≤ 1000，留一格存 '\0'

// dp[j] 表示把 a 的前 i 个字符变成 b 的前 j 个字符的最少操作次数
// 内层循环跑在较短串上，整体只用一行滚动数组
ll dp[MAXL];

char a_buf[MAXL];
char b_buf[MAXL];

// 计算 a 变成 b 的最少操作次数（编辑距离）
ll edit_distance(char *a, ll la, char *b, ll lb) {
    // 增与删互为反向操作，距离对称；让内层循环跑在短串上
    if (la < lb) {
        swap(a, b);
        ll t = la; la = lb; lb = t;
    }

    // 第 0 行：空 a 补齐 b 的前 j 个字符，代价 j
    for (ll j = 0; j <= lb; j++) {
        dp[j] = j;
    }

    for (ll i = 1; i <= la; i++) {
        ll diag = dp[0];   // 左上角：a 的前 i-1 个字符对上 b 的前 0 个字符
        dp[0] = i;          // 第 i 行边界：a 的前 i 个字符整段删空
        char ca = a[i - 1];
        for (ll j = 1; j <= lb; j++) {
            ll old = dp[j]; // 先取出「上」：它马上会被本行覆盖，留给下一格当「左上」
            if (ca == b[j - 1]) {
                dp[j] = diag; // 相同则白拿左上角
            } else {
                ll m = diag;
                if (old < m) m = old;
                if (dp[j - 1] < m) m = dp[j - 1];
                dp[j] = m + 1;
            }
            diag = old;
        }
    }
    return dp[lb];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int case_idx = 0; case_idx < n; case_idx++) {
        cin >> a_buf >> b_buf;
        ll la = strlen(a_buf);
        ll lb = strlen(b_buf);
        cout << edit_distance(a_buf, la, b_buf, lb) << "\n";
    }
    return 0;
}