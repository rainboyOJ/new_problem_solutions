/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-01 02:00
 * update_at: 2026-08-01 02:00
 */

/* P1102 A-B 数对 */
/* 排序后，对每个 a[i] 用二分查找统计 a[i]+C 的出现次数。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const long long INF = 1e18; // 哨兵值，保证 bs_find 一定能找到答案

int n;
long long c;
long long a[MAXN]; // 输入数组，排序后使用；a[n+1]=INF 作为哨兵

int mid(int l,int r) {
    return (l+r) >> 1; //这是最快的写法
}

//检查pos位置的值是否符合要求
bool check(int pos,long long val){
    return a[pos] >= val;
}

//bs_find = binary search find
//返回 [l,r] 中第一个满足 a[pos] >= val 的位置，找不到返回 r
int bs_find(int l,int r,long long val) {
    while( l < r) {
        int m = mid(l,r);
        if( check(m,val)) //成立
            r = m;
        else //不成立,抛弃左半边
            l = m+1;
    }
    return l ;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 先排序
    sort(a + 1, a + n + 1);
    a[n + 1] = INF; // 哨兵，使二分查找找不到目标时能返回 n+1

    long long ans = 0;
    // 对每个 B = a[i]，用二分找 A = a[i]+c 的个数
    for (int i = 1; i <= n; i++) {
        long long target = a[i] + c; // 要找的 A
        // 等于 target 的元素个数 = 第一个 >= target+1 的位置 - 第一个 >= target 的位置
        int left = bs_find(1, n + 1, target);
        int right = bs_find(1, n + 1, target + 1);
        ans += right - left;
    }

    cout << ans << "\n";
    return 0;
}
