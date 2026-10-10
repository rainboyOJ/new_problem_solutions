/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 石子合并：区间 DP + 四边形不等式（Knuth 优化），O(n^2)
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

int n;

// 上三角表逐个区间存：第 i 行放 f[i][i..n-1]，f[i][j] 落在 off(i) + (j - i)
int off(int i) {
    return i * n - i * (i - 1) / 2;
}
// f[i][j]：把区间 [i,j] 合并成一堆的最小代价（用 int 存，与原实现一致）
vector<int> f;
// opt[i][j]：区间 [i,j] 的最优断点
vector<unsigned short> opt;
vector<ll> ps; // ps[i] = 前 i 堆的质量和

int main() {
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    ps.assign(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        ps[i + 1] = ps[i] + x;
    }
    f.assign(n * n, 0);
    opt.assign(n * n, 0);
    for (int i = 0; i < n; i++) {
        opt[off(i)] = (unsigned short)i;
    }

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i + length - 1 < n; i++) {
            int j = i + length - 1;
            // 最优断点随区间单调：p[i][j-1] <= p[i][j] <= p[i+1][j]
            int lo = opt[off(i) + (j - 1 - i)];
            int hi = opt[off(i + 1) + (j - i - 1)];
            ll best = -1;
            int bk = lo;
            for (int k = lo; k <= hi; k++) {
                ll v = (ll)f[off(i) + (k - i)] + f[off(k + 1) + (j - k - 1)];
                if (best < 0 || v < best) {
                    best = v;
                    bk = k;
                }
            }
            f[off(i) + (j - i)] = (int)(best + (ps[j + 1] - ps[i]));
            opt[off(i) + (j - i)] = (unsigned short)bk;
        }
    }
    printf("%d\n", f[off(0) + (n - 1)]);
    return 0;
}
