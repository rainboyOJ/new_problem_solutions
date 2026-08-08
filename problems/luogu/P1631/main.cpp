/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 09:50
 * update_at: 2026-08-05 10:30
 */
// 多路归并：固定 A[i] 后 A[i]+B[j] 单调不降，用堆合并 N 条有序流，弹 N 次即得最小 N 个和。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long a[MAXN], b[MAXN]; // 两个单调不降序列

// 堆元素：(和, 行号, 列号)
struct HeapNode {
    long long sum;  // 和
    int row;        // 行号
    int col;        // 列号
    bool operator<(const HeapNode& o) const { return sum > o.sum; } // 小根堆
};
priority_queue<HeapNode> pq;

long long ans[MAXN]; // 答案数组

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    // 初始把每行的第一个元素 A[i]+B[0] 入堆
    for (int i = 0; i < n; i++)
        pq.push({a[i] + b[0], i, 0});

    for (int k = 0; k < n; k++) {
        HeapNode node = pq.top();
        pq.pop();
        ans[k] = node.sum;
        // 同一行的下一个元素入堆
        if (node.col + 1 < n)
            pq.push({a[node.row] + b[node.col + 1], node.row, node.col + 1});
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << ans[i];
    }
    cout << "\n";

    return 0;
}
