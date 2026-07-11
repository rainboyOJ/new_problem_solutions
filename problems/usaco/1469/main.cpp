/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:26
 * update_at: 2026-07-11 15:29
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 7505;

int n;
int a[MAXN], b[MAXN];
long long ans[MAXN]; // ans[c] 表示恰好 c 头奶牛能体检的反转方案数。
int base_match;

void expand_center(int l, int r) {
    int match = base_match;

    while (l >= 1 && r <= n) {
        // 反转区间继续向外扩一层，相当于交换 a[l] 和 a[r]。
        match -= (a[l] == b[l]);
        match -= (a[r] == b[r]);
        match += (a[l] == b[r]);
        match += (a[r] == b[l]);

        ans[match]++;

        l--;
        r++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    for (int i = 1; i <= n; i++) {
        if (a[i] == b[i]) base_match++;
    }

    for (int mid = 1; mid <= n; mid++) {
        expand_center(mid, mid);       // 奇数长度区间。
        expand_center(mid, mid + 1);   // 偶数长度区间。
    }

    for (int c = 0; c <= n; c++) {
        cout << ans[c] << '\n';
    }

    return 0;
}
