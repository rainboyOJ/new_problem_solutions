/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * date: 2026-07-07 00:00:00
 */
// brute.cpp：小数据暴力解，用 vector 模拟插入和删除。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> q;         // 队列，存储从左到右的同学编号
    q.push_back(1);        // 1 号同学初始在最左侧

    // 处理插入
    for (int i = 2; i <= n; i++) {
        int k, p;
        cin >> k >> p;
        // 找到 k 号同学在队列中的位置
        auto it = find(q.begin(), q.end(), k);
        if (p == 0) {
            q.insert(it, i);  // 插到 k 左边
        } else {
            q.insert(it + 1, i); // 插到 k 右边
        }
    }

    int m;
    cin >> m;
    // 处理删除
    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        auto it = find(q.begin(), q.end(), x);
        if (it != q.end()) {
            q.erase(it);
        }
    }

    // 输出最终队列
    for (int x : q) cout << x << ' ';
    cout << '\n';

    return 0;
}
