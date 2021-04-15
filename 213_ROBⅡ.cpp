class Solution {
public:
    int robline(vector<int>& nums,int start,int end){
        if(end-start==0) return nums[start];
        vector<int> dp(end-start+1,0);
        dp[0] = nums[start];
        dp[1] = max(nums[start],nums[start+1]);
        for(int i=2;i<end-start+1;i++){
            dp[i] = max(dp[i-2]+nums[i+start],dp[i-1]);
        }
        return dp[end-start];
    }
    int rob(vector<int>& nums) {
        if(nums.size()==1) return nums[0];
        return max(robline(nums,0,nums.size()-2),robline(nums,1,nums.size()-1));
    }
};
