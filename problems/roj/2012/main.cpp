/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:25
 * update_at: 2026-10-06 09:25
 */
#include <iostream>
using namespace std;

typedef long long ll;

int n;
int digit[15];   // 输入的数字集合，允许重复使用
bool in_set[15]; // in_set[d] 表示数字 d 是否在给定集合中，用来校验乘积的每一位
ll answer;

// 判断 value 的十进制写法是否恰好 length 位，且每一位数字都在给定集合中
bool valid(ll value, int length) {
    int cnt = 0;
    while (value > 0) {
        int d = value % 10;
        if (!in_set[d]) {
            return false;
        }
        value /= 10;
        cnt++;
    }
    return cnt == length;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> digit[i];
        in_set[digit[i]] = true;
    }

    // 枚举三位被乘数 a
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                int a = digit[i] * 100 + digit[j] * 10 + digit[k];
                // 枚举两位乘数 b
                for (int p = 1; p <= n; p++) {
                    for (int q = 1; q <= n; q++) {
                        int b = digit[p] * 10 + digit[q];
                        // 两条部分积各 3 位，最终积 4 位，且三个乘积每位数字都合法
                        if (valid(a * (b % 10), 3) && valid(a * (b / 10), 3) && valid(a * b, 4)) {
                            answer++;
                        }
                    }
                }
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
