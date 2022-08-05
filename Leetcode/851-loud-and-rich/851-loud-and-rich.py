class Solution:
    def loudAndRich(self, richer: List[List[int]], quiet: List[int]) -> List[int]:
        adj = [[] for row in range(len(quiet))]
        dp = [-1 for col in range(len(quiet))]
        # dp[x] = y: x보다 더 부자인 사람 중, 가장 조용한 사람 y

        for rich, poor in richer:
            adj[poor].append(rich)

        # curr보다 부자인 사람들을 위상정렬해가며, 그 중 가장 조용한 사람을 리턴함
        def dfs(curr: int) -> int:
            if dp[curr] != -1: return dp[curr]

            dp[curr] = curr
            for next in adj[curr]:
                dp_next = dfs(next) # next보다 부자 중 가장 조용한 사람
                if quiet[ dp[curr] ] > quiet[dp_next]: dp[curr] = dp_next
            return dp[curr]


        for i in range(len(quiet)): dfs(i)
        return dp