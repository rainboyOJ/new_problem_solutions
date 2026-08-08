#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;

int a1[maxn];
int a2[maxn];
int a3[maxn];
int n,m;

void add(int l,int r,int idx) {
    int *a;
    if(idx== 1) a = a1;
    if(idx== 2) a = a2;
    if(idx== 3) a = a3;

    a[l]++;
    a[r+1]--;
}

void review(int idx) {
    int *a;
    if(idx== 1) a = a1;
    if(idx== 2) a = a2;
    if(idx== 3) a = a3;

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        a[i]  += a[i-1];
    }
}

void debug(int idx) {
    int *a;
    if(idx== 1) a = a1;
    if(idx== 2) a = a2;
    if(idx== 3) a = a3;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cout << a[i] << " " ;
    }
    std::cout  << "\n";

}


int main (int argc, char *argv[]) {

    std::cin >> n;
    std::cin >> m;

    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int l,r,k;
        std::cin >> l;
        std::cin >> r;
        std::cin >> k;
        add(l,r,k);
    }

    // hui fu 
    review(1);
    review(2);
    review(3);

    // debug(1);
    // debug(2);
    // debug(3);

    int ans = 0;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        if( a1[i] >= 1 && a2[i] >= 1 && a3[i] == 0)
            ans++;
    }
    std::cout << ans << "\n";

    
    return 0;
}
