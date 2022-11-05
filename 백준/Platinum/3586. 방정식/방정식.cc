#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl;
#define debugVec(v) do{\
    cout << "[debug] " << #v << endl;\
    for (auto e: v) cout << v << " | ";\
    cout << endl;\
}while(0);
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define __PRINT_ERROR_NONE__ cout << "NONE" << endl
#define __PRINT_ERROR_MULTIPLE__ cout << "MULTIPLE" << endl
typedef long long ll;

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return abs(a);
}

// @Fraction: p/q
struct Frac {
    ll p, q;
    Frac() { p = 0, q = 1; }
    Frac(ll _p, ll _q) {
        p = _p / gcd(_p, _q);
        q = _q / gcd(_p, _q);
        if (p == 0) q = 1;
    }
    Frac operator+(const Frac& other) const {
        Frac ret;
        ret.p = this->p * other.q + this->q * other.p;
        ret.q = this->q * other.q;
        ret = Frac(ret.p, ret.q);
        return ret;
    }
    Frac operator*(const Frac& other) const {
        Frac ret;
        ret.p = this->p * other.p;
        ret.q = this->q * other.q;
        ret = Frac(ret.p, ret.q);
        return ret;
    }
    Frac operator-(const Frac& other) const {
        return *this + other * Frac(-1, 1);
    }
    Frac operator/(const Frac& other) const {
        assert(other.p != 0);        
        return Frac(*this * Frac(other.q, other.p));
    }
    bool operator==(const Frac& other) const {
        Frac ft = Frac(this->p, this->q);
        Frac sc = Frac(other.p, other.q);
        return (ft.p == sc.p) && (ft.q == sc.q);
    }
    bool operator!=(const Frac& other) const {
        return !(*this == other);
    }
    friend ostream& operator << (ostream& out, const Frac& frac);
};

std::ostream& operator << (ostream& out, Frac& frac) {
    if (frac.q < 0) {
        frac.p *= -1;
        frac.q *= -1;
    }
    out << frac.p << "/" << frac.q;
    return out;
}

const Frac ZERO(0, 1);
const Frac ONE(1, 1);
const Frac MINUS(-1, 1);

// @Expression: (ax + b)/(cx + d)
struct Expr {
    Frac a, b, c, d;
    Expr() {};
    Expr(Frac _a, Frac _b, Frac _c, Frac _d) {
        a = _a, b = _b, c = _c, d = _d;
    }
    Expr(ll _a, ll _b, ll _c, ll _d) {
        a = Frac(_a, 1), b = Frac(_b, 1), c = Frac(_c, 1), d = Frac(_d, 1);
    }
    Expr operator+(const Expr& rhs) const {
        Expr ret;
        ret.a = this->a * rhs.d + this->d * rhs.a + this->b * rhs.c + this->c * rhs.b;
        ret.b = this->b * rhs.d + this->d * rhs.b;
        ret.c = this->c * rhs.d + this->d * rhs.c;
        ret.d = this->d * rhs.d;
        return ret;
    }
    Expr operator-(const Expr& rhs) const {
        Expr mrhs = rhs;
        mrhs.a = MINUS * rhs.a;
        mrhs.b = MINUS * rhs.b;
        return *this + mrhs;
    }
    Expr operator*(const Expr& rhs) const {
        Expr ret;
        ret.a = this->a * rhs.b + this->b * rhs.a;
        ret.b = this->b * rhs.b;
        ret.c = this->c * rhs.d + this->d * rhs.c;
        ret.d = this->d * rhs.d;
        return ret;
    }
    Expr operator/(const Expr& rhs) const {
        if (rhs.a == ZERO && rhs.b == ZERO) {
            __PRINT_ERROR_NONE__;
            exit(0);
        }
        Expr irhs = Expr(rhs.c, rhs.d, rhs.a, rhs.b);
        return *this * irhs;
    }
};

bool isNum(char x) {
    return x >= '0' && x <= '9';
}

Expr init_var(char x) {
    if (isNum(x)) return Expr(0, x - '0', 0, 1);
    return Expr(1, 0, 0, 1); 
}

stack<Expr> S;
Expr run_stack(string postfix, Frac real_x = ZERO, bool execute=false) {
    S = {};

    for (char x : postfix) {
        if (x == 'X') {
            Expr var = execute ? Expr(ZERO, real_x, ZERO, ONE) : init_var(x);
            S.push(var);
        }
        else if (isNum(x)) {
            Expr num = init_var(x);
            S.push(num);
        }
        else if (x == '+') {
            Expr rhs = S.top(); S.pop();
            Expr lhs = S.top(); S.pop();
            S.push(lhs + rhs);
        }
        else if (x == '-') {
            Expr rhs = S.top(); S.pop();
            Expr lhs = S.top(); S.pop();
            S.push(lhs - rhs);
        }
        else if (x == '*') {
            Expr rhs = S.top(); S.pop();
            Expr lhs = S.top(); S.pop();
            S.push(lhs * rhs);
        }
        else if (x == '/') {
            Expr rhs = S.top(); S.pop();
            Expr lhs = S.top(); S.pop();
            S.push(lhs / rhs);
        }
    }

    return S.top();
}

int main() {
    string inp; 
    getline(cin, inp);
    string postfix;
    for (char ch : inp) {
        if (ch == ' ') continue;
        postfix += ch;
    }

    Expr res = run_stack(postfix);

    if ((res.a == ZERO && res.b == ZERO) && (res.c != ZERO || res.d != ZERO)) {
        __PRINT_ERROR_MULTIPLE__;
        return 0;
    }
    if (res.a == ZERO || (res.c == ZERO && res.d == ZERO)) {
        __PRINT_ERROR_NONE__;
        return 0;
    }

    // 이항해서 X 구함
    Frac X = MINUS * res.b / res.a;

    // check answer (check if divide-by-zero happens)
    run_stack(postfix, X, true);
    cout << "X = " << X << endl;
    return 0;
}