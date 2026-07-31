#include <cstring>
#include <iostream>
int a[1000000] = {0};

int main(){
    a[0] = 1;
    int n;
    int i,j;
    int idx = 1;
    std::cin >> n;
    for (i=1;i<=n;i++){

        int jin = 0;
        for(j=0;j<idx;j++){
            int t= ( jin+a[j]+a[j]) % 10;
            jin = ( jin+a[j]+a[j]) / 10;
            a[j] = t;
        }
        if(jin){
            a[idx] = jin;
            idx++;
        }
    }
    for(i = idx-1;i>=0;i--)
        std::cout << a[i];
    return 0;
}
