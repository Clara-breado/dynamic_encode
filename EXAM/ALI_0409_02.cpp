#include<iostream>
#include<vector>
using namespace std;
void reverse(vector<int>& arr,int start,int end){
    while(start<end){
        swap(arr[start++],arr[end--]);
    }
}
int main(){
    int n,k;
    n = 5;k=3;
    vector<int> src(n,0);
    for(int i=0;i<n;i++){
        src[i] = i+1;
    }
    reverse(src,1-1,3-1);
    vector<vector<int>> op(k,vector<int>(2,0));
    for(int i=0;i<k;i++){
        cin>>op[i][0]>>op[i][1];
    }
    cout<<op[1][1];
}
