/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:40
 * update_at: 2026-10-06 01:40
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 1005;

ll a[MAXN];          // a[i]：第 i 堆石子的数量（下标从 1 开始）
ll Ldp[MAXN][MAXN];  // Ldp[i][j]：在区间 [i,j] 左侧加一堆石子，使整个新局面成为先手必败态所需的石子数
ll Rdp[MAXN][MAXN];  // Rdp[i][j]：在区间 [i,j] 右侧加一堆石子，使整个新局面成为先手必败态所需的石子数

// 在子区间的一端新增石子数为 x 的一堆，求该端对应区间 [i,j] 的必败阈值。
// is_left 为 1：新堆在左端，子区间为 [i,j-1]，l/r 为其两侧阈值；
// is_left 为 0：新堆在右端，子区间为 [i+1,j]，l/r 为其两侧阈值。
// 转移按 x 与两侧阈值 l、r 的大小关系分为五类；注意 x 恰好等于一侧阈值时，
// 取差 1 的临界值而非保持相等，这是本题最容易写错的边界。
ll next_end_state(ll x, ll l, ll r, int is_left) {
    if (is_left) {
        if (x == r) return 0; // 右端本身已是必败态，左侧无需再补石子
    } else {
        if (x == l) return 0; // 左端本身已是必败态，右侧无需再补石子
    }
    // 新堆石子数同时大于或同时小于两侧阈值：保持两端相等即可用对称模仿控制局面
    if ((x < l && x < r) || (x > l && x > r)) return x;
    // 夹在两侧阈值之间：按方向取差 1 的临界值
    if (is_left) {
        if (x >= l && x < r) return x + 1;
        return x - 1;
    } else {
        if (x >= r && x < l) return x + 1;
        return x - 1;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);

        if (n == 1) { // 只有一堆时先手直接取完获胜
            printf("1\n");
            continue;
        }

        // 区间长度为 1 时，在任意一侧放上相同数量的石子即为必败态
        for (int i = 1; i <= n; i++) Ldp[i][i] = Rdp[i][i] = a[i];

        // 按区间长度从小到大递推两侧必败阈值
        for (int len = 2; len <= n; len++) {
            for (int i = 1; i + len - 1 <= n; i++) {
                int j = i + len - 1;
                Ldp[i][j] = next_end_state(a[j], Ldp[i][j - 1], Rdp[i][j - 1], 1);
                Rdp[i][j] = next_end_state(a[i], Ldp[i + 1][j], Rdp[i + 1][j], 0);
            }
        }

        // 把 a[1] 看作区间 [2,n] 左侧实际存在的堆：若与必败阈值相等则先手必败
        if (a[1] == Ldp[2][n]) printf("0\n");
        else printf("1\n");
    }
    return 0;
}
