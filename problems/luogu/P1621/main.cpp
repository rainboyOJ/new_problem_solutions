/**
 * P1621 集合
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXB = 100005;

int fa[MAXB];

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) fa[x] = y;
}

bool is_prime[MAXB];
int a, b, p;

int main() {
    scanf("%d%d%d", &a, &b, &p);
    int n = b - a + 1; // 区间中的整数个数
    for (int i = 0; i < n; ++i) fa[i] = i;

    // 筛法求素数
    memset(is_prime, 1, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= b; ++i) {
        if (is_prime[i]) {
            if ((long long)i * i <= b) {
                for (int j = i * i; j <= b; j += i)
                    is_prime[j] = false;
            }
            // 对每个 ≥p 的素数，合并区间内所有它的倍数
            if (i >= p) {
                int first = (a + i - 1) / i * i; // 区间中第一个 i 的倍数
                for (int j = first + i; j <= b; j += i)
                    unite(first - a, j - a);
            }
        }
    }
    // 统计集合数
    int ans = 0;
    for (int i = 0; i < n; ++i)
        if (fa[i] == i) ++ans;
    printf("%d\n", ans);
    return 0;
}
