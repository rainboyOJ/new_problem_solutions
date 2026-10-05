/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:04
 * update_at: 2026-10-06 01:04
 */

#include <cstdio>
#include <deque>
using namespace std;

typedef long long ll;

const int MAXN = 200005;

int n, m;
ll a[MAXN]; // a[i] 表示第 i 个数
ll s[MAXN]; // s[i] 表示前缀和 A_1 + ... + A_i，s[0] = 0

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        s[i] = s[i - 1] + a[i];
    }

    // 以 i 结尾、长度不超过 m 的子段和 = s[i] - s[j]，j ∈ [i-m, i-1]，
    // 即用单调队列维护窗口 [i-m, i-1] 内最小的 s[j]
    deque<int> dq; // 队列装前缀和下标，下标递增、对应 s 值也递增，队首是窗口最小值
    dq.push_back(0);
    ll ans = s[1] - s[0]; // 长度为 1 的子段 A_1 至少存在（m >= 1）
    for (int i = 1; i <= n; i++) {
        // 弹出队首里已经滑出窗口的下标（j < i-m 时子段长度超过 m）
        while (!dq.empty() && dq.front() < i - m)
            dq.pop_front();

        // 此时窗口 [i-m, i-1] 内最小前缀和在队首，更新答案
        ll cur = s[i] - s[dq.front()];
        if (cur > ans)
            ans = cur;

        // 队尾淘汰：s 值不小于 s[i] 的下标以后永远当不了最小值，直接出队
        while (!dq.empty() && s[dq.back()] >= s[i])
            dq.pop_back();
        dq.push_back(i);
    }

    printf("%lld\n", ans);
    return 0;
}
