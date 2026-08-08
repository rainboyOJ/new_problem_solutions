/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-31 17:10:31
 * desc: 使用三路切分 (3-Way Partition) 实现 Quick Select
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e6 + 10; // 开稍微大一点
int a[maxn];
int n, k;

// 简单的快读函数 (为了防止 IO 导致的超时)
inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}

// 三路 Quick Select
// l, r: 当前处理的区间下标
// k: 全局目标的排名 (绝对位置)
int quick_select(int l, int r, int k) {
    if (l >= r) return a[l];

    swap(a[l],a[(l+r)/2]);
    int key = a[l];

    // 2. 三路切分初始化
    int lt = l;      // [l, lt-1] < key
    int gt = r;      // [gt+1, r] > key
    int i = l + 1;   // [lt, i-1] == key

    // 3. 扫描并分类
    while (i <= gt) {
        if (a[i] < key) {
            swap(a[i], a[lt]);
            lt++;
            i++;
        } 
        else if (a[i] > key) {
            swap(a[i], a[gt]);
            gt--;
            // 注意：此时 i 不动，因为从后面换过来的数还没检查
        } 
        else {
            i++;
        }
    }

    // 切分完毕后，数组分为三段：
    // Range 1: [l, lt-1]   < key
    // Range 2: [lt, gt]    == key
    // Range 3: [gt+1, r]   > key

    // 4. 判断 k 在哪个区间，只递归那一个区间
    if (k < lt) {
        // 目标在左边
        return quick_select(l, lt - 1, k);
    } 
    else if (k > gt) {
        // 目标在右边
        return quick_select(gt + 1, r, k);
    } 
    else {
        // 目标就在中间的“等于区”，直接返回 key
        return key;
    }
}

int main() {
    // 随机数种子初始化

    // 使用快读读入
    n = read();
    k = read(); // 题目中 k 是 0-indexed，直接用即可
    
    for (int i = 0; i < n; ++i) {
        a[i] = read();
    }

    // 搜索范围 0 到 n-1，找第 k 小
    printf("%d\n", quick_select(0, n - 1, k));

    return 0;
}
