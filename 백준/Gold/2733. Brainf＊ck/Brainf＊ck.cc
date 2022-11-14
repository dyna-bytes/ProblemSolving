#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cstring>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl
#define debugVec(v) do{\
	cout << "[debug] " << #v << endl;\
	for (auto e: v) cout << e << " | ";\
	cout << endl;\
}while(0)
#define debugpii(p) cout << "[debug]" << #p << " is " << "{" << p.first << ", " << p.second << "}" << endl
typedef pair<int, int> pii;
typedef vector<int> vint;
typedef vector<pii> vpii;
#define __PRINT_ERROR__ cout << "COMPILE ERROR" << endl

const int MAX_N = 32768;
int A[MAX_N];
int pointer = 0;
unordered_map<int, int> par_hash;

void init() {
	memset(A, 0, MAX_N);
	pointer = 0;
}

void right_shift_pointer() {
	if (++pointer == MAX_N) pointer = 0;
}

void left_shift_pointer() {
	if (--pointer == -1) pointer = MAX_N - 1;
}

void add_pointer() {
	if (++A[pointer] == 256) A[pointer] = 0;
}

void sub_pointer() {
	if (--A[pointer] == -1) A[pointer] = 255;
}

char print_pointer() {
	return (char)A[pointer];
}

int stack_handler(stack<pii>& spii) {
	if (spii.empty()) return -1;

	while (spii.top().first != '[') {
		spii.pop();
		if (spii.empty()) return -1;
	}

	pii left_par = spii.top();
	spii.pop();
	return left_par.second;
}

int preprocess(string& line) {
	stack<pii> spii;
	par_hash = {};

	for (int i = 0; i < line.size(); i++) {
		if (line[i] == '[') spii.push({ line[i], i });
		if (line[i] == ']') {
			int r_par = i;
			int l_par = stack_handler(spii);
			if (l_par < 0) return -1;

			par_hash[l_par] = r_par;
			par_hash[r_par] = l_par;
		}
	}
	return 0;
}

void solve(string & line) {
	for (int i = 0; i < line.size(); ) {
		// right-shift pointer
		if (line[i] == '>') {
			right_shift_pointer();
			i++;
		}
		
		// left-shift pointer
		if (line[i] == '<') {
			left_shift_pointer();
			i++;
		}

		// add pointer
		if (line[i] == '+') {
			::add_pointer();
			i++;
		}

		// sub pointer
		if (line[i] == '-') {
			sub_pointer();
			i++;
		}

		// print pointer
		if (line[i] == '.') {
			cout << print_pointer();
			i++;
		}

		// move cursor to right par if (*pointer == 0)
		if (line[i] == '[') {
			if (par_hash.find(i) == par_hash.end()) {
				__PRINT_ERROR__;
				return;
			}

			int r_par = par_hash[i];

			if (A[pointer] == 0) i = r_par;
			else i++;
		}

		// move cursor to left par if (*pointer != 0)
		if (line[i] == ']') {
			if (par_hash.find(i) == par_hash.end()) {
				__PRINT_ERROR__;
				return;
			}

			int l_par = par_hash[i];

			if (A[pointer] != 0) i = l_par;
			else i++;
		}
	}

	cout << endl;
}

int main() {
	FASTIO;
	int T; cin >> T;
	string enter;
	getline(cin, enter);

	for (int t = 1; t <= T; t++) {
		string inp; 
		string line;
		while (true) {
			getline(cin, inp);
			if (inp == "end") break;
			for (char ch : inp) {
				if (ch == '%') break;
				if (ch == '<' || ch == '>' || ch == '+' || ch == '-' || ch == '.' || ch == '[' || ch == ']')
					line += ch;
			}
		}

		cout << "PROGRAM #" << t << ":" << endl;
		int ret = preprocess(line);
		if (ret < 0) {
			__PRINT_ERROR__;
			continue;
		}
		init();
		solve(line);
	}
}