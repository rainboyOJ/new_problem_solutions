/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-06 21:12
 * update_at: 2026-11-06 21:12
 */
// CF670C Cinema：语言离散化（排序 + 二分统计人数）
// 选片准则：听懂配音的人最多；一样多时看懂字幕的人最多；仍然一样就取编号最小的
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;

ll n, m;
ll a[MAXN]; // 每位科学家会的语言，排序后用于二分统计人数
ll b[MAXN]; // 第 i 部电影的配音语言
ll c[MAXN]; // 第 i 部电影的字幕语言

// 有多少位科学家会语言 x
ll count_lang(ll x) {
    return upper_bound(a + 1, a + n + 1, x) - lower_bound(a + 1, a + n + 1, x);
}

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    cin >> m;
    for (ll i = 1; i <= m; i++) {
        cin >> b[i];
    }
    for (ll i = 1; i <= m; i++) {
        cin >> c[i];
    }
}

void solve() {
    ll best = 1;
    ll best_audio = -1;
    ll best_sub = -1;
    for (ll i = 1; i <= m; i++) {
        ll audio = count_lang(b[i]);
        ll sub = count_lang(c[i]);
        if (audio > best_audio || (audio == best_audio && sub > best_sub)) {
            best_audio = audio;
            best_sub = sub;
            best = i;
        }
    }
    cout << best << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
