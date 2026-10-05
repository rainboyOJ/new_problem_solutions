/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:41
 * update_at: 2026-10-05 09:41
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1005; // 最多 1000 发导弹

ll a[MAXN];   // 依次飞来的高度
ll tails[MAXN]; // tails[len] 表示长度为 len 的严格上升子序列的最小结尾高度
int tail_cnt;   // tails 当前有效长度

// 在 tails[1..tail_cnt] 中找到第一个 >= h 的位置（下界）
int find_pos(ll h) {
    int l = 1, r = tail_cnt, ans = tail_cnt + 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (tails[mid] >= h) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll h;
    int n = 0;
    while (cin >> h) {
        a[++n] = h;
    }

    tail_cnt = 0;
    for (int i = 1; i <= n; i++) {
        int pos = find_pos(a[i]);
        tails[pos] = a[i];
        if (pos > tail_cnt) {
            tail_cnt = pos;
        }
    }

    cout << tail_cnt << endl;
    return 0;
}
