/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:44
 * update_at: 2026-10-05 12:44
 */

#include <cstdio>
#include <queue>

using namespace std;

typedef long long ll;

const int MAXN = 30;

ll xmin[MAXN], xmax[MAXN], ymin[MAXN], ymax[MAXN]; // 每张幻灯片（A,B,...）的边界
int candidates[MAXN]; // 每个数字点的候选字母集合，第 j 位为 1 表示字母 j 在候选中
int match_letter[MAXN]; // match_letter[j] = 占用字母 j 的数字编号（-1 表示未占用）

int main() {
    int n;
    scanf("%d", &n);

    // 读入 n 个矩形，按顺序对应字母 A,B,...
    for (int j = 0; j < n; j++) {
        scanf("%lld %lld %lld %lld", &xmin[j], &xmax[j], &ymin[j], &ymax[j]);
    }

    // 读入 n 个数字点，计算每个点落在哪些矩形内（含边界）
    for (int i = 0; i < n; i++) {
        ll x, y;
        scanf("%lld %lld", &x, &y);
        candidates[i] = 0;
        for (int j = 0; j < n; j++) {
            if (xmin[j] <= x && x <= xmax[j] && ymin[j] <= y && y <= ymax[j]) {
                candidates[i] |= (1 << j);
            }
        }
    }

    for (int j = 0; j < n; j++) {
        match_letter[j] = -1;
    }

    queue<int> q;
    // 初始候选唯一的数字入队
    for (int i = 0; i < n; i++) {
        int bits = candidates[i] & -candidates[i]; // 最低位的 1
        if (candidates[i] != 0 && (candidates[i] ^ bits) == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        // 取唯一候选字母
        int letter = 0;
        int tmp = candidates[i];
        while (tmp > 1) {
            tmp >>= 1;
            letter++;
        }

        if (match_letter[letter] != -1) {
            printf("None\n");
            return 0;
        }
        match_letter[letter] = i;

        int bit = (1 << letter);
        for (int k = 0; k < n; k++) {
            if (k == i) continue;
            if (candidates[k] & bit) {
                candidates[k] &= ~bit;
                // 删除后候选恰好为 1 个，入队
                int low = candidates[k] & -candidates[k];
                if (candidates[k] != 0 && (candidates[k] ^ low) == 0) {
                    q.push(k);
                }
            }
        }
    }

    // 仍有字母没被占用 → 多解或无解
    for (int j = 0; j < n; j++) {
        if (match_letter[j] == -1) {
            printf("None\n");
            return 0;
        }
    }

    // 按字母升序输出
    for (int j = 0; j < n; j++) {
        printf("%c %d\n", 'A' + j, match_letter[j] + 1);
    }

    return 0;
}
