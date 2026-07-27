/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int cnt[26]; // cnt[i] 记录大写字母 'A'+i 的出现次数
char line[105];

int main() {
    // 读入 4 行文本，统计大写字母
    for (int k = 1; k <= 4; k++) {
        cin.getline(line, 105);
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] >= 'A' && line[i] <= 'Z')
                cnt[line[i] - 'A']++;
        }
    }

    // 找最大高度
    int maxh = 0;
    for (int i = 0; i < 26; i++)
        if (cnt[i] > maxh) maxh = cnt[i];

    // 从最高层向下输出柱状图
    for (int h = maxh; h >= 1; h--) {
        for (int i = 0; i < 26; i++) {
            if (cnt[i] >= h) cout << "*";
            else cout << " ";
            if (i != 25) cout << " ";
        }
        cout << "\n";
    }

    // 输出字母行
    for (int i = 0; i < 26; i++) {
        cout << char('A' + i);
        if (i != 25) cout << " ";
    }
    return 0;
}
