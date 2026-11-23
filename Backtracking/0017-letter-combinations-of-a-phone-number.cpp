class Solution {
private:
    const vector<string> letters = {
        "", "", "abc", "def", "ghi",
        "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    void backtrack(const string& digits, int index,
                   string& current, vector<string>& result) {
        if (index == static_cast<int>(digits.size())) {
            result.push_back(current);
            return;
        }

        const string& choices = letters[digits[index] - '0'];

        for (char ch : choices) {
            current.push_back(ch);
            backtrack(digits, index + 1, current, result);
            current.pop_back();
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty())
            return {};

        vector<string> result;
        string current;
        backtrack(digits, 0, current, result);
        return result;
    }
};
