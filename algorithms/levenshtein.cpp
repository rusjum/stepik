#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    int n = a.length() + 1;
    int m = b.length() + 1;
    int **dp = new int* [n];
    int max_len = (n + m) * 2;
    for (int i = 0; i < n; ++i) {
        dp[i] = new int[m]();
    }
    for (int i = 0; i < n; ++i) {
        dp[i][0] = i;
    }
    for (int j = 0; j < m; ++j) {
        dp[0][j] = j;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            int ins = dp[i - 1][j] + 1;
            int rem = dp[i][j - 1] + 1;
            int rep = dp[i - 1][j - 1] + a.at(i - 1) == b.at(j - 1) ? 0 : 1;
            dp[i][j] = min(ins, min(rem, rep));
        }
    }
    int res = dp[n - 1][m - 1];
    for (int i = 0; i < n; ++i) {
        delete[] dp[i];
    }
    delete[] dp;
    cout << res;
}
