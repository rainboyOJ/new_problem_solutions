/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 蚂蚁的旅行：每条无向边拆成两条反向弧，求欧拉回路
#include <cstdio>
#include <vector>
using namespace std;

const int NO_ARC = -1; // 邻接链表结束标记

int n, m;
vector<int> head, nxt, to;

int main() {
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }
    // 弧 2i / 2i+1 是同一条边的两个方向：弧 arc 的起点是 to[arc^1]，终点是 to[arc]
    to.assign(2 * m, 0);
    for (int i = 0; i < 2 * m; i++) {
        scanf("%d", &to[i]);
    }
    nxt.assign(2 * m, NO_ARC);
    head.assign(n + 1, NO_ARC);
    for (int arc = 0; arc < 2 * m; arc++) {
        int v = to[arc ^ 1];
        nxt[arc] = head[v];
        head[v] = arc;
    }

    // 栈里存的是一条尚未走完的路径前缀；栈顶点没有出边了就钉到回路末尾
    vector<int> stk, tour;
    stk.push_back(1);
    while (!stk.empty()) {
        int u = stk.back();
        int arc = head[u];
        if (arc == NO_ARC) {
            tour.push_back(u);
            stk.pop_back();
        } else {
            head[u] = nxt[arc]; // 摘掉这条弧，保证每条边只用一次
            stk.push_back(to[arc]);
        }
    }

    for (int i = (int)tour.size() - 1; i >= 0; i--) {
        printf("%d", tour[i]);
        if (i) {
            printf("\n");
        }
    }
    return 0;
}
