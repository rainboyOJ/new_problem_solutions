/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:20
 * update_at: 2026-10-06 11:20
 */

#include <cstdio>
using namespace std;

typedef long long ll;

const int LIMIT = 20;   // 只输出前 20 个
const int MAXN = 25;    // n <= 20

int n;                  // 火车数量
int ans_cnt;            // 已收集的出站序列数
int stk[MAXN];          // 手动栈，stk[1..top]
int top;                // 栈顶指针
int out_seq[MAXN];      // 已出站序列，out_seq[1..out_cnt]
int out_cnt;            // 已出站数量

// 从当前状态出发 DFS，优先「出栈」再「进栈」，天然按字典序
void dfs(int next_in) {
    if (ans_cnt == LIMIT) return;           // 收满 20 个，整树剪枝
    if (out_cnt == n) {                     // 全部出站，得到一个合法序列
        for (int i = 1; i <= n; ++i)
            printf("%d", out_seq[i]);
        printf("\n");
        ++ans_cnt;
        return;
    }
    // 分支一：栈顶出站，能让当前出站序列更小，优先走
    if (top > 0) {
        out_seq[++out_cnt] = stk[top--];
        dfs(next_in);
        stk[++top] = out_seq[out_cnt--];    // 回溯
    }
    // 分支二：下一节火车进站
    if (next_in <= n) {
        stk[++top] = next_in;
        dfs(next_in + 1);
        --top;                              // 回溯
    }
}

int main() {
    scanf("%d", &n);
    dfs(1);
    return 0;
}
