#include <iostream>
#include <cmath>

struct Node {
    int coef; // 系数
    int exp;  // 指数
    Node* link; // 指向下一个节点的指针
};

class Polynomial {
private:
    Node* head;  // 指向头节点的指针

    // 插入节点的私有方法
    void InsertNode(int coef, int exp);

    // 用于管理空闲空间链表的私有方法
    static Node* avail;
    static Node* GetNode();
    static void RetNode(Node* node);

public:
    Polynomial();  // 构造函数
    Polynomial(const Polynomial& a);  // 拷贝构造函数
    ~Polynomial(); // 析构函数

    Polynomial& operator=(const Polynomial& a);  // 赋值运算符
    Polynomial operator+(const Polynomial& b) const;  // 加法运算符
    Polynomial operator-(const Polynomial& b) const;  // 减法运算符
    Polynomial operator*(const Polynomial& b) const;  // 乘法运算符
    float Evaluate(float x) const;  // 评估多项式值

    friend std::istream& operator>>(std::istream& is, Polynomial& x);  // 输入运算符重载
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& x);  // 输出运算符重载
};

// 初始化可用空间列表
Node* Polynomial::avail = nullptr;

Node* Polynomial::GetNode() {
    if (avail) {
        Node* node = avail;
        avail = avail->link;
        return node;
    }
    return new Node;
}

void Polynomial::RetNode(Node* node) {
    node->link = avail;
    avail = node;
}

// 构造函数
Polynomial::Polynomial() {
    head = GetNode();
    head->link = head; // 初始化头节点指向自己，形成循环链表
}

// 拷贝构造函数
Polynomial::Polynomial(const Polynomial& a) {
    head = GetNode();
    head->link = head;

    Node* current = a.head->link;
    while (current != a.head) {
        InsertNode(current->coef, current->exp);
        current = current->link;
    }
}

// 析构函数
Polynomial::~Polynomial() {
    Node* current = head->link;
    while (current != head) {
        Node* temp = current;
        current = current->link;
        RetNode(temp);
    }
    RetNode(head);
}

// 赋值运算符重载
Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this == &a) return *this;

    Node* current = head->link;
    while (current != head) {
        Node* temp = current;
        current = current->link;
        RetNode(temp);
    }
    head->link = head;

    current = a.head->link;
    while (current != a.head) {
        InsertNode(current->coef, current->exp);
        current = current->link;
    }
    return *this;
}

// 插入节点的方法
void Polynomial::InsertNode(int coef, int exp) {
    Node* newNode = GetNode();
    newNode->coef = coef;
    newNode->exp = exp;

    Node* prev = head;
    Node* current = head->link;

    while (current != head && current->exp > exp) {
        prev = current;
        current = current->link;
    }

    newNode->link = current;
    prev->link = newNode;
}

// 加法运算符重载
Polynomial Polynomial::operator+(const Polynomial& b) const {
    Polynomial result;
    Node* aTerm = head->link;
    Node* bTerm = b.head->link;

    while (aTerm != head || bTerm != b.head) {
        if (aTerm != head && (bTerm == b.head || aTerm->exp > bTerm->exp)) {
            result.InsertNode(aTerm->coef, aTerm->exp);
            aTerm = aTerm->link;
        }
        else if (bTerm != b.head && (aTerm == head || bTerm->exp > aTerm->exp)) {
            result.InsertNode(bTerm->coef, bTerm->exp);
            bTerm = bTerm->link;
        }
        else {
            int newCoef = aTerm->coef + bTerm->coef;
            if (newCoef != 0)
                result.InsertNode(newCoef, aTerm->exp);
            aTerm = aTerm->link;
            bTerm = bTerm->link;
        }
    }
    return result;
}

// 减法运算符重载
Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial result;
    Node* aTerm = head->link;
    Node* bTerm = b.head->link;

    while (aTerm != head || bTerm != b.head) {
        if (aTerm != head && (bTerm == b.head || aTerm->exp > bTerm->exp)) {
            result.InsertNode(aTerm->coef, aTerm->exp);
            aTerm = aTerm->link;
        }
        else if (bTerm != b.head && (aTerm == head || bTerm->exp > aTerm->exp)) {
            result.InsertNode(-bTerm->coef, bTerm->exp);
            bTerm = bTerm->link;
        }
        else {
            int newCoef = aTerm->coef - bTerm->coef;
            if (newCoef != 0)
                result.InsertNode(newCoef, aTerm->exp);
            aTerm = aTerm->link;
            bTerm = bTerm->link;
        }
    }
    return result;
}

// 乘法运算符重载
Polynomial Polynomial::operator*(const Polynomial& b) const {
    Polynomial result;

    for (Node* aTerm = head->link; aTerm != head; aTerm = aTerm->link) {
        Polynomial temp;
        for (Node* bTerm = b.head->link; bTerm != b.head; bTerm = bTerm->link) {
            temp.InsertNode(aTerm->coef * bTerm->coef, aTerm->exp + bTerm->exp);
        }
        result = result + temp;
    }
    return result;
}

// 评估多项式值
float Polynomial::Evaluate(float x) const {
    float result = 0.0;
    Node* curr = head->link;
    while (curr != head) {
        result += curr->coef * pow(x, curr->exp);
        curr = curr->link;
    }
    return result;
}

// 输入运算符重载
std::istream& operator>>(std::istream& is, Polynomial& x) {
    int n;
    is >> n;
    for (int i = 0; i < n; i++) {
        int coef, exp;
        is >> coef >> exp;
        x.InsertNode(coef, exp);
    }
    return is;
}

// 输出运算符重载
std::ostream& operator<<(std::ostream& os, const Polynomial& x) {
    Node* curr = x.head->link;
    while (curr != x.head) {
        os << curr->coef << "x^" << curr->exp;
        if (curr->link != x.head) os << " + ";
        curr = curr->link;
    }
    return os;
}
int main() {
    Polynomial p1, p2, p3;

    // 輸入第一個多項式
    std::cout << "輸入第一個多項式 (格式: n, C1, e1, C2, e2, ..., Cn, en): ";
    std::cin >> p1;

    // 輸出第一個多項式
    std::cout << "第一個多項式: " << p1 << std::endl;

    // 輸入第二個多項式
    std::cout << "輸入第二個多項式 (格式: n, C1, e1, C2, e2, ..., Cn, en): ";
    std::cin >> p2;

    // 輸出第二個多項式
    std::cout << "第二個多項式: " << p2 << std::endl;

    // 計算並輸出兩個多項式的和
    p3 = p1 + p2;
    std::cout << "兩個多項式的和: " << p3 << std::endl;

    // 計算並輸出兩個多項式的差
    p3 = p1 - p2;
    std::cout << "兩個多項式的差: " << p3 << std::endl;

    // 計算並輸出兩個多項式的積
    p3 = p1 * p2;
    std::cout << "兩個多項式的積: " << p3 << std::endl;

    // 評估並輸出第一個多項式在某個值下的結果
    float x;
    std::cout << "輸入一個值來評估第一個多項式: ";
    std::cin >> x;
    std::cout << "評估結果: " << p1.Evaluate(x) << std::endl;

    return 0;
}
