/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:58
 * update_at: 2026-10-05 02:58
 */
#include <iostream>
#include <string>
#include <map>

typedef long long ll;

ll n; // 游戏局数
std::map<std::string, std::string> win_over; // win_over[s] = 被 s 克制的出法

int main() {
    // 固定克制表：石头克剪刀，剪刀克布，布克石头
    win_over["Rock"] = "Scissors";
    win_over["Scissors"] = "Paper";
    win_over["Paper"] = "Rock";

    std::cin >> n;
    for (ll i = 1; i <= n; ++i) {
        std::string s1, s2;
        std::cin >> s1 >> s2;
        if (s1 == s2)
            std::cout << "Tie\n";
        else if (win_over[s1] == s2)
            std::cout << "Player1\n";
        else
            std::cout << "Player2\n";
    }
    return 0;
}
