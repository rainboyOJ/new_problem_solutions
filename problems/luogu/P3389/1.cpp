#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 105;
const double EPS = 1e-7; // 用于判断浮点数是否为0

int n;
double a[MAXN][MAXN]; // 增广矩阵

void debug() {
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 1;j <= n+1 ;++j ) // j: 1->n
        {
            printf("%0.2lf ",a[i][j]);
        }  
        printf("\n");
    }
    printf("------------------\n");
    printf("------------------\n");
    printf("------------------\n");

}

int main() {
    // 1. 输入数据
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            scanf("%lf", &a[i][j]);
        }
    }

    // 2. 高斯消元主过程
    for (int i = 1; i <= n; i++) {
        // [选主元] 寻找当前列(第i列)中绝对值最大的行
        int max_r = i;
        for (int r = i + 1; r <= n; r++) {
            if (fabs(a[r][i]) > fabs(a[max_r][i])) {
                max_r = r;
            }
        }

        // [判断无解/无穷解] 如果这一列最大值都是0，说明矩阵奇异，无法唯一求解
        if (fabs(a[max_r][i]) < EPS) {
            printf("No Solution\n");
            return 0;
        }

        // [交换行] 将绝对值最大的行换到当前行，保证精度稳定性
        if (max_r != i) {
            for (int j = 1; j <= n + 1; j++) swap(a[i][j], a[max_r][j]);
        }

        // [归一化] 将当前行第i个元素变为1 (这一步不做也可以，但做了方便后续处理)
        // 注意：要从第 n+1 列往前除，或者单独存 div 变量，防止 a[i][i] 被提前修改
        double div = a[i][i];
        for (int j = i; j <= n + 1; j++) {
            a[i][j] /= div; 
        }

        // [消元] 将其他所有行(j != i)的第i列消为0
        for (int j = 1; j <= n; j++) { // 枚举行
            if (i == j) continue; // 跳过当前行自己
            double ratio = a[j][i]; // 因为上面a[i][i]已经归一化为1了，这里直接是倍数
            for (int k = i; k <= n + 1; k++) { 
                // k是这一行(j)的 [i,n+1]
                // 第i行i前面的全是0,其它行,减去也是0,所以不用减少
                a[j][k] -= ratio * a[i][k];
            }
        }

        // debug();
    }

    // 3. 输出结果
    // 此时矩阵已化简为对角矩阵，a[i][n+1] 即为 x_i
    for (int i = 1; i <= n; i++) {
        // 防止出现 -0.00 的情况 (题目虽说SPJ处理，但严谨一点好)
        // 如果值非常接近0且是负数，有的编译器可能会输出 -0.00
        // 不过 printf("%.2lf") 配合 EPS 判断通常没问题
        printf("%.2lf\n", a[i][n + 1]); 
    }

    return 0;
}
