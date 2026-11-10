/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:16
 * update_at: 2026-11-11 00:16
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int s_idx, t_idx, w;
string str;

// 生成下一个字典序合法的 Jam 数字
bool next_jam(string& cur) {
    char max_char = static_cast<char>('a' + t_idx - 1);

    // 从后向前寻找第一个尚未达到上界的字符位置
    int pos = -1;
    for (int i = w - 1; i >= 0; --i) {
        // 第 i 位后面还要放 w - 1 - i 个严格递增的字符
        char limit = static_cast<char>(max_char - (w - 1 - i));
        if (cur[i] < limit) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        return false; // 已达到最大组合
    }

    // 该位自增 1
    cur[pos]++;

    // 其后各位紧随其后取连续的最小字符
    for (int i = pos + 1; i < w; ++i) {
        cur[i] = static_cast<char>(cur[i - 1] + 1);
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> s_idx >> t_idx >> w)) return 0;
    if (!(cin >> str)) return 0;

    for (int cnt = 0; cnt < 5; ++cnt) {
        if (next_jam(str)) {
            cout << str << "\n";
        } else {
            break;
        }
    }

    return 0;
}
