/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-19 22:27
 * update_at: 2026-09-14 17:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;

int n, k;
int a[MAXN];                         // 输入序列，使用 1-based 下标。
deque<int> qmin, qmax;                // 分别保存求最小值、最大值时的下标。
int ans_min[MAXN], ans_max[MAXN];     // 每个窗口的最小值和最大值。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 双端队列中保存的是下标，不是元素值。
    // qmin 对应的 a[下标] 递增，qmax 对应的 a[下标] 递减。
    int answer_count = 0; // 已经得到的窗口数量。

    for (int i = 1; i <= n; i++) {
        // 当前窗口是 [i - k + 1, i]。
        // 下标 <= i - k 的元素已经滑出窗口，从队头删除。
        while (!qmin.empty() && qmin.front() <= i - k) {
            qmin.pop_front();
        }

        // 保持队列中的 a[下标] 递增。
        // 新元素更小，则队尾较大的元素以后不可能成为最小值，可以删除。
        while (!qmin.empty() && a[qmin.back()] >= a[i]) {
            qmin.pop_back();
        }
        qmin.push_back(i);

        // 同样维护一个递减队列，用来查询当前窗口的最大值。
        while (!qmax.empty() && qmax.front() <= i - k) {
            qmax.pop_front();
        }

        // 保持队列中的 a[下标] 递减。
        // 新元素更大，则队尾较小的元素以后不可能成为最大值，可以删除。
        while (!qmax.empty() && a[qmax.back()] <= a[i]) {
            qmax.pop_back();
        }
        qmax.push_back(i);

        // i >= k 时，第一个长度为 k 的窗口已经形成。
        // 单调队列的队头分别就是当前窗口最小值、最大值所在的下标。
        if (i >= k) {
            answer_count++;
            ans_min[answer_count] = a[qmin.front()];
            ans_max[answer_count] = a[qmax.front()];
        }
    }

    // 第一行输出所有窗口的最小值。
    for (int i = 1; i <= answer_count; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << ans_min[i];
    }
    cout << '\n';

    // 第二行输出所有窗口的最大值。
    for (int i = 1; i <= answer_count; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << ans_max[i];
    }
    cout << '\n';

    return 0;
}
