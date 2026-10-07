/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:50
 * update_at: 2026-10-06 01:52
 */
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 1005;

typedef long long ll;

ll n;
ll sums[2 * MAXN]; // 打乱后排序的 2n 个前缀和、后缀和
ll ans[MAXN];      // ans[i] 为还原出的原数列第 i 项
ll total;          // 整个数列的总和，也就是最大的那个和
bool inS[505];     // inS[x] 表示 x 是否属于给定的合法数字集合 S

// 深度优先搜索：正处理第 k 个和，左右两端待填区间为 [x, y]，
// pre 是已确定的左端前缀和，suf 是已确定的右端后缀和。
// 优先把当前和当作前缀和填左侧，从而保证第一组解字典序最小。
bool dfs(ll k, ll x, ll y, ll pre, ll suf) {
    if (x == y) {
        ll rem = total - pre - suf; // 中间剩下的那一项
        if (rem >= 1 && rem <= 500 && inS[rem]) {
            ans[x] = rem;
            return true;
        }
        return false;
    }

    ll diff_pre = sums[k] - pre; // 当归为前缀和时，左侧新填的数
    if (diff_pre >= 1 && diff_pre <= 500 && inS[diff_pre]) {
        ans[x] = diff_pre;
        if (dfs(k + 1, x + 1, y, sums[k], suf)) {
            return true;
        }
    }

    ll diff_suf = sums[k] - suf; // 当归为后缀和时，右侧新填的数
    if (diff_suf >= 1 && diff_suf <= 500 && inS[diff_suf]) {
        ans[y] = diff_suf;
        if (dfs(k + 1, x, y - 1, pre, sums[k])) {
            return true;
        }
    }

    return false;
}

void solve() {
    cin >> n;
    ll len = 2 * n;
    for (ll i = 0; i < len; i++) {
        cin >> sums[i];
    }
    sort(sums, sums + len);

    ll m;
    cin >> m;
    for (ll i = 0; i < m; i++) {
        ll value;
        cin >> value;
        if (value >= 1 && value <= 500) {
            inS[value] = true;
        }
    }

    total = sums[len - 1]; // 最大的和就是整个数列的总和

    if (dfs(0, 1, n, 0, 0)) {
        for (ll i = 1; i <= n; i++) {
            if (i > 1) {
                cout << ' ';
            }
            cout << ans[i];
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
