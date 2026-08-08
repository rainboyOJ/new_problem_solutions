#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1e4 + 5;

ll a[maxn];    // 输入的数字 (0~9)
ll dp[maxn];   // dp[i] = 以 i 结尾的 LNDS 长度
ll sum[maxn];  // sum[i] = 该序列的元素和
int pre[maxn]; // pre[i] = 该序列中 i 的前驱下标 (0 表示无前驱)

int n;

void init() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    // 第一个位置：序列只有自己
    dp[1] = 1;
    sum[1] = a[1];

    // 递推位置 2..n
    for (int i = 2; i <= n; ++i) {
        dp[i] = 1;     // 至少是长度为 1 的序列（只包含自己）
        sum[i] = a[i];

        int pre_j = 0; // 当前最优前驱
        for (int j = 1; j < i; ++j) {
            if (a[j] > a[i]) continue; // 不满足不下降

            int clen = dp[j] + 1;

            if (clen > dp[i]) {
                // 长度更优，直接替换
                dp[i] = clen;
                sum[i] = sum[j] + a[i];
                pre_j = j;
            } else if (clen == dp[i]) {
                // 长度相同：保留编号字典序更小的序列
                // 因为 pre_j 一定是之前找到的编号更小的前驱，
                // 而 j 是更大的编号，默认保留 pre_j 即可得到字典序更小的序列
            }
        }

        pre[i] = pre_j;
    }

    // 输出所有结果
    for (int i = 1; i <= n; ++i) {
        cout << sum[i] << " \n"[i == n];
    }

    return 0;
}
