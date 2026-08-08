#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int n, k;
int a[MAXN], b[MAXN];
int used[MAXN];         // 服务器是否已经被占用
int ans[MAXN];          // 当前构造的分配方案
bool found_answer;

void dfs(int step) {
    if (found_answer) {
        return;
    }
    if (step > k) {
        found_answer = true;
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (used[i]) {
            continue;
        }
        if (a[i] < b[step]) {
            continue;
        }
        used[i] = 1;
        ans[step] = i;
        dfs(step + 1);
        if (found_answer) {
            return;
        }
        used[i] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= k; i++) {
        cin >> b[i];
    }

    memset(used, 0, sizeof(used));
    found_answer = false;
    dfs(1);

    if (!found_answer) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 1; i <= k; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}
