#include <iostream>

void Insertion(int a[],int n){
    int index, value;
    for(int i=0;i<n;i++){
        index = i;
        value = a[i];
        while(index > 0 && a[index-1] > value){
            a[index] = a[index-1];
            index--;
        }
        a[index] = value;
    }
}
int main(){
    int n; std::cin>>n;
    int a[n];
    for(int i=0;i<n;i++) std::cin>>a[i];
    Insertion(a,n);
    for(int i=0;i<n;i++) std::cout<<a[i]<<" ";
    return 0;
}