#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define bool int
#define true 1
#define false 0
#define MAX 200005

struct Q {
	int q[MAX];
	int s;
	int e;
} Q;
void init(struct Q* Q) {
	Q->s = Q->e = 0;
	memset(Q->q, 0, sizeof(Q->q));
}

bool isEmpty(struct Q* Q) {
	return Q->s == Q->e;
}
bool isFull(struct Q* Q) {
	return (Q->e + 1) % MAX == Q->s;
}
bool enqueue(struct Q* Q, int val) {
	if (isFull(Q)) return false;
	Q->q[Q->e] = val;
	Q->e++;
	return true;
}
bool dequeue(struct Q* Q, int *ret) {
	if (isEmpty(Q)) return false;
	*ret = Q->q[Q->s];
	Q->s++;
	return true;
}

struct Node {
	int val;
	struct Node* next;
} Nodes[MAX * 2];
int smalloc_idx = 0;
struct Node* smalloc() {
	return &Nodes[++smalloc_idx];
}

void printlist(struct Node* head) {
	for (struct Node* ptr = head; ptr; ptr = ptr->next)
		printf("%d -> ", ptr->val);
	printf("NULL\n");
}
// push front
void push(struct Node** head, int val) {
	struct Node* newNode = smalloc();
	newNode->next = *head;
	newNode->val = val;
	*head = newNode;
}
struct Node* merge(struct Node* left, struct Node* right) {
	if (left == NULL) return right;
	if (right == NULL) return left;

	struct Node* ret = NULL;
	if (left->val < right->val) {
		ret = left;
		ret->next = merge(left->next, right);
	}
	else {
		ret = right;
		ret->next = merge(left, right->next);
	}
	return ret;
}
void split(struct Node* source, struct Node** left, struct Node** right) {
	if (source == NULL || source->next == NULL) {
		*left = source;
		*right = NULL;
		return;
	}

	struct Node* slow = source;
	struct Node* fast = source->next;

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
void sort(struct Node** head) {
	if (*head == NULL || (*head)->next == NULL) return;
	struct Node* left, * right;
	split(*head, &left, &right);
	sort(&left);
	sort(&right);
	*head = merge(left, right);
}

int N, M, R;
struct Node* edge[MAX / 2];
void input() {
	scanf("%d %d %d", &N, &M, &R);
	int u, v;
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &u, &v);
		push(&edge[u], v);
		push(&edge[v], u);
	}

	for (int i = 1; i <= N; i++) 
		sort(&edge[i]);
}

int visited[MAX / 2];
void bfs(int R) {
	init(&Q);
	int cnt = 0;
	visited[R] = ++cnt;
	enqueue(&Q, R);

	while (!isEmpty(&Q)) {
		int curr;
		dequeue(&Q, &curr);
		for (struct Node* neighbor = edge[curr]; neighbor; neighbor = neighbor->next) {
			if (visited[neighbor->val]) continue;
			visited[neighbor->val] = ++cnt;
			enqueue(&Q, neighbor->val);
		}
	}
}

void sol() {
	for (int i = 1; i <= N; i++) 
		printf("%d\n", visited[i]);
}

int main() {
	input();
	bfs(R);
	sol();

	return 0;
}
#endif