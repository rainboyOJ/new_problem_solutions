/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:11
 * update_at: 2026-10-06 10:11
 */
// main.cpp：坐标压缩后逐格定色，统计每种颜色的可见面积。
#include <algorithm>
#include <cstdio>

typedef long long ll;

const int MAXN = 1005;     // 长方形数量上限（含底层白纸）
const int MAXC = 10005;    // 坐标值域上界，坐标到压缩下标可直接用数组映射
const int MAXCOLOR = 1000; // 颜色编号 1..1000

ll A, B, n;

ll llx[MAXN], lly[MAXN], urx[MAXN], ury[MAXN], col[MAXN]; // 每个长方形的原坐标与颜色
ll xs[2 * MAXN], ys[2 * MAXN]; // 排序去重后的 x / y 断点坐标
ll xid[MAXC], yid[MAXC];       // 坐标 -> 压缩下标
ll area[MAXCOLOR + 1];         // area[c] = 颜色 c 的最终可见面积

int main() {
    scanf("%lld %lld %lld", &A, &B, &n);

    // 白纸作为最底层长方形，颜色为 1；下标越大表示叠得越高。
    llx[0] = 0; lly[0] = 0; urx[0] = A; ury[0] = B; col[0] = 1;
    for (ll i = 1; i <= n; i++) {
        scanf("%lld %lld %lld %lld %lld", &llx[i], &lly[i], &urx[i], &ury[i], &col[i]);
    }

    // 收集所有 x / y 端点（白纸贡献 0、A 与 0、B），排序去重得到断点。
    ll xn = 0, yn = 0;
    for (ll i = 0; i <= n; i++) {
        xs[xn++] = llx[i];
        xs[xn++] = urx[i];
        ys[yn++] = lly[i];
        ys[yn++] = ury[i];
    }
    std::sort(xs, xs + xn);
    xn = std::unique(xs, xs + xn) - xs;
    std::sort(ys, ys + yn);
    yn = std::unique(ys, ys + yn) - ys;

    // 坐标 -> 压缩下标，方便长方形区间与格子下标直接比较。
    for (ll i = 0; i < xn; i++) xid[xs[i]] = i;
    for (ll i = 0; i < yn; i++) yid[ys[i]] = i;

    // 格 (i, j) 覆盖 [xs[i], xs[i+1]) x [ys[j], ys[j+1])，内部无边界线所以整格同色；
    // 自顶层向下找第一个覆盖它的长方形即该格颜色，白纸兜底为颜色 1。
    for (ll i = 0; i + 1 < xn; i++) {
        for (ll j = 0; j + 1 < yn; j++) {
            ll c = 1;
            for (ll k = n; k >= 1; k--) {
                if (xid[llx[k]] <= i && i < xid[urx[k]] &&
                    yid[lly[k]] <= j && j < yid[ury[k]]) {
                    c = col[k];
                    break;
                }
            }
            area[c] += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]);
        }
    }

    for (ll c = 1; c <= MAXCOLOR; c++) {
        if (area[c] > 0) printf("%lld %lld\n", c, area[c]);
    }
    return 0;
}
