/**
    SubsetSum.cpp is a C++ implementation of a dynamic programming algorithm
    for solving the subset sum problem. See ``https://en.wikipedia.org/wiki/
    Subset_sum_problem#Pseudo-polynomial_time_dynamic_programming_solution''

    @author Joseph Boyd
*/

#include <iostream>
#include <vector>

using namespace std;


/**
    SubsetSum is a class for solving the subset sum problem for a given set 
    of integers.
*/
class SubsetSum {
public:
    SubsetSum(vector<int> nums) : _nums(nums) {
        this->_N = this->_nums.size();
        this->_min = sumNegatives();
        this->_max = sumPositives();
        this->_lookup = new bool*[this->_N];

        for(int i = 0; i < this->_N; i++) {
            this->_lookup[i] = new bool[this->_max - this->_min + 1];
        }
    }

    ~SubsetSum() {
        for(int i = 0; i < this->_N; i++) {
            delete[] this->_lookup[i];
        }
    }

    /**
        Solves subset sum problem for member numbers in feasible range
    */
    void solve() {
        for (int i = 0; i < this->_N; i++) {
            for (int j = this->_min; j <= this->_max; j++) {
                if (i == 0) {
                    this->_lookup[i][j - this->_min] = (this->_nums[i] == j);
                }
                else if (_min <= j - _nums[i] && j - _nums[i] <= _max) {
                    this->_lookup[i][j - this->_min] = 
                        this->_nums[i] == j ||
                        this->_lookup[i - 1][j - this->_min] ||
                        this->_lookup[i - 1][j - this->_min - this->_nums[i]];

                }
                else {
                    this->_lookup[i][j - this->_min] = 
                        this->_nums[i] == j ||
                        this->_lookup[i - 1][j - this->_min];
                }
            }
        }
    }

    /**
        Returns vector of numbers summing to target value

        @param target sum value
        @return vector of numbers summing to target value
    */
    vector<int> retrieve_subset(int target) {
        vector<int> subset;

        if (target < this->_min || target > this->_max || 
            ! this->_lookup[this->_N - 1][target - this->_min]) {
            return subset;
        }

        for(int i = this->_N - 1; i >= 0; i--) {
            if (this->_nums[i] == target) {
                subset.push_back(this->_nums[i]);
                return subset;
            }
            else if(! this->_lookup[i - 1][target - this->_min]) {
                subset.push_back(this->_nums[i]);
                target = target - this->_nums[i];
            }
        }
        return subset;
    }

private:
    vector<int> _nums;
    int _N;
    int _min;
    int _max;
    bool** _lookup;
    
    /**
        Returns sum of positives in integer array

        @param nums array of integers
        @return sum of positives in integer array
    */
    int sumPositives() {
        int sum = 0;
        for(int i = 0; i < this->_N; i++) {
            if (this->_nums[i] > 0) sum += this->_nums[i];
        }
        return sum;
    }

    /**
        Returns sum of negatives in integer array

        @param nums array of integers
        @return sum of negatives in integer array
    */
    int sumNegatives() {
        int sum = 0;
        for(int i = 0; i < this->_N; i++) {
            if (this->_nums[i] < 0) sum += this->_nums[i];
        }
        return sum;
    }
};

int main() {
    const int N = 10;
    vector<int> vecNums(N);
    
    int nums[N] = {1, -2, 3, -4, 5, -6, 7, -8, 9, 10};
    for(int i = 0; i < N; i++) {
        vecNums[i] = nums[i];
    }

    SubsetSum ss = SubsetSum(vecNums);
    ss.solve();
    vector<int> subset = ss.retrieve_subset(30);

    cout << "{ ";
    for (int i = 0; i < subset.size(); i++) {
        cout << subset[i] << " ";
    }
    cout << "}" << endl;
}
