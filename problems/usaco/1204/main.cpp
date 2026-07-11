/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:41
 * update_at: 2026-07-11 17:42
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int a[MAXN], b[MAXN];
int pos_in_b[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        pos_in_b[b[i]] = i;
    }

    int ans = 0;
    int max_so_far = 0;

    for (int i = 1; i <= n; i++) {
        int order = pos_in_b[a[i]];
        if (order > max_so_far) {
            max_so_far = order;
        } else {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}
