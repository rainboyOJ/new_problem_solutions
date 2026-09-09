/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 21:52
 * update_at: 2026-08-28 21:52
 */
#include <bits/stdc++.h>
using namespace std;

// D. 食堂(Meal)
// 思路：
// 1) 每个窗口内部按 b 降序排队最优（相邻交换论证），所以全局按 b 降序排序后，
//    任意窗口的队列（子序列）自动保持 b 降序，队内顺序这一自由度被消掉。
// 2) 剩下唯一决策：每人进 1 号窗口还是 2 号窗口。
//    按 b 降序依次处理每个人 i，此时第 i 人进某窗口一定排在该窗口队尾，
//    其吃完时刻 = 该窗口累计打饭时间 + b[i]。
// 3) 背包式 DP：f[j] 表示处理完当前前缀后、1 号窗口累计打饭时间为 j 时，
//    已经处理的这些人里最晚吃完时刻的最小值。
//    转移（第 i 人，s_i 为 a 的前缀和）：
//      - 进 1 号窗口：f[j] = min(f[j], max(f[j-a[i]], j + b[i]))
//      - 进 2 号窗口：f[j] = max(f[j], (s_i - j) + b[i])
//    答案 = min f[j]。

const int MAXN = 505;
const int INF = 0x3f3f3f3f;

struct Person {
    int a, b; // 打饭耗时、吃饭耗时
} p[MAXN];

int n;
int f[250005]; // 滚动数组：1 号窗口累计打饭时间为 j 时的最小"最晚吃完时刻"

bool cmp(const Person &x, const Person &y) {
    return x.b > y.b; // 按 b 降序
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].a >> p[i].b;
    }

    sort(p + 1, p + n + 1, cmp);

    memset(f, 0x3f, sizeof(f));
    f[0] = 0;

    int s = 0; // a 的前缀和
    for (int i = 1; i <= n; i++) {
        s += p[i].a;
        // j 从大到小：保证下面的 f[j - p[i].a] 还是上一层的值（0/1 背包式）
        for (int j = s; j >= 0; j--) {
            // 第 i 人进 2 号窗口：2 号窗口累计打饭 = s - j
            f[j] = max(f[j], s - j + p[i].b);
            // 第 i 人进 1 号窗口：打完饭时刻 = j，吃完时刻 = j + b[i]
            if (j >= p[i].a) {
                f[j] = min(f[j], max(f[j - p[i].a], j + p[i].b));
            }
        }
    }

    int ans = INF;
    for (int j = 0; j <= s; j++) {
        ans = min(ans, f[j]);
    }
    cout << ans << '\n';

    return 0;
}
