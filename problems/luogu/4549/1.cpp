#include <bits/stdc++.h>
using namespace std;

int n;
int a,b;

int gcd(int a,int b) {
    if( b == 0 ) return a;
    return gcd(b , a %b);
}

int main (int argc, char *argv[]) {
    std::cin >> n;
    std::cin >> a >> b;
    int g = gcd(a,b);
    for(int i = 3;i <= n ;++i ) // i: 3->n
    {
        int t;
        std::cin >> t;
        g = gcd(g,t);
    }
    if( g < 0 ) g*=-1;
    std::cout << g << "\n";

    
    return 0;
}
