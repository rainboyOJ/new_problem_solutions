/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:03
 * update_at: 2026-11-10 23:03
 */
#include <iostream>

using namespace std;

// 上界取 10000001
const int MAXV = 10000005;

// bad[i] 表示数字 i 是否不能报出
bool bad[MAXV + 5];

// nxt[i] 记录合法数 i 的下一个合法数
int nxt[MAXV + 5];

// 检查十进制表示中是否含有数字 7
inline bool check_has_seven(int x) {
    while (x > 0) {
        if (x % 10 == 7) return true;
        x /= 10;
    }
    return false;
}

// 埃氏筛预处理
void init() {
    for (int i = 1; i <= MAXV; ++i) {
        if (bad[i]) continue;
        if (check_has_seven(i)) {
            // 将其所有倍数标记为不可报出
            for (int j = i; j <= MAXV; j += i) {
                bad[j] = true;
            }
        }
    }

    // 构建后继表：链式记录每个合法数下一个是谁
    int last = 0;
    for (int i = 1; i <= MAXV; ++i) {
        if (!bad[i]) {
            nxt[last] = i;
            last = i;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        int x;
        cin >> x;
        if (bad[x]) {
            cout << -1 << "\n";
        } else {
            cout << nxt[x] << "\n";
        }
    }

    return 0;
}
