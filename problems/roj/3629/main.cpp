/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2025-03-28 10:18
 * update_at: 2026-10-06 15:32
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 200000 + 5; // 最大人数

int n;              // 人数
int to[MAXN];       // to[i] 表示 i 的信息传递对象
int color[MAXN];    // 0 未访问，1 当前路径中，2 已处理完
int path[MAXN];     // 当前遍历经过的节点序列
int pos[MAXN];      // 节点在本轮 path 中的位置，0 表示未入栈
int ans;            // 最短环长度

// 三色标记找环：每个点只入栈、归档一次，时间 O(n)
void find_rings() {
    for (int start = 1; start <= n; ++start) {
        if (color[start] != 0) continue; // 已被处理过，跳过

        int u = start;
        int len = 0; // 当前 path 长度

        // 沿出边走，直到遇到非 0 节点
        while (color[u] == 0) {
            color[u] = 1;
            pos[u] = ++len;
            path[len] = u;
            u = to[u];
        }

        // 如果终止点是本轮路径上的点，说明形成了环
        if (color[u] == 1) {
            int ring_len = len - pos[u] + 1;
            if (ring_len < ans) ans = ring_len;
        }

        // 把本轮经过的所有点归档为已处理
        for (int i = 1; i <= len; ++i) {
            color[path[i]] = 2;
            pos[path[i]] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &to[i]);
    }

    ans = n + 1; // 初始化为比最大可能环长更大的值
    find_rings();

    printf("%d\n", ans);
    return 0;
}
