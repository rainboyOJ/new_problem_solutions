/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:00
 * update_at: 2026-10-06 16:00
 */
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 2005;

typedef long long ll;

int m, n;

ll cur[MAXN]; // 前若干个序列能凑出的最小的 n 个和，非降序
ll row[MAXN]; // 当前读入的这一个序列，排序后前 n 个才可能参与答案
ll res[MAXN]; // 合并 cur 与 row 之后得到的新的最小的 n 个和

// 小顶堆里存的是打包后的候选和：key = (和 << 22) | (i << 11) | j。
// 非负数的数值大小先由高位决定，所以对 key 做小顶堆等价于按和排序。
// i、j 都不超过 n-1 <= 1999 < 2^11，占 11 位。
priority_queue<ll, vector<ll>, greater<ll> > heap;

// 把 cur 与 row（都非降序，长度均为 n）加法表里最小的 n 个和写入 res。
// 加法表在行、列两个方向都单调不减，等价于在矩阵上做多路归并。
// 每个格子只由固定的一个前驱生成：非第一列由左邻生成，第一列由上一行开头顺延生成。
void merge_top_n() {
    while (!heap.empty()) heap.pop();

    heap.push(((cur[0] + row[0]) << 22));

    for (int t = 0; t < n; t++) {
        ll key = heap.top();
        heap.pop();
        ll sum = key >> 22;
        ll i = (key >> 11) & 2047;
        ll j = key & 2047;
        res[t] = sum;

        // 第 0 列：顺延生成下一行的开头
        if (j == 0 && i + 1 < n) {
            heap.push(((cur[i + 1] + row[0]) << 22) | ((i + 1) << 11));
        }
        // 同一行内向右推进一格
        if (j + 1 < n) {
            heap.push(((cur[i] + row[j + 1]) << 22) | (i << 11) | (j + 1));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> m >> n;
        for (int k = 0; k < m; k++) {
            for (int i = 0; i < n; i++) {
                cin >> row[i];
            }
            sort(row, row + n);
            if (k == 0) {
                // 只有一个序列时，最小的 n 个和就是它自己
                for (int i = 0; i < n; i++) cur[i] = row[i];
            } else {
                merge_top_n();
                for (int i = 0; i < n; i++) cur[i] = res[i];
            }
        }
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << ' ';
            cout << cur[i];
        }
        cout << '\n';
    }

    return 0;
}
