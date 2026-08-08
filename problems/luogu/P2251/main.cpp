#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
int a[MAXN];
int q[MAXN]; // 单调队列里存下标

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int head = 1;
    int tail = 0;

    for (int i = 1; i <= n; i++) {
        // 把已经滑出窗口左端的下标弹掉。
        while (head <= tail && q[head] <= i - m) {
            head++;
        }

        // 维护队列中对应的值单调递增，这样队头就是窗口最小值。
        while (head <= tail && a[q[tail]] >= a[i]) {
            tail--;
        }

        q[++tail] = i;

        if (i >= m) {
            cout << a[q[head]] << '\n';
        }
    }

    return 0;
}
