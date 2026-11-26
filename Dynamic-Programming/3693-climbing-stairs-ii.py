from typing import List


class Solution:
    def minCost(self, n: int, costs: List[int]) -> int:
        dp = [float('inf')] * (n + 1)
        dp[0] = 0

        for i in range(1, n + 1):
            for jump in range(1, 4):
                if i >= jump:
                    dp[i] = min(
                        dp[i],
                        dp[i - jump] + costs[i - 1] + jump * jump
                    )

        return dp[n]
