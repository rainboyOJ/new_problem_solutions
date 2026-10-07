// ROJ 1796《斐波那契串》
// ---------------------------------------------------------------------------
// 题意（题面见 problem.md）：
//   S[0]="0", S[1]=? , S[i]=S[i-2]+S[i-1]（字符串拼接）。
//   给定 N,M,P 与长度 M 的 0/1 串 T，求 T 在 S[N] 中作为子串的出现次数（可重叠）mod P。
//
// 【题面笔误】content.md 写 “S[1]="0"”，但若 S[0]=S[1]="0" 则所有 S[i] 全为 0，
//   样例 T="101" 在 S[7] 中不可能出现 8 次（恒为 0），与样例输出 8 矛盾。
//   结合真实数据 problem8（N=10^9, M=1, T="1"，答案非 0）可确认正确初值是
//   S[0]="0", S[1]="1"（即经典 Fibonacci word）。本题按此建模。
//
// 【算法】O(M + log N)
//   记 f[i] = T 在 S[i] 中的出现次数。S[i]=S[i-2]S[i-1]，故
//       f[i] = f[i-2] + f[i-1] + cross[i],
//   cross[i] 为“跨越拼接缝”的出现次数（起点落在左块 S[i-2] 内、终点落在右块 S[i-1] 内）。
//   跨界的匹配只可能向左伸入 M-1 个字符、向右伸入 M-1 个字符，因此 cross[i] 只由
//   suffix_{M-1}(S[i-2]) 与 prefix_{M-1}(S[i-1]) 决定。
//   取最小的 K 使 |S[K]| >= M-1（M<=10^4 保证 K<=21）：
//     * S[i] 以 S[i-1] 结尾 => 对 i>=K+1，suffix_{M-1}(S[i]) 恒等于 suffix_{M-1}(S[K])，恒定；
//     * S[i] 以 S[i-2] 开头 => 对 i>=K+2，prefix_{M-1}(S[i]) = prefix_{M-1}(S[i-2])，只与奇偶有关。
//   于是对 i>=K+3，cross[i] 只随 i 的奇偶取两个定值，即 cross[i]=cross[i+2]。
//
//   实现上不手推前后缀，直接暴力构造 S[0..min(N,K+5)] 并用 KMP 数出精确的 f[i]，
//   再用容斥反推两个常数：cEven = f[e]-f[e-1]-f[e-2]，cOdd = f[e+1]-f[e]-f[e-1]（e 为 >=K+3 的偶数）。
//   之后按“步长 2”递推（a_k=f[e+2k]，b_k=f[e+2k+1]）：
//       a_{k+1} = a_k + b_k + cEven
//       b_{k+1} = a_k + 2*b_k + cEven + cOdd
//   写成 3x3 转移矩阵，对 (a,b,1) 做快速幂，指数 k=(N-e)/2，O(27 log N)。
//
// 【来源】本题素材源带 data.py 生成脚本，data/ 为自造数据；std.cpp 与本实现独立，
//   算法思路一致（均为“前后缀稳定 + 跨界计数 + 矩阵快速幂”）。正确性以 10 个真实点为准。
// ---------------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

static ll N, P;      // N 为迭代次数，P 为模数
static int M;        // 模式串长度
static string T;     // 模式串

static vector<int> piArr;  // T 的失配数组（前缀函数）

// 预处理 T 的前缀函数，O(M)
static void buildPi() {
    piArr.assign(M, 0);
    for (int i = 1; i < M; i++) {
        int j = piArr[i - 1];
        while (j > 0 && T[i] != T[j]) j = piArr[j - 1];
        if (T[i] == T[j]) j++;
        piArr[i] = j;
    }
}

// 统计 T 在 s 中的出现次数（允许重叠），O(|s|)
static ll countOcc(const string &s) {
    if ((ll)s.size() < (ll)M) return 0;
    ll cnt = 0;
    int j = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        while (j > 0 && s[i] != T[j]) j = piArr[j - 1];
        if (s[i] == T[j]) j++;
        if (j == M) { cnt++; j = piArr[j - 1]; }
    }
    return cnt;
}

// 3x3 矩阵（mod P）
struct Mat {
    ll a[3][3];
    Mat() { memset(a, 0, sizeof(a)); }
};

static Mat mul(const Mat &x, const Mat &y) {
    Mat r;
    for (int i = 0; i < 3; i++)
        for (int k = 0; k < 3; k++) {
            if (!x.a[i][k]) continue;
            for (int j = 0; j < 3; j++)
                r.a[i][j] = (ll)((r.a[i][j] + (lll)x.a[i][k] * y.a[k][j]) % P);
        }
    return r;
}

static Mat matPow(Mat b, ll e) {
    Mat r;
    for (int i = 0; i < 3; i++) r.a[i][i] = 1 % P;   // P=1 时单位元取 0，保持模意义一致
    while (e > 0) {
        if (e & 1) r = mul(r, b);
        b = mul(b, b);
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> N >> M >> P)) return 0;
    cin >> T;
    if ((int)T.size() != M) T.resize(M, '0');  // 容错：输入串长度应与 M 一致

    buildPi();

    // 求最小的 K 使 |S[K]| >= M-1（长度迅速超过 M-1 <= 9999，K <= 21）
    vector<ll> len;
    len.push_back(1);   // S[0] = "0"
    len.push_back(1);   // S[1] = "1"
    int K = 0;
    for (int i = 0;; i++) {
        if (i >= 2) len.push_back(len[i - 1] + len[i - 2]);
        if (len[i] >= (ll)M - 1) { K = i; break; }
    }

    // 需要构造的串下标上界：min(N, K+5)（K+5 保证 a0,b0 与两个常数都可用）
    ll need = min<ll>(N, (ll)K + 5);
    vector<string> S;
    S.push_back("0");
    if (need >= 1) S.push_back("1");
    while ((ll)S.size() - 1 < need) {
        int c = (int)S.size() - 1;
        S.push_back(S[c - 1] + S[c]);
    }

    // 暴力统计精确的 f[i]（不取模，最大也才 |S[K+5]| ~ 2*10^5）
    vector<ll> f(need + 1, 0);
    for (ll i = 0; i <= need; i++) f[i] = countOcc(S[(int)i]);

    if (N <= need) {   // 小 N：直接输出
        cout << (f[N] % P) << "\n";
        return 0;
    }

    // 现在必有 N > K+5，长度足够，跨界计数已进入周期 2 的稳定区
    ll e = ((K + 3) % 2 == 0) ? (ll)(K + 3) : (ll)(K + 4);   // 第一个 >= K+3 的偶数下标
    ll a0 = f[e], b0 = f[e + 1];
    ll cEven = f[e] - f[e - 1] - f[e - 2];          // cross[e]
    ll cOdd  = f[e + 1] - f[e] - f[e - 1];          // cross[e+1]

    Mat base;
    base.a[0][0] = 1 % P;  base.a[0][1] = 1 % P;  base.a[0][2] = ((cEven % P) + P) % P;
    base.a[1][0] = 1 % P;  base.a[1][1] = 2 % P;  base.a[1][2] = (((cEven + cOdd) % P) + P) % P;
    base.a[2][2] = 1 % P;

    ll steps = (N - e) / 2;
    Mat R = matPow(base, steps);

    ll va = (ll)(((lll)R.a[0][0] * (a0 % P) + (lll)R.a[0][1] * (b0 % P) + R.a[0][2]) % P);
    ll vb = (ll)(((lll)R.a[1][0] * (a0 % P) + (lll)R.a[1][1] * (b0 % P) + R.a[1][2]) % P);

    ll ans = ((N - e) % 2 == 0) ? va : vb;
    ans = ((ans % P) + P) % P;
    cout << ans << "\n";
    return 0;
}
