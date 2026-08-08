#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

char s[MAXN];
int first_pos[MAXN * 2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> (s + 1);
    int n = (int)strlen(s + 1);

    int limit = 2 * n + 2;
    for (int i = 0; i <= limit; i++) {
        first_pos[i] = -1;
    }

    int sum = 0;
    int offset = n;
    int ans = 0;

    // 前缀和为 0 在位置 0 先出现一次。
    first_pos[offset] = 0;

    for (int i = 1; i <= n; i++) {
        if (s[i] == 'G') {
            sum++;
        } else {
            sum--;
        }

        int idx = sum + offset;
        if (first_pos[idx] == -1) {
            first_pos[idx] = i;
        } else {
            ans = max(ans, i - first_pos[idx]);
        }
    }

    cout << ans << '\n';
    return 0;
}
