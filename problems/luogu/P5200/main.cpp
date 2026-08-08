#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int a[MAXN];
int bit[MAXN];
int ans[MAXN];

int lowbit(int x) {
    return x & -x;
}

// 树状数组单点加一，表示某个数已经进入了“后缀有序段”。
void add(int pos, int val) {
    for (int i = pos; i <= n; i += lowbit(i)) {
        bit[i] += val;
    }
}

// 查询当前已经放进去的数里，有多少个值 <= pos。
int sum(int pos) {
    int ret = 0;
    for (int i = pos; i > 0; i -= lowbit(i)) {
        ret += bit[i];
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int start = n;

    // 从后往前找最长严格递增后缀。
    while (start > 1 && a[start - 1] < a[start]) {
        start--;
    }

    cout << start - 1 << '\n';

    // 先把已经有序的后缀放入树状数组。
    for (int i = start; i <= n; i++) {
        add(a[i], 1);
    }

    for (int i = 1; i < start; i++) {
        // 把当前队首拿走后，前面还会保留 start-i-1 头“尚未处理”的奶牛。
        // 之后再接上已经有序的后缀里所有比它小的奶牛，这就是本次需要后移的步数。
        ans[i] = (start - i - 1) + sum(a[i]);
        add(a[i], 1);
    }

    if (start > 1) {
        for (int i = 1; i < start; i++) {
            if (i > 1) {
                cout << ' ';
            }
            cout << ans[i];
        }
    }
    cout << '\n';

    return 0;
}
