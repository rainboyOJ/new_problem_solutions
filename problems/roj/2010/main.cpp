/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:25
 * update_at: 2026-10-06 09:25
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXC = 205;

ll a[MAXC]; // 有牛牛棚编号
ll gaps[MAXC]; // 相邻间隙

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll m, s, c;
    cin >> m >> s >> c;
    for (int i = 1; i <= c; ++i) cin >> a[i];
    sort(a + 1, a + c + 1);

    // 整块板覆盖 [a[1], a[c]]，然后切最大的 k-1 个间隙
    int k = (int)min(m, c); // 实际使用的板数
    for (int i = 1; i < c; ++i) gaps[i] = a[i + 1] - a[i] - 1;
    sort(gaps + 1, gaps + c); // 升序
    reverse(gaps + 1, gaps + c); // 转成降序

    ll total = a[c] - a[1] + 1;
    for (int i = 1; i <= k - 1 && i < c; ++i) total -= gaps[i];
    cout << total << "\n";
    return 0;
}
