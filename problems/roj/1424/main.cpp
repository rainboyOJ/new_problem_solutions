/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:22
 * update_at: 2026-10-05 23:22
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 15005;  // 最多喷头数

int n;                   // 每组喷头数量
ll L, W;                 // 草坪长、宽

double segL[MAXN];       // 每个有效喷头的左端点
double segR[MAXN];       // 每个有效喷头的右端点

// 对有效区间按左端点升序排序（指针扫过时只需左端有序）
bool cmp_seg(int a, int b) {
    return segL[a] < segL[b];
}

// 单组数据求解：最少喷头数，无法覆盖返回 -1
int solve_one() {
    if (L == 0) return 0;  // 无需覆盖

    int m = 0;             // 有效喷头数量
    double half = W / 2.0; // 半宽

    for (int i = 0; i < n; i++) {
        ll pos, r;
        scanf("%lld %lld", &pos, &r);
        double dr = r;  // 避免后续强制转换
        // 半径不超过半宽则圆够不到上下边，此喷头无效
        if (dr <= half) continue;
        double reach = sqrt(dr * dr - half * half);  // 中心线有效半长
        segL[m] = pos - reach;
        segR[m] = pos + reach;
        m++;
    }

    // idx 为区间按左端点排序后的下标
    int idx[MAXN];
    for (int i = 0; i < m; i++) idx[i] = i;
    sort(idx, idx + m, cmp_seg);

    double cur = 0.0;      // 当前已覆盖到的位置
    int i = 0;             // 排序后区间的扫描指针
    int ans = 0;

    while (cur < L) {
        double far = cur;  // 本步能到达的最远右端
        int j = i;
        // 所有左端不超过 cur 的区间中，取右端最远的
        while (j < m && segL[idx[j]] <= cur + 1e-9) {
            if (segR[idx[j]] > far) far = segR[idx[j]];
            j++;
        }
        // 没有区间能继续推进
        if (j == i || far <= cur + 1e-9) return -1;
        cur = far;
        i = j;
        ans++;
    }

    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %lld %lld", &n, &L, &W);
        printf("%d\n", solve_one());
    }
    return 0;
}
