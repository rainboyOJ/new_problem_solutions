#include <iostream>

int n;
int a[1005][1005];
int w,h;

int main(){
    std::cin >> n;
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            std::cin >> a[i][j];
        }
    }
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            if( a[i][j] == 0){
                w = 1;
                h = 1;
                int pos = j;
                for(j=j+1;j<=n;j++){
                    if(a[i][j] == 0)
                        w++;
                    else
                        break;
                }
                for(j=i+1;j<=n;j++){
                    if( a[j][pos] == 0)
                        h++;
                    else
                        break;
                }

                int ans = w*h -( (w-2)*2+(h-2)*2+4);
                std::cout << ans << "\n";

                return 0;
            }
        }
    }
    std::cout << "0";
    return 0;
}
