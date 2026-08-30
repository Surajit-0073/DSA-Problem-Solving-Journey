class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        int minIndex = min_element(begin(nums), end(nums)) - begin(nums);
        int maxIndex = max_element(begin(nums), end(nums)) - begin(nums);

        int left = min(minIndex, maxIndex);
        int right = max(minIndex, maxIndex);

        return min({left+1+n-right, right+1, n-left});

        
    }
};