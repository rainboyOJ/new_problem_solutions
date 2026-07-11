/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:29
 * update_at: 2026-07-11 14:30
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
int b[MAXN];   // b[i] = a[i] + a[i+1]
int ans[MAXN]; // 当前尝试得到的排列
bool used[MAXN];

bool build_and_check(int first_value) {
    memset(used, 0, sizeof(used));

    ans[1] = first_value;
    for (int i = 2; i <= n; i++) {
        ans[i] = b[i - 1] - ans[i - 1];
    }

    for (int i = 1; i <= n; i++) {
        if (ans[i] < 1 || ans[i] > n) {
            return false;
        }
        if (used[ans[i]]) {
            return false;
        }
        used[ans[i]] = true;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> b[i];
    }

    // 从小到大枚举 a[1]，第一个合法排列就是字典序最小。
    for (int first_value = 1; first_value <= n; first_value++) {
        if (build_and_check(first_value)) {
            for (int i = 1; i <= n; i++) {
                if (i > 1) {
                    cout << ' ';
                }
                cout << ans[i];
            }
            cout << '\n';
            return 0;
        }
    }

    return 0;
}
