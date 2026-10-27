/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-27 15:41
 * update_at: 2026-10-27 15:41
 */
// brute.cpp：小数据暴力解，直接维护数列，每个操作逐元素模拟。
// 用来讲清操作 3 的含义（第一个让 a[x] + ... + a[i] >= d 的 i），并和 main.cpp 对拍。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1000000 + 5;

int n, m;
ll a[MAXN];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);

    for (int step = 1; step <= m; step++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, y;
            ll v;
            scanf("%d %d %lld", &x, &y, &v);
            for (int i = x; i <= y; i++) a[i] += v;
        } else if (op == 2) {
            int x, y;
            scanf("%d %d", &x, &y);
            ll answer = 0;
            for (int i = x; i <= y; i++) answer += a[i];
            printf("%lld\n", answer);
        } else if (op == 3) {
            int x, y;
            ll d;
            scanf("%d %d %lld", &x, &y, &d);
            ll acc = 0;          // acc = a[x] + ... + a[i]
            int answer = y + 1;  // 整段都不到 d 时按要求输出 y + 1
            for (int i = x; i <= y; i++) {
                acc += a[i];
                if (acc >= d) {
                    answer = i;
                    break;
                }
            }
            printf("%d\n", answer);
        } else {
            int x;
            ll d;
            scanf("%d %lld", &x, &d);
            a[x] = d;
        }
    }
    return 0;
}
