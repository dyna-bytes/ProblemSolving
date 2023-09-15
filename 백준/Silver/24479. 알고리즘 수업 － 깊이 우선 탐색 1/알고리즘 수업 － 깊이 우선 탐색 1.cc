#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#define DEBUG
#ifdef DEBUG
#include <iostream>
#include <time.h>
using namespace std;
#define FL "[" << __func__ << "](" << __LINE__ << ") "
#define debug(x) cout << FL << #x << " is " << x << endl
#define EXPECT_EQ(a, b) do { \
    auto A = a, B = b; \
    if (A != B) cout << FL << A << "!=" << B << endl; \
} while (0)
#else
#define debug(x) {}
#define EXPECT_EQ(a, b) {}
#endif // DEBUG

const int MAX = 200000 + 10;

typedef struct Node {
    int val;
    Node* next;
} Node;
Node nodes[MAX << 1];
Node* smalloc(int val = 0, Node* next = NULL) {
    static int sidx;
    Node* ret = &nodes[++sidx];
    ret->val = val, ret->next = next;
    return ret;
}

int print_nodes(Node* head) {
    int num_nodes = 0;
    for (Node* node = head; node; node = node->next, num_nodes++)
        printf("%d -> ", node->val);
    printf("NULL\n");
    return num_nodes;
}
/* push front */
void push(Node** head, int val) {
    Node* newNode = smalloc(val);
    newNode->next = *head;
    *head = newNode;
}

/* split array in half. [ | | | | ] --> [ | | ] + [ | ] */
void split(Node* source, Node** left, Node** right) {
    if (source == NULL || source->next == NULL) {
        *left = source;
        *right = NULL;
        return;
    }

    // find middle
    Node* slow = source;
    Node* fast = source->next;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = source;
    *right = slow->next;
    slow->next = NULL;
}
Node* merge(Node* left, Node* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    Node* ret;
    if (left->val < right->val) {
        ret = left;
        ret->next = merge(left->next, right);
    } else {
        ret = right;
        ret->next = merge(left, right->next);
    }
    return ret;
}
void sort(Node** head) {
    if (*head == NULL || (*head)->next == NULL) return;

    Node* left, * right;
    split(*head, &left, &right);
    sort(&left);
    sort(&right);
    *head = merge(left, right);
}

#ifdef DEBUG
void node_test() {
    clock_t time = clock();

    Node* head = smalloc(0);
    push(&head, 5);
    push(&head, 4);
    EXPECT_EQ(print_nodes(head), 3);
    push(&head, 2);
    push(&head, 3);
    EXPECT_EQ(print_nodes(head), 5);
    sort(&head);
    print_nodes(head);

    time = clock() - time;
    debug(time);
}
#endif // DEBUG

Node* adj[MAX >> 1];
int visited[MAX >> 1];
int level = 0;
void dfs(int curr) {
    debug(curr);
    visited[curr] = ++level;
    for (Node* next = adj[curr]; next; next = next->next) {
        if (visited[next->val]) continue;
        dfs(next->val);
    }
}

#ifdef DEBUG
int __main() {
#else
int main() {
#endif
    int N, M, R;
    scanf("%d %d %d", &N, &M, &R);
    
    int u, v;
    for (int i = 0; i < M; ++i) {
        scanf("%d %d", &u, &v);
        push(&adj[u], v);
        push(&adj[v], u);
    }

    for (int i = 1; i <= N; ++i)
        sort(&adj[i]);
    
    dfs(R);
    for (int i = 1; i <= N; ++i)
        printf("%d\n", visited[i]);
    return 0;
}

#ifdef DEBUG
void main_test() {
    clock_t time = clock();
    freopen("prob24479_input.txt", "r", stdin);
    
    EXPECT_EQ(__main(), 0);

    time = clock() - time;
    debug(time);
}

int main() {
    node_test();
    main_test();
    return 0;
}
#endif // DEBUG

#endif