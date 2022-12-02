#include <stdio.h>
#include <string.h>
using namespace std;
const int MAX_SIZE = 1e5 + 1;
#define SWAP(a, b) { typeof(a) T = a; a = b; b = T; }
struct elem {
    int m_val;
    int m_idx;
    bool operator < (elem* other) {
        return (this->m_val < other->m_val) ||
        (this->m_val == other->m_val && this->m_idx < other->m_idx);
    }
}elem_pool[MAX_SIZE];
int pool = 0;
elem* myalloc(int m_val=0, int m_idx=0) {
    elem_pool[pool] = {m_val, m_idx};
    return &elem_pool[pool++];
}

// min heap
struct priority_queue {
    int heap_size = 1;
    int heap_index[MAX_SIZE]; // A[i]의 i에 대한 힙 내부 인덱스
    elem* heap[MAX_SIZE];
    elem top() { return *heap[1]; }
    void push(int val, int idx) {
        if (heap_size >= MAX_SIZE) return;
        heap[heap_size] = myalloc(val, idx);
        heap_index[idx] = heap_size;
        heapify_up(heap_size);
        heap_size++;
    }
    void heapify_up(int curr) {
        while (curr > 1) {
            int parent = curr / 2;
            if (heap[parent]->m_val < heap[curr]->m_val || 
            (heap[parent]->m_val == heap[curr]->m_val && heap[parent]->m_idx < heap[curr]->m_idx)) break;
            
            SWAP(heap[parent], heap[curr]);
            heap_index[ heap[parent]->m_idx ] = parent;
            heap_index[ heap[curr]->m_idx ] = curr;
            curr = parent;
        }
    }
    elem pop() {
        if (heap_size == 1) return elem{-1, -1};
        elem ret = *heap[1];
        heap[1] = heap[--heap_size];
        heapify_down(1);
        return ret;
    }
    void heapify_down(int curr) {
        while (true) {
            int child;
            int left = curr*2;
            int right = curr*2 + 1;
            if (left >= heap_size) break;
            else if (right >= heap_size) child = left;
            else if ((heap[left]->m_val < heap[right]->m_val) ||
            (heap[left]->m_val == heap[right]->m_val && heap[left]->m_idx < heap[right]->m_idx)) child = left;
            else child = right;

            if (heap[curr]->m_val < heap[child]->m_val || 
            (heap[curr]->m_val == heap[child]->m_val && heap[curr]->m_idx < heap[child]->m_idx)) break;
            
            SWAP(heap[curr], heap[child]);
            heap_index[ heap[curr]->m_idx ] = curr;
            heap_index[ heap[child]->m_idx ] = child;
            curr = child;
        }
    }
    void heap_update_direct(int val, int idx) {
        heap[ heap_index[idx] ]->m_val = val;
        heapify_up(heap_index[idx]);
        heapify_down(heap_index[idx]);
    }
};

int main() {
    priority_queue pq;

    int N; scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int A; scanf("%d", &A);
        pq.push(A, i);
    }

    int M; scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int query; scanf("%d", &query);
        if (query == 1) {
            int idx, val; scanf("%d %d", &idx, &val);
            pq.heap_update_direct(val, idx);
        } else if (query == 2) {
            printf("%d\n", pq.top().m_idx);
        }
    }
    
    return 0;
}