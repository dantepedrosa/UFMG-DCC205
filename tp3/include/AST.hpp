#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    string temp;
    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (isspace(c)) continue;

        if (c == '(' || c == ')') {
            tokens.push_back(string(1, c));
        } else if (c == '&' && i + 1 < expr.size() && expr[i + 1] == '&') {
            tokens.push_back("&&");
            i++;
        } else if (c == '=' && i + 1 < expr.size() && expr[i + 1] == '=') {
            tokens.push_back("==");
            i++;
        } else if (c == '<' && i + 1 < expr.size() && expr[i + 1] == '=') {
            tokens.push_back("<=");
            i++;
        } else {
            temp += c;
            if (i + 1 == expr.size() || !isalnum(expr[i + 1])) {
                tokens.push_back(temp);
                temp = "";
            }
        }
    }
    return tokens;
}

Node* parseExpression(const vector<string>& tokens) {
    stack<Node*> nodes;
    stack<string> ops;
    for (const string& token : tokens) {
        if (token == "(") {
            ops.push(token);
        } else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                Node* right = nodes.top(); nodes.pop();
                Node* left = nodes.top(); nodes.pop();
                Node* opNode = new Node(ops.top()); ops.pop();
                opNode->left = left;
                opNode->right = right;
                nodes.push(opNode);
            }
            ops.pop();
        } else if (token == "&&") {
            while (!ops.empty() && ops.top() != "(") {
                Node* right = nodes.top(); nodes.pop();
                Node* left = nodes.top(); nodes.pop();
                Node* opNode = new Node(ops.top()); ops.pop();
                opNode->left = left;
                opNode->right = right;
                nodes.push(opNode);
            }
            ops.push(token);
        } else if (token == "==" || token == "<=") {
            ops.push(token);
        } else {
            nodes.push(new Node(token));
        }
    }
    return nodes.top();
}

void printTree(Node* root, int level = 0) {
    if (!root) return;
    printTree(root->right, level + 1);
    cout << string(level * 4, ' ') << root->value << endl;
    printTree(root->left, level + 1);
}

int main() {
    string expression = "(((org==DEN)&&(dst==ORD))&&((prc<=500)&&(dur<=8400)))";
    vector<string> tokens = tokenize(expression);
    Node* root = parseExpression(tokens);
    printTree(root);
    return 0;
}
