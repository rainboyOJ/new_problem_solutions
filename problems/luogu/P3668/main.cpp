#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int a[MAXN];
int first_pos[MAXN], last_pos[MAXN];
int stk[MAXN], top_idx;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        first_pos[i] = 0;
        last_pos[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 0) {
            continue;
        }
        if (first_pos[a[i]] == 0) {
            first_pos[a[i]] = i;
        }
        last_pos[a[i]] = i;
    }

    top_idx = 0;
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        if (a[i] == 0) {
            if (top_idx > 0) {
                cout << -1 << '\n';
                return 0;
            }
            continue;
        }

        if (i == first_pos[a[i]]) {
            stk[++top_idx] = a[i];
            ans = max(ans, top_idx);
        }

        if (stk[top_idx] != a[i]) {
            cout << -1 << '\n';
            return 0;
        }

        if (i == last_pos[a[i]]) {
            top_idx--;
        }
    }

    cout << ans << '\n';
    return 0;
}
