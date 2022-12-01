#include <stdio.h>
#define SWAP(a, b) { typeof(a) tmp = a; a = b; b = tmp; }

const int MAX_SIZE = 1e5 + 1;

struct priority_queue {
    int heap_size = 1;
    int heap[MAX_SIZE];
    
    int top() { return heap[1]; }

    void push(int val) {
        heap[heap_size++] = val;
        heapify_up(heap_size - 1);
    }

    void heapify_up(int curr) {
        while (curr > 1) {
            int parent = curr/2;
            if (heap[parent] <= heap[curr]) break;
            SWAP(heap[parent], heap[curr]);
            curr = parent;
        }
    }

    int pop() {
        if (heap_size == 1) return 0;
        int ret = heap[1];
        heap[1] = heap[--heap_size];
        heapify_down();
        return ret;
    }
    
    void heapify_down() {
        int curr = 1;
        while (true) {
            int child = -1;
            int left = curr*2;
            int right = curr*2 + 1;
            if (left >= heap_size) break;
            else if (right >= heap_size) child = left;
            else if (heap[left] < heap[right]) child = left;
            else child = right;

            if (heap[curr] <= heap[child]) break;
            SWAP(heap[curr], heap[child]);
            curr = child;
        }
    }
};

int main() {
    priority_queue pq;
    int N; scanf("%d", &N);
    for (int i = 0;  i < N; i++) {
        int op; scanf("%d", &op);
        if (op == 0) printf("%d\n", pq.pop());
        else pq.push(op);
    }
}