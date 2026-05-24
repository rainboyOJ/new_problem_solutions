#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;

const int maxn = 1e5+5;
int del[maxn];
int n;

int main (int argc, char *argv[]) {
    std::cin >> n;
    n++;

    for(int i = 2;i<=n;i++) {

        if( del[i] == 0) {
            // std::cout << i << "\n";

            if( i > n / i ) continue;

            for(int j = i * i; j <=n;j +=i) {
                del[j] = 1;
            }
        }
    }
    // std::cout << "-----------"<< "\n";

    if( n <=3) {
        cout <<  1 << endl;
    }
    else 
        cout << 2 << endl;

    for(int i = 2;i<=n;i++) {

        if( del[i] == 0) {
            std::cout << 1 << " ";
        }
        else {
            std::cout << 2 << " ";
        }
    }
    
    return 0;
}
