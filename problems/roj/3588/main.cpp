/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:42
 * update_at: 2026-10-06 14:42
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 10005;

struct Carpet {
    ll a, b, g, k; // 左下角 (a,b)，x 方向长 g，y 方向长 k
} carpets[MAXN];

int n;
ll xq, yq; // 查询点

// 第 i 张地毯是否覆盖查询点（含边界）
bool cover(int i) {
    return carpets[i].a <= xq && xq <= carpets[i].a + carpets[i].g &&
           carpets[i].b <= yq && yq <= carpets[i].b + carpets[i].k;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld %lld %lld", &carpets[i].a, &carpets[i].b, &carpets[i].g, &carpets[i].k);
    }
    scanf("%lld %lld", &xq, &yq);

    // 后铺的在上，倒序找第一个覆盖查询点的地毯
    for (int i = n; i >= 1; --i) {
        if (cover(i)) {
            printf("%d\n", i);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}
