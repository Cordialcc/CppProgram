#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e6;
int q[N], tmp[N];

void merge_sort(int q[], int l, int r) {
    if (l >= r) return;

    int mid = (l + r) >> 1;
    merge_sort(q, l, mid);
    merge_sort(q, mid+1, r);

    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j<=r) {
        if (q[i] <= q[j]) tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    }
    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];

    for (int i=l, j=0; i <= r; ++i, ++j) q[i] = tmp[j];
    
}

int main() {
    freopen ("a.in", "r", stdin);
    freopen ("a.ans", "w" , stdout);
    ios::sync_with_stdio(false); cin.tie (0);

    int n; cin >> n;
    for (int i=0; i<n; ++i) cin >> q[i];

    merge_sort(q, 0, n-1);
    for(int i=0; i<n; ++i) cout << q[i] << " ";
    return 0;
}