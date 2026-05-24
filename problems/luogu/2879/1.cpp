/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-13
 * Problem: P2879 [USACO07JAN] Tallest Cow S
 * Algorithm: Difference Array (差分数组)
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// 差分数组
// c[i] 表示第 i 个数相对于前一个数的增量（在本题逻辑中用于累积减少量）
int c[10005]; 

// 用于去重，记录已经处理过的关系
// key: pair<int, int>, value: bool
map<pair<int, int>, bool> visited;

int main() {
    // 优化 I/O 效率
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, I, H, R;
    // N: 奶牛数, I: 最高奶牛编号, H: 最高身高, R: 关系数
    if (!(cin >> N >> I >> H >> R)) return 0;

    for (int i = 0; i < R; ++i) {
        int a, b;
        cin >> a >> b;
        
        // 保证 a < b，方便处理区间
        if (a > b) swap(a, b);
        
        // 如果 a 和 b 是相邻的，中间没有奶牛，不需要处理
        // 例如 1 和 2，中间区间为空
        if (a + 1 >= b) continue;

        // 去重：如果这对关系已经处理过，直接跳过
        if (visited[{a, b}]) continue;
        visited[{a, b}] = true;

        // 核心逻辑：差分数组更新
        // 也就是区间 [a+1, b-1] 的全体数值 -1
        // 根据差分数组定义: 
        // D[L] -= 1
        // D[R+1] += 1
        // 这里 L = a+1, R = b-1 -> R+1 = b
        c[a + 1] -= 1;
        c[b] += 1;
    }

    // 计算前缀和并输出
    // current_reduction 表示当前位置相对于最高身高 H 减少了多少
    int current_reduction = 0;
    for (int i = 1; i <= N; ++i) {
        current_reduction += c[i];
        // 最终身高 = 最高身高 + 累积的减少量
        // (注意 current_reduction 是负数或0)
        cout << H + current_reduction << "\n";
    }

    return 0;
}
