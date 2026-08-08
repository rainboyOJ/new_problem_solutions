#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000005;

int n, d;
long long p;
int a[MAXN];
long long prefix_sum[MAXN];
// window_sum[i]：长度恰好为 d、起点是 i 的连续段和。
long long window_sum[MAXN];
// 单调队列里存的是“长度为 d 的子段起点”。
int que[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p >> d;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        prefix_sum[i] = prefix_sum[i - 1] + a[i];
    }

    // window_sum[i]：长度恰好为 d、起点是 i 的连续段的元素和。
    if (d <= n) {
        for (int i = 1; i + d - 1 <= n; i++) {
            window_sum[i] = prefix_sum[i + d - 1] - prefix_sum[i - 1];
        }
    }

    int ans = 0;
    int left = 1;
    long long cur_sum = 0;
    int head = 1, tail = 0;

    for (int right = 1; right <= n; right++) {
        cur_sum += a[right];

        // 新增一个“长度为 d 的子段”进入当前右端点的候选集合。
        int start = right - d + 1;
        if (start >= 1) {
            while (head <= tail && window_sum[que[tail]] <= window_sum[start]) {
                tail--;
            }
            que[++tail] = start;
        }

        // 只要当前窗口长度大于 d，并且“总和 - 最佳可清零的 d 段和”仍然超过 p，
        // 就不断移动左端点。
        while (left <= right) {
            int len = right - left + 1;
            if (len <= d) {
                // 如果总长度本来就不超过 d，可以整段全部清零，一定合法。
                break;
            }

            while (head <= tail && que[head] < left) {
                head++;
            }

            if (head <= tail && cur_sum - window_sum[que[head]] <= p) {
                break;
            }

            cur_sum -= a[left];
            left++;
        }

        int len = right - left + 1;
        if (len > ans) {
            ans = len;
        }
    }

    cout << ans << '\n';
    return 0;
}
