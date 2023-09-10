#if 1
#define _CRT_SECURE_NO_WARNINGS
//#define CONFIG_DEBUG
#include <stdio.h>
#include <memory.h>

#ifdef CONFIG_DEBUG
#include <iostream>
#include <time.h>
using namespace std;
#define DEBUG_LINE(func, line) "[" << func << "](" << line << ") "
#define DEBUG(x) cout << DEBUG_LINE(__func__, __LINE__) << #x << " is " << x << endl;
#define EXPECT_EQ(a, b) do{ \
	auto A = a, B = b; \
	if (A != B) cout << DEBUG_LINE(__func__, __LINE__) << A << " != " << B << endl; \
} while (0);
#else
#define DEBUG_LINE(f, l) {}
#define DEBUG(x) {};
#define EXPECT_EQ(a, b) {};
#endif // CONFIG_DEBUG

const int dy[] = { -1, 1, 0, 0 }, dx[] = { 0, 0, -1, 1 };
const int MAX = 105;
int board[MAX][MAX];
bool visited[MAX][MAX];
int Y, X;
bool inRange(int y, int x) {
	return 0 <= y && y < Y && 0 <= x && x < X;
}

void print_board() {
#ifdef CONFIG_DEBUG
	for (int y = 0; y < Y; ++y) {
		for (int x = 0; x < X; ++x)
			printf("%d ", board[y][x]);
		printf("\n");
	}
#endif // CONFIG_DEBUG
}

typedef struct Node {
	int y;
	int x;
	int val;
} Node;
Node nodes[MAX * MAX * MAX];
Node* smalloc(int y = 0, int x = 0, int val = 0) {
	static int s_idx;
	Node* ret = &nodes[++s_idx];
	ret->y = y, ret->x = x, ret->val = val;
	return ret;
}

#ifdef CONFIG_DEBUG;
const int Q_SIZE = 4;
#else
const int Q_SIZE = MAX * MAX;
#endif
Node Q[Q_SIZE];
typedef struct Queue {
	int qs;
	int qe;
	Node* Q;
} Queue;
static Queue queue;
void init(Queue* queue) {
	memset(Q, 0, sizeof(Q));
	queue->Q = Q;
	queue->qs = 0;
	queue->qe = 0;
}
bool isFull(Queue *queue) {
	return (queue->qe + 1) % Q_SIZE == queue->qs;
}
bool isEmpty(Queue* queue) {
	return (queue->qs == queue->qe);
}
bool enqueue(Queue* queue, Node* node) {
	if (isFull(queue)) return false;
	Node* Q = queue->Q;
	Q[queue->qe] = *node;
	queue->qe = (queue->qe + 1) % Q_SIZE;
	return true;
}
bool dequeue(Queue* queue, Node* ret) {
	if (isEmpty(queue)) return false;
	Node* Q = queue->Q;
	*ret = Q[queue->qs];
	queue->qs = (queue->qs + 1) % Q_SIZE;
	return true;
}
#ifdef CONFIG_DEBUG
void q_test() {
	clock_t start = clock();

	init(&queue);

	Node n1 = { 1, 1 }, n2 = { 2, 2 }, n3 = { 3, 3 }, n4 = { 4, 4 };
	Node res;
	EXPECT_EQ(enqueue(&queue, &n1), true);
	EXPECT_EQ(enqueue(&queue, &n2), true);
	EXPECT_EQ(enqueue(&queue, &n3), true);
	EXPECT_EQ(enqueue(&queue, &n3), false);
	EXPECT_EQ(dequeue(&queue, &res), true);
	EXPECT_EQ(res.y, n1.y);
	EXPECT_EQ(res.x, n1.x);
	EXPECT_EQ(dequeue(&queue, &res), true);
	EXPECT_EQ(res.x, n2.x);
	EXPECT_EQ(dequeue(&queue, &res), true);
	EXPECT_EQ(res.x, n3.x);

	double time = (clock() - start) / CLOCKS_PER_SEC;
	DEBUG(time);
}
#endif // CONFIG_DEBUG

int bfs() {
	Node* start = smalloc(0, 0, 1);
	
	visited[0][0] = true;
	init(&queue);
	enqueue(&queue, start);

	while (!isEmpty(&queue)) {
		Node* curr = smalloc();
		dequeue(&queue, curr);
		int y = curr->y, x = curr->x;
		int step = curr->val;
		DEBUG(y); DEBUG(x); DEBUG(step); DEBUG("\n");
		for (int d = 0; d < 4; ++d) {
			int ny = y + dy[d], nx = x + dx[d];
			if (!inRange(ny, nx)) continue;
			if (visited[ny][nx]) continue;
			if (board[ny][nx] == 0) continue;

			if (ny == Y - 1 && nx == X - 1) return step + 1;
			visited[ny][nx] = true;
			Node* next = smalloc(ny, nx, step + 1);
			enqueue(&queue, next);
		}
	}

	return -1;
}
#ifdef CONFIG_DEBUG
void bfs_test() {
	clock_t start = clock();

	memset(board, 0, sizeof(board));
	memset(visited, 0, sizeof(visited));
	Y = X = 3;
	board[0][0] = board[0][1] = board[0][2]
		= board[1][2] = board[2][2] = 1;
	print_board();
	EXPECT_EQ(bfs(), 5);

	double time = (clock() - start) / CLOCKS_PER_SEC;
	DEBUG(time);
}
#endif // CONFIG_DEBUG


#ifdef CONFIG_DEBUG
int __main() {
#else
int main() {
#endif // CONFIG_DEBUG
	char buf;
	scanf("%d %d\n", &Y, &X);
	for (int y = 0; y < Y; ++y)	{
		for (int x = 0; x < X; ++x) {
			scanf("%c", &board[y][x]);
			board[y][x] -= '0';
		}
		scanf("%c", &buf); // enter clear
	}

	print_board();
	printf("%d\n", bfs());
	return 0;
}

#ifdef CONFIG_DEBUG
void main_test() {
	clock_t start = clock();
	for (int TC = 0; TC < 4; ++TC)
	{
		memset(board, 0, sizeof(board));
		memset(visited, 0, sizeof(visited));
		memset(Q, 0, sizeof(Q));
		__main();
	}

	double time = (clock() - start) / CLOCKS_PER_SEC;
	DEBUG(time);
}
#endif // CONFIG_DEBUG

#ifdef CONFIG_DEBUG
int main() {
	freopen("prob2178_input.txt", "r", stdin);
	main_test();
	bfs_test();
	q_test();
	return 0;
}
#endif // CONFIG_DEBUG
#endif