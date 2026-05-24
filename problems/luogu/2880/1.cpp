#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const int MAXN = 50005; // 根据题目 N <= 50000
const int LOGN = 17;    // 2^16 = 65536 > 50000，开 17 足够了

// 定义两个 ST 表
int st_max[MAXN][LOGN];
int st_min[MAXN][LOGN];
int Log[MAXN]; // 预处理 log 值
int n, q;

// 预处理函数
void init() {
    // 1. 预处理 Log 数组 (我们刚才证明过的公式)
    Log[1] = 0;
    for (int i = 2; i <= n; i++) {
        Log[i] = Log[i / 2] + 1;
    }

    // 2. DP 构建 ST 表
    // 注意：st_max[i][0] 和 st_min[i][0] 在输入时已经填好了
    
    for (int j = 1; j < LOGN; j++) { // 枚举长度指数 2^j
        for (int i = 1; i + (1 << j) - 1 <= n; i++) { // 枚举起点
            // 状态转移：当前区间 = max(左半边, 右半边)
            // 右半边的起点是 i + 2^(j-1)
            int half_len = 1 << (j - 1);
            
            st_max[i][j] = max(st_max[i][j - 1], st_max[i + half_len][j - 1]);
            st_min[i][j] = min(st_min[i][j - 1], st_min[i + half_len][j - 1]);
        }
    }
}

// 查询最大值
int query_max(int l, int r) {
    int k = Log[r - l + 1];
    // 覆盖左边和右边，取 max
    return max(st_max[l][k], st_max[r - (1 << k) + 1][k]);
}

// 查询最小值
int query_min(int l, int r) {
    int k = Log[r - l + 1];
    // 覆盖左边和右边，取 min
    return min(st_min[l][k], st_min[r - (1 << k) + 1][k]);
}

int main() {
    // 1. 加速 IO
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 2. 输入
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int h;
        cin >> h;
        // 初始化 ST 表的第 0 层（长度为 1 的区间）
        st_max[i][0] = h;
        st_min[i][0] = h;
    }

    // 3. 构建 ST 表
    init();

    // 4. 处理询问
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        // 题目保证 a <= b，不需要 swap
        // 直接输出差值
        cout << query_max(a, b) - query_min(a, b) << "\n";
    }

    return 0;
}

