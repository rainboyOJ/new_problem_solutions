/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:09
 * update_at: 2026-10-05 08:09
 */
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

// 祖孙询问：DFS 括号序把每棵子树压成一段连续区间，
// "u 是 v 的祖先" 等价于 tin[u] <= tin[v] <= tout[u]。

const int MAXX = 40005; // 节点编号不超过 4×10^4，留几个冗余位置

int n;    // 节点个数
int m;    // 询问个数
int root; // 根节点编号（输入中 b = -1 的那条边的 a）

vector<int> g[MAXX]; // g[u] 保存与 u 相邻的节点编号
int tin[MAXX];       // tin[u] = DFS 进入 u 的时刻
int tout[MAXX];      // tout[u] = u 子树中最大的进入时刻
int timer;           // 全局时刻，只在进入节点时递增

// 显式栈模拟 DFS，每个节点入栈两次（进入阶段、离开阶段），最多 2n 个栈元素
int stack_u[2 * MAXX];     // 栈中节点编号
int stack_par[2 * MAXX];   // 栈中节点的父亲，用来避免走回父亲
int stack_stage[2 * MAXX]; // 0 表示进入该节点，1 表示离开该节点
int top;

// 迭代 DFS 标出括号序，避免链状树递归过深
void build_order() {
    top = 0;
    stack_u[top] = root;
    stack_par[top] = -1;
    stack_stage[top] = 0;
    top++;

    while (top > 0) {
        top--;
        int u = stack_u[top];
        int parent = stack_par[top];
        int stage = stack_stage[top];

        if (stage == 0) {
            timer++;
            tin[u] = timer;
            // 先把 u 的离开阶段压回栈底，再压孩子，
            // 这样孩子全部走完后才轮到 u 收尾，tout[u] 就是子树里最大的 tin
            stack_u[top] = u;
            stack_par[top] = parent;
            stack_stage[top] = 1;
            top++;
            for (int i = 0; i < (int)g[u].size(); i++) {
                int v = g[u][i];
                if (v == parent) {
                    continue; // 父亲不回头
                }
                stack_u[top] = v;
                stack_par[top] = u;
                stack_stage[top] = 0;
                top++;
            }
        } else {
            tout[u] = timer;
        }
    }
}

int main() {
    scanf("%d", &n);
    root = 0;
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (b == -1) {
            root = a; // 题目保证会出现这样一行
        } else {
            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    build_order();

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        // x ≠ y 时两个方向的包含关系互斥，先判 x 是否为祖先
        if (tin[x] <= tin[y] && tin[y] <= tout[x]) {
            printf("1\n");
        } else if (tin[y] <= tin[x] && tin[x] <= tout[y]) {
            printf("2\n");
        } else {
            printf("0\n");
        }
    }
    return 0;
}
