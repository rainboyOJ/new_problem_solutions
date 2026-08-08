#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

int n;
int w[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> w[i][j];
            w[j][i] = w[i][j];
        }
    }

    int answer = 0;

    // 对于每个武将 i：
    // 如果小涵第一步先拿 i，
    // 计算机一定会抢走和 i 默契值最大的那个武将。
    // 那么小涵以后能和 i 组成的最好搭档，只能是“这一行的次大值”对应的人。
    // 在所有起手武将里取最大的次大值，就是最终答案。
    for (int i = 1; i <= n; i++) {
        int first_max = 0;
        int second_max = 0;
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                continue;
            }
            if (w[i][j] > first_max) {
                second_max = first_max;
                first_max = w[i][j];
            }
            else if (w[i][j] > second_max) {
                second_max = w[i][j];
            }
        }
        answer = max(answer, second_max);
    }

    cout << 1 << '\n';
    cout << answer << '\n';

    return 0;
}
