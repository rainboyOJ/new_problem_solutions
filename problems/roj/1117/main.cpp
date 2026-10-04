/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:25
 * update_at: 2026-10-05 02:26
 */
// main.cpp：稳定去重正解。按值索引开 bool 桶 seen，从左到右扫描，
// 首次出现的值保留并登记到 keep（紧凑前缀），天然保序且 O(n) 完成。

#include <cstdio>

typedef long long ll;

const int MAXV = 5001; // 值域上界 5000 也必须是合法下标，所以表长取 5001 而不是 5000

int n;                  // 输入序列长度
int a[MAXV];            // 读入的元素（n<=20000，足够装下）
int keep[MAXV];         // keep[k] = 第 k 个首次出现的值；[0, k) 即为输出
int seen[MAXV];         // seen[x] 标记值 x 是否已经在前面出现过：0 否 / 1 是
int k;                  // 已记录的首次出现个数 = 紧凑前缀长度

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    k = 0;
    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        if (!seen[x]) {          // x 还没出现过：保留并登记到前缀
            seen[x] = 1;
            keep[k] = x;
            ++k;
        }
        // 否则跳过，等价于删除该位置
    }

    for (int i = 0; i < k; ++i) {
        if (i) putchar(' ');
        printf("%d", keep[i]);
    }
    putchar('\n');

    return 0;
}