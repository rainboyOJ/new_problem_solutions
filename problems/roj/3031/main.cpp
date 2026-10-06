/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:06
 * update_at: 2026-10-06 15:06
 */

// 火车进出栈问题：按字典序输出前 20 个出栈序列（评测数据以此为准）。
// 关键性质：栈非空时「出栈」分支的任意结果都字典序小于「进栈」分支，
// 所以每个状态先走「出栈」再走「进栈」，DFS 触达叶子的顺序就是字典序。
// n 可达 60000、递归深度可达 2n，改用显式帧栈代替真递归，避免爆栈。

#include <cstdio>
using namespace std;

typedef long long ll;

const int LIMIT = 20;              // 只输出字典序最小的 20 个出栈序列
const int MAXN = 60005;            // n 最大 60000
const int MAXFRAME = 2 * MAXN + 5; // 帧栈最深约 2n

int n;                             // 车厢数

int stk[MAXN];                     // 站内车厢，stk[stk_top-1] 是栈顶待出
int stk_top;                       // 站内车厢数 (栈顶指针)

int seq[MAXN];                     // 已出站的车厢编号
int seq_len;                       // 已出站车厢数

int found;                         // 已产出的出栈序列个数

// 显式帧：frame_next[i] 为该帧「下一节待进站」的编号；
// frame_phase[i] 表示该帧做到哪一步：0=刚进入 1=出栈分支已回溯 2=进栈分支已回溯
int frame_next[MAXFRAME];
int frame_phase[MAXFRAME];
int frame_top;                     // 帧栈大小

void solve() {
    scanf("%d", &n);

    frame_top = 0;
    frame_next[frame_top] = 1;
    frame_phase[frame_top] = 0;
    ++frame_top;

    while (frame_top > 0 && found < LIMIT) { // 收满 20 个立即整树剪枝
        int idx = frame_top - 1;
        int next_in = frame_next[idx];
        int phase = frame_phase[idx];

        if (phase == 0) {                        // 刚进入该状态
            if (next_in > n && stk_top == 0) {   // 叶子：全部车厢已出站
                for (int i = 0; i < seq_len; ++i) {
                    printf("%d", seq[i]);
                }
                printf("\n");
                ++found;
                --frame_top;
            } else if (stk_top > 0) {            // 优先「出栈」，字典序更小
                frame_phase[idx] = 1;
                seq[seq_len] = stk[--stk_top];
                ++seq_len;
                frame_next[frame_top] = next_in;
                frame_phase[frame_top] = 0;
                ++frame_top;
            } else {                             // 栈空时只能「进栈」
                frame_phase[idx] = 2;
                stk[stk_top] = next_in;
                ++stk_top;
                frame_next[frame_top] = next_in + 1;
                frame_phase[frame_top] = 0;
                ++frame_top;
            }
        } else if (phase == 1) {                 // 出栈分支已回溯
            stk[stk_top] = seq[--seq_len];       // 出站车厢退回栈顶
            ++stk_top;
            if (next_in <= n) {                  // 再试「进栈」分支
                frame_phase[idx] = 2;
                stk[stk_top] = next_in;
                ++stk_top;
                frame_next[frame_top] = next_in + 1;
                frame_phase[frame_top] = 0;
                ++frame_top;
            } else {
                --frame_top;
            }
        } else {                                 // 进栈分支已回溯
            --stk_top;                           // 车厢退回未进站状态
            --frame_top;
        }
    }
}

int main() {
    solve();
    return 0;
}
