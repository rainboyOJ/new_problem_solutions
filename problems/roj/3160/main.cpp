/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <cstdio>
using namespace std;

typedef long long ll;

// 答案可达 2^(50*49/2) = 2^1225，约 369 位十进制，超出 64 位整数，必须自己写大整数。
// 用 10^4 进制：一段一个「万进制位」，逐段存低位在前，段与段相乘不超过 1e8，不会溢出。
const ll BASE = 10000;
const int MAXSEG = 260;

struct Big {
    int len;        // 段数，len = 0 表示数值 0
    ll seg[MAXSEG]; // 低位在前，每段小于 BASE
};

Big big_small(ll v) {
    Big r;
    r.len = 0;
    while (v > 0) {
        r.seg[r.len] = v % BASE;
        r.len++;
        v /= BASE;
    }
    return r;
}

Big big_add(Big a, Big b) {
    Big r;
    r.len = a.len > b.len ? a.len : b.len;
    ll carry = 0;
    for (int i = 0; i < r.len; i++) {
        ll v = carry;
        if (i < a.len) v += a.seg[i];
        if (i < b.len) v += b.seg[i];
        r.seg[i] = v % BASE;
        carry = v / BASE;
    }
    if (carry > 0) {
        r.seg[r.len] = carry;
        r.len++;
    }
    return r;
}

// 减法，调用者保证 a >= b（本题里被减数是「全部无向图个数」，一定不小于被扣掉的和）
Big big_sub(Big a, Big b) {
    Big r;
    r.len = a.len;
    ll borrow = 0;
    for (int i = 0; i < a.len; i++) {
        ll v = a.seg[i] - borrow;
        if (i < b.len) v -= b.seg[i];
        if (v < 0) {
            v += BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }
        r.seg[i] = v;
    }
    while (r.len > 0 && r.seg[r.len - 1] == 0) r.len--;
    return r;
}

Big big_mul(Big a, Big b) {
    Big r;
    r.len = 0;
    if (a.len == 0 || b.len == 0) return r;
    ll acc[2 * MAXSEG];
    int total = a.len + b.len;
    for (int i = 0; i < total; i++) acc[i] = 0;
    for (int i = 0; i < a.len; i++)
        for (int j = 0; j < b.len; j++) acc[i + j] += a.seg[i] * b.seg[j];
    for (int i = 0; i < total; i++) { // 逐段进位，低位段处理完就再也不会变
        ll carry = acc[i] / BASE;
        acc[i] %= BASE;
        if (i + 1 < total) acc[i + 1] += carry;
    }
    r.len = total;
    while (r.len > 0 && acc[r.len - 1] == 0) r.len--;
    for (int i = 0; i < r.len; i++) r.seg[i] = acc[i];
    return r;
}

void big_print(Big a) {
    if (a.len == 0) {
        printf("0\n");
        return;
    }
    printf("%lld", a.seg[a.len - 1]);
    for (int i = a.len - 2; i >= 0; i--) printf("%04lld", a.seg[i]);
    printf("\n");
}

const int MAXN = 50;

Big graph[MAXN + 1];  // graph[n]：n 个标号点的任意无向图个数，每条可能边独立取舍，共 2^(n(n-1)/2)
Big conn[MAXN + 1];   // conn[n]：n 个标号点的连通无向图个数
ll binom[MAXN + 1][MAXN + 1]; // 组合数，最大 C(49,24) 仍在 64 位内

// n 个标号点的任意无向图个数：每条可能边独立取舍
Big graph_count(ll n) {
    ll edges = n * (n - 1) / 2;
    Big r = big_small(1);
    Big two = big_small(2);
    for (ll i = 0; i < edges; i++) r = big_mul(r, two);
    return r;
}

int main() {
    for (int i = 0; i <= MAXN; i++) { // 杨辉三角求组合数
        binom[i][0] = 1;
        for (int j = 1; j <= i; j++)
            binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
    }
    graph[0] = big_small(1);
    for (int n = 1; n <= MAXN; n++) graph[n] = graph_count(n);

    // conn[n] = 全部无向图个数 - 1 号点所在连通块大小 k < n 的分类情形：
    // 选 k-1 个同伴 C(n-1,k-1)，块内连通 conn[k]，块外任意 graph[n-k]
    for (int n = 1; n <= MAXN; n++) {
        Big sum = big_small(0);
        for (int k = 1; k < n; k++) {
            Big term = big_mul(big_small(binom[n - 1][k - 1]), conn[k]);
            term = big_mul(term, graph[n - k]);
            sum = big_add(sum, term);
        }
        conn[n] = big_sub(graph[n], sum);
    }

    ll n;
    // 输入多组，0 表示输入终止（0 本身不产生输出行）
    while (scanf("%lld", &n) == 1) {
        if (n == 0) break;
        big_print(conn[n]);
    }
    return 0;
}
