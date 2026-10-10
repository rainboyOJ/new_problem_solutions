/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 07:42
 * update_at: 2026-10-08 07:42
 */

// [USACO19OPEN] Milk Factory
// 题意：N 个加工站、N-1 条单向传送带 a -> b，且这些通道是用最少数量把所有站连起来的，
//       所以忽略方向后是一棵连通无环的树。求最小的 i，使得从其他每个站出发沿单向边
//       （可经过中间站）都能到达 i；不存在则输出 -1。
// 做法：树的有向定向不可能出现有向环，所以从任意站顺着出边一直走必然停在某个出度为 0
//       的站（sink）。若出度为 0 的站超过 1 个，任何一个 sink 都到不了别的 sink，无解；
//       若恰好一个，则所有站的路径都只能终止于它，它就是答案。故答案 = 唯一的 sink。
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 105;
int out_degree[MAXN]; // out_degree[i]：从 i 出发的传送带条数

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0; // 保证 1 <= N <= 100

    for (int k = 1; k <= n - 1; ++k) {
        int a, b;
        scanf("%d %d", &a, &b); // 传送带 a -> b，只有出发站 a 的出度增加
        out_degree[a]++;
    }

    int sink_count = 0; // 出度为 0 的站（路径终点）个数
    int answer = -1;
    for (int i = 1; i <= n; ++i) { // 升序扫描，顺便保证答案取最小
        if (out_degree[i] == 0) {
            sink_count++;
            answer = i;
        }
    }

    if (sink_count == 1) {
        printf("%d\n", answer);
    } else {
        printf("-1\n");
    }
    return 0;
}
