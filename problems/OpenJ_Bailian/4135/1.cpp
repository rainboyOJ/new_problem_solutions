/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-15 22:09:50
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];
int max_spend;

//oisnip_beginbinary_search.cpp
//这是最快的写法
ll mid(ll l,ll r) { return (l+r) >> 1; }

//检查pos位置的值是否符合要求
bool check(ll money){
    int cnt = 0;
    ll sum = 0;
    for(int i =1;i<=n;i++) {
        if( sum + a[i] <= money) {
            sum += a[i];
        }
        else {
            cnt++;
            sum = a[i];
        }
    }
    cnt++;
    return cnt <= m;
}

//bs_find = binary search find
// 返回第一个满足条件的位置
// 如果所有的值都不满足条件,返回r, 
// !!! r位置对应的是Guard,一个虚拟的位置,保证一定各满足check
// !!! 写题目的时候一定要注意r的值,通常是n+1
// 保障初始区间[l,r],r一定是满足的,通常r = n+1
ll  bs_find(ll l,ll r) {
    while( l < r) {
        int m = mid(l,r);
        if( check(m)) //成立
            r = m;
        else //不成立,抛弃左半边
            l = m+1;
    }
    return l ;
}
//oisnip_end

void init(){
    std::cin >> n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
        if( max_spend < a[i])
            max_spend = a[i];
    }

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    ll pos = bs_find(max_spend, 1e9);
    std::cout << pos << "\n";
    
    return 0;
}
