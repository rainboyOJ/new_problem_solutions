#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;

int n;
long long h[MAXN], v[MAXN];
long long rec[MAXN]; // rec[i] 表示第 i 个发射站最终收到的总能量
int st[MAXN];        // 手写栈，保存可能成为“最近更高站”的位置
int top_pos;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i] >> v[i];
    }

    // 从左到右，求每个点左边最近的更高站。
    top_pos = 0;
    for (int i = 1; i <= n; i++) {
        while (top_pos > 0 && h[st[top_pos]] < h[i]) {
            top_pos--;
        }
        if (top_pos > 0) {
            rec[st[top_pos]] += v[i];
        }
        st[++top_pos] = i;
    }

    // 从右到左，求每个点右边最近的更高站。
    top_pos = 0;
    for (int i = n; i >= 1; i--) {
        while (top_pos > 0 && h[st[top_pos]] < h[i]) {
            top_pos--;
        }
        if (top_pos > 0) {
            rec[st[top_pos]] += v[i];
        }
        st[++top_pos] = i;
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, rec[i]);
    }

    cout << ans << '\n';
    return 0;
}
