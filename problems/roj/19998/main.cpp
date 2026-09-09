/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 19:06
 * update_at: 2026-08-28 19:06
 */
/**
 * C. yet LIS
 * 每个位置 i 有 k 个已排序的候选值 a[i][1] <= ... <= a[i][k]，
 * 每个位置恰好选一个数构成序列，求所有可能序列的最长严格上升子序列的最大长度。
 *
 * 做法（官方双指针，O(n^2 + n*k)）：
 *   v[L] = 处理完已走过的位置后，长度为 L 的严格上升子序列的最小结尾值。
 *   v[1..] 严格递增，v[L] = INF 表示长度 L 目前不可达。
 *   对当前位置的 k 个候选值（已排序）：
 *     1) 先用"上一阶段"的 v 一次性算出每个候选值的 dp[j]：
 *        双指针 p 表示最大的下标满足 v[p] < a[j]，则 dp[j] = p + 1。
 *     2) 再统一更新 v[dp[j]] = min(v[dp[j]], a[j])。
 *    分两步是为了避免同一位置的候选值互相"接龙"（同一个位置用了两个数）。
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXK = 5005;   // k 的最大值
const int MAXN = 1005;   // n <= 1000，留几个空位
const int INF = 1000000010; // 比所有值(<=1000)都大，表示"不可达"

int k, n;          // 每个位置 k 个候选值，共 n 个位置
int a[MAXK];       // 当前这一行的 k 个候选值（题目保证已排序）
int v[MAXN];       // v[L] = 长度为 L 的严格上升子序列的最小结尾值，INF 表示不可达
int dp[MAXK];      // dp[j] = 本轮选择候选值 a[j] 能得到的最长上升子序列长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> k >> n;   // 注意输入顺序：k 在前，n 在后
    for (int L = 1; L <= n; L++) v[L] = INF;

    for (int i = 1; i <= n; i++) {          // 依次处理每个位置
        for (int j = 1; j <= k; j++) cin >> a[j];

        // 第一步：用上一阶段结束时的 v，一次性算出所有 dp[j]。
        // v 严格递增、a[j] 单调不降，所以 p 单调不降，可以双指针。
        int p = 0;                          // 最大的下标满足 v[p] < a[j]
        for (int j = 1; j <= k; j++) {
            while (p + 1 <= n && v[p + 1] < a[j]) p++;
            dp[j] = p + 1;                  // 长度 dp[j]-1 的链都能接上 a[j]
        }

        // 第二步：统一应用更新。同一长度取更小的结尾值（min 自动完成）。
        for (int j = 1; j <= k; j++) {
            v[dp[j]] = min(v[dp[j]], a[j]);
        }
    }

    // 答案 = 最大的可达长度
    for (int L = n; L >= 1; L--) {
        if (v[L] != INF) {
            cout << L << '\n';
            return 0;
        }
    }
    return 0;
}