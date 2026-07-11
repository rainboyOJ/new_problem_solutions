/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:00
 * update_at: 2026-07-11 19:02
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 150005;

int n, q;
ll a[MAXN];       // 原数组，按输入下标保存
ll b[MAXN];       // 排序后的数组
ll prefix_sum[MAXN];
ll base_answer;
int ord[MAXN];    // 原下标的排序顺序
int pos[MAXN];    // pos[i] 表示原第 i 个数在排序数组中的位置

bool cmp_ord(int x, int y) {
    if (a[x] != a[y]) return a[x] < a[y];
    return x < y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
        ord[i] = i;
    }

    sort(ord + 1, ord + n + 1, cmp_ord);
    for (int i = 1; i <= n; i++) {
        pos[ord[i]] = i;
    }

    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + b[i];
        base_answer += (ll)i * b[i];
    }

    cin >> q;
    while (q--) {
        int idx;
        ll val;
        cin >> idx >> val;

        int old_pos = pos[idx];
        ll old_val = b[old_pos];

        int new_pos = lower_bound(b + 1, b + n + 1, val) - b;
        if (val > old_val) {
            new_pos--;
        }

        ll ans = base_answer;
        ans -= (ll)old_pos * old_val;

        if (new_pos >= old_pos) {
            // old_pos+1..new_pos 整体向左移动一格，贡献各减去自身值。
            ans -= prefix_sum[new_pos] - prefix_sum[old_pos];
        } else {
            // new_pos..old_pos-1 整体向右移动一格，贡献各增加自身值。
            ans += prefix_sum[old_pos - 1] - prefix_sum[new_pos - 1];
        }

        ans += (ll)new_pos * val;
        cout << ans << '\n';
    }

    return 0;
}
