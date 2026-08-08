#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n;
int a[MAXN];
int first_pos[MAXN], last_pos[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i <= n; i++) {
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

    // 先检查是否存在交叉区间。
    for (int x = 1; x <= n; x++) {
        if (first_pos[x] == 0) {
            continue;
        }
        for (int y = x + 1; y <= n; y++) {
            if (first_pos[y] == 0) {
                continue;
            }
            bool cross1 = first_pos[x] < first_pos[y] && first_pos[y] < last_pos[x] && last_pos[x] < last_pos[y];
            bool cross2 = first_pos[y] < first_pos[x] && first_pos[x] < last_pos[y] && last_pos[y] < last_pos[x];
            if (cross1 || cross2) {
                cout << -1 << '\n';
                return 0;
            }
        }
    }

    int ans = 0;

    // 慢版枚举每个位置，显式找“覆盖这个位置的最内层区间”。
    for (int i = 1; i <= n; i++) {
        int cover = 0;
        int top_color = 0;
        int best_first = -1;

        for (int color = 1; color <= n; color++) {
            if (first_pos[color] == 0) {
                continue;
            }
            if (first_pos[color] <= i && i <= last_pos[color]) {
                cover++;
                if (first_pos[color] > best_first) {
                    best_first = first_pos[color];
                    top_color = color;
                }
            }
        }

        if (a[i] == 0) {
            if (cover != 0) {
                cout << -1 << '\n';
                return 0;
            }
            continue;
        }

        if (top_color != a[i]) {
            cout << -1 << '\n';
            return 0;
        }

        ans = max(ans, cover);
    }

    cout << ans << '\n';
    return 0;
}
