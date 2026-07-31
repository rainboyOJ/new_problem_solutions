#include <iostream>

int n,m,k;
int a[200][200];
int b[200][200];
int c[200][200];
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
             b[j][n-i+1]= a[i][j];
        }
    }
    for (i=1;i<=m;i++){
        for (j=1;j<=n;j++){
            std::cout << b[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
