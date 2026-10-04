/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:07
 * update_at: 2026-10-05 03:07
 */
// main.cpp：逐个药名整理大小写，首位字母大写、其余字母小写。
#include <cctype>
#include <iostream>
#include <string>

typedef long long ll;

ll n; // 需要整理的药名个数，不超过 100

int main() {
    std::cin >> n;
    for (ll i = 1; i <= n; i++) {
        std::string word;
        std::cin >> word;
        ll len = word.size(); // 每个药名长度不超过 20
        for (ll j = 0; j < len; j++) {
            // 首位字母转大写，其余字母转小写；数字和 - 不是字母，保持不变
            if (j == 0) {
                word[j] = std::toupper(word[j]);
            } else {
                word[j] = std::tolower(word[j]);
            }
        }
        std::cout << word << std::endl;
    }
    return 0;
}
