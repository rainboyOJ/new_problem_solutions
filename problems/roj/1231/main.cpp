/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:04
 * update_at: 2026-10-05 06:04
 */
//
// main.cpp：删 k 位求最小新整数。
// 解法：单调栈一次遍历，每个数位最多进出栈各一次，整体 O(m)。
// 与 main.py 同算法，方便 C++ 学习者对照。
//

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 20;          // m < 10，位串不会超过 9，留点余量

char n_buf[MAXM];             // 输入的整数串，按字符存放，避免 int 丢位数
char stk[MAXM];               // 单调非降栈：栈内保存当前选定的输出位
int top;                      // 表示每层数位的栈顶下标（stk 表示已选位）

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int k;
        scanf("%s %d", n_buf, &k);

        top = 0;              // 每组重新建栈，top=0 表示空栈
        // 一次扫描：栈顶 > 当前数位 且 还有删除额度，就弹栈顶
        for (int i = 0; n_buf[i]; ++i) {
            char d = n_buf[i];
            while (k > 0 && top > 0 && stk[top - 1] > d) {
                --top;        // 弹栈顶，花掉一次额度
                --k;
            }
            stk[top++] = d;   // 弹不动再压栈；压栈后栈仍非降
        }

        // 若扫描结束还剩额度，说明栈内已经非降，剩余删除全部砍在末尾
        int keep = top - k;
        for (int i = 0; i < keep; ++i) {
            putchar(stk[i]);
        }
        putchar('\n');
    }
    return 0;
}