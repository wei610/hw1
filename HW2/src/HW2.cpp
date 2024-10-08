﻿#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// 生成并格式化输出幂集的函数
void powerset(const vector<string>& set) {
    int set_size = set.size(); // 集合的大小
    int powerset_size = 1 << set_size; // 幂集的大小为2^set_size
    ostringstream oss;
    oss << "powerset(S)={";

    // 遍历所有可能的子集
    for (int counter = 0; counter < powerset_size; ++counter) {
        oss << "(";
        bool first = true;
        for (int j = 0; j < set_size; ++j) {
            // 检查当前元素是否在子集中
            if (counter & (1 << j)) {
                if (!first) {
                    oss << ",";
                }
                oss << set[j];
                first = false;
            }
        }
        oss << ")";
        if (counter != powerset_size - 1) {
            oss << ",";
        }
    }
    oss << "}";

    cout << oss.str() << endl;
}

int main() {
    vector<string> S;
    string input;
    cout << "Enter elements (type 'end' to finish):" << endl;
    while (cin >> input && input != "end") {
        S.push_back(input);
    }

    powerset(S);

    return 0;
}
