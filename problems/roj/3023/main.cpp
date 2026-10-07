/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:21
 * update_at: 2026-10-06 11:21
 */

// 盒子分形：B(n) 由五份 B(n-1) 放在左上、右上、正中、左下、右下构成，
// 边长为 3^(n-1)，n <= 7 时边长最大 729，直接用二维数组画出所有级别即可。

#include <cstdio>

typedef long long ll;

const int MAXN = 7;              // 最大级别
const int MAXS = 729;            // 3^6 = 729，最大边长

char f[MAXN + 1][MAXS][MAXS];    // f[n][r][c] = 第 n 级分形第 r 行第 c 列的字符（'X' 或 ' '）
ll len[MAXN + 1];                // len[n] = 第 n 级分形的边长 3^(n-1)

int main() {
    // 初始化第 1 级：只有一个 X
    len[1] = 1;
    f[1][0][0] = 'X';

    // 由第 n-1 级逐级构造第 n 级：每个 X 复制到五个位置
    for (int n = 2; n <= MAXN; n++) {
        ll half = len[n - 1];    // 上一级的边长，也是各副本的平移量
        len[n] = half * 3;
        for (ll r = 0; r < half; r++) {
            for (ll c = 0; c < half; c++) {
                if (f[n - 1][r][c] != 'X') continue;
                f[n][r][c] = 'X';                       // 左上
                f[n][r][c + 2 * half] = 'X';            // 右上
                f[n][r + half][c + half] = 'X';         // 正中
                f[n][r + 2 * half][c] = 'X';            // 左下
                f[n][r + 2 * half][c + 2 * half] = 'X'; // 右下
            }
        }
    }

    int n;
    while (scanf("%d", &n) == 1) {
        if (n == -1) break;      // 终止标记
        ll size = len[n];
        for (ll r = 0; r < size; r++) {
            // 找本行最后一个 X，行尾空格不输出
            ll last = -1;
            for (ll c = size - 1; c >= 0; c--) {
                if (f[n][r][c] == 'X') { last = c; break; }
            }
            for (ll c = 0; c <= last; c++) {
                char ch = f[n][r][c];
                if (ch != 'X') ch = ' ';   // 数组未写过的位置按空格输出
                putchar(ch);
            }
            putchar('\n');
        }
        printf("-\n");           // 每组输出后一个短划线
    }
    return 0;
}
