class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> children(n);
        for (int i = 1; i < n; i++)
            children[parent[i]].push_back(i);

        vector<int> newParent = parent;
        vector<int> lastSeen(26, -1);
        vector<int> previous(n, -1);

        vector<pair<int, bool>> st;
        st.push_back({0, false});

        while (!st.empty()) {
            auto [node, exiting] = st.back();
            st.pop_back();

            int c = s[node] - 'a';

            if (exiting) {
                lastSeen[c] = previous[node];
                continue;
            }

            previous[node] = lastSeen[c];

            if (node != 0 && lastSeen[c] != -1)
                newParent[node] = lastSeen[c];

            lastSeen[c] = node;

            st.push_back({node, true});

            for (int i = (int)children[node].size() - 1; i >= 0; i--)
                st.push_back({children[node][i], false});
        }

        vector<vector<int>> modifiedChildren(n);

        for (int i = 1; i < n; i++)
            modifiedChildren[newParent[i]].push_back(i);

        vector<int> order;
        vector<int> stack = {0};

        while (!stack.empty()) {
            int node = stack.back();
            stack.pop_back();

            order.push_back(node);

            for (int child : modifiedChildren[node])
                stack.push_back(child);
        }

        vector<int> answer(n, 1);

        for (int i = n - 1; i > 0; i--) {
            int node = order[i];
            answer[newParent[node]] += answer[node];
        }

        return answer;
    }
};
