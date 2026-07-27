/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

char s[105]; // 原始字符串
int n;

// 统计字符串中 "VK" 子串的个数
int count_vk(char *str, int len) {
    int cnt = 0;
    for (int i = 0; i < len - 1; i++) {
        if (str[i] == 'V' && str[i + 1] == 'K') cnt++;
    }
    return cnt;
}

int main() {
    cin >> n >> s;
    int ans = count_vk(s, n);
    // 枚举修改每个位置
    for (int i = 0; i < n; i++) {
        char bak = s[i];
        s[i] = (s[i] == 'V') ? 'K' : 'V'; // 切换字符
        ans = max(ans, count_vk(s, n));
        s[i] = bak; // 恢复
    }
    cout << ans;
    return 0;
}
