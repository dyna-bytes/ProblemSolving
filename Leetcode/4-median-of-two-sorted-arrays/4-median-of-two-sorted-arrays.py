class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        MAX = 10 ** 6 + 1
        A, B = [-MAX]*2 + nums1 + [MAX]*2, [-MAX]*2+ nums2 + [MAX]*2
        total = len(A) + len(B)
        half = total // 2
        
        if len(B) < len(A):
            A, B = B, A
        
        l, r = -1, len(A)
        
        while True:
            i = (l + r) // 2
            j = half - i - 2 # minus 2 for indexing
            
            Aleft = A[i] # if i >= 0 else float("-infinity")
            Aright = A[i + 1] # if (i + 1) < len(A) else float("infinity")
            Bleft = B[j] # if j >= 0 else float("-infinity") # j가 -1 일 수 있다는 위험이 있다
            Bright = B[j + 1] # if (j + 1) < len(B) else float("infinity")
            
            if Aleft <= Bright and Bleft <= Aright:
                # odd
                if total % 2:
                    return max(max(Aleft, Bleft), min(Aright, Bright))
                else:
                    return (max(Aleft, Bleft) + min(Aright, Bright)) / 2
            elif Aleft > Bright:
                r = i - 1
            else:
                l = i + 1