/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:27
 * update_at: 2026-10-06 13:28
 */
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 10005;

ll a[MAXN]; // a[i] 表示第 i 种果子的数目（堆的重量）
int n;

// 小根堆：每次取出当前最小的两堆合并
priority_queue<ll, vector<ll>, greater<ll> > heap;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        heap.push(a[i]);
    }

    // 哈夫曼贪心：每次合并最小的两堆，代价累加
    // 注意代价总和可能超过 int 范围，用 ll 累加
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ll x = heap.top(); heap.pop(); // 当前最小的一堆
        ll y = heap.top(); heap.pop(); // 当前次小的一堆
        ans += x + y;
        heap.push(x + y);
    }

    printf("%lld\n", ans);
    return 0;
}
