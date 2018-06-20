#include <iostream>
#include <stdlib.h> 
#include <algorithm>

using namespace std;

int compare(const void *a, const void *b) {
    return *((int*)a) - *((int*)b);
}

int main() {

    int weight, n;
    cin >> weight >> n;
    int *items = new int[n];
    int **dp = new int*[weight + 1];
    for (int i = 0; i <= weight; ++i) {
        dp[i] = new int[n + 1]();
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> items[i];
    }
    qsort(items, n, sizeof(int), compare);

    for (int i = 0; i <= weight; ++i) {
        for (int j = 0; j < n; ++j) {
            if (items[j] <= i)
                dp[i][j + 1] = max(dp[i][j], max(dp[i][j + 1], dp[i - items[j]][j] + items[j]));
            if (i > 0)
                dp[i][j + 1] = max(dp[i][j + 1], max(dp[i][j], dp[i - 1][j + 1]));
        }
    }
    int res = dp[weight][n];
    delete[] items;
    for (int i = 0; i <= weight; ++i) {
        delete[] dp[i];
    }
    delete[] dp;
    cout << res << endl;
    return 0;
}
