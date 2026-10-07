/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:33
 * update_at: 2026-10-06 09:33
 */
#include <cstdio>

typedef long long ll;

// 九种移动各自拨动的时钟集合，时钟按 A~I 编号 0~8，用二进制位记录
// 1 ABDE  2 ABC  3 BCEF  4 ADG  5 BDEFH  6 CFI  7 DEGH  8 GHI  9 EFHI
const int msk[10] = {0, 27, 7, 54, 73, 186, 292, 216, 448, 432};

int t[9];   // t[i] 表示第 i 只钟的初始位置：12/3/6/9 记 0/1/2/3
int c[10];  // c[m] 表示第 m 种移动做几次（0~3，做 4 次等于没做）

// 检验次数向量 c[1..9] 能否把九只钟都拨回 12 点：每只钟初值加被拨次数模 4 为 0
bool check() {
    for (int i = 0; i < 9; i++) {
        int sum = t[i];
        for (int m = 1; m <= 9; m++)
            if ((msk[m] >> i) & 1) sum += c[m];
        if (sum % 4 != 0) return false;
    }
    return true;
}

// 把次数向量展开成移动序列输出
void print_ans() {
    bool first = true;
    for (int m = 1; m <= 9; m++)
        for (int k = 0; k < c[m]; k++) {
            if (!first) printf(" ");
            first = false;
            printf("%d", m);
        }
    printf("\n");
}

int main() {
    // 读入九只钟的初始时间并转换：12->0 3->1 6->2 9->3，即 (时间/3)%4
    for (int i = 0; i < 9; i++) {
        int x;
        scanf("%d", &x);
        t[i] = x / 3 % 4;
    }

    // 把 9 种移动各做几次编码成 18 位四进制数，枚举全部 4^9 = 262144 个候选
    // 影响矩阵模 4 可逆（det = 5 为奇数），每个初态恰有一个解，找到即可输出
    for (int code = 0; code < 262144; code++) {
        for (int m = 1; m <= 9; m++)
            c[m] = (code >> (2 * (m - 1))) & 3;
        if (check()) {
            print_ans();
            return 0;
        }
    }
    return 0;
}
