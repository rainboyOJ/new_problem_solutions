/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-05 10:12
 * update_at: 2026-09-05 10:12
 */
// main-queue.cpp：排序 + 双队列写法，合并阶段 O(n)，不依赖堆。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10005;

int n;
ll a[MAXN];      // 读入的 n 堆果子，排序后进入 q1
queue<ll> q1;    // 装排好序的原始果子堆，队首最小
queue<ll> q2;    // 装合并产生的新果子堆，天然单调递增
ll ans;          // 总消耗的体力

// 取出当前全局最小的那堆：只可能来自两个队列的队首。
ll take_min() {
    if (q1.empty()) {          // q1 取空后，只能从 q2 取
        ll v = q2.front();
        q2.pop();
        return v;
    }
    if (q2.empty()) {          // q2 还没有新堆
        ll v = q1.front();
        q1.pop();
        return v;
    }
    if (q1.front() <= q2.front()) {
        ll v = q1.front();
        q1.pop();
        return v;
    }
    ll v = q2.front();
    q2.pop();
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 原始堆先排序：之后 q1 从队首到队尾严格递增。
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        q1.push(a[i]);
    }

    // 合并 n-1 次，每次都取当前最小的两堆。
    // 新堆 x+y 一定 >= 上一个放进 q2 的新堆，
    // 所以 q2 保持单调递增，新堆直接放队尾即可。
    for (int i = 1; i <= n - 1; i++) {
        ll x = take_min();
        ll y = take_min();
        ll sum = x + y;
        ans += sum;
        q2.push(sum);
    }

    cout << ans << '\n';
    return 0;
}
