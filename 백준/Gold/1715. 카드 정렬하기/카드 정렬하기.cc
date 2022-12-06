#include <stdio.h>
#define SWAP(a, b) { typeof(a) t = a; a = b; b = t; }
#define MAXN 100001

struct priority_queue {
    int heap_size = 1;
    int heap[MAXN];
    bool empty() {
        return heap_size == 1;
    }
    int size() {
        return heap_size - 1;
    }
    int top() {
        return heap[1];
    }
    void push(int val) {
        heap[heap_size] = val;
        int curr = heap_size;
        heap_size++;
        while (curr > 1) {
            int parent = curr/2;
            if (heap[parent] < heap[curr]) break;
            SWAP(heap[parent], heap[curr]);
            curr = parent;
        }
    }    
    void pop() {
        heap[1] = heap[--heap_size];
        int curr = 1;
        while (true) {
            int child = -1;
            int left = curr*2;
            int right = curr*2 + 1;
            if (left >= heap_size) break;
            else if (right >= heap_size) child = left;
            else if (heap[left] < heap[right]) child = left;
            else child = right;

            if (heap[curr] < heap[child]) break;
            SWAP(heap[curr], heap[child]);
            curr = child;
        }
    }
};

int main() {
    priority_queue pq;
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int cards; scanf("%d", &cards);
        pq.push(cards);
    }

    int ret = 0;
    while (pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        ret += (a + b);
        pq.push(a + b);
    }

    printf("%d\n", ret);

    return 0;
}