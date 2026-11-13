#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    while (q--) {
        long long x;
        cin >> x;
        auto it = lower_bound(a.begin(), a.end(), x);

        if (it != a.end() && *it == x) {
            // 1-based index: (iterator offset) + 1
            cout << (it - a.begin() + 1) << "\n";
        } else {
            cout << -1 << "\n";
        }
    }

    return 0;
}