#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const int MAXN = 5005;
long long a[MAXN], b[MAXN];

int main() {
    // 优化标准输入输出流
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    // 计算不翻转时的初始总权值和
    long long init_sum = 0;
    for (int i = 1; i <= n; i++) {
        init_sum += a[i] * b[i];
    }

    long long max_sum = init_sum;

    // 1. 枚举奇数长度子数组的对称中心（长度为 1 的单点中心 i）
    for (int i = 1; i <= n; i++) {
        long long cur = init_sum;
        int l = i - 1, r = i + 1;
        while (l >= 1 && r <= n) {
            // 翻转导致 a[l] 移动到 r，a[r] 移动到 l
            cur += (a[l] * b[r] + a[r] * b[l]) - (a[l] * b[l] + a[r] * b[r]);
            max_sum = max(max_sum, cur);
            l--;
            r++;
        }
    }

    // 2. 枚举偶数长度子数组的对称中心（长度为 2 的相邻缝隙中心 (i, i+1)）
    for (int i = 1; i < n; i++) {
        long long cur = init_sum;
        int l = i, r = i + 1;
        while (l >= 1 && r <= n) {
            cur += (a[l] * b[r] + a[r] * b[l]) - (a[l] * b[l] + a[r] * b[r]);
            max_sum = max(max_sum, cur);
            l--;
            r++;
        }
    }

    cout << max_sum << "\n";
    return 0;
}
