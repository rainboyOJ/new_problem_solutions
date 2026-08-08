#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
const int MAXS = 1000000;

int n;
int a[MAXN];
bool diff_exist[MAXS + 5]; // diff_exist[d] 表示是否存在一对奶牛编号差值恰好为 d

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1);

    int max_diff = a[n] - a[1];

    // 如果两头奶牛在模 K 意义下落到同一个厩，
    // 那么它们的编号差一定是 K 的倍数。
    // 所以先把所有可能的差值记录下来。
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            diff_exist[a[j] - a[i]] = true;
        }
    }

    // K 至少要有 n 个不同余数位，所以从 n 开始枚举。
    for (int k = n; k <= max_diff; k++) {
        bool ok = true;

        // 只要某个差值是 k 的倍数，就说明有两头奶牛会撞到同一个厩。
        for (int d = k; d <= max_diff; d += k) {
            if (diff_exist[d]) {
                ok = false;
                break;
            }
        }

        if (ok) {
            cout << k << '\n';
            return 0;
        }
    }

    // 当 K > 最大编号差时，任意两头奶牛的差都小于 K，
    // 不可能再同余，所以 max_diff + 1 一定可行。
    cout << max_diff + 1 << '\n';

    return 0;
}
