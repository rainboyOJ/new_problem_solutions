/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:53
 * update_at: 2026-07-11 18:56
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;
const ll INF = 4000000000000000000LL;

struct CowGroup {
    ll w;   // 重量
    ll cnt; // 这种重量的奶牛数量
};

int n;
ll m, k;
CowGroup cow[MAXN];
deque<CowGroup> tower; // 每组表示若干座当前顶部重量相同的塔

bool cmp_cow(CowGroup a, CowGroup b) {
    return a.w > b.w;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> cow[i].w >> cow[i].cnt;
    }

    sort(cow + 1, cow + n + 1, cmp_cow);

    // 空塔可以看成顶部有一个无穷重的虚拟奶牛。
    tower.push_back((CowGroup){INF, m});

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll w = cow[i].w;
        ll remaining = cow[i].cnt;

        // 当前重量的奶牛只能放到顶部重量至少为 w + k 的塔上。
        while (!tower.empty() && remaining > 0 && w + k <= tower.front().w) {
            ll use = min(remaining, tower.front().cnt);
            remaining -= use;
            tower.front().cnt -= use;

            if (tower.front().cnt == 0) {
                tower.pop_front();
            }
        }

        ll placed = cow[i].cnt - remaining;
        if (placed > 0) {
            tower.push_back((CowGroup){w, placed});
            ans += placed;
        }
    }

    cout << ans << '\n';

    return 0;
}
