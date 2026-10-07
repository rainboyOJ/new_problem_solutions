/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:45
 * update_at: 2026-10-06 10:45
 */

// usaco 5.2.3 威斯康星州的牧场：
// 回溯搜索 + 位掩码 + 记忆化。
// 关键观察：每个格子恰好换一次，且换入字母必不等于该格原字母，
// 所以"已换的格子 / 各字母剩余需求"都由当前棋盘唯一决定，
// 记忆化只需要以棋盘编码为键；字母升序 x 格子升序扩展，
// 深度优先的第一个完整叶子就是字典序最小的方案。

#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
typedef long long ll;

const int NEED[5] = {3, 3, 3, 4, 3}; // 每种字母要搬进的小奶牛群数

int nbMask[16];   // nbMask[i]：格子 i 的 8 邻域（含对角线，不含自身）位掩码
int occ[5];       // occ[t]：当前放着字母 t 的格子集合
int leftCnt[5];   // leftCnt[t]：还差多少群 t 型小奶牛没搬进来
int usedMask;     // 已经换过奶牛的格子集合（每个格子只能换一次）
ll boardCode;     // 棋盘编码：每个格子用 3 bit 存字母编号 0..4，共 48 bit
map<ll, ll> memo; // memo[棋盘编码] = 从该棋盘出发能完成的合法搬运序列数

int pathT[16];    // 当前搜索路径：第 step 步放的字母编号
int pathCell[16]; // 当前搜索路径：第 step 步放的格子编号
int ansT[16];     // 答案方案：每步放的字母编号
int ansCell[16];  // 答案方案：每步放的格子编号
bool hasAns = false;

// 第一次走到的完整叶子就是字典序最小的方案，把它抄进答案数组
void recordAnswer() {
    for (int i = 0; i < 16; i++) {
        ansT[i] = pathT[i];
        ansCell[i] = pathCell[i];
    }
    hasAns = true;
}

// 返回从当前棋盘出发能完成的合法搬运序列总数
ll dfs(int step) {
    if (step == 16) { // 16 步全部走完，得到一个完整方案
        if (!hasAns) recordAnswer();
        return 1;
    }
    map<ll, ll>::iterator it = memo.find(boardCode);
    if (it != memo.end()) return it->second; // 相同棋盘只展开一次
    ll cnt = 0;
    // 第 0 步必须先搬 D；其余步按字母升序枚举，配合格子升序保证字典序最小
    int tBegin = (step == 0 ? 3 : 0);
    int tEnd = (step == 0 ? 3 : 4);
    for (int t = tBegin; t <= tEnd; t++) {
        if (leftCnt[t] == 0) continue; // 这种字母已经搬够
        for (int i = 0; i < 16; i++) { // 格子按行主序升序枚举
            int bit = 1 << i;
            if (usedMask & bit) continue;     // 该格已经换过
            if (occ[t] & bit) continue;       // 该格当前就是 t，不能放
            if (nbMask[i] & occ[t]) continue; // 8 邻域里有 t，不能放
            int old = (boardCode >> (3 * i)) & 7; // 该格当前住的字母
            boardCode ^= (ll)(t ^ old) << (3 * i); // 换入 t：翻转该格 3 bit
            occ[old] ^= bit;
            occ[t] |= bit;
            leftCnt[t]--;
            usedMask |= bit;
            pathT[step] = t;
            pathCell[step] = i;
            cnt += dfs(step + 1);
            usedMask &= ~bit; // 回溯，恢复现场
            leftCnt[t]++;
            occ[t] &= ~bit;
            occ[old] |= bit;
            boardCode ^= (ll)(t ^ old) << (3 * i);
        }
    }
    memo[boardCode] = cnt; // boardCode 已恢复到进入时的值
    return cnt;
}

int main() {
    // 预处理每个格子的 8 邻域位掩码
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            int mask = 0;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    int r2 = r + dr, c2 = c + dc;
                    if (r2 < 0 || r2 >= 4 || c2 < 0 || c2 >= 4) continue;
                    if (r2 == r && c2 == c) continue;
                    mask |= 1 << (r2 * 4 + c2);
                }
            }
            nbMask[r * 4 + c] = mask;
        }
    }
    // 读入初始棋盘：四行，每行一个 4 字母的字符串
    for (int i = 0; i < 16; i++) {
        char ch;
        cin >> ch;
        int t = ch - 'A';
        boardCode |= (ll)t << (3 * i);
        occ[t] |= 1 << i;
    }
    for (int t = 0; t < 5; t++) leftCnt[t] = NEED[t];

    ll total = dfs(0);

    // 输出字典序最小的 16 步方案（字母 行 列，行列从 1 开始）和方案总数
    for (int i = 0; i < 16; i++) {
        printf("%c %d %d\n", 'A' + ansT[i], ansCell[i] / 4 + 1, ansCell[i] % 4 + 1);
    }
    printf("%lld\n", total);
    return 0;
}
