#include <bits/stdc++.h>
using namespace std;

static int n;
static string bits;
static vector<int> prefix_one;

// 用前缀和 O(1) 判断当前区间是 B、I 还是 F。
char segment_type(int l, int r) {
    int ones = prefix_one[r] - prefix_one[l - 1];
    int len = r - l + 1;
    if (ones == 0) {
        return 'B';
    }
    if (ones == len) {
        return 'I';
    }
    return 'F';
}

// 后序遍历顺序是左、右、根，因此递归完左右区间后再输出当前类型。
void solve(int l, int r) {
    if (l == r) {
        cout << segment_type(l, r);
        return;
    }

    int mid = (l + r) >> 1;
    solve(l, mid);
    solve(mid + 1, r);
    cout << segment_type(l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> bits;
    int m = 1 << n;
    prefix_one.assign(m + 1, 0);

    for (int i = 1; i <= m; ++i) {
        prefix_one[i] = prefix_one[i - 1] + (bits[i - 1] == '1');
    }

    solve(1, m);
    cout << '\n';
    return 0;
}
