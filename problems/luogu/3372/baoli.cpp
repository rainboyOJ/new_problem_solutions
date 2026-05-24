#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int n,m;
int a[maxn];


int main (int argc, char *argv[]) {
    std::cin >> n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        
        int opt,x,y,k;
        std::cin >> opt >> x >> y;
        if( opt == 1) {
            std::cin >> k;
            for(int i = x;i <= y ;++i ) // i: x->y
            {
                a[i] += k;
            }
        }
        else {
            int sum = 0;
            for(int i = x;i <= y ;++i ) // i: x->y
            {
                sum += a[i];
            }
            std::cout << sum << "\n";
        }
    }
    
    return 0;
}
