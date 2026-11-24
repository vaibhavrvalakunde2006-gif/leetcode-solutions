from collections import deque


class Solution:
    def countNonDecreasingSubarrays(self, nums, k):
        n = len(nums)
        dq = deque()

        right = n - 1
        cost = 0
        ans = 0

        for left in range(n - 1, -1, -1):
            while dq and nums[dq[0]] < nums[left]:
                idx = dq.popleft()
                end = dq[0] if dq else right + 1
                cost += (end - idx) * (nums[left] - nums[idx])

            dq.appendleft(left)

            while cost > k:
                idx = dq[-1]
                cost -= nums[idx] - nums[right]

                if idx == right:
                    dq.pop()

                right -= 1

            ans += right - left + 1

        return ans
