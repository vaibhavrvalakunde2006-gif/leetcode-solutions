from typing import List


class Solution:
    def maximumSaleItems(self, items: List[List[int]], budget: int) -> int:
        n = len(items)

        free = [0] * n

        for i in range(n):
            for j in range(n):
                if i != j and items[j][0] % items[i][0] == 0:
                    free[i] += 1

        groups = {}

        for i in range(n):
            price = items[i][1]
            value = 1 + free[i]
            groups.setdefault(price, []).append(value)

        dp = [-1] * (budget + 1)
        dp[0] = 0
        ans = 0

        for price in sorted(groups, reverse=True):
            cur = [-1] * (budget + 1)

            for value in groups[price]:
                for cost in range(budget, price - 1, -1):
                    if dp[cost - price] != -1:
                        cur[cost] = max(
                            cur[cost],
                            dp[cost - price] + value
                        )

                    if cur[cost - price] != -1:
                        cur[cost] = max(
                            cur[cost],
                            cur[cost - price] + value
                        )

            for cost in range(budget + 1):
                if cur[cost] != -1:
                    extra = (budget - cost) // price
                    ans = max(ans, cur[cost] + extra)

            for cost in range(budget + 1):
                dp[cost] = max(dp[cost], cur[cost])

        return ans
