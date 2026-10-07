/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:26
 * update_at: 2026-10-06 14:26
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 10005;
const int MAXM = 105;

ll w[MAXN];       // 每个同学的接水量
ll taps[MAXM];    // 每个龙头的当前占用结束时刻，下标从1开始
int n, m;

// 小根堆上浮
typedef ll heap_type;

void push_up(int idx) {
    while (idx > 1) {
        int fa = idx >> 1;
        if (taps[fa] <= taps[idx]) break;
        swap(taps[fa], taps[idx]);
        idx = fa;
    }
}

// 小根堆下沉
void push_down(int idx, int sz) {
    while ((idx << 1) <= sz) {
        int son = idx << 1;
        if (son + 1 <= sz && taps[son + 1] < taps[son]) son++;
        if (taps[idx] <= taps[son]) break;
        swap(taps[idx], taps[son]);
        idx = son;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];

    // 初始 m 个龙头都空闲，结束时刻为 0
    int sz = m;
    for (int i = 1; i <= m; i++) taps[i] = 0;
    // 建堆
    for (int i = m >> 1; i >= 1; i--) push_down(i, sz);

    // 依次处理 n 个同学，每次把最早空闲的龙头占用 w[i] 秒
    for (int i = 1; i <= n; i++) {
        ll t = taps[1];          // 堆顶：最早空闲时刻
        taps[1] = t + w[i];      // 该同学占用后新的结束时刻
        push_down(1, sz);        // 维护堆性质
    }

    // 答案为所有龙头结束时刻的最大值
    ll ans = 0;
    for (int i = 1; i <= m; i++)
        if (taps[i] > ans) ans = taps[i];
    cout << ans << '\n';
    return 0;
}
