#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

const int maxn = 1e6+5;
ull ans;

int n;
const ull p = 131;
ull pp[maxn];
char s1[maxn]; // 原字符串
char s2[maxn]; // s1的反串
ull h1[maxn]; // s1的 前缀hash
ull h2[maxn]; // s2的 后缀hash

ull hash_range_s1(int l,int r) {
    return h1[r] - h1[l-1]* pp[r-l+1];
}

ull hash_range_s2(int l,int r) {
    return h2[l] - h2[r+1]* pp[r-l+1];
}


void init() {
    scanf("%d",&n);
    scanf("%s",s1+1);
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        s2[i] = (s1[i] == '0' ? '1' : '0');
    }

    // 求前缀hash
    for(int i = 1;i <= n ;++i ) // i: 1->n
        h1[i] = h1[i-1] * p + (s1[i]);

    for(int i = n;i >=1; --i)
        h2[i] = h2[i+1] * p + s2[i];

    pp[0] = 1;
    for(int i = 1;i <= n ;++i ) pp[i] = pp[i-1] * p;
}


bool check(int pos,int len) {
    ull t1 = hash_range_s1(pos-len+1, pos) ;
    ull t2 = hash_range_s2(pos+1, pos+1 + len -1);
    return t1 == t2;
}


int bin_search(int pos) {
    int maxlen = min(pos,n-pos);
    int l = 1 , r = maxlen+1;

    // 查找第一个失败的位置
    while( l < r ) {
        int mid = (l + r ) >> 1;

        if( !check(pos,mid) ) {
            r = mid;
        }
        else l = mid + 1;

    }
    return l - 1;
}



int main (int argc, char *argv[]) {
    init();

    // ull t1 = hash_range_s1(1, 2);
    // ull t2 = hash_range_s2(3, 4);
    // std::cout << t1 << "\n";
    // std::cout << t2 << "\n";

    // 枚举中间位置
    for(int i = 1;i <= n-1 ;++i ) // i: 1->n
    {
        int tval = bin_search(i);
        // printf("pos = %d ,ans = %d\n",i,tval);
        ans += tval;
    }
   
    printf("%lld",ans);
    return 0;
}
