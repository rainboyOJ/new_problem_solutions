/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 20:19
 * update_at: 2026-11-10 19:58
 */
// main.cpp：标准 DFS 树遍历 + 回溯栈解法。
// 核心思路：从根结点开始 DFS，用全局栈维护根到当前结点的未匹配左括号。
// 遇到 '(' 时压栈；遇到 ')' 且栈非空时弹栈匹配，以当前结点结尾的合法括号子串数等于
// 配对左括号的父亲结点的合法子串数加一；离开结点时恢复栈现场。
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const int MAXN = 500005; // 节点数上限 5e5

int n;
char bracket[MAXN];        // bracket[u]：结点 u 上的括号字符
int parent_node[MAXN];     // parent_node[u]：结点 u 的父亲结点，根结点 1 的父亲为 0
vector<int> children[MAXN];// children[u]：结点 u 的孩子结点列表

int stk[MAXN];             // 维护根到当前结点路径上未匹配的左括号结点编号
int stack_top;             // 栈顶指针，0 表示空栈

ll end_cnt[MAXN];          // end_cnt[u]：以结点 u 结尾的合法括号子串数量
ll total_cnt[MAXN];        // total_cnt[u]：根到结点 u 路径上的全部合法括号子串总数

// 递归遍历树，进入结点时更新状态，离开时恢复栈
void dfs(int u) {
    int matched_node = 0; // 若当前右括号成功配对，记录弹出的左括号结点编号
    bool pushed = false;  // 记录当前结点是否被压入栈中

    if (bracket[u] == '(') {
        stk[++stack_top] = u;
        pushed = true;
        end_cnt[u] = 0;
    } else { // bracket[u] == ')'
        if (stack_top > 0) {
            matched_node = stk[stack_top--];
            // 新形成的匹配接在配对左括号父亲结尾的合法串后面
            end_cnt[u] = end_cnt[parent_node[matched_node]] + 1;
        } else {
            end_cnt[u] = 0;
        }
    }

    total_cnt[u] = total_cnt[parent_node[u]] + end_cnt[u];

    for (int v : children[u]) {
        dfs(v);
    }

    // 回溯：离开结点时恢复栈现场
    if (pushed) {
        stack_top--;
    } else if (matched_node != 0) {
        stk[++stack_top] = matched_node;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> bracket[i];
    }
    for (int i = 2; i <= n; i++) {
        cin >> parent_node[i];
        children[parent_node[i]].push_back(i);
    }

    dfs(1);

    ll answer = 0;
    for (int u = 1; u <= n; u++) {
        answer ^= static_cast<ll>(u) * total_cnt[u];
    }

    cout << answer << '\n';

    return 0;
}
