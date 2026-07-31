#include <iostream>

int n,m;
int a[200][200];
int b[200][200];
int main(){
    int i,j;
    std::cin >> n >> m;
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            std::cin >> a[i][j];
        }
    }
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            std::cin >> b[i][j];
        }
    }
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            a[i][j] +=b[i][j];
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
