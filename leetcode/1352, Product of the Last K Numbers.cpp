// https://leetcode.com/problems/product-of-the-last-k-numbers/
// https://youtu.be/GgyjxJO-b9c

class ProductOfNumbers {
public:
    vector<int> S;  // ArrayList, list

    ProductOfNumbers() {
        S.push_back(1);
    }

    // O(1)
    void add(int num) {
        if (num == 0) {
            S.clear();
            S.push_back(1);
        } else {
            S.push_back(S.back() * num);
        }
    }

    // O(1)
    int getProduct(int k) {
        int n = int(S.size()) - 1;
        if (n < k)
            return 0;
        return int(S.back() / S[n - k]);
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
