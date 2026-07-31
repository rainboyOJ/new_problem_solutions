#include <iostream>

int a[50005] = {0};
int main(){
    int n,m;
    int i,j;
    std::cin >> n >> m;

    for (i=2;i<=m;i++){
        for(j=i;j<=n;j+=i){
            a[j] = !a[j];
        }
    }
    for (i=1;i<=n;i++){
        if( !a[i]){
            std::cout << i;
            break;
        }
    }
    for( i++; i<=n;i++){
        if( !a[i]){
            std::cout << "," << i;
        }
    }
    return 0;
}
