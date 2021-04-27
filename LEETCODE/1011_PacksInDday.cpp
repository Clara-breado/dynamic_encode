class Solution {
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int l = getMin(weights);
        int r = getMax(weights);
        while(l<r){
            int mid = (l+r)/2;
            if(canFinish(weights,mid,D)){
                r = mid;
            }else{
                l = mid+1;
            }
        }
        return l;//l==max
    }
    int getMin(vector<int>& weights){
        int max = weights[0];
        for(auto weight:weights){
            max = max>weight?max:weight;
        }
        return max;
    }
    int getMax(vector<int>& weights){
        int sum;
        for(auto weight:weights){
            sum +=weight;
        }
        return sum;
    }
    bool canFinish(vector<int>& weights,int speed,int D){
        int day = 1;
        int rawSpeed = speed;
        for(int i=0;i<weights.size();i++){
            if(speed>=weights[i]){
                speed -= weights[i];
            }else{
                day++;
                speed = rawSpeed;
                speed -= weights[i];
            }
        }
        return day<=D;

    }
};