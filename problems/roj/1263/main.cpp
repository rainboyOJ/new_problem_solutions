/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:37
 * update_at: 2026-10-04 23:37
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5005;

struct Link {
    ll south; // 南岸坐标
    ll north; // 北岸坐标
};

ll n;
Link link[MAXN];    // 全部友好城市对
ll tails[MAXN];     // tails[k] 表示所有长度为 k+1 的不下降子序列中最小的结尾值
ll tails_len;

// 先按南岸坐标升序，南岸相同时再按北岸坐标升序。
// 这样南岸相同的两条航道（共端点，不算交叉）会自然按北岸递增排列。
bool cmp_link(Link a, Link b) {
    if (a.south != b.south) return a.south < b.south;
    return a.north < b.north;
}

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> link[i].south >> link[i].north;
    }
}

// 按南岸排好序后，“航道两两不交叉”等价于北岸坐标单调不下降，
// 于是问题变成在 north 序列上求最长不下降子序列。
// 用 upper_bound 找第一个大于当前值的位置：取右侧插入点，允许相等的值接在后面。
void solve() {
    sort(link + 1, link + n + 1, cmp_link);

    tails_len = 0;
    for (ll i = 1; i <= n; i++) {
        ll value = link[i].north;
        ll pos = upper_bound(tails, tails + tails_len, value) - tails;
        tails[pos] = value;
        if (pos == tails_len) {
            tails_len++;
        }
    }

    cout << tails_len << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
