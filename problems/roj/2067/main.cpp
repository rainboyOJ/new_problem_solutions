/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:54
 * update_at: 2026-10-06 10:54
 */
#include <cstdio>
#include <queue>
#include <utility>
using namespace std;

typedef long long ll;

const int MAXN = 1005;  // 工件数量上限
const int MAXM = 35;    // 单类机器数量上限

ll n;         // 工件数量
ll m1;        // A 型机器数量
ll m2;        // B 型机器数量
ll time_a[MAXM];  // A 型每台机器完成一次操作的时间
ll time_b[MAXM];  // B 型每台机器完成一次操作的时间

ll finish_a[MAXN];  // A 车间第 k 个工件的最早完工时刻，升序
ll finish_b[MAXN];  // B 车间第 k 个可用收尾槽位，升序

// 把 jobs 个工件派给这批同型机器，升序返回「全车间第 k 个工件的最早完工时刻」。
// 每台机器的时间表是 t,2t,3t,...，把「给这台机器再派一件」看作待选事件，
// 事件键就是它产生的完工时刻；小根堆弹出第 k 次即为第 k 个完工时刻。
void finish_times(ll times[], ll m, ll jobs, ll done[]) {
    // 堆元素：(这台机器下一个完工时刻, 该机器单次耗时)
    priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, greater<pair<ll, ll> > > heap;
    for (ll j = 1; j <= m; j++) {
        heap.push(make_pair(times[j], times[j]));
    }
    for (ll k = 1; k <= jobs; k++) {
        ll finish = heap.top().first;
        ll t = heap.top().second;
        heap.pop();
        done[k] = finish;
        heap.push(make_pair(finish + t, t));  // 同一台机器顺延到下一件
    }
}

int main() {
    scanf("%lld %lld %lld", &n, &m1, &m2);
    for (ll j = 1; j <= m1; j++) {
        scanf("%lld", &time_a[j]);
    }
    for (ll j = 1; j <= m2; j++) {
        scanf("%lld", &time_b[j]);
    }

    finish_times(time_a, m1, n, finish_a);
    finish_times(time_b, m2, n, finish_b);

    ll ans_a = finish_a[n];  // A 车间独立完成的最短时间

    // B 车间收尾：A 完工时刻降序第 p 项，配 B 升序第 p 个槽位，取最大
    ll ans_b = 0;
    for (ll p = 1; p <= n; p++) {
        ll cur = finish_a[n - p + 1] + finish_b[p];
        if (cur > ans_b) {
            ans_b = cur;
        }
    }

    printf("%lld %lld\n", ans_a, ans_b);
    return 0;
}
