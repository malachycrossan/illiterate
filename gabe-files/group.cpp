#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

static unordered_map<string, int> m;

void printQueries(int queries) {
    int week;
    string qname;
    // Loops through queries.
    for(int q = 0; q < queries; q++) {
        cin >> qname;
        if(auto search = m.find(qname); search == m.end()) {
            // Cannot find student.
            cout << -1 << endl;
        } else {
            // Displays associated week.
            cout << m.at(qname) << endl;
        }
    }

    return;
}

int main() {
    int cases, students, queries, week;
    string name;
    cin >> cases;

    for(int i = 0; i < cases; i++) {
        cin >> students >> queries;
        for(int j = 0; j < students; j++) {
            cin >> name;
            cin >> week;
            m.insert({name, week});
        }

        printQueries(queries);
    }

    return 0;
}