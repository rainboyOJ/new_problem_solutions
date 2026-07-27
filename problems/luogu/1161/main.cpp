/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

bool lights[2000005]; // lights[id] = true 表示灯亮，false 表示灯灭
int n;

int main() {
    cin >> n;
    double a;
    int t;
    for (int i = 1; i <= n; i++) {
        cin >> a >> t;
        for (int k = 1; k <= t; k++) {
            int id = int(a * k); // 取整得到灯编号
            lights[id] = !lights[id]; // 切换开关
        }
    }
    // 找到唯一亮着的灯
    for (int i = 1; ; i++) {
        if (lights[i]) {
            cout << i;
            return 0;
        }
    }
}
