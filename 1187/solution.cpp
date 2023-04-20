class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(), arr2.end());
        unordered_map<int, int> dp;
        dp[-1] = 0;
        for(int i=0; i<arr1.size(); i++) {
            unordered_map<int, int> next;
            for(auto &p : dp) {
                if(arr1[i] > p.first) {
                    next[arr1[i]] = next.count(arr1[i]) ? min(next[arr1[i]], p.second) : p.second;
                }
                auto iter = upper_bound(arr2.begin(), arr2.end(), p.first);
                if(iter == arr2.end()) continue;
                next[*iter] = next.count(*iter) ? min(next[*iter], p.second+1) : p.second + 1;
            }
            swap(next, dp);
        }
        int ans = INT_MAX;
        for(auto &p : dp) {
            ans = min(ans, p.second);
        }
        return ans == INT_MAX ? -1 : ans;
    }
};
