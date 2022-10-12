#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

bool checkSubstr(string needle, string haystack) {
    int needlePointer = 0;

    int lenNeedle = needle.length();
    int lenHaystack = haystack.length();

    if (lenNeedle == 0) {
        return false;
    }

    if (lenHaystack == 0) {
        return true;
    }

    for (int i = 0; i < lenHaystack; i++) {
        if (needle[needlePointer] != haystack[i]) {
            needlePointer = 0;
            continue;
        }

        needlePointer++;

        if (needlePointer == lenNeedle) {
            return true;
        }
    }

    return false;
}

void printResult(vector<string> strings, int n, map<string, vector<string> > mp) {
    cout << "Results are:" << endl;
    for (int i = 0; i < n; i++) {
        cout << strings[i] << ": ";
        if (mp.find(strings[i]) != mp.end()) {
            vector<string> v1 = mp[strings[i]];
            for (int j = 0; j < v1.size(); j++) {
                cout << v1[j] << " ";
            }
        }
        cout << endl;
    }
}

void findSubstrings(vector<string> strings) {
    int n = strings.size();

    map<string, vector<string> > mp;
    set<string> computedSet;

    for (int i = 0; i < n; i++) {
        if (computedSet.find(strings[i]) != computedSet.end()) {
            continue;
        }

        for (int j = 0; j < n; j++) {
            if (i != j && checkSubstr(strings[i], strings[j])) {
                mp[strings[i]].push_back(strings[j]);
            }
        }
        computedSet.insert(strings[i]);
    }

    printResult(strings, n, mp);
}

int main() {
    int n;
    cout << "Enter number of strings:";
    cin >> n;

    vector<string> strings;

    cout << "Enter strings:" << endl;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        strings.push_back(s);
    }

    findSubstrings(strings);
}