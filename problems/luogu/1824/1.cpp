/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-25 08:47:01
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e5+5; // 数据范围是1e5，开稍微大一点
int n, m;
int a[maxn];

// 计算中间值
int mid(int l,int r) { return (l+r) >> 1; }

// check 函数逻辑：
// 我们尝试以 val 作为最小间距来放牛
// 如果 【不能】 放下 m 头牛，说明 val 太大了，返回 true (让二分往左走)
// 如果 【能】 放下 m 头牛，说明 val 合法（可能还有更大的），返回 false (让二分往右走)
bool check(int val){
    int cow_cnt = 1;       // 第一头牛肯定放在第一个位置
    int last_pos = a[1];   // 上一头牛的位置
    
    for(int i = 2; i <= n; i++) {
        // 如果当前隔间和上一头牛的距离 >= val，就可以放一头
        if(a[i] - last_pos >= val) {
            cow_cnt++;
            last_pos = a[i];
        }
    }
    
    // 如果放下的牛数量 < m，说明 val 这个距离太大了，这种方案【不满足】题目要求
    // 对应二分模板：我们需要找更小的距离，所以返回 true 让 r = m
    return cow_cnt < m;
}

// bs_find = binary search find
// 返回第一个满足条件(check返回true)的位置
// 在本题逻辑中，返回的是第一个【不可行/距离过大】的位置
int bs_find(int l,int r) {
    while( l < r) {
        int m = mid(l,r);
        if( check(m)) // 如果距离太大了(不可行)
            r = m;    // 尝试缩小距离，保留这个不可行的边界
        else          // 如果距离可行
            l = m+1;  // 尝试更大的距离
    }
    return l ;
}

void init(){
    // 读入数据
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    // 贪心策略的前提是位置有序，题目没保证有序，必须排序
    sort(a + 1, a + 1 + n);
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    init();

    // 二分范围：
    // 最小距离可能是 0 (或者1)
    // 最大距离可能是 a[n] - a[1] (头尾差距)，为了作为哨兵，右边界设得稍大一点 1e9+1
    // bs_find 将返回第一个 "不可行" 的距离
    int ans_idx = bs_find(0, 1000000001);

    // 因为 ans_idx 是第一个不可行的，所以 ans_idx - 1 就是最后一个可行的（最大的最小距离）
    cout << ans_idx - 1 << endl;
    
    return 0;
}
