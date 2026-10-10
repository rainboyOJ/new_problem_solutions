/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 排序：位图传递闭包，逐条加入关系并检查是否成环 / 是否已全序
#include <cstdio>
using namespace std;

typedef long long ll;

const int A_CODE = 65; // 变量编号 = 字母 - A_CODE
const int MAXN = 32;

unsigned int bits[MAXN]; // 第 i 个 bit 为 1 表示已知 i < j（含自环位）

// 把邻接位图原地扩成传递闭包；逐个把点 k 当一次中转站
void closure(int n) {
    for (int k = 0; k < n; k++) {
        unsigned int bit = 1u << k;
        for (int i = 0; i < n; i++) {
            if (bits[i] & bit) {
                bits[i] |= bits[k];
            }
        }
    }
}

int popcount32(unsigned int x) {
    int c = 0;
    while (x) {
        x &= x - 1;
        c++;
    }
    return c;
}

// 位图构成全序时输出序号表（按可达点数从大到小），否则返回 0
int ordered(int n, char* out) {
    int pc[MAXN];
    for (int i = 0; i < n; i++) {
        pc[i] = popcount32(bits[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (pc[i] == pc[j]) {
                return 0; // 有并列说明还存在不可比的两点
            }
        }
    }
    // n 个互不相同的可达点数 ⇒ 排序唯一，按可达点数降序输出
    for (int t = 0; t < n; t++) {
        int pick = -1;
        for (int i = 0; i < n; i++) {
            if (pc[i] >= 0 && (pick < 0 || pc[i] > pc[pick])) {
                pick = i;
            }
        }
        out[t] = (char)(A_CODE + pick);
        pc[pick] = -1;
    }
    out[n] = 0;
    return 1;
}

int main() {
    int printed = 0;
    while (true) {
        int n;
        if (scanf("%d", &n) != 1) {
            break;
        }
        if (n == 0) {
            break;
        }
        int m;
        scanf("%d", &m);

        char rel_lo[512], rel_hi[512];
        for (int t = 0; t < m; t++) {
            char tok[8];
            scanf("%7s", tok); // 兼容 "A<B" 与拆成 "A" "<" "B" 的写法
            if (tok[1] == 0) {
                char mid[8], rhs[8];
                scanf("%7s %7s", mid, rhs);
                rel_lo[t] = tok[0];
                rel_hi[t] = rhs[0];
            } else {
                rel_lo[t] = tok[0];
                rel_hi[t] = tok[2];
            }
        }

        for (int i = 0; i < n; i++) {
            bits[i] = 1u << i; // 先只保留自环
        }
        bool finished = false;
        for (int step = 1; step <= m; step++) {
            int lo = rel_lo[step - 1] - A_CODE;
            int hi = rel_hi[step - 1] - A_CODE;
            if ((bits[hi] >> lo) & 1) { // 已知 hi < lo，再加 lo < hi 就成环
                printf("Inconsistency found after %d relations.\n", step);
                printed++;
                finished = true;
                break;
            }
            bits[lo] |= 1u << hi;
            closure(n);
            char seq[MAXN];
            if (ordered(n, seq)) {
                printf("Sorted sequence determined after %d relations: %s.\n", step, seq);
                printed++;
                finished = true;
                break;
            }
        }
        if (!finished) {
            printf("Sorted sequence cannot be determined.\n");
            printed++;
        }
    }
    if (printed == 0) {
        printf("\n");
    }
    return 0;
}
