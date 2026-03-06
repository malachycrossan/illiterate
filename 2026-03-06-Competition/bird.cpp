#include <iostream>
using namespace std;

typedef long T;

struct BIT {
    T tree[100001];
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
            if (tree[index] < 0) tree[index] = 0;
            index += lsb(index);
        }
    }
};

int main() {
    int t;
    cin >> t;
    for (int case_num = 0; case_num < t; case_num++){
        int n;
        cin >> n;
        // cout << "n: " << n;
        int q;
        cin >> q;
        // cout << " q: " << q << endl;
        T feeder[100001];
        for (int i = 0; i < n; i++){
            cin >> feeder[i];
            // cout << i << ":" << feeder[i] << " ";
        }

        BIT ft(feeder, n);

        for (int i = 0; i < q; i++) {
            char op;
            cin >> op;
            if (op == 'A') {
                int p; T x; cin >> p; cin >> x;
                // p -= 1;
                // cout << endl << "Found Add: " << p << " " << x;
                // cout << " query " << ft.query(p);
                ft.update(p, x);
                // cout << " => " << ft.query(p);
            } else if (op == 'S') {
                int p; T x; cin >> p; cin >> x;
                // p -= 1;
                // cout << endl << "Found Sub: " << p << " " << -x;
                T rem = min(x, ft.query(p,p));
                ft.update(p, -rem);
                // cout << " => " << ft.query(p);
            } else if (op == 'Q') {
                int l, r; T a; cin >> l; cin >> r; cin >> a;
                // l -= 1; r -= 1;
                T total = (a * (r - l + 1));
                // cout << endl << "Found Query: " << l << " -> " << r << "Avg: " << a << "a*(r-l) = " << total;
                T must_add = max((long)0,total - ft.query(l, r));
                cout << must_add << endl;
            }
        }
    }
}
