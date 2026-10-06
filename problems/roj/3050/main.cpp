/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:31
 * update_at: 2026-10-06 16:32
 */
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <cstddef>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int MAXN = 1005;                  // M、N 的上限
const ull MOD = (1ULL << 61) - 1;       // Mersenne 素数 2^61-1，二维哈希取模
const int BUFSZ = 1 << 20;              // 快速读入缓冲区大小

ll m, n, a, b, q;                       // 原矩阵行数、列数，询问矩阵行数、列数，询问个数
string grid[MAXN];                      // 原矩阵每一行（01 串）
ull rowhash[MAXN][MAXN];                // rowhash[i][j]：第 i 行第 j 列起长度为 b 的窗口指纹
ull pw2[2 * MAXN];                      // pw2[k] = 2^k mod MOD
ull H[MAXN];                            // H[j]：以当前行为底的 a 行窗口在第 j 列的指纹
map<ull, vector<int> > query_group;     // 询问指纹 -> 具有该指纹的询问下标列表（去重）
int ans[MAXN];                          // ans[i]：第 i 个询问的答案

char inbuf[BUFSZ];                      // 输入缓冲区
int inpos = 0, inlen = 0;

// 从缓冲区读入一个字符，缓冲区空时补读一块
inline char next_char() {
    if (inpos == inlen) {
        inlen = (int)fread(inbuf, 1, BUFSZ, stdin);
        inpos = 0;
        if (inlen == 0) return '\0';
    }
    return inbuf[inpos++];
}

// 读入一个非负整数
ll read_int() {
    char c = next_char();
    while (c < '0' || c > '9') c = next_char();
    ll x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = next_char();
    }
    return x;
}

// 2^61-1 下的乘法，用 __int128 承接中间结果防止溢出
ull mul_mod(ull x, ull y) {
    return (ull)((unsigned __int128)x * y % MOD);
}

// (x - y) mod MOD
ull sub_mod(ull x, ull y) {
    return x >= y ? x - y : x + MOD - y;
}

// 读入长度为 len 的 01 串（跳过空白），返回其按位拼成的整数 mod MOD
ull read_row_hash(ll len) {
    ull h = 0;
    ll done = 0;
    while (done < len) {
        ll take = len - done;
        if (take > 30) take = 30;       // 每 30 位成块，减少取模次数
        ull block = 0;
        for (ll k = 0; k < take; k++) {
            char c = next_char();
            while (c < '0' || c > '1') c = next_char();
            block = block * 2 + (c - '0');
        }
        h = (mul_mod(h, pw2[take]) + block) % MOD;
        done += take;
    }
    return h;
}

// 读入 q 个询问矩阵，各自按行主序折叠成一个指纹，相同指纹的询问合并到一组
void read_queries() {
    q = read_int();
    for (int i = 1; i <= q; i++) {
        ull h = 0;
        for (ll r = 1; r <= a; r++) {
            ull rowval = read_row_hash(b);  // 这一行 b 个字符拼成的 b 位整数
            h = (mul_mod(h, pw2[b]) + rowval) % MOD;
        }
        query_group[h].push_back(i);
    }
}

int main() {
    m = read_int();
    n = read_int();
    a = read_int();
    b = read_int();
    for (ll i = 1; i <= m; i++) {
        grid[i].reserve(n);
        for (ll j = 0; j < n; j++) {
            char c = next_char();
            while (c < '0' || c > '1') c = next_char();
            grid[i].push_back(c);
        }
    }

    pw2[0] = 1;
    for (int k = 1; k < 2 * MAXN; k++) pw2[k] = pw2[k - 1] * 2 % MOD;

    read_queries();

    if (a > m || b > n) {               // 询问矩阵比原矩阵还大，任何位置都放不下
        for (int i = 1; i <= q; i++) printf("0\n");
        return 0;
    }

    ll ncol = n - b + 1;                // 每行横向长度为 b 的窗口个数
    // 第一步：每行用滑动窗口求出所有 b 位窗口指纹
    for (ll i = 1; i <= m; i++) {
        ull val = 0;
        for (ll c = 0; c < b; c++) val = (val * 2 + (grid[i][c] - '0')) % MOD;
        rowhash[i][1] = val;
        for (ll j = 1; j < ncol; j++) {
            ull del = (grid[i][j - 1] == '1') ? pw2[b - 1] : 0; // 左端最高位
            ull mid = sub_mod(rowhash[i][j], del);
            rowhash[i][j + 1] = (mid * 2 + (grid[i][j + b - 1] - '0')) % MOD;
        }
    }

    // 第二步：竖向按 2^b 进制折叠，顶行权最大；滑动时每列 O(1) 维护
    ull pwB = pw2[b];
    ull pwTop = 1;                      // 顶行的权 pwB^(a-1)
    for (ll k = 1; k <= a - 1; k++) pwTop = mul_mod(pwTop, pwB);

    for (ll j = 1; j <= ncol; j++) {
        ull h = 0;
        for (ll i = 1; i <= a; i++) h = (mul_mod(h, pwB) + rowhash[i][j]) % MOD;
        H[j] = h;
    }

    for (ll r = a; r <= m; r++) {       // r 为当前 a×b 子矩阵的底行
        if (r > a) {
            ll out = r - a;             // 滑出的行
            ll in = r;                  // 滑入的行
            for (ll j = 1; j <= ncol; j++) {
                ull outv = mul_mod(rowhash[out][j], pwTop);
                ull mid = sub_mod(H[j], outv);
                H[j] = (mul_mod(mid, pwB) + rowhash[in][j]) % MOD;
            }
        }
        for (ll j = 1; j <= ncol; j++) {
            map<ull, vector<int> >::iterator it = query_group.find(H[j]);
            if (it != query_group.end()) {
                for (size_t t = 0; t < it->second.size(); t++) ans[it->second[t]] = 1;
                query_group.erase(it);  // 该指纹已命中，后续无需再查
            }
        }
        if (query_group.empty()) break; // 所有询问都已找到
    }

    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}
