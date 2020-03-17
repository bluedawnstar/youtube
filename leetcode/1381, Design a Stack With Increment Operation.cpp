// https://leetcode.com/problems/design-a-stack-with-increment-operation/
// https://youtu.be/Nt3iFIbnQvU

class CustomStack {
public:
    int maxSize;
    vector<int> stk;
    vector<int> add;

    CustomStack(int maxSize) : maxSize(maxSize) {
    }

    // O(1)
    void push(int x) {
        if (stk.size() < maxSize) {
            stk.push_back(x);
            add.push_back(0);
        }
    }

    // O(1)
    int pop() {
        if (stk.empty())
            return -1;

        int x = stk.back();
        stk.pop_back();

        int addVal = add.back();
        add.pop_back();

        if (!add.empty())
            add.back() += addVal;

        return x + addVal;
    }

    // O(1)
    void increment(int k, int val) {
        if (stk.empty())
            return;

        int size = min(k, int(stk.size()));
        add[size - 1] += val;
    }
};
