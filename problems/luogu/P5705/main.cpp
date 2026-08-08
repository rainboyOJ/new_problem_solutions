/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    // 输入是一位带小数点的数字，当作字符串处理更容易反转
    char s[10];
    cin >> s;
    int len = strlen(s);
    // 从后往前输出每个字符，实现字符串反转
    for (int i = len - 1; i >= 0; i--) {
        cout << s[i];
    }
    cout << endl;
    return 0;
}
