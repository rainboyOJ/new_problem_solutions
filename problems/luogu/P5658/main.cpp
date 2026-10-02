/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 20:19
 * update_at: 2026-10-01 20:39
 */
// main.cpp：题目保证 f_u < u，按结点编号从小到大递推，用两个数组模拟“根到当前结点的未匹配左括号栈”。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 500005;   // n <= 5e5，结点编号用 int 足够，还能直接当数组下标

int n;
char bracket_char[MAXN];   // bracket_char[u]：结点 u 上的括号
int parent_node[MAXN];     // parent_node[u]：u 的父亲，根结点 1 的父亲记为 0

// 用两个数组表示根到 u 路径上“尚未匹配的左括号”栈：
// stack_top[u] 是 u 处栈顶结点的编号（0 表示栈空），
// stack_next[x] 是结点 x 在栈中的下一个结点，沿着它就能还原整条栈。
// 这样每个结点只需从父亲处继承栈顶，不必在回溯时恢复现场。
int stack_top[MAXN];
int stack_next[MAXN];

ll end_count[MAXN];    // end_count[u]：根到 u 的串中，以结点 u 结尾的合法括号子串数
ll total_count[MAXN];  // total_count[u]：根到 u 的串中全部合法括号子串数，即题面的 k_u

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> (bracket_char + 1);   // 直接读到下标 1 开始，和结点编号对齐
    for (int i = 2; i <= n; i++) {
        cin >> parent_node[i];
    }

    ll answer = 0;

    // f_u < u 保证按编号递增递推时，父亲一定已经算完，因此不需要 DFS。
    for (int u = 1; u <= n; u++) {
        int fa = parent_node[u];

        if (bracket_char[u] == '(') {
            // 左括号自己入栈，成为新的栈顶，没有合法括号串以它结尾。
            end_count[u] = 0;
            stack_next[u] = stack_top[fa];
            stack_top[u] = u;
        } else if (stack_top[fa] != 0) {
            // 右括号与父亲路径上最近的未匹配左括号 left_node 配对，
            // 再接到以 left_node 父亲结尾的合法串后面。
            int left_node = stack_top[fa];
            end_count[u] = end_count[parent_node[left_node]] + 1;
            stack_top[u] = stack_next[left_node];
        } else {
            // 栈空，说明当前右括号配不到左括号，不能作为任何合法子串的结尾。
            end_count[u] = 0;
            stack_top[u] = 0;
        }

        total_count[u] = total_count[fa] + end_count[u];
        answer ^= u * total_count[u];
    }

    cout << answer << '\n';
    return 0;
}
