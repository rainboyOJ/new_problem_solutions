#include <iostream>
#include <algorithm> // 用于 std::max
using namespace std;

const int MAXN = 1000005; // 树木数量最大值 10^6
int N;           // 树木的数量
long long M;     // 需要的木材总量 (注意：M可能很大，虽然题目说2*10^9在int范围内，但累加和可能超，用long long更保险)
int h[MAXN];     // 存储每棵树的高度

// check 函数：模拟锯片在 height 高度时，能得到的木材总量
// 如果得到的木材 >= M，返回 true (表示这个高度是可行的，但可能还能更高)
// 如果得到的木材 < M，返回 false (表示这个高度太高了，锯不到足够的木头)
bool check(int height) {
    long long sum = 0; // 累加砍下来的木材长度，必须用 long long 防止溢出
    for (int i = 1; i <= N; i++) {
        // 只有当树比锯片高的时候，才能砍下木材
        if (h[i] > height) {
            sum += (long long)(h[i] - height);
        }
    }
    // 如果砍下的总长度 >= 需要的 M，说明这个高度是“达标”的
    return sum < M;
}

// 找到第一个不成立的
int bs_find(int l, int r) {
    while (l < r) {
        int mid = (l + r ) >> 1; 

        if (check(mid)) { 
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    // 当 l == r 时，循环结束，l (或 r) 就是我们要找的最大高度
    return l;
}

int main() {
    // 1. 读入数据
    // 建议在数据量大时关闭流同步，加快 cin 速度
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;

    int max_h = 0; // 记录最高的树，作为二分的右边界
    for (int i = 1; i <= N; i++) {
        cin >> h[i];
        if (h[i] > max_h) {
            max_h = h[i];
        }
    }

    // 2. 开始二分查找
    // 锯片高度范围：从 0 到 最高的树(max_h)
    long long ans = bs_find(0, max_h+1);

    // 3. 输出结果
    cout << ans-1 << endl;

    return 0;
}
