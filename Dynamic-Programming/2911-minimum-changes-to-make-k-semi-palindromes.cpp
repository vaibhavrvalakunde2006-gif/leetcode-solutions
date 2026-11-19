#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        vector<vector<int>> cost(n, vector<int>(n, INF));

        // Precompute the cost of making every substring semi-palindromic.
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r < n; r++) {
                int len = r - l + 1;

                for (int d = 1; d < len; d++) {
                    if (len % d != 0) continue;

                    int changes = 0;
                    int groups = len / d;

                    for (int offset = 0; offset < d; offset++) {
                        for (int a = 0; a < groups / 2; a++) {
                            int left = l + offset + a * d;
                            int right = l + offset + (groups - 1 - a) * d;

                            if (s[left] != s[right]) {
                                changes++;
                            }
                        }
                    }

                    cost[l][r] = min(cost[l][r], changes);
                }
            }
        }

        // dp[p][i] = minimum changes for first i characters
        // split into exactly p semi-palindromes.
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, INF));
        dp[0][0] = 0;

        for (int p = 1; p <= k; p++) {
            for (int end = 2 * p; end <= n; end++) {
                for (int start = 2 * (p - 1); start <= end - 2; start++) {
                    if (dp[p - 1][start] == INF) continue;

                    dp[p][end] = min(
                        dp[p][end],
                        dp[p - 1][start] + cost[start][end - 1]
                    );
                }
            }
        }

        return dp[k][n];
    }
};
