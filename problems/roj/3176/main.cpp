/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 围栏：线段树区间覆盖（记时间戳）+ 端点自底向上递推
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef long long ll;

const int ORIGIN = 100001; // 坐标整体平移量
const int SIZE = 1 << 18;   // 线段树叶子数
const int GROUND = 0;       // 地面编号

int stamp[SIZE * 2]; // 节点整段被覆盖的层号（越大表示覆盖越晚）
int who[SIZE * 2];   // 节点整段被哪条围栏覆盖，0 表示地面

int f_left[300005], f_right[300005]; // 围栏端点（编号即层号 y）
int down[300005][2];                 // 每条围栏左右端点到地面的最少水平距离

// 把横坐标区间 [left,right] 整段覆盖成围栏 value
void assign_range(int left, int right, int value) {
    left += SIZE;
    right += SIZE + 1;
    while (left < right) {
        if (left & 1) {
            stamp[left] = who[left] = value;
            left++;
        }
        if (right & 1) {
            right--;
            stamp[right] = who[right] = value;
        }
        left >>= 1;
        right >>= 1;
    }
}

// 横坐标 x 正上方最近的一条围栏编号（没有围栏时是地面）
int query(int x) {
    int node = x + SIZE;
    int latest = 0, res = GROUND;
    while (node) {
        if (stamp[node] > latest) { // 越晚的覆盖越贴近上方
            latest = stamp[node];
            res = who[node];
        }
        node >>= 1;
    }
    return res;
}

// 从 (x, 某个高度) 竖直下落，再沿接住它的围栏走到端点下到地面
int ground_cost(int x) {
    int below = query(x);
    int a = f_left[below], b = f_right[below];
    int da = (a > x ? a - x : x - a) + down[below][0];
    int db = (b > x ? b - x : x - b) + down[below][1];
    return da < db ? da : db;
}

int main() {
    int n, s;
    if (scanf("%d %d", &n, &s) != 2) {
        return 0;
    }
    s += ORIGIN;
    f_left[GROUND] = f_right[GROUND] = ORIGIN; // 地面：两端点都取原点
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        f_left[i] = a + ORIGIN;
        f_right[i] = b + ORIGIN;
    }

    // 自底向上：查两端点脚下的围栏（此时树里只有更低的层），再把本层覆盖上去
    for (int level = 1; level <= n; level++) {
        down[level][0] = ground_cost(f_left[level]);
        down[level][1] = ground_cost(f_right[level]);
        assign_range(f_left[level], f_right[level], level);
    }
    printf("%d\n", ground_cost(s));
    return 0;
}
