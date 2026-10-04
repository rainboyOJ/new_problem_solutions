/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:04
 * update_at: 2026-10-05 00:04
 */
#include <cstdio>
#include <set>
using namespace std;

typedef long long ll;

const int MAXV = 500; // 顶点编号 1~500
const int MAXF = 1024; // 栅栏数上限，路径长度为 F+1

multiset<int> adj[MAXV + 5]; // adj[v] 存 v 的所有邻点，重复边按多重集保存
int path[MAXF + 5]; // 依次出栈的顶点，反转后即为欧拉路径
int degree[MAXV + 5]; // 各顶点的度数，用于挑选起点

int main() {
    int fences;
    scanf("%d", &fences);

    for (int i = 1; i <= fences; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].insert(v);
        adj[v].insert(u);
        degree[u]++;
        degree[v]++;
    }

    // 有奇度点时欧拉路径必须以奇度点为两端，取较小的奇度点作起点；
    // 全为偶度点时存在欧拉回路，取编号最小的有边顶点即可。
    int start = -1;
    for (int v = 1; v <= MAXV; v++) {
        if (degree[v] % 2 == 1) {
            start = v;
            break;
        }
    }
    if (start == -1) {
        for (int v = 1; v <= MAXV; v++) {
            if (degree[v] > 0) {
                start = v;
                break;
            }
        }
    }

    // 迭代版 Hierholzer：栈顶还有边就一直往编号最小的邻点走，
    // 走不动时出栈记录；出栈序列反转后得到字典序最小的欧拉路径。
    int stack_vertex[MAXF + 5]; // 显式数组模拟 DFS 栈，避免递归深度问题
    int top = 0;
    int path_len = 0;
    stack_vertex[++top] = start;
    while (top > 0) {
        int v = stack_vertex[top];
        if (!adj[v].empty()) {
            int u = *adj[v].begin(); // 贪心取编号最小的可用邻点
            adj[v].erase(adj[v].begin()); // 删掉一条 v->u 的边
            adj[u].erase(adj[u].find(v)); // 无向边，反向也要删掉一条
            stack_vertex[++top] = u;
        } else {
            path[++path_len] = v;
            top--;
        }
    }

    for (int i = path_len; i >= 1; i--) {
        printf("%d\n", path[i]);
    }
    return 0;
}
