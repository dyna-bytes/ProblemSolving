from typing import List, Dict
import sys

input = sys.stdin.readline

def transpose(arr: List[List[int]]):
    return list(zip(*arr[::]))
def rotate_cw(arr: List[List[int]]):
    return list(zip(*arr[::-1]))
def rotate_ccw(arr):
    return rotate_cw(rotate_cw(rotate_cw(arr)))
def print2D(arr2D: List[List[int]]):
    for arr1D in arr2D:
        print(arr1D)

global N, M
global board, queries, request
global delta, psum

N, M = map(int, input().split())
board = [list(map(int, input().split())) for _ in range(N)]
queries = [list(map(int, input().split())) for _ in range(M-1)]
request = list(map(int, input().split()))

delta = [[0 for _ in range(N + 1)] for _ in range(N + 1)]
psum = [[0 for _ in range(N + 2)] for _ in range(N + 2)]

def solve():
    global N, M
    global board, queries, request
    global delta, psum

    for (op, sy, sx, ey, ex, val) in queries:
        delta[sy][sx] += val
        delta[sy][ex+1] -= val
        delta[ey+1][sx] -= val
        delta[ey+1][ex+1] += val

    for y in range(N + 1):
        for x in range(N + 1):
            psum[y+1][x+1] = psum[y][x+1] + psum[y+1][x] \
                            - psum[y][x] + delta[y][x]
                            
    psum.pop(0)
    psum.pop(-1)
    psum = rotate_cw(psum)

    psum.pop(0)
    psum.pop(-1)
    psum = rotate_cw(psum)
    
    psum = rotate_cw(psum)
    psum = rotate_cw(psum)

    for y in range(N):
        for x in range(N):
            board[y][x] += psum[y][x]

    psum.clear()
    psum = [[0 for _ in range(N + 1)] for _ in range(N + 1)]
    for y in range(N):
        for x in range(N):
            psum[y+1][x+1] = psum[y][x+1] + psum[y+1][x] \
                            - psum[y][x] + board[y][x]
    
    op, sy, sx, ey, ex = request
    return psum[ey+1][ex+1] - psum[ey+1][sx] - psum[sy][ex+1] + psum[sy][sx]

def main():
    print(solve())
    return 0

if __name__ == '__main__':
    main()