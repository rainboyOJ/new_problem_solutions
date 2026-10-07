/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:55
 * update_at: 2026-10-06 14:59
 */
#include <iostream>
using namespace std;

typedef long long ll;
const ll MOD = 20123;          // 密钥模数
const int MAXN = 10005;        // 最大层数
const int MAXM = 105;          // 每层最大房间数

int n, m;                      // 层数、每层的房间数
ll s[MAXN][MAXM];              // s[i][j]：第 i 层 j 号房间是否有楼梯
ll x[MAXN][MAXM];              // x[i][j]：第 i 层 j 号房间指示牌数字
ll pre[MAXN][MAXM + 1];        // pre[i][j]：第 i 层 [0, j) 内楼梯个数
int stairs[MAXN][MAXM];        // 每层有楼梯的房间编号，按升序存放
int cnt[MAXN];               // 每层楼梯总数

// 在第 floor 层从 start 出发，返回逆时针数第 x 个有楼梯的房间编号
int climb(int floor_id, int start, ll sign) {
    int total = cnt[floor_id];               // 本层楼梯总数
    // 第 sign 个与第 k 个相同，去掉绕整圈的影响
    ll k = (sign - 1) % total + 1;
    ll before = total - pre[floor_id][start]; // [start, M-1] 中的楼梯数
    if (before >= k) {
        // 不用回绕：start 及其之后的第 k 个楼梯
        return stairs[floor_id][pre[floor_id][start] + k - 1];
    }
    // 回绕到 [0, start) 段，取剩余的第 k - before 个楼梯
    return stairs[floor_id][k - before - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> s[i][j] >> x[i][j];
        }
        // 预处理前缀和与楼梯编号
        pre[i][0] = 0;
        cnt[i] = 0;
        for (int j = 0; j < m; j++) {
            pre[i][j + 1] = pre[i][j] + s[i][j];
            if (s[i][j]) {
                stairs[i][cnt[i]++] = j;
            }
        }
    }

    int room;
    cin >> room;

    ll key = 0;
    for (int i = 0; i < n; i++) {
        key = (key + x[i][room]) % MOD; // 累加本层进入房间的指示牌数字
        room = climb(i, room, x[i][room]); // 找到上层的进入房间
    }

    cout << key << "\n";
    return 0;
}
