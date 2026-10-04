/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 14:20
 * update_at: 2026-10-05 00:40
 */
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

// 反悔贪心：作业按截止时间排序逐个接下，容量超限时丢弃学分最小的已选作业
const int MAXN = 1e6 + 5;

struct Job {
    ll d; // 截止时间（第 d 天结束前完成）
    ll w; // 学分
};

Job jobs[MAXN]; // jobs[i]：第 i 个作业，下标从 1 开始
ll n;

// 小根堆维护已接作业的学分，堆顶 = 当前最"后悔"（学分最小）的作业
priority_queue<ll, vector<ll>, greater<ll> > heap;

bool cmp_job(const Job &a, const Job &b) {
    return a.d < b.d;
}

int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld %lld", &jobs[i].d, &jobs[i].w);
    }

    // 按截止时间 d 升序排序，保证容量检查只针对当前最大的 d
    sort(jobs + 1, jobs + n + 1, cmp_job);

    ll ans = 0; // 最终堆中学分之和，即答案
    for (ll i = 1; i <= n; i++) {
        heap.push(jobs[i].w);
        ans += jobs[i].w;
        if ((ll)heap.size() > jobs[i].d) { // 已接作业数超过前 d 天容量
            ans -= heap.top();             // 反悔：丢弃学分最小的作业
            heap.pop();
        }
    }

    printf("%lld\n", ans);
    return 0;
}
