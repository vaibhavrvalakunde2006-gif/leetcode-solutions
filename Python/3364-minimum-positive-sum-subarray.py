class Solution:
    def minimumSumSubarray(self, nums, l, r):
        ans = float('inf')
        n = len(nums)

        for i in range(n):
            total = 0

            for j in range(i, min(i + r, n)):
                total += nums[j]
                length = j - i + 1

                if l <= length and total > 0:
                    ans = min(ans, total)

        if ans == float('inf'):
            return -1

        return ans
