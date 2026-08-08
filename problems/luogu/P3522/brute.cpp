#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;

int n;
int x_arr[MAXN], y_arr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x_arr[i] >> y_arr[i];
    }

    int ans = 1;
    for (int l = 1; l <= n; l++) {
        int max_low = x_arr[l];
        for (int r = l; r <= n; r++) {
            max_low = max(max_low, x_arr[r]);
            if (max_low <= y_arr[r]) {
                ans = max(ans, r - l + 1);
            }
            else {
                break;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
