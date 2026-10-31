/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-10-31 19:10
 */
// main.cpp：把每一局结束时留在桌上的点集写成一条「跳转链」：
// T[i] = { a[i] } + T[last[a[i]] + 1]，即 a[i] 这张牌最终一定留在最左端起始终不动，
// 而它右侧的局面与「最后一次出现 a[i] 之后的那一局」完全相同。
// 于是只要统计每个位置被多少条链经过，按点数累加即可。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5 + 5;
int n, m;
int a[maxn];
int last[300005];   // last[v]：点数 v 在序列中最后一次出现的位置
ll cnt[maxn];       // cnt[i]：有多少局游戏的链经过位置 i
ll ans[300005];     // ans[v]：桌面上留有点数 v 的局数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        last[a[i]] = i;         // 从左到右扫，最后一次赋值就是最后一次出现
    }

    // 每个位置自己先算一次；再把它的游戏数推给链上的下一个位置
    // 下一个位置是 last[a[i]] + 1，一定比 i 大，所以从小到大扫就能一次算完
    for (int i = 1; i <= n; ++i) cnt[i] = 1;
    cnt[n + 1] = 0;
    for (int i = 1; i <= n; ++i) {
        cnt[last[a[i]] + 1] += cnt[i];
    }

    for (int i = 1; i <= n; ++i) {
        ans[a[i]] += cnt[i];
    }

    for (int v = 1; v <= m; ++v) {
        cout << ans[v] << (v == m ? '\n' : ' ');
    }
    return 0;
}
