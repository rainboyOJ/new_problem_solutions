/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-09 20:36
 * update_at: 2026-11-10 10:50
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;

int n, k;
int a[MAXN];
int s0[MAXN]; // 0 的个数前缀和：s0[i] 表示 a[1..i] 中 0 的数量

// 检查是否存在长度为 len 且 0 的个数不超过 k 的窗口
// 若存在，把满足条件的起始左端点记入 out_l
bool check(int len, int &out_l) {
    for (int l = 1; l + len - 1 <= n; l++) {
        int r = l + len - 1;
        if (s0[r] - s0[l - 1] <= k) {
            out_l = l;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s0[i] = s0[i - 1] + (a[i] == 0);
    }

    // 二分最长合法连续长度 len，范围 [0, n]
    int l = 0, r = n;
    int best_len = 0, best_l = 1;

    while (l <= r) {
        int mid = (l + r) / 2;
        int cur_l = 1;
        if (check(mid, cur_l)) {
            best_len = mid;
            best_l = cur_l;
            l = mid + 1; // 尝试寻找更长窗口
        } else {
            r = mid - 1;
        }
    }

    for (int i = best_l; i < best_l + best_len; i++) {
        a[i] = 1;
    }

    cout << best_len << "\n";
    for (int i = 1; i <= n; i++) {
        cout << a[i] << (i == n ? '\n' : ' ');
    }

    return 0;
}
