/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:38
 * update_at: 2026-11-11 00:38
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 选取用于周期预筛选的较小质数 P0，以及两个用于精准双哈希验证的大质数 P1, P2
const int P0 = 21893;
const int P1 = 1000000007;
const int P2 = 1000000009;

const int MAXN = 105;

int n, m;
long long a0[MAXN], a1[MAXN], a2[MAXN];
bool ok_mod[P0];

// 在读入高达 10000 位的超大系数时，边读字符流边对模数取模
bool read_big(long long& v0, long long& v1, long long& v2) {
    char c = 0;
    while (cin.get(c) && (c == ' ' || c == '\n' || c == '\r'));
    if (!cin) return false;

    bool neg = false;
    if (c == '-') {
        neg = true;
        c = cin.get();
    }

    v0 = 0; v1 = 0; v2 = 0;
    while (c >= '0' && c <= '9') {
        int d = c - '0';
        v0 = (v0 * 10 + d) % P0;
        v1 = (v1 * 10 + d) % P1;
        v2 = (v2 * 10 + d) % P2;
        c = cin.get();
    }

    if (neg) {
        v0 = (P0 - v0) % P0;
        v1 = (P1 - v1) % P1;
        v2 = (P2 - v2) % P2;
    }
    return true;
}

// 秦九韶算法求多项式在模 P 下的值
long long eval_poly(int x, const long long* a, int mod) {
    long long res = 0;
    for (int i = n; i >= 0; --i) {
        res = (res * x + a[i]) % mod;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i <= n; ++i) {
        read_big(a0[i], a1[i], a2[i]);
    }

    // 第一步：在较小模数 P0 下预处理所有余数 r in [0, P0 - 1] 的值
    // 由于同余性质 x = r (mod P0) 时必有 f(x) = f(r) (mod P0)
    for (int r = 0; r < P0; ++r) {
        if (eval_poly(r, a0, P0) == 0) {
            ok_mod[r] = true;
        }
    }

    // 第二步：遍历 [1, m]，先用 P0 余数快速排除，再用大双质数双重验证
    vector<int> ans;
    for (int x = 1; x <= m; ++x) {
        if (!ok_mod[x % P0]) continue; // 快速剪枝

        if (eval_poly(x, a1, P1) == 0 && eval_poly(x, a2, P2) == 0) {
            ans.push_back(x);
        }
    }

    cout << ans.size() << "\n";
    for (int x : ans) {
        cout << x << "\n";
    }

    return 0;
}
