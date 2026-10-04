/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:32
 * update_at: 2026-10-05 03:32
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 50005;

bool is_composite[MAXN]; // is_composite[i] 为 true 表示 i 已被筛掉，是合数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    // 埃拉托斯特尼筛：从小到大枚举素数 p，把 p*p, p*p+p, ... 标记为合数
    for (ll p = 2; p * p <= n; p++) {
        if (is_composite[p]) {
            continue;
        }
        for (ll j = p * p; j <= n; j += p) {
            is_composite[j] = true;
        }
    }

    // 统计 [2, n] 中未被标记的数的个数，即素数个数
    ll answer = 0;
    for (ll i = 2; i <= n; i++) {
        if (!is_composite[i]) {
            answer++;
        }
    }

    cout << answer << endl;

    return 0;
}
