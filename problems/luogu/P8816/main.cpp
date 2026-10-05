#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MAXK = 105;
const int NEG = -1000000000; // 表示“不可达”的负无穷

struct Point {
    int x, y;
};

int n, k;
Point p[MAXN];
// dp[i][t]：以第 i 个给定点作为点列终点，恰好用了 t 个自由点（新增点）时，
//           整条点列最多包含多少个点（自由点也算进去）。
int dp[MAXN][MAXK];

bool cmp_point(const Point &a, const Point &b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    sort(p + 1, p + n + 1, cmp_point); // 坐标单调，排序后只需从前向后转移（类似 LIS）

    for (int i = 1; i <= n; i++) {
        for (int t = 0; t <= k; t++) {
            dp[i][t] = NEG;
        }
        dp[i][0] = 1; // 只选自己一个给定点，不用自由点
    }

    // 类似 LIS：枚举终点 i，再从它左边找一个前驱 j 来转移
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (p[j].y > p[i].y) {
                continue; // 前驱的 y 也必须不大于当前点
            }

            // 从 j 走到 i，中间需要补的点数：
            // 横纵坐标一共要前进 dx+dy 步，去掉 i 自己是给定点，中间要新增 dx+dy-1 个点。
            int need = (p[i].x - p[j].x) + (p[i].y - p[j].y) - 1;
            if (need < 0 || need > k) {
                continue; // 坐标重合（重题面不会给）或自由点不够，无法把 j 接到 i 前面
            }

            for (int t = 0; t + need <= k; t++) {
                if (dp[j][t] == NEG) {
                    continue; // j 用 t 个自由点不可达
                }
                // 接上 need 个自由点，再算上终点 i 本身
                dp[i][t + need] = max(dp[i][t + need], dp[j][t] + need + 1);
            }
        }
    }

    // 剩下的自由点可以继续往终点之后再延伸（一直往右/上走），所以答案 = dp[i][t] + (k - t)
    int best = 0;
    for (int i = 1; i <= n; i++) {
        for (int t = 0; t <= k; t++) {
            if (dp[i][t] == NEG) {
                continue;
            }
            best = max(best, dp[i][t] + (k - t));
        }
    }

    cout << best << '\n';
    return 0;
}
