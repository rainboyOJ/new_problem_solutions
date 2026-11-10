/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:59
 * update_at: 2026-11-10 23:59
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 字符转换为数值
int char_to_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

// 检查数组是否构成回文
bool is_palindrome(const vector<int>& num) {
    int len = num.size();
    for (int i = 0; i < len / 2; ++i) {
        if (num[i] != num[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

// 高精度 N 进制反转相加
vector<int> add_reverse(const vector<int>& num, int base) {
    vector<int> rev = num;
    reverse(rev.begin(), rev.end());

    vector<int> res;
    int carry = 0;
    int len = num.size();

    for (int i = 0; i < len; ++i) {
        int sum = num[i] + rev[i] + carry;
        res.push_back(sum % base);
        carry = sum / base;
    }
    if (carry > 0) {
        res.push_back(carry);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string m_str;
    if (!(cin >> n >> m_str)) return 0;

    // 低位在前存储
    vector<int> num;
    for (int i = static_cast<int>(m_str.size()) - 1; i >= 0; --i) {
        num.push_back(char_to_val(m_str[i]));
    }

    // 最多进行 30 步加法模拟
    for (int step = 1; step <= 30; ++step) {
        num = add_reverse(num, n);
        if (is_palindrome(num)) {
            cout << "STEP=" << step << "\n";
            return 0;
        }
    }

    cout << "Impossible!\n";
    return 0;
}
