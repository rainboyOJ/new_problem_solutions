/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:06
 * update_at: 2026-10-04 22:06
 */
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

int bits[3][6]; // bits[0/1/2][j] 表示时/分/秒的 6 位二进制中从高到低的第 j 位

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string time_text;
    cin >> time_text; // 形如 HH:MM:SS

    // 时、分、秒各自拆出 6 位二进制，依次占矩阵的一行（时 <= 23、分秒 <= 59 都放得下）
    ll value[3];
    value[0] = (time_text[0] - '0') * 10 + (time_text[1] - '0');
    value[1] = (time_text[3] - '0') * 10 + (time_text[4] - '0');
    value[2] = (time_text[6] - '0') * 10 + (time_text[7] - '0');
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            bits[i][j] = (value[i] >> (5 - j)) & 1;
        }
    }

    // 竖着取：每列自上而下（时、分、秒），列从左到右
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 3; i++) {
            cout << bits[i][j];
        }
    }
    cout << " ";
    // 横着取：三行首尾相接
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            cout << bits[i][j];
        }
    }
    cout << "\n";

    return 0;
}
