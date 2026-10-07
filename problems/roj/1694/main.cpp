/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:45
 * update_at: 2026-10-07 15:50
 */
// main.cpp：回文串（一本通 1694）。
//
// 记 A_x 为 A 的第 x 长后缀（长度 n-x+1），B_y 为 B 的第 y 长前缀（长度 m-y+1）。
// 对询问 (x,y) 取 st = x-1、L = m-y+1、P = LCP(A[st..], rev(B)[y-1..])，把方案按 |S|、|T| 分类：
//   |S| <= |T|：匹配段要求 |S| <= P，去掉末尾 |S| 个字符后剩下的中段须回文，
//               于是每个 p = 1..P 贡献 cntB[L-p]+1 种，合计 sum_{e=L-P}^{L-1}(cntB[e]+1)；
//   |S| >  |T|：匹配段要求 |T| <= P，去掉开头 |T| 个字符后剩下的中段须回文，
//               于是每个 q = 1..P 贡献 fA[st+q] 种，合计 sum_{q=1}^{P} fA[st+q]。
// 其中 cntB[e] = B[1..e] 的非空回文后缀个数，fA[i] = A[i..] 的非空回文前缀个数，
// 两者都用 Manacher + 差分数组预处理成前缀和，做到 O(1) 求区间和；
// 唯一的动态量 P 用双底数哈希 + 二分求出。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 800005; // |A|、|B| 的上界 8*10^5

char strA[MAXN]; // 原串 A
char strB[MAXN]; // 原串 B
char strR[MAXN]; // rev(B)：B_y 的匹配方向正好是 B 的逆序，于是把 B 反过来当第二个串

int n, m; // |A|、|B|

int d1[MAXN]; // Manacher 奇回文半径：d1[i] 表示 s[i] 为中心的最长奇回文半径
int d2[MAXN]; // Manacher 偶回文半径：d2[i] 表示 s[i-1]、s[i] 为中心的最长偶回文半径

ll diff[MAXN]; // 差分数组：把每个回文串对"起点集合 / 终点集合"的贡献压成一次区间加

ll cntStart[MAXN]; // cntStart[i] = A[i..] 的非空回文前缀个数（1-based，i=1..n；cntStart[n+1]=0）
ll preStart[MAXN]; // preStart[i] = cntStart[1..i] 的前缀和
ll cntEnd[MAXN];   // cntEnd[e] = B[1..e] 的非空回文后缀个数（e=0..m，cntEnd[0]=0）
ll preEnd[MAXN];   // preEnd[k] = sum_{e=0}^{k-1} (cntEnd[e]+1)

// 双底数滚动哈希，模 2^64 自然溢出；hash[0] 用 BASE1、hash[1] 用 BASE2
const unsigned long long BASE1 = 1315423911ULL;
const unsigned long long BASE2 = 2654435761ULL;
unsigned long long hashA[2][MAXN]; // hashA[k][i] = A 前 i 个字符的哈希值
unsigned long long hashR[2][MAXN]; // hashR[k][i] = rev(B) 前 i 个字符的哈希值
unsigned long long power[2][MAXN]; // power[k][i] = BASE_{k+1}^i

// Manacher：求串 s 的奇偶回文半径，结果放进全局 d1/d2，两个串依次复用
void manacher(const char *s, int len) {
    for (int i = 0, l = 0, r = -1; i < len; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < len && s[i - k] == s[i + k]) k++;
        d1[i] = k;
        if (i + k - 1 > r) { l = i - k + 1; r = i + k - 1; }
    }
    for (int i = 0, l = 0, r = -1; i < len; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < len && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k;
        if (i + k - 1 > r) { l = i - k; r = i + k - 1; }
    }
}

// 预处理 fA：把"每个回文子串给它的起点记一次"用差分数组摊平，再取前缀和
void build_start(const char *s, int len) {
    manacher(s, len);
    for (int i = 0; i <= len + 1; i++) diff[i] = 0;
    for (int i = 0; i < len; i++) {
        // 奇回文 s[i-k+1..i+k-1]，k=1..d1[i]：起点落在 [i-d1[i]+1, i]
        diff[i - d1[i] + 1] += 1;
        diff[i + 1] -= 1;
        // 偶回文 s[i-k..i+k-1]，k=1..d2[i]：起点落在 [i-d2[i], i-1]
        if (d2[i] > 0) {
            diff[i - d2[i]] += 1;
            diff[i] -= 1;
        }
    }
    ll cur = 0;
    for (int i = 0; i < len; i++) {
        cur += diff[i];
        cntStart[i + 1] = cur; // 起点 i（0-based）对应 1-based 下标 i+1
    }
    cntStart[len + 1] = 0; // 空后缀没有回文前缀，正好支持 x+P = n+1 的取值
    preStart[0] = 0;
    for (int i = 1; i <= len + 1; i++) preStart[i] = preStart[i - 1] + cntStart[i];
}

// 预处理 cntB：回文串给它的结束位置记一次；再写成 preEnd[k] = sum_{e<k}(cntB[e]+1)
void build_end(const char *s, int len) {
    manacher(s, len);
    for (int i = 0; i <= len + 1; i++) diff[i] = 0;
    for (int i = 0; i < len; i++) {
        // 奇回文结束位置 e 落在 [i+1, i+d1[i]]（e 为 1-based 的结束下标）
        diff[i + 1] += 1;
        diff[i + d1[i] + 1] -= 1;
        // 偶回文 s[i-k..i+k-1]，k=1..d2[i]：结束位置同样是 [i+1, i+d2[i]]
        if (d2[i] > 0) {
            diff[i + 1] += 1;
            diff[i + d2[i] + 1] -= 1;
        }
    }
    ll cur = 0;
    cntEnd[0] = 0;
    for (int e = 1; e <= len; e++) {
        cur += diff[e];
        cntEnd[e] = cur;
    }
    preEnd[0] = 0;
    for (int k = 1; k <= len + 1; k++) preEnd[k] = preEnd[k - 1] + cntEnd[k - 1] + 1;
}

// 对串 s 建双底数滚动哈希，h[k][i] 表示 s 前 i 个字符的哈希值
void build_hash(unsigned long long h[2][MAXN], const char *s, int len) {
    for (int k = 0; k < 2; k++) {
        unsigned long long base = (k == 0 ? BASE1 : BASE2);
        h[k][0] = 0;
        for (int i = 0; i < len; i++) h[k][i + 1] = h[k][i] * base + (unsigned char)s[i];
    }
}

// 两套底数的幂表，长度到 max(|A|,|B|)
void build_power(int len) {
    for (int k = 0; k < 2; k++) {
        unsigned long long base = (k == 0 ? BASE1 : BASE2);
        power[k][0] = 1;
        for (int i = 1; i <= len; i++) power[k][i] = power[k][i - 1] * base;
    }
}

// 哈希判等：A[l..l+len-1] 与 rev(B)[r..r+len-1] 是否相同（两套底数都过才算相同）
bool same_hash(int l, int r, int len) {
    for (int k = 0; k < 2; k++) {
        unsigned long long x = hashA[k][l + len] - hashA[k][l] * power[k][len];
        unsigned long long y = hashR[k][r + len] - hashR[k][r] * power[k][len];
        if (x != y) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string dtype;
    if (!(cin >> dtype)) return 0; // 第一行是数据类型，本题的算法与它无关
    cin >> strA >> strB;
    n = strlen(strA);
    m = strlen(strB);
    for (int i = 0; i < m; i++) strR[i] = strB[m - 1 - i]; // rev(B)

    build_start(strA, n);
    build_end(strB, m);
    build_power(max(n, m));
    build_hash(hashA, strA, n);
    build_hash(hashR, strR, m);

    int q;
    cin >> q;
    string out;
    out.reserve((size_t)q * 16);
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        int st = x - 1;        // A_x 在 A 中的起点（0-based）
        int L = m - y + 1;     // B_y 的长度
        int limit = min(n - st, L); // P 的上界：两个串都要取得到这么长的前缀

        // 二分求 P = LCP(A[st..], rev(B)[y-1..])
        int lo = 0, hi = limit;
        while (lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if (same_hash(st, y - 1, mid)) lo = mid;
            else hi = mid - 1;
        }

        ll ans = (preEnd[L] - preEnd[L - lo]) + (preStart[x + lo] - preStart[x]);
        out += to_string(ans);
        out += '\n';
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
