/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:40
 * update_at: 2026-10-05 01:40
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 10005;
int seq[MAXN]; // seq[i] 存序列第 i 个元素，下标从 1 开始与题面一致

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, x;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> seq[i];
    }
    cin >> x;

    // 序列无序，只能从左到右线性扫描，遇到的第一个匹配即“第一次出现”的位置
    ll answer = -1;
    for (ll i = 1; i <= n; i++) {
        if (seq[i] == x) {
            answer = i;
            break;
        }
    }

    cout << answer << "\n";
    return 0;
}
