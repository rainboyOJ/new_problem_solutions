#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

const int maxn=1e4+5;
int n;
ull a[maxn];
char s[maxn];

ull rk_hash(char * str) {
    ull p = 131,H = 0;
    int n = strlen(str);
    for(int i = 0 ;i < n;i++) {
        H = H * p + (str[i] - 'a' +1);
    }
    return H;
}


int main (int argc, char *argv[]) {
    scanf("%d",&n);
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        scanf("%s",s);
        a[i] = rk_hash(s);
    }
    std::sort(a+1,a+1+n);
    int ans = 0;


    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        if( a[i] != a[i-1])
            ans++;
    }
    
    printf("%d\n",ans);
    return 0;
}
