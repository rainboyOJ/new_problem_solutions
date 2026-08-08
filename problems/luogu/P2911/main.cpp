/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int cnt[85]; // cnt[s] 记录点数和 s 出现的次数（最大和 = s1+s2+s3 <= 80）
int s1, s2, s3;

int main() {
    cin >> s1 >> s2 >> s3;
    // 三重循环枚举所有骰子点数组合
    for (int a = 1; a <= s1; a++)
        for (int b = 1; b <= s2; b++)
            for (int c = 1; c <= s3; c++)
                cnt[a + b + c]++;
    // 找出现次数最多的最小和
    int best_sum = 0, best_cnt = 0;
    for (int s = 3; s <= s1 + s2 + s3; s++) {
        if (cnt[s] > best_cnt) {
            best_cnt = cnt[s];
            best_sum = s;
        }
    }
    cout << best_sum;
    return 0;
}
