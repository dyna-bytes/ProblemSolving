from typing import List, Dict

N, M = map(int, input().split())
arr = list(map(int, input().split()))
queries = [list(map(int, input().split())) for _ in range(M)]
pSum = [0]

def prefix_sum(s: int, e: int)->int:
    return pSum[e] - pSum[s-1]

def main():
    sum_val = 0
    for val in arr:
        sum_val += val
        pSum.append(sum_val)
    
    for (s, e) in queries:
        print(prefix_sum(s, e))

if __name__ == '__main__':
    main()