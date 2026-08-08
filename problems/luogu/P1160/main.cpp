/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * date: 2026-07-07 00:00:00
 */
// main.cpp：数组模拟双向链表，O(1) 插入/删除。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
int L[MAXN], R[MAXN];  // L[i] 和 R[i] 分别表示编号 i 同学的左、右邻居
int del[MAXN];         // del[i] = 1 表示编号 i 已删除

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 初始化：1 号同学入队，形成只有一个节点的双向链表
    L[1] = 0;
    R[1] = 0;

    // 处理 2~N 号同学的插入
    for (int i = 2; i <= n; i++) {
        int k, p;
        cin >> k >> p;

        if (p == 0) {
            // 将 i 插入到 k 的左边
            // 原链表：... <-> left_k <-> k <-> ...
            // 变为：... <-> left_k <-> i <-> k <-> ...
            int left_k = L[k];
            L[i] = left_k;
            R[i] = k;
            if (left_k != 0) R[left_k] = i;
            L[k] = i;
        } else {
            // 将 i 插入到 k 的右边
            // 原链表：... <-> k <-> right_k <-> ...
            // 变为：... <-> k <-> i <-> right_k <-> ...
            int right_k = R[k];
            R[i] = right_k;
            L[i] = k;
            if (right_k != 0) L[right_k] = i;
            R[k] = i;
        }
    }

    // 处理删除操作
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        if (del[x]) continue;  // 已经删除，忽略
        del[x] = 1;

        // 将 x 从链表中摘除，连接左右邻居
        int l = L[x], r = R[x];
        if (l != 0) R[l] = r;
        if (r != 0) L[r] = l;
    }

    // 找到链表头（最左侧的同学，没有左邻居）
    int head = 0;
    for (int i = 1; i <= n; i++) {
        if (!del[i] && L[i] == 0) {
            head = i;
            break;
        }
    }

    // 从左到右输出
    for (int cur = head; cur != 0; cur = R[cur]) {
        cout << cur << ' ';
    }
    cout << '\n';

    return 0;
}
