/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

char line[205]; // 存储每行输入的字符串
int n;          // 矩阵大小

int main() {
    // 读入第一行，确定 n
    cin >> line;
    n = strlen(line);
    // 把所有行拼成一行字符
    string all = line;
    for (int i = 2; i <= n; i++) {
        cin >> line;
        all += line;
    }

    cout << n << " "; // 先输出矩阵大小
    char cur = '0';   // 从 0 的游程开始统计
    int cnt = 0;
    for (char ch : all) {
        if (ch == cur) {
            cnt++;
        } else {
            cout << cnt << " ";
            cur = ch;
            cnt = 1;
        }
    }
    cout << cnt; // 最后一段游程
    return 0;
}
