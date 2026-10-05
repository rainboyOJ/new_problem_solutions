/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:33
 * update_at: 2026-10-05 08:33
 */
// 扔鸡蛋：f[i][j] = i 层楼、j 个蛋，最坏情况下最少扔蛋次数
// 在 x 层扔一次：碎 -> 剩 x-1 层、j-1 个蛋；不碎 -> 剩 i-x 层、j 个蛋
// 对手挑更糟的分支（max），我方挑最优的首扔位置（min）

#include <cstdio>

typedef long long ll;

const int MAXN = 100;   // 楼高上限
const int MAXM = 10;    // 蛋数上限

ll f[MAXN + 5][MAXM + 5]; // f[楼层数][蛋数] = 最坏情况最少扔蛋次数

int main() {
    // 按楼层数从小到大、蛋数从小到大填表，两个子分支都已算好
    for (int j = 0; j <= MAXM; ++j) f[0][j] = 0; // 0 层楼不用扔
    for (int i = 1; i <= MAXN; ++i) {
        f[i][1] = i; // 单蛋只能从低到高逐层试
        for (int j = 2; j <= MAXM; ++j) {
            f[i][j] = MAXN; // 先放一个上界
            for (int x = 1; x <= i; ++x) {
                ll worst = f[x - 1][j - 1];
                if (f[i - x][j] > worst) worst = f[i - x][j];
                if (worst + 1 < f[i][j]) f[i][j] = worst + 1;
            }
        }
    }

    // 多组询问直接 O(1) 查表
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        printf("%lld\n", f[n][m]);
    }
    return 0;
}
