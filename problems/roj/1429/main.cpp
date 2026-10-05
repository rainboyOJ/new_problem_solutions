/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:31
 * update_at: 2026-10-05 23:31
 */
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 1000005; // 最大线段数

struct Seg {
    ll l, r;
} seg[MAXN];

// 按右端点升序排序
bool cmp(Seg a, Seg b) {
    return a.r < b.r;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &seg[i].l, &seg[i].r);
    }
    sort(seg + 1, seg + n + 1, cmp);
    int ans = 0;
    ll last_right = -1; // 已选最后一条线段的右端点
    for (int i = 1; i <= n; i++) {
        if (last_right == -1 || seg[i].l >= last_right) {
            ans++;
            last_right = seg[i].r;
        }
    }
    printf("%d\n", ans);
    return 0;
}
