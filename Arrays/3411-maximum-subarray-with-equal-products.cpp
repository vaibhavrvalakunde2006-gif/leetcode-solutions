#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 1;

        for (int i = 0; i < n; i++) {
            __int128 prod = 1;
            long long g = 0;
            long long l = 1;

            for (int j = i; j < n; j++) {
                long long x = nums[j];

                g = gcd(g, x);
                l = l / gcd(l, x) * x;

                __int128 target = (__int128)g * l;

                // Avoid overflowing __int128.
                if (prod > target / x) {
                    break;
                }

                prod *= x;

                if (prod == target) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};
