class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        // Coordinate compression
        vector<int> a = nums;
        sort(a.begin(), a.end());

        a.erase(unique(a.begin(), a.end()), a.end());

        vector<int> s(n);

        for (int i = 0; i < n; i++) {
            s[i] = lower_bound(a.begin(), a.end(), nums[i])
                   - a.begin();
        }

        // Build suffix array
        vector<int> sa(n), rank(n), temp(n);

        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rank[i] = s[i];
        }

        for (int k = 1; k < n; k *= 2) {
            sort(sa.begin(), sa.end(), [&](int i, int j) {
                if (rank[i] != rank[j])
                    return rank[i] < rank[j];

                int ri = (i + k < n) ? rank[i + k] : -1;
                int rj = (j + k < n) ? rank[j + k] : -1;

                return ri < rj;
            });

            temp[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                int x = sa[i - 1];
                int y = sa[i];

                bool different =
                    rank[x] != rank[y] ||
                    (x + k < n ? rank[x + k] : -1) !=
                    (y + k < n ? rank[y + k] : -1);

                temp[y] = temp[x] + different;
            }

            rank = temp;

            if (rank[sa[n - 1]] == n - 1)
                break;
        }

        // Build inverse suffix array
        vector<int> pos(n);

        for (int i = 0; i < n; i++) {
            pos[sa[i]] = i;
        }

        // Kasai's LCP algorithm
        vector<int> lcp(n, 0);
        int h = 0;

        for (int i = 0; i < n; i++) {
            int p = pos[i];

            if (p == 0) {
                h = 0;
                continue;
            }

            int j = sa[p - 1];

            while (i + h < n && j + h < n &&
                   s[i + h] == s[j + h]) {
                h++;
            }

            lcp[p] = h;

            if (h > 0)
                h--;
        }

        // Find minimum unique subarray length
        int ans = n;

        for (int i = 0; i < n; i++) {
            int p = pos[i];

            int left = (p > 0) ? lcp[p] : 0;
            int right = (p + 1 < n) ? lcp[p + 1] : 0;

            int needed = max(left, right) + 1;

            if (needed <= n - i) {
                ans = min(ans, needed);
            }
        }

        return ans;
    }
};
