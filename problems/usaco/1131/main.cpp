/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:24
 * update_at: 2026-07-11 13:28
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, L;
int citation[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        cin >> citation[i];
    }

    sort(citation + 1, citation + n + 1, greater<int>());

    int h = 0;
    for (int i = 1; i <= n; i++) {
        if (citation[i] >= i) {
            h = i;
        }
    }

    int target = h + 1;
    if (target <= n) {
        int already_ok = 0; // 已经达到 target 次引用的论文数。
        int can_add = 0;    // 加 1 次引用后能达到 target 的论文数。

        for (int i = 1; i <= n; i++) {
            if (citation[i] >= target) {
                already_ok++;
            } else if (citation[i] + 1 >= target) {
                can_add++;
            }
        }

        int need = target - already_ok;
        if (need <= L && need <= can_add) {
            h = target;
        }
    }

    cout << h << '\n';

    return 0;
}
