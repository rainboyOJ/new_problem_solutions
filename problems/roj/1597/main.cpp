/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:54
 * update_at: 2026-10-06 00:54
 */
// main.cpp：单调队列求滑动窗口最值，队尾淘汰被支配的下标、队首弹出过期下标。
#include <cstdio>

typedef long long ll;

const int MAXN = 1000005; // N 最大 10^6，数组多开几位留余量

ll a[MAXN];      // a[i] 表示第 i 个数（下标从 0 开始）
int dq[MAXN];    // 单调队列，存下标，队列里对应的 a 值保持单调
ll ans[MAXN];    // ans 暂存每个窗口的最值，按窗口顺序排列
int head, tail;  // dq 的队首下标与队尾后一位，区间为 [head, tail)

// 扫描整个序列，求每个长度为 k 的窗口的最值并写入 ans。
// want_max 为真求最大值（队列值递减），为假求最小值（队列值递增）。
void window_extremes(int n, int k, bool want_max) {
    head = 0;
    tail = 0;
    int cnt = 0; // 已经产出的答案个数
    for (int i = 0; i < n; i++) {
        // 队尾淘汰：新元素不劣于队尾时，队尾更早过期且不会更优，可以丢弃
        while (head < tail) {
            bool keep;
            if (want_max) {
                keep = a[dq[tail - 1]] > a[i];
            } else {
                keep = a[dq[tail - 1]] < a[i];
            }
            if (keep) {
                break;
            }
            tail--;
        }
        dq[tail] = i;
        tail++;
        // 队首过期：下标已滑出窗口左边界，弹出
        if (dq[head] <= i - k) {
            head++;
        }
        // 第一个完整窗口形成后，每步输出队首对应的最值
        if (i >= k - 1) {
            ans[cnt] = a[dq[head]];
            cnt++;
        }
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    // 第一行最小值
    window_extremes(n, k, false);
    int total = n - k + 1;
    for (int i = 0; i < total; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%lld", ans[i]);
    }
    printf("\n");

    // 第二行最大值，复用同一段扫描
    window_extremes(n, k, true);
    for (int i = 0; i < total; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%lld", ans[i]);
    }
    printf("\n");
    return 0;
}
