#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000005;

int n, m;
int a[MAXN];
int que[MAXN]; // 单调队列存下标，队头对应当前窗口内最小值。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int head = 1, tail = 0;
    for (int i = 1; i <= n; i++) {
        // 查询的是第 i 项前面的 m 个数，不包含 a[i] 本身。
        while (head <= tail && que[head] < i - m) {
            head++;
        }

        if (head > tail) {
            cout << 0 << '\n';
        } else {
            cout << a[que[head]] << '\n';
        }

        // 把 a[i] 放进队列，供后面的元素查询。
        while (head <= tail && a[que[tail]] >= a[i]) {
            tail--;
        }
        tail++;
        que[tail] = i;
    }

    return 0;
}
