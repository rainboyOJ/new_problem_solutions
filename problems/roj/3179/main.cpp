/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 洗牌：状态只记「还剩 k 张的面值各有多少个」+ 上一张牌的面值档次
#include <cstdio>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int SHIFT[4] = {0, 4, 8, 12}; // 高位中“恰好还剩 k 张的面值个数”占的位偏移，k = size-1
const int CODE_MAX = 1 << 18;       // code = body<<2 | (上一张档次)，body 只有 16 位

int cnt[128];                   // 每个面值出现了几次（牌数 <= 20000，面值最多 52 种）
ull memo[CODE_MAX];
char done[CODE_MAX];

// 状态码 code：牌集合按相邻面值不同排成一列有多少种放法（答案对 2^64 取模）
ull free_ways(int code) {
    if (done[code]) {
        return memo[code];
    }
    done[code] = 1;
    int body = code >> 2, last = code & 3;
    if (!body) {
        memo[code] = 1; // 牌放完了，空后缀算一种放法
        return 1;
    }
    ull total = 0;
    for (int size = 1; size <= 4; size++) {
        int left = (body >> SHIFT[size - 1]) & 15; // 还剩 size 张的面值有多少个
        int pick = left - (last == size);          // 上一张同面值的牌后面这个空位不能放
        if (pick <= 0) {
            continue;
        }
        int nxt = body - (1 << SHIFT[size - 1]); // 该面值掉到 size-1 档
        if (size > 1) {
            nxt += 1 << SHIFT[size - 2];
        }
        total += (ull)size * pick * free_ways(nxt << 2 | (size - 1));
    }
    memo[code] = total;
    return total;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) {
        return 0;
    }
    for (int tc = 1; tc <= T; tc++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < 128; i++) {
            cnt[i] = 0;
        }
        char card[16];
        for (int i = 0; i < n; i++) {
            scanf("%15s", card);
            cnt[(unsigned char)card[0]]++;
        }
        // 只需统计「剩 k 张的面值有几个」
        int by_size[5] = {0, 0, 0, 0, 0};
        for (int i = 0; i < 128; i++) {
            if (cnt[i]) {
                by_size[cnt[i]]++;
            }
        }
        int code = 0;
        for (int size = 1; size <= 4; size++) {
            code += by_size[size] << SHIFT[size - 1];
        }
        code <<= 2;
        printf("Case #%d: %llu\n", tc, free_ways(code));
    }
    return 0;
}
