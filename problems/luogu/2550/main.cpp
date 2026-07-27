/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int win[7];      // 中奖号码
bool is_win[34]; // 标记某个号码是否中奖号码（号码范围 1~33）
int ans[8];      // ans[i] 表示匹配 i 个号码的彩票数
int n;

int main() {
    cin >> n;
    for (int i = 0; i < 7; i++) {
        cin >> win[i];
        is_win[win[i]] = true;
    }
    for (int i = 1; i <= n; i++) {
        int cnt = 0; // 该张彩票命中个数
        for (int j = 0; j < 7; j++) {
            int x;
            cin >> x;
            if (is_win[x]) cnt++;
        }
        ans[7 - cnt]++; // 匹配 cnt 个对应第 7-cnt 等奖
    }
    for (int i = 0; i < 7; i++) cout << ans[i] << " ";
    return 0;
}
