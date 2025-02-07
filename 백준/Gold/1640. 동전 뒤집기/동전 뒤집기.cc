#include <bits/stdc++.h>
#define FASTIO cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0)
#define endl '\n'
using namespace std;

int Y, X;
vector<vector<int>> matrix;
vector<int> is_even_row, is_even_col;

void input() {
    cin >> Y >> X;
    matrix.resize(Y, vector<int>(X));
    is_even_row.resize(Y, 0), is_even_col.resize(X, 0);
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            char num;
            cin >> num;
            matrix[y][x] = num - '0';
            is_even_row[y] ^= matrix[y][x];
        }
        is_even_row[y] = !is_even_row[y];
    }

    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            is_even_col[x] ^= matrix[y][x];
        }
        is_even_col[x] = !is_even_col[x];
    }
}

int solve() {
    int count_even_rows = 0;
    for (bool r: is_even_row) count_even_rows += r;
    int count_even_cols = 0;
    for (bool c: is_even_col) count_even_cols += c;

    // 모든 row를 odd 또는 even으로 통일
    auto flip_rows = [&](bool try_even_rows) {
        if (try_even_rows) return count_even_rows;
        return Y - count_even_rows;
    };
    int try_row_odd = flip_rows(false);
    int try_row_even = flip_rows(true);

    // 모든 column을 even으로 통일
    auto filp_cols = [&](int num_of_filped_rows) {
        // 1. 만약 모든 뒤집은 row 의 개수가 짝수개였다면, odd 인 column 들을 뒤집음
        if (num_of_filped_rows % 2) return count_even_cols;
        // 2. 만약 모든 뒤집은 row 의 개수가 홀수개였다면, even 인 column 들을 뒤집음
        return X - count_even_cols;
    };
    try_row_odd += filp_cols(try_row_odd);
    try_row_even += filp_cols(try_row_even);

    return min(try_row_odd, try_row_even);
}

int main() {
    FASTIO;
    input();
    cout << solve() << endl;
    return 0;
}