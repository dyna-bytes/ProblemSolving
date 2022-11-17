#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
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
const int INF = 1e9;
const int ENDLESS_LOOP = 5e7;
const int MOD = 256;

int MAX, C, I;
vint A(1e5 + 100);
int pointer = 0;
int cursor = 0;
map<int, int> par_hash;

void init() {
	A = vint(1e5 + 100);
	pointer = 0;
	cursor = 0;
	par_hash = {};
}

void right_shift_pointer() {
	pointer = (pointer + 1) % MAX;
}

void left_shift_pointer() {
	pointer = (pointer - 1 + MAX) % MAX;
}

void add_pointer() {
	A[pointer] = (A[pointer] + 1) % MOD;
}

void sub_pointer() {
	A[pointer] = (A[pointer] - 1 + MOD) % MOD;
}

char print_pointer() {
	return (char)A[pointer];
}

void getchar_pointer(string& inputs) {
	A[pointer] = (cursor == I) ? MOD - 1 : inputs[cursor++];
}

void preprocess(string& line) {
	stack<int> s;

	for (int i = 0; i < line.size(); i++) {
		if (line[i] == '[') s.push(i);
		else if (line[i] == ']') {
			int l_par = s.top(); s.pop();

			par_hash[l_par] = i;
			par_hash[i] = l_par;
		}
	}
}

void solve(string& line, string& inputs) {
	int program_count = 0;
	int last_l_par = INF;
	bool inLoop = false;

	for (int i = 0; i < line.size(); i++) {
		// right-shift pointer
		if (line[i] == '>') {
			right_shift_pointer();
		}

		// left-shift pointer
		else if (line[i] == '<') {
			left_shift_pointer();
		}

		// add pointer
		else if (line[i] == '+') {
			::add_pointer();
		}

		// sub pointer
		else if (line[i] == '-') {
			sub_pointer();
		}

		// print pointer
		else if (line[i] == '.') {
			print_pointer();
		}

		// getchar pointer
		else if (line[i] == ',') {
			getchar_pointer(inputs);
		}

		// move cursor to right par if (*pointer == 0)
		else if (line[i] == '[') {
			int r_par = par_hash[i];

			if (A[pointer] == 0) i = r_par;
		}

		// move cursor to left par if (*pointer != 0)
		else if (line[i] == ']') {
			int l_par = par_hash[i];

			if (A[pointer] != 0) i = l_par;
		}

		if (++program_count > ENDLESS_LOOP)
			last_l_par = min(last_l_par, i);

		if (program_count > ENDLESS_LOOP * 2) {
			inLoop = true;
			break;
		}
	}

	if (inLoop) cout << "Loops " << last_l_par << " " << par_hash[last_l_par] << endl;
	else cout << "Terminates" << endl;
}

int main() {
	FASTIO;
	
	int T; cin >> T;
	while (T--) {
		cin >> MAX >> C >> I;
		
		string line; 
		cin >> line;

		string inputs;
		cin >> inputs;

		init();
		preprocess(line);
		solve(line, inputs);
	}
}