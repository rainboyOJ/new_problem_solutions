#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 100005;
const int LOGN = 20; // 2^17 > 100000，开到 20 足够了

// f[i][j] 表示从 i 开始，长度为 2^j 的区间最小值
int f[MAXN][LOGN];
// Log[i] 存储 i 的以 2 为底的对数 (向下取整)
int Log[MAXN]; 
int n, m;

void init() {
    // 1. 预处理 Log 数组
    // Log[1] = 0, Log[2]=1, Log[3]=1, Log[4]=2 ...
    Log[1] = 0;
    for (int i = 2; i <= m; i++) {
        Log[i] = Log[i / 2] + 1;
    }

    // 2. 初始化 ST 表的第一列 (长度为 2^0 = 1 的区间)
    // 这一步在输入时已经完成了，即 f[i][0] = input[i]

    // 3. 动态规划填表
    // j 是长度指数，必须在外层循环
    for (int j = 1; j <= LOGN - 1; j++) {
        // i 是起点
        // 注意边界：i + 2^j - 1 不能超过 m
        for (int i = 1; i + (1 << j) - 1 <= m; i++) {
            // 状态转移：左半部分 和 右半部分 取 min
            // 右半部分的起点是 i + 2^(j-1)
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r) {
    int len = r - l + 1;
    int k = Log[len]; // 找到最大的 k 使得 2^k <= len
    
    // 覆盖左边 [l, l + 2^k - 1] 和 右边 [r - 2^k + 1, r]
    return min(f[l][k], f[r - (1 << k) + 1][k]);
}

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 题目中输入是 m, n
    // m 是账目数量(数组大小), n 是询问次数
    cin >> m >> n;

    for (int i = 1; i <= m; i++) {
        cin >> f[i][0]; // 读入数据直接存入 ST 表的第 0 层
    }

    // 构建 ST 表
    init();

    // 处理询问
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        cout << query(a, b) << " ";
    }
    cout << endl;

    return 0;
}

