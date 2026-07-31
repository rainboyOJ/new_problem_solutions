/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 16:37
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long h[MAXN];
int st[MAXN], top;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    // 右端补一个高度为 0 的柱子，统一结算栈中剩余矩形。
    h[n + 1] = 0;
    long long ans = 0;

    for (int i = 1; i <= n + 1; i++) {
        // 更矮柱子确定右边界；相等高度则由新下标替代旧下标。
        while (top > 0 && h[st[top]] >= h[i]) {
            int mid = st[top];
            top--;

            int left = st[top];
            long long width = i - left - 1;
            long long area = h[mid] * width;
            ans = max(ans, area);
        }
        st[++top] = i;
    }

    cout << ans << '\n';
    return 0;
}
