#if 1
// #define CONFIG_DEBUG
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef unsigned long ul;
typedef long long ll;

#ifdef CONFIG_DEBUG
#include <Windows.h>
#include <iostream>
using namespace std;
#define DEBUG_LINE(func, line) "[" << func << "](" << line << ") "
#define DEBUG(x) cout << DEBUG_LINE(__func__, __LINE__) << #x << " is " << x << endl;
#define EXPECT_EQ(A, B) do { \
	auto a = A; \
	auto b = B; \
	if (a != b) cout << DEBUG_LINE(__func__, __LINE__) << a << ", " << b << endl; \
} while (0);
#else
#define DEBUG_LINE(func, line) {};
#define DEBUG(x) {};
#define EXPECT_EQ(A, B) {};
ul GetTickCount() { return 0; }
#endif /* CONFIG_DEBUG */

const int MAX = 55;
const int dy[] = { -1, 1, 0, 0 }, dx[] = { 0, 0, -1, 1 };
#ifdef CONFIG_DEBUG;
const int Q_SIZE = 4;
#else
const int Q_SIZE = MAX * MAX;
#endif

typedef struct Node {
	int y, x;
	int val;
} Node;
Node nodes[MAX * MAX * MAX];
Node* smalloc() {
	static int static_idx;
	return &nodes[++static_idx];
}

Node q[Q_SIZE];
int qs, qe;
bool isEmpty() {
	return qs == qe;
}
bool isFull() {
	return (qe + 1) % Q_SIZE == qs;
}
bool enqueue(Node* node) {
	if (isFull()) return false;
	q[qe] = *node;
	qe = (qe + 1) % Q_SIZE;
	return true;
}
bool dequeue(Node* ret) {
	if (isEmpty()) return false;
	*ret = q[qs];
	qs = (qs + 1) % Q_SIZE;
	return true;
}
#ifdef CONFIG_DEBUG
void q_test() {
	ul time = GetTickCount();

	qs = 0; qe = 0;
	memset(q, 0, sizeof(q));

	Node n1 = { 1, 1, 1 }, n2 = { 2, 2, 2 }, n3 = { 3, 3, 3 }, n4 = { 4, 4, 4 };
	Node res;
	EXPECT_EQ(enqueue(&n1), true);
	EXPECT_EQ(enqueue(&n2), true);
	EXPECT_EQ(enqueue(&n3), true);
	EXPECT_EQ(enqueue(&n3), false);
	EXPECT_EQ(dequeue(&res), true);
	EXPECT_EQ(res.val, n1.val);
	EXPECT_EQ(dequeue(&res), true);
	EXPECT_EQ(res.val, n2.val);
	EXPECT_EQ(dequeue(&res), true);
	EXPECT_EQ(res.val, n3.val);

	printf("[%s] %ld ms\n", __func__, GetTickCount() - time);
}
#endif

int Y, X;
int board[MAX][MAX];
bool visited[MAX][MAX];
bool inRange(int y, int x) {
	return 0 <= y && y < Y && 0 <= x && x < X;
}
int bfs(int sy, int sx) {
	int cnt = 0;
	if (board[sy][sx] == 0) return 0;
	if (visited[sy][sx]) return 0;

	visited[sy][sx] = true;
	Node* start = smalloc();
	start->y = sy, start->x = sx;
	enqueue(start);
	cnt++;

	while (!isEmpty()) {
		Node* curr = smalloc();
		dequeue(curr);
		int y = curr->y, x = curr->x;
		DEBUG(y);
		DEBUG(x);
		for (int d = 0; d < 4; d++) {
			int ny = y + dy[d], nx = x + dx[d];
			if (!inRange(ny, nx)) continue;
			if (board[ny][nx] == 0) continue;
			if (visited[ny][nx]) continue;

			visited[ny][nx] = true;
			Node* next = smalloc();
			next->y = ny, next->x = nx;
			enqueue(next);
			cnt++;
		}
	}

	return cnt;
}
#ifdef CONFIG_DEBUG
void bfs_test() {
	ul time = GetTickCount();

	memset(board, 0, sizeof(board));
	board[2][4] = board[3][4] = 1;
	board[4][2] = board[4][3] = 1;
	board[5][4] = 1;
	Y = X = 10;

	memset(visited, 0, sizeof(visited));
	EXPECT_EQ(bfs(2, 4), 2);
	memset(visited, 0, sizeof(visited));
	EXPECT_EQ(bfs(3, 4), 2);
	memset(visited, 0, sizeof(visited));
	EXPECT_EQ(bfs(4, 2), 2);
	memset(visited, 0, sizeof(visited));
	EXPECT_EQ(bfs(4, 3), 2);
	memset(visited, 0, sizeof(visited));
	EXPECT_EQ(bfs(5, 4), 2);

	printf("[%s] %ld ms\n", __func__, GetTickCount() - time);
}
#endif

#ifdef CONFIG_DEBUG
int __main() {
#else
int main() {
#endif
	int T;
	scanf("%d", &T);
	
	while (T--) {
		memset(board, 0, sizeof(board));
		memset(visited, 0, sizeof(visited));

		int K;
		scanf("%d %d %d", &X, &Y, &K);
		int ix, iy;
		for (int i = 0; i < K; i++) {
			scanf("%d %d", &ix, &iy);
			board[iy][ix] = 1;
		}

		int ans = 0;
		for (int y = 0; y < Y; y++)
			for (int x = 0; x < X; x++) {
				if (board[y][x] == 0) continue;
				if (bfs(y, x)) ans++;
			}

		printf("%d\n", ans);
	}
	return 0;
}
#ifdef CONFIG_DEBUG
void main_test() {
	ul time = GetTickCount();
	freopen("prob1012_input.txt", "r", stdin);
	for (int TC = 0; TC < 2; TC++)
		__main();
	
	printf("[%s] %ld ms\n", __func__, GetTickCount() - time);
}
#endif

#ifdef CONFIG_DEBUG
int main() {
	main_test();
	//bfs_test();
	//q_test();
	return 0;
}
#endif

#endif /* CONFIG_DEBUG */