#include <iostream>
using namespace std;

typedef int T;

struct BIT {
    T tree[100000];
    int n;

    BIT(T* values, int size) {
        n = size;
        for (int i = 1; i <= n; i++)
            tree[i] = values[i - 1];
        for (int i = 1; i <= n; i++) {
            int parent = i + lsb(i);
            if (parent <= n) tree[parent] += tree[i];
        }
    }

    int lsb(int n) { return n & (-n); }

    T query(int index) {
        T sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= lsb(index);
        }
        return sum;
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }

    T all () { return query(n - 1); }

    void update(int index, T value) {
        while (index <= n) {
            tree[index] += value;
            index += lsb(index);
        }
    }
};

int main() {
    int n;
    cin >> n;
    T values[100000];
    for (int i = 0; i < n; i++) cin >> values[i];

    BIT ft(values, n);

    int q;
    cin >> q;
    while (q--) {
        char op;
        cin >> op;
        if (op == 'Q') {
            int i; cin >> i;
            cout << ft.query(i) << "\n";
        } else if (op == 'R') {
            int l, r; cin >> l >> r;
            cout << ft.query(l, r) << "\n";
        } else if (op == 'U') {
            int i; T v; cin >> i >> v;
            ft.update(i, v);
        }
    }
    return 0;
}
