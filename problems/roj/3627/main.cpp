/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:25
 * update_at: 2026-10-06 15:25
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

struct House {
    ll s; // 到入口的距离 S
    ll a; // 推销得到的疲劳值 A
};

int n;
House house[MAXN];       // 排序后的住户：按 A 降序，A 相同则距离大者优先
ll sumA[MAXN];           // sumA[i] = 排序后前 i 家 A 之和
ll farest[MAXN];         // farest[i] = 排序后前 i 家中最远的距离
ll suffixBest[MAXN];     // suffixBest[i] = max_{j >= i} (2*S_j + A_j)

// 按推销疲劳值 A 降序排序，A 相同时距离大者优先。
// 这样「排序前 i 项」恰好是「A 前 i 大里距离尽量大的那组」。
bool cmp_house(const House &x, const House &y) {
    if (x.a != y.a) {
        return x.a > y.a;
    }
    return x.s > y.s;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &house[i].s);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &house[i].a);
    }

    sort(house + 1, house + n + 1, cmp_house);

    // 前缀和与前缀最远距离
    for (int i = 1; i <= n; i++) {
        sumA[i] = sumA[i - 1] + house[i].a;
        farest[i] = max(farest[i - 1], house[i].s);
    }

    // 后缀最大值 h_i = max_{j >= i} (2*S_j + A_j)，表示从第 i 名往后任选一家当最远点的最佳贡献
    suffixBest[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        ll cand = 2 * house[i].s + house[i].a;
        suffixBest[i] = max(suffixBest[i + 1], cand);
    }

    // 对每个 X：要么最远点落在 A 前 X 大中，要么舍弃第 X 名换去更远处
    for (int i = 1; i <= n; i++) {
        ll plan1 = sumA[i] + 2 * farest[i];
        ll plan2 = sumA[i - 1] + suffixBest[i];
        printf("%lld\n", max(plan1, plan2));
    }
    return 0;
}
