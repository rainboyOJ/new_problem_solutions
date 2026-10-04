/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:27
 * update_at: 2026-10-05 05:27
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 1000005; // k < 1000000，留足余量
const int MOD = 32767;

int p[MAXN]; // p[i] 表示 Pell 数列第 i 项模 32767 的值，值域 [0, 32766]，用 int 即可
int q[MAXN]; // 所有询问的 k

int main() {
    int n;
    scanf("%d", &n);

    int L = 0; // 询问中最大的 k
    for (int i = 0; i < n; i++) {
        scanf("%d", &q[i]);
        if (q[i] > L) L = q[i];
    }

    p[1] = 1;
    p[2] = 2;
    for (int i = 3; i <= L; i++) {
        p[i] = (2 * p[i - 1] + p[i - 2]) % MOD;
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", p[q[i]]);
    }

    return 0;
}
