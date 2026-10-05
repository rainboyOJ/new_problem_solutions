/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:41
 * update_at: 2026-10-06 00:41
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1000005;

ll a[MAXN];          // 原始序列
int q1[MAXN], q2[MAXN]; // q1 维护最大值（值递减），q2 维护最小值（值递增）
int h1, t1, h2, t2;     // 队首、队尾指针

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    h1 = t1 = h2 = t2 = 0; // 队列清空（下标从 1 开始存）

    for (int i = 1; i <= n; ++i) {
        // 最大值队列：队尾值 <= a[i] 则永无出头之日，弹出
        while (h1 < t1 && a[q1[t1]] <= a[i]) --t1;
        q1[++t1] = i;
        // 最小值队列：队尾值 >= a[i] 则永无出头之日，弹出
        while (h2 < t2 && a[q2[t2]] >= a[i]) --t2;
        q2[++t2] = i;

        // 队首过期：窗口左端为 i-k+1，更小的下标已滑出
        while (h1 < t1 && q1[h1 + 1] <= i - k) ++h1;
        while (h2 < t2 && q2[h2 + 1] <= i - k) ++h2;

        if (i >= k) {
            cout << a[q1[h1 + 1]] << ' ' << a[q2[h2 + 1]] << '\n';
        }
    }
    return 0;
}
