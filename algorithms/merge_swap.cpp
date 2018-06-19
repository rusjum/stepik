#include <iostream>

using namespace std;

int merge(int *arr, int l, int mid, int r) {
//    cout << "start: " << l << " mid: " << mid << " end: " << r << endl;
    int len = r - l + 1;
    int *temp = new int[len];
    int l_idx = l;
    int r_idx = mid + 1;
    int swap_count = 0;
    for (int i = 0; i < len; ++i) {
        if (l_idx > mid) {
            temp[i] = arr[r_idx++];
        } else if (r_idx > r) {
            temp[i] = arr[l_idx++];
        } else {
            if (arr[l_idx] > arr[r_idx]) {
                swap_count += mid - l_idx + 1;
                temp[i] = arr[r_idx++];
            } else {
                temp[i] = arr[l_idx++];
            }
        }
    }
  //  cout << "swaps: " << swap_count << endl;  
    for (int i = 0; i < len; ++i) {
        arr[l + i] = temp[i];
    }
    delete [] temp;
    return swap_count;
}

int merge_sort(int *arr, int start, int end) {
    if (end - start < 1) return 0;
    int mid = start + (end - start) / 2;
    int l = merge_sort(arr, start, mid);
    int r = merge_sort(arr, mid + 1, end);
    return l + r + merge(arr, start, mid, end);
}

int main() {
    int n;
    cin >> n;
    int* nums = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    cout << merge_sort(nums, 0, n - 1) << endl;
    delete [] nums;
    return 0;
}
