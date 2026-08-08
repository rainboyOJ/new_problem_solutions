#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int MAXK = 55;

int n, k, p;
int color[MAXN], costv[MAXN];
long long total_cnt[MAXK]; // 到当前位置之前，每种颜色一共出现了多少次
long long valid_cnt[MAXK]; // 到最近一个低消费客栈位置为止，每种颜色出现了多少次

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> p;
    for (int i = 1; i <= n; i++) {
        cin >> color[i] >> costv[i];
    }

    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        int c = color[i];

        // 如果当前位置本身就是一个低消费客栈，
        // 那么对后面的所有位置来说，区间里已经保证能找到一个消费 <= p 的客栈。
        // 因此此时把“可作为左端点的数量”整体刷新为当前所有已出现客栈数。
        if (costv[i] <= p) {
            for (int col = 0; col < k; col++) {
                valid_cnt[col] = total_cnt[col];
            }
        }

        // 当前位置作为右端点时，能和多少个同色左端点配对，
        // 只取决于这些左端点是否在最近一个低消费客栈之前。
        ans += valid_cnt[c];

        total_cnt[c]++;

        // 如果当前位置本身低消费，那么它也能成为后面位置的合法左端点。
        if (costv[i] <= p) {
            valid_cnt[c]++;
        }
    }

    cout << ans << '\n';

    return 0;
}
