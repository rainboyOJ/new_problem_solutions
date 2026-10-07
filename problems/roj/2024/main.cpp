/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:46
 * update_at: 2026-10-06 09:46
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXV = 25;
const int MAXG = 15;

ll need[MAXV + 1];          // 每种维生素的需求量
ll a[MAXG + 1][MAXV + 1];   // a[i][j] 第 i 号饲料第 j 种维生素的含量
int n, m;                   // n 维生素种类数，m 饲料种数

// sum[s][j]：状态 s 里所有被选饲料的第 j 种维生素含量之和
ll sum[1 << MAXG][MAXV + 1];

// 返回状态 s 的二进制中 1 的个数，即所选饲料份数
int count_bit(int s) {
    int cnt = 0;
    while (s) {
        cnt++;
        s &= s - 1;
    }
    return cnt;
}

// 判断状态 s 是否可行：每种维生素的总量都不小于需求
bool ok(int s) {
    for (int j = 1; j <= n; j++) {
        if (sum[s][j] < need[j]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> need[i];
    cin >> m;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    int total = 1 << m;
    // 按最低位拆分递推：sum[s] = sum[s 去掉最低位] + 最低位对应饲料的含量
    for (int s = 1; s < total; s++) {
        int low = s & -s;            // 最低位的 1
        int g = __builtin_ctz(low);  // 最低位对应饲料编号 0..m-1
        for (int j = 1; j <= n; j++) {
            sum[s][j] = sum[s ^ low][j] + a[g + 1][j];
        }
    }

    // 按份数 k 递增枚举，第一个可行的状态即最优解
    for (int k = 1; k <= m; k++) {
        for (int s = 1; s < total; s++) {
            if (count_bit(s) != k) continue;
            if (ok(s)) {
                cout << k;
                for (int i = 1; i <= m; i++) {
                    if (s & (1 << (i - 1))) cout << " " << i;
                }
                cout << "\n";
                return 0;
            }
        }
    }

    return 0;
}
