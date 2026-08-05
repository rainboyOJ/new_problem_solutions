/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 09:50
 * update_at: 2026-08-05 09:50
 */
// 多路归并：固定 A[i] 后 A[i]+B[j] 单调不降，用堆合并 N 条有序流，弹 N 次即得最小 N 个和。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    // 堆元素：(和, 行号A[i], 列号B[j])
    // 初始把每行的第一个元素 A[i]+B[0] 入堆
    using T = tuple<long long, int, int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    for (int i = 0; i < n; i++)
        pq.push({a[i] + b[0], i, 0});

    vector<long long> ans;
    ans.reserve(n);
    for (int k = 0; k < n; k++) {
        auto [val, row, col] = pq.top();
        pq.pop();
        ans.push_back(val);
        // 同一行的下一个元素入堆
        if (col + 1 < n)
            pq.push({a[row] + b[col + 1], row, col + 1});
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << ans[i];
    }
    cout << "\n";

    return 0;
}
