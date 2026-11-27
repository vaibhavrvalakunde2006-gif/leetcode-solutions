from typing import List


class Solution:
    def busiestServers(self, k: int, arrival: List[int], load: List[int]) -> List[int]:
        import heapq

        bit = [0] * (k + 1)

        def update(i, delta):
            i += 1
            while i <= k:
                bit[i] += delta
                i += i & -i

        def query(i):
            i += 1
            result = 0
            while i > 0:
                result += bit[i]
                i -= i & -i
            return result

        def find_kth(target):
            idx = 0
            step = 1 << (k.bit_length() - 1)

            while step:
                nxt = idx + step
                if nxt <= k and bit[nxt] < target:
                    idx = nxt
                    target -= bit[nxt]
                step >>= 1

            return idx

        for i in range(k):
            update(i, 1)

        busy = []
        count = [0] * k

        for i, time in enumerate(arrival):
            while busy and busy[0][0] <= time:
                _, server = heapq.heappop(busy)
                update(server, 1)

            if query(k - 1) == 0:
                continue

            preferred = i % k
            before = query(preferred - 1) if preferred > 0 else 0
            total = query(k - 1)

            if total > before:
                server = find_kth(before + 1)
            else:
                server = find_kth(1)

            update(server, -1)
            count[server] += 1
            heapq.heappush(busy, (time + load[i], server))

        maximum = max(count)
        return [i for i in range(k) if count[i] == maximum]
