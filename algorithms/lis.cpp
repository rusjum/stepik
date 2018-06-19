#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *nums = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    int *dp = new int[n]();
    int res = 0;
    for (int i = 0; i < n; ++i) {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; --j) {
            if (dp[i] < dp[j] + 1 && nums[i] % nums[j] == 0) {
                dp[i] = dp[j] + 1;
            }
        }
        res = max(res, dp[i]);
    }
    delete[] nums;
    delete[] dp;
    cout << res;
}
