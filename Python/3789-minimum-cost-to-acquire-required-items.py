class Solution:
    def minimumCost(self, cost1: int, cost2: int, costBoth: int, need1: int, need2: int) -> int:

        # Option 1: Buy everything separately
        cost_a = need1 * cost1 + need2 * cost2

        # Option 2: Buy common requirements using type 3
        common = min(need1, need2)

        cost_b = (
            common * costBoth
            + (need1 - common) * cost1
            + (need2 - common) * cost2
        )

        # Option 3: Buy only type 3 items
        cost_c = max(need1, need2) * costBoth

        return min(cost_a, cost_b, cost_c)
