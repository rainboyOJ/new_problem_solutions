// P2882 [USACO07MAR] Face The Right Way G
// N 头牛排成一列（F 朝前，B 朝后），每次可将连续 K 头牛转向。
// 枚举 K，贪心从左到右翻转，求最小 K 和对应最少操作数。

#include <cstdio>
#include <cstring>

const int N = 5005;

int n;
char cows[N];       // cows[i] = 'F' 或 'B'
int ends[N];        // 差分数组：ends[i]=1 表示第 i 个位置有一个翻转结束

// 固定窗口大小 K，贪心扫描，返回所需操作数，不可行则返回 n+1
int operations(int K) {
    memset(ends, 0, sizeof(ends));
    int flipped = 0;    // 当前位置是否处于被翻转状态
    int moves = 0;      // 操作次数

    for (int i = 0; i < n; i++) {
        flipped ^= ends[i];     // i 是某个翻转的结束位置，则取消翻转效果

        // 当前牛的真实朝向：cows[i]=='B' 再异或 flipped
        // 如果朝向是 B（需要被翻），就从 i 开始翻一个长度为 K 的窗口
        if ((cows[i] == 'B') ^ flipped) {
            if (i + K > n) {    // 窗口越界，这个 K 不可行
                return n + 1;
            }
            moves++;
            flipped ^= 1;           // 标记当前位置进入翻转
            ends[i + K] ^= 1;       // 在 i+K 处标记翻转结束
        }
    }
    return moves;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char s[5];
        scanf("%s", s);
        cows[i] = s[0];
    }

    int bestK = 1, bestM = n + 1;
    // 枚举所有可能的窗口大小
    for (int K = 1; K <= n; K++) {
        int m = operations(K);
        if (m < bestM) {          // 更少的操作数 → 更新答案
            bestM = m;
            bestK = K;
        }
        // 操作数相同时保持 K 更小的那个（因为 K 从小到大枚举）
    }

    printf("%d %d\n", bestK, bestM);
    return 0;
}
