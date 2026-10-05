/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:11
 * update_at: 2026-10-06 02:11
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 55;
const ll INF = 1000000000000000000LL; // "还够不着"的不可达哨兵，远大于任何合法生气总量

struct Customer {
    ll p;   // 位置
    ll a;   // 生气值
    int id; // 原始输入下标（0 起），用来在排序后定位起点
};
Customer cust[MAXN];

int n;         // 客户数量
int c;         // 阿什尼初始在第 c 个客户的位置（1 起）
ll pos[MAXN];  // pos[i] 排序后第 i 个客户的位置
ll sumA[MAXN]; // sumA[i+1]-sumA[j] = 排序后区间 [j,i] 的生气值之和（前缀和）
ll total;      // 全部客户的生气值之和

// f[l][r][0/1]：已送达连续区间 [l,r]、人停在左端 l(0) 或右端 r(1) 时，
// 已发生的生气总量最小值。区间外未送达客户在这段移动中一直按各自的 A 累加。
ll f[MAXN][MAXN][2];

// 客户按位置升序，区间 DP 才能把"已送达集"表示成连续下标区间
bool cmp_pos(Customer x, Customer y) {
    return x.p < y.p;
}

int main() {
    scanf("%d %d", &n, &c);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &cust[i].p, &cust[i].a);
        cust[i].id = i;
    }
    int start_id = c - 1; // 起点客户的原始下标

    sort(cust, cust + n, cmp_pos);

    int s = 0; // 起点客户排序后落在哪个下标
    for (int i = 0; i < n; i++) {
        pos[i] = cust[i].p;
        if (cust[i].id == start_id) {
            s = i;
        }
    }
    sumA[0] = 0;
    for (int i = 0; i < n; i++) {
        sumA[i + 1] = sumA[i] + cust[i].a;
    }
    total = sumA[n];

    for (int l = 0; l < n; l++) {
        for (int r = 0; r < n; r++) {
            f[l][r][0] = INF;
            f[l][r][1] = INF;
        }
    }
    f[s][s][0] = 0;
    f[s][s][1] = 0;

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            // W(l+1,r)：由 [l+1,r] 走向 l 时，区间外仍在生气的客户生气值之和
            ll wait_from_right = total - (sumA[r + 1] - sumA[l + 1]);
            // W(l,r-1)：由 [l,r-1] 走向 r 时，区间外仍在生气的客户生气值之和
            ll wait_from_left = total - (sumA[r] - sumA[l]);

            ll v0 = f[l + 1][r][0] + (pos[l + 1] - pos[l]) * wait_from_right; // 从 l+1 直走到 l
            ll v1 = f[l + 1][r][1] + (pos[r] - pos[l]) * wait_from_right;     // 从右端 r 折返到 l
            if (v1 < v0) {
                v0 = v1;
            }
            f[l][r][0] = v0;

            ll v2 = f[l][r - 1][0] + (pos[r] - pos[l]) * wait_from_left;      // 从左端 l 横穿到 r
            ll v3 = f[l][r - 1][1] + (pos[r] - pos[r - 1]) * wait_from_left;  // 从 r-1 直走到 r
            if (v3 < v2) {
                v2 = v3;
            }
            f[l][r][1] = v2;
        }
    }

    ll answer = f[0][n - 1][0];
    if (f[0][n - 1][1] < answer) {
        answer = f[0][n - 1][1];
    }
    printf("%lld\n", answer);
    return 0;
}
