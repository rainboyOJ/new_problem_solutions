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
    int m, t, s; // 苹果总数, 吃一个所需分钟, 已过分钟
    cin >> m >> t >> s;
    if (t == 0) {
        // t = 0 时不能做除法，吃掉所有苹果需要 0 分钟，所以全被吃过
        cout << 0 << endl;
    } else {
        // 已经吃过的苹果数，向上取整
        int eaten = (s + t - 1) / t;
        int remaining = m - eaten;
        if (remaining < 0) remaining = 0; // 剩余不为负
        cout << remaining << endl;
    }
    return 0;
}
