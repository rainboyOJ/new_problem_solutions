/**
 * Author by Rainboy
 * Problem: POJ 3018 Giftbox
 * Analysis: 
 * 1. 这是一个多维偏序问题，即寻找 DAG 上的最长路。
 * 2. "任意排列" 等价于 -> 将盒子的维度内部排序后，对应位严格小于。
 * 3. 算法流程：
 * - 读取礼物和盒子，将每个物体的维度内部 sort。
 * - 将礼物也视为一个盒子加入列表。
 * - 对所有盒子进行排序（按维度字典序），保证拓扑序。
 * - 跑 O(N^2) 的 LIS (最长上升子序列) 变种 DP。
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 505;   // 盒子数量上限
const int MAXD = 1005;  // 维度上限

int n, d;

// 定义盒子结构体
struct Box {
    int id;             // 原始编号，用于调试或标记是否是礼物
    int dims[MAXD];     // 维度数组
    
    // 重载 < 运算符，用于给盒子列表排序 (DP的拓扑序)
    bool operator<(const Box &b) const {
        for(int i = 0; i < d; ++i) {
            if (dims[i] != b.dims[i])
                return dims[i] < b.dims[i];
        }
        return false;
    }
};

// 存储所有盒子（包括礼物）
vector<Box> boxes;
// DP 数组
int f[MAXN];

// 检查 box A 是否能放入 box B
// 前提：A 和 B 的维度都已经内部排序过
bool check_fit(const Box &a, const Box &b) {
    for(int i = 0; i < d; ++i) {
        if (a.dims[i] >= b.dims[i]) return false;
    }
    return true;
}

void solve() {
    boxes.clear();
    
    // 1. 读取并处理礼物 (作为第0个盒子)
    Box gift;
    gift.id = -1; // 标记为礼物
    for(int i = 0; i < d; ++i) scanf("%d", &gift.dims[i]);
    sort(gift.dims, gift.dims + d);
    boxes.push_back(gift);

    // 2. 读取并处理商店里的 N 个盒子
    for(int i = 0; i < n; ++i) {
        Box b;
        b.id = i;
        for(int j = 0; j < d; ++j) scanf("%d", &b.dims[j]);
        sort(b.dims, b.dims + d); // 内部维度排序
        boxes.push_back(b);
    }

    // 3. 对所有盒子进行排序，确定 DP 顺序
    // 如果 A 能放入 B，那么排序后 A 一定在 B 前面 (因为 A 的每一维都小于 B)
    sort(boxes.begin(), boxes.end());

    // 4. DP 初始化
    // f[i] 表示以 sorted_boxes[i] 为最外层盒子时的最大嵌套层数
    // 初始化为 -1 表示该状态不可达 (无法装入礼物)
    for(int i = 0; i <= n; ++i) f[i] = -1;

    // 找到礼物在排序后的位置
    int start_pos = -1;
    for(int i = 0; i <= n; ++i) {
        if (boxes[i].id == -1) { // 找到礼物
            start_pos = i;
            f[i] = 0; // 礼物本身不算一层盒子
            break;
        }
    }

    // 5. 开始 DP
    int ans = 0;
    // 从礼物的位置开始往后遍历
    for(int i = start_pos + 1; i <= n; ++i) {
        // 尝试把前面的盒子 j (或者礼物) 放进 i
        for(int j = start_pos; j < i; ++j) {
            // 如果盒子 j 是有效的 (能装礼物) 且 j 能放入 i
            if (f[j] != -1 && check_fit(boxes[j], boxes[i])) {
                if (f[j] + 1 > f[i]) {
                    f[i] = f[j] + 1;
                }
            }
        }
        if (f[i] > ans) ans = f[i];
    }

    // 6. 输出结果
    if (ans == 0) {
        printf("Please look for another gift shop!\n");
    } else {
        printf("%d\n", ans);
    }
}

int main() {
    // 多组测试数据
    while (scanf("%d %d", &n, &d) != EOF) {
        solve();
    }
    return 0;
}
