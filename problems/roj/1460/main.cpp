/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:35
 * update_at: 2026-10-05 02:35
 */

// 求子串最短循环节：字符串哈希 O(1) 检验周期 + 线性筛最小质因数分解贪心试除。
#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 500005;   // 字符串最大长度
const ll MOD = 1000000007; // 哈希模数
const ll BASE = 131;       // 哈希进制

int n, q; // n <= 5e5, q <= 2e6，都在 int 范围内
char s[MAXN];     // 原字符串，下标从 1 开始
ll hsh[MAXN];     // hsh[i] = s[1..i] 的前缀哈希值
ll pw[MAXN];      // pw[i] = BASE^i mod MOD
int minp[MAXN];   // minp[x] = x 的最小质因数（线性筛预处理）
int primes[MAXN]; // 线性筛筛出的质数表（个数约 41538，开 MAXN 足够）

// ---------- 快读：一次性读入整个输入 ----------
char ibuf[1 << 25]; // 输入约 24MB，缓冲区开 32MB
int ipos = 0, ilen = 0;

// 读入一个非负整数
ll read_num() {
    while (ipos < ilen && (ibuf[ipos] < '0' || ibuf[ipos] > '9')) ipos++;
    ll x = 0;
    while (ipos < ilen && ibuf[ipos] >= '0' && ibuf[ipos] <= '9') {
        x = x * 10 + (ibuf[ipos] - '0');
        ipos++;
    }
    return x;
}

// ---------- 快写：一次性输出所有答案 ----------
char obuf[1 << 24]; // q 行答案，每行最多 7 字节，16MB 足够
int opos = 0;

void write_num(ll x) {
    char tmp[24];
    int len = 0;
    if (x == 0) tmp[len++] = '0';
    while (x > 0) {
        tmp[len++] = '0' + x % 10;
        x /= 10;
    }
    while (len > 0) obuf[opos++] = tmp[--len];
    obuf[opos++] = '\n';
}

// 取 s[l..r] 的哈希值
ll get_hash(int l, int r) {
    return (hsh[r] - hsh[l - 1] * pw[r - l + 1] % MOD + MOD) % MOD;
}

// 判断 k 是否为 s[a..b] 的循环节：
// 等价于去掉末尾 k 个字符的前缀与去掉开头 k 个字符的后缀完全相同
bool check(int a, int b, int k) {
    return get_hash(a, b - k) == get_hash(a + k, b);
}

// 线性筛预处理 [2, n] 内每个数的最小质因数
void sieve() {
    int cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes[cnt++] = i;
        }
        for (int j = 0; j < cnt && (ll)primes[j] * i <= n; j++) {
            minp[primes[j] * i] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
}

int facs[40]; // 临时存放当前区间长度的质因子（含重数，最多约 20 个）

int main() {
    ilen = fread(ibuf, 1, sizeof(ibuf), stdin);

    n = read_num();
    // 读入字符串，跳过非小写字母
    while (ipos < ilen && (ibuf[ipos] < 'a' || ibuf[ipos] > 'z')) ipos++;
    for (int i = 1; i <= n; i++) s[i] = ibuf[ipos++];
    q = read_num();

    // 预处理前缀哈希与幂次
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i - 1] * BASE % MOD;
        hsh[i] = (hsh[i - 1] * BASE + s[i]) % MOD;
    }
    sieve();

    for (int t = 0; t < q; t++) {
        int a = read_num();
        int b = read_num();
        int L = b - a + 1; // 询问子串长度

        // 沿最小质因数分解 L，得到全部质因子（含重数）
        int fc = 0;
        for (int x = L; x > 1; x /= minp[x]) facs[fc++] = minp[x];

        // 贪心试除：循环节长度集合对 gcd 封闭，从 L 开始尽量除去质因子
        int ans = L;
        for (int i = 0; i < fc; i++) {
            int cand = ans / facs[i];
            if (check(a, b, cand)) ans = cand;
        }
        write_num(ans);
    }

    fwrite(obuf, 1, opos, stdout);
    return 0;
}
