/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:21
 * update_at: 2026-11-11 00:21
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    // 采用高精度大整数记录 A_n，小端序存储（A[0] 为个位）
    // 初始 A_0 = 0，用空 vector 表示
    vector<int> a;

    // 递推 n 次：A_i = 2 * A_{i-1} + 2
    for (int i = 1; i <= n; ++i) {
        int carry = 2; // 乘 2 之后加 2，等价于将初始进位设为 2
        for (size_t j = 0; j < a.size(); ++j) {
            int cur = a[j] * 2 + carry;
            a[j] = cur % 10;
            carry = cur / 10;
        }
        while (carry > 0) {
            a.push_back(carry % 10);
            carry /= 10;
        }
    }

    // 从高位到低位输出
    for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
        cout << a[i];
    }
    cout << "\n";

    return 0;
}
