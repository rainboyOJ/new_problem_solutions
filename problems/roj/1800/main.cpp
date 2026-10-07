/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 03:54
 * update_at: 2026-10-08 03:54
 */
// main.cpp：把 1..n 分成尽量少的集合，使每个集合的元素和都是质数。
// 记 S = n(n+1)/2。答案只可能是 -1（n=1）、1（S 为质数）、2（S 拆成两质数之和）
// 或 3（S 为奇数且 S-2 为合数时拆成 3 个质数之和，用哥德巴赫猜想的弱形式兜底）。
// 集合的构造用"从 n 往下贪心凑和"，因为 1..n 的连续整数一定能凑出任意不超过 S 的目标和。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 6000;         // 题面 n 的上限
const ll MAXS = 18003000;      // S 的上限：6000*6001/2
const int MAXP = 800;          // 不超过 6000 的质数个数（实际 783）

char comp[MAXS + 1];           // comp[x] = 1 表示 x 是合数（或 0/1），值域只有 0/1 用 char 省内存
int primeList[MAXP + 1];       // 不超过 n 的质数，升序
int primeCnt;
int belong[MAXN + 1];          // belong[i] = 自然数 i 所属的集合编号（1 起）

ll sum_all;                    // S = n(n+1)/2

// 埃氏筛，标记 [0, sum_all] 内的合数
void build_sieve() {
    comp[0] = comp[1] = 1;
    for (ll i = 2; i * i <= sum_all; i++) {
        if (comp[i]) continue;
        for (ll j = i * i; j <= sum_all; j += i) comp[j] = 1;
    }
}

// 收集不超过 n 的质数，供 cnt=3 分支挑 a、b 用
void build_primes(int n) {
    primeCnt = 0;
    for (int i = 2; i <= n; i++)
        if (!comp[i]) primeList[++primeCnt] = i;
}

// 从 n 往下贪心，把和为 target 的一组数标成集合 1；剩余的数保持集合 2
void greedy_split(int n, ll target) {
    ll rest = target;
    for (int i = n; i >= 1 && rest > 0; i--) {
        if (i <= rest) {           // 余量还装得下 i，就取走 i
            belong[i] = 1;
            rest -= i;
        }
    }
}

// 按题面格式输出归属数组，集合编号空间 [1, cnt]
void output(int n, int cnt) {
    printf("%d\n", cnt);
    for (int i = 1; i <= n; i++) printf("%d%c", belong[i], i == n ? '\n' : ' ');
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    if (n == 1) {                  // S = 1 既不是质数也无法再拆，唯一无解情形
        printf("-1\n");
        return 0;
    }

    sum_all = (ll)n * (n + 1) / 2;
    build_sieve();

    if (!comp[sum_all]) {          // S 自身是质数：全部数字放一个集合
        for (int i = 1; i <= n; i++) belong[i] = 1;
        output(n, 1);
        return 0;
    }

    // 找最小的质数 x 使 x 与 S-x 都是质数；找到了就能只拆两个集合
    ll pick = -1;
    for (ll x = 2; x <= sum_all / 2; x++) {
        if (!comp[x] && !comp[sum_all - x]) { pick = x; break; }
    }
    if (pick != -1) {
        for (int i = 1; i <= n; i++) belong[i] = 2;
        greedy_split(n, pick);     // 集合 1 凑出和 pick，集合 2 的和自然是 S-pick
        output(n, 2);
        return 0;
    }

    // 否则 S 是奇数且 S-2 是合数：取两个不同的质数 a、b 把 S-a-b 也凑成质数
    build_primes(n);
    ll selA = -1, selB = -1;
    for (int i = 1; i <= primeCnt && selA < 0; i++) {
        for (int j = 1; j <= primeCnt; j++) {
            if (primeList[j] == primeList[i]) continue;      // a、b 必须是两个不同的数
            if (!comp[sum_all - primeList[i] - primeList[j]]) {
                selA = primeList[i];
                selB = primeList[j];
                break;
            }
        }
    }

    if (selA < 0) {                // 理论上不会发生，保留兜底
        printf("-1\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) belong[i] = 3;
    belong[selA] = 1;              // 集合 1 = {a}
    belong[selB] = 2;              // 集合 2 = {b}，集合 3 的和 = S-a-b 是质数
    output(n, 3);

    return 0;
}
