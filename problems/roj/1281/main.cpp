/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:50
 * update_at: 2026-10-05 07:50
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 1005; // N ≤ 1000，留一点裕量

int n;
int a[MAXN]; // 序列元素，值域 0..10000，用 int 足够

// tails[k] 表示当前已扫描前缀中，长度为 k+1 的上升子序列的最小可能结尾。
// tails 始终严格递增，长度上限等于 LIS 长度 ≤ N。
int tails[MAXN];
int len_t; // tails 当前有效长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    len_t = 0;
    for (int i = 1; i <= n; i++) {
        int v = a[i];
        // 在严格递增的 tails 中找第一个 >= v 的位置（lower_bound），等值只能替换不追加
        int pos = lower_bound(tails, tails + len_t, v) - tails;
        if (pos == len_t) {
            tails[len_t++] = v; // 比所有层结尾都大，LIS 长度 +1
        } else {
            tails[pos] = v;     // 同长度下结尾更小，后续更容易接
        }
    }

    cout << len_t << "\n";
    return 0;
}
