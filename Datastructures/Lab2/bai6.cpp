#include<iostream>
#include<vector>
using namespace std;

long long merge(int a[],int temp[],int l,int m,int r){
    int i=l,j=m+1;
    long long cnt=0;
    int k=l;
    while(i<=m && j<=r){
        if(a[i]<=a[j]){
            temp[k++]=a[i++];
        }
        else{
            cnt+=m-i+1;
            temp[k++]=a[j++];
        }
    }
    while(i<=m){
        temp[k++]=a[i++];
    }
    while(j<=r){
        temp[k++]=a[j++];
    }
    for(int i=l;i<=r;++i){
        a[i]=temp[i];
    }
    return cnt;
}    
long long mergeSort(int a[],int temp[],int l,int r){
    long long dem=0;
    if(l<r){
        int m=(l+r)/2;
        dem+=mergeSort(a,temp,l,m);
        dem+=mergeSort(a,temp,m+1,r);
        dem+=merge(a,temp,l,m,r);
    }
    return dem;
}

int main(){
    int n; 
    cin>>n;
    int a[n];
    int temp[n];
    for(int i=0;i<n;i++) {
        cin>>a[i];
    }
    cout<<mergeSort(a,temp,0,n-1);
    return 0;
}


