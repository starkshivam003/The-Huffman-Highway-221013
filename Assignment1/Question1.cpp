#include <iostream>

int main (){
    int n;
    std::cout<<"Input: ";
    std::cin>>n;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(j%2==!0){
                for(int k=1; k<=i; k++){
                    std::cout<<k;
                }
                for(int k=i+1; k<=n; k++){
                    std::cout<<" ";
                }
            }
            else{
                for (int k = i + 1; k <= n; ++k) {
                    std::cout << " ";
                }
                for (int k = i; k >= 1; k--) {
                    std::cout << k;
                }
            }
        }
        std::cout<<"\n";
    }
}
