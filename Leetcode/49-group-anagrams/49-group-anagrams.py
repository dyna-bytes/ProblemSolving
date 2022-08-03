class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        if len(strs) == 0: return [[]]
        hash: Dict[Tuple, List[str]] = {}
        for s in strs:
            key = tuple(sorted(s))
            hash[key] = hash.get(key, []) + [s]
        return hash.values()