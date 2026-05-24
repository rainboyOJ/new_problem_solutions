/*
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-24 14:36:17
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
struct node {
    int val;
    int pos;
} a[maxn];

bool compare(node & a ,node &b) {
    if( a.val == b.val) {
        return a.pos < b.pos;
    }
    return a.val < b.val;
}
//这是最快的写法
int mid(int l,int r) { return (l+r) >> 1; }


// 第一个 >val 的位置
// 第一个>4 的位置,就是第一个>=5的位置
int bs_find_g(int l,int r,int val) {
    while( l < r) {
        int m = mid(l,r);
        if( a[m].val > val ) //成立
            r = m;
        else //不成立,抛弃左半边
            l = m+1;
    }
    return l ;
}

//只比较位置
int bs_find_pos(int l,int r,int pos) {
    while( l < r) {
        int m = mid(l,r);
        if( a[m].pos > pos ) //成立
            r = m;
        else //不成立,抛弃左半边
            l = m+1;
    }
    return l ;
}


void init(){
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int t;
        std::cin >> t;
        a[i].pos = i;
        a[i].val = t;
    }
    std::sort(a+1,a+1+n,compare);
    // for(int i = 1;i <= n ;++i ) printf("%d ",a[i].pos);
    // printf("\n");
    // for(int i = 1;i <= n ;++i ) printf("%d ",a[i].val);
    // printf("\n");
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    init();
    int T;
    std::cin >> T;
    while (T--) {
        int l,r,x;
        std::cin >> l >> r >> x;
        
        // 找到第一个 val >= x 的位置
        int L = bs_find_g(1, n+1, x-1);
        if( L == n+1 || a[L].val != x) {
            std::cout << 0 << "\n";
            continue;
        }

        //第一个 > x 的位置
        int R = bs_find_g(1, n+1,x);

        //第一个>= l的位置
        int ll = bs_find_pos(L, R, l-1);

        //第一个> r的位置
        int rr = bs_find_pos(L, R, r);
        std::cout << rr- ll << "\n";
    }

    return 0;
}

