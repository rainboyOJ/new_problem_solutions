/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:18
 * update_at: 2026-08-14 15:18
 */
/* P1255 数楼梯：递推 f(n) = f(n-1) + f(n-2)，答案超出 64 位整数，用字符串模拟高精度加法。 */

#include <iostream>
#include <string>
#include <algorithm>

// 高精度加法：把两个用十进制字符串表示的大数相加
std::string add_big(const std::string& x, const std::string& y) {
    std::string result;
    int carry = 0;
    int i = (int)x.size() - 1;  // 从最低位开始
    int j = (int)y.size() - 1;

    // 两个数都没加完，或者还有进位时继续
    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) {
            sum += x[i] - '0';
            i -= 1;
        }
        if (j >= 0) {
            sum += y[j] - '0';
            j -= 1;
        }
        carry = sum / 10;
        result.push_back(char(sum % 10 + '0'));  // 先得到低位，最后整体反转
    }

    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    int n;
    std::cin >> n;

    std::string before = "1";   // 走到第 1 阶：1 种走法
    std::string current = "2";  // 走到第 2 阶：2 种走法
    if (n == 1) {
        std::cout << before << '\n';
        return 0;
    }

    // 只滚动保留前两项，避免保存整个 dp 数组
    for (int step = 3; step <= n; step += 1) {
        std::string next = add_big(before, current);
        before = current;
        current = next;
    }

    std::cout << current << '\n';
    return 0;
}
