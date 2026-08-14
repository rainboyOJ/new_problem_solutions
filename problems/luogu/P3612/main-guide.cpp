/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:08
 * update_at: 2026-08-14 15:08
 */
#include <iostream>
#include <string>

std::string s;       // 初始字符串
long long base_len;  // 初始字符串的长度
long long n;         // 要找第 n 个字符（n 可能达到 1e18，必须用 long long）

// 在长度为 len 的串中找第 pos 个字符：
// 后半段等于前半段整体右移一位，所以把 pos 映射回前半段，问题规模折半
char find(long long pos, long long len) {
    if (pos <= base_len) { // 已经落回初始字符串内，直接返回
        return s[pos - 1];
    }
    long long half = len / 2;
    if (pos == half + 1) { // 后半段第 1 个字符来自前半段最后一个字符
        pos = half;
    } else if (pos > half + 1) { // 其余位置比前半段对应位置多 1
        pos = pos - half - 1;
    }
    return find(pos, half);
}

int main() {
    std::cin >> s >> n;
    base_len = static_cast<long long>(s.size());

    long long len = base_len;
    while (len < n) { // 倍增到第一个不小于 n 的长度
        len *= 2;
    }

    std::cout << find(n, len) << '\n';
    return 0;
}
