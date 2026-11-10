/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:21
 * update_at: 2026-11-11 00:21
 */
// brute.cpp：通过计算 2^{n+1} - 2 独立实现
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    // 计算 2^{n+1}
    vector<int> a = {1};
    for (int i = 0; i < n + 1; ++i) {
        int carry = 0;
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

    // 减去 2
    int borrow = 2;
    for (size_t j = 0; j < a.size(); ++j) {
        a[j] -= borrow;
        if (a[j] < 0) {
            a[j] += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
    }
    while (a.size() > 1 && a.back() == 0) {
        a.pop_back();
    }

    for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
        cout << a[i];
    }
    cout << "\n";

    return 0;
}
