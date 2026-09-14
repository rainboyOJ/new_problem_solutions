/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-14 16:17
 * update_at: 2026-09-14 16:17
 */
// main-multiset.cpp：用 C++ 自带的 std::multiset（有序可重集）维护滑动窗口。
// 窗口 [i-k+1, i] 的最小值 = 集合首元素，最大值 = 集合尾元素。
// 窗口右移一格 = 删除出窗元素 + 插入入窗元素，每次操作 O(log n)，总 O(n log n)。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000000 + 5;

int n, k;
int a[maxn];        // 输入序列，1-based
int ans_min[maxn];  // 每个窗口的最小值
int ans_max[maxn];  // 每个窗口的最大值

multiset<int> ms;   // 当前窗口元素组成的有序可重集

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 先把第一个窗口 [1, k] 装进有序可重集
    for (int i = 1; i <= k; i++) {
        ms.insert(a[i]);
    }

    int cnt = 0;
    for (int i = k; i <= n; i++) {
        if (i > k) {
            // 窗口右移一格：删掉出窗的 a[i-k]，加入入窗的 a[i]
            multiset<int>::iterator it = ms.find(a[i - k]);
            ms.erase(it);
            ms.insert(a[i]);
        }

        // 有序可重集的首元素最小，尾元素最大
        cnt++;
        ans_min[cnt] = *ms.begin();
        ans_max[cnt] = *ms.rbegin();
    }

    for (int i = 1; i <= cnt; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << ans_min[i];
    }
    cout << '\n';

    for (int i = 1; i <= cnt; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << ans_max[i];
    }
    cout << '\n';

    return 0;
}
