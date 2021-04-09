#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
void solve(vector<vector<int>>& LR){
    //vector<int>res(LR.size(),0);
    int cnt = 1;
    for(int i=0;i<LR.size();i++){
        if(LR[i][1]>=cnt){
            LR[i][3] = cnt++;
        }else{
            LR[i][3] = 0;
        }
    }

}
int main(){
    int t;
    cin>>t;
    //vector<vector<int>> res;
    vector<vector<vector<int>>> res;
    for(int i=0;i<t;i++){
        int n;
        cin>>n;
        vector<int> L(n,0);
        vector<int> R(n,0);
        vector<vector<int>> LR(n,vector<int>(4,0));
        for(int j=0;j<n;j++){
            cin>>L[j];
            cin>>R[j];
            LR[j][0] = L[j];
            LR[j][1] = R[j];
            LR[j][2] = j;//raw idx
        }
        //cout<<"h"<<endl;
        sort(LR.begin(),LR.end(),[](const auto& u,const auto &v){
            return u[0]<v[0];
        });
        solve(LR);

        sort(LR.begin(),LR.end(),[](const auto& u,const auto &v){
            return u[2]<v[2];
        });
        res.push_back(LR);
    }
    //output
    for(auto re:res){
        for(auto r:re){

        }
        cout<<endl;
    }
    for(int i=0;i<t;i++){
        for(int j=0;j<res[i].size();j++){
            cout<<res[i][j][3]<<" ";
        }
        cout<<endl;
    }
}
