#include <iostream>

#define inf 0x7f7f7f7f

int n;
int min = inf;
int max= -inf;

int main(){
    int n;
    int i,t;
    std::cin >> n;
    for (i=1;i<=n;i++){
        std::cin >> t;
        if( min  > t) 
            min = t;
        if( max < t)
            max = t;
    }
    std::cout << max-min;
    return 0;
}
