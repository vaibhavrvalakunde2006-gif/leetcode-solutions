#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";

        string prefix = strs[0];

        for (int i = 1; i < (int)strs.size(); i++) {
            int j = 0;

            while (j < (int)prefix.size() &&
                   j < (int)strs[i].size() &&
                   prefix[j] == strs[i][j]) {
                j++;
            }

            prefix.resize(j);
            if (prefix.empty()) return "";
        }

        return prefix;
    }
};
