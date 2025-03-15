逻辑结构：

线性结构，树形结构，图结构。

存储结构（物理结构）：

顺序结构，链式结构，索引结构，散列结构,链式存储的数据结构的注意点：

- 通常会用结构体表示结点，用结构体指针表示整个链式结构

- 可以带或者不带头结点，有头结点会方便一些，这里都用头结点

常用操作：

插入，删除，查找（按值，按位），求长，输出（遍历），判空，判满。

# 一、线

## 1 表

顺序存储结构即数组，也叫顺序表、线性表；链式存储即链表，区别：

- 访问效率：
  
  * 顺序表在连续空间，效率 O(1)
  
  * 链表 O\(n\)

- 插入/删除效率：
  
  * 顺序表需要移动插入/删除位置后的所有元素，平均 O\(n\)
  
  * 链表只需要改变 next 指向即可，但也需要先遍历，判，平均也是 O\(n\) ，但比顺序表移动元素的效率好

- 空间利用
  
  * 顺序表由于是连续空间，因此会产生内存碎片，造成浪费；且顺序表需要初始化一片空间，太大太小都不合适，动态分配内存也需要拷贝所有元素，效率低下
  
  * 链表则可以利用内存中的一块块小的内存空间；也不需要像顺序表每次动态分配内存都需要拷贝所有元素；但如果是确定长度的情况下，链表需要频繁动态分配内存，效率就不如顺序表

### 1.1 顺序表

对数组进行封装：

```
#include<iostream>
#include<stdlib.h>
using namespace std;

// 顺序表结构
typedef struct SeqList {
    // 静态书序表
    // int data[10];
    // 动态顺序表
    int *data;
    int maxSize;
    int length;
} SeqList;

// 初始化
bool initSeqList(SeqList &list, int len) {
    list.data = (int*)malloc(sizeof(int) * len);
    if (!list.data)  return false;
    list.maxSize = len;
    list.length = 0;
    return true;
}

// 增加长度
bool addSeqListLength(SeqList &list, int len) {
    int *p = list.data;
    list.data = (int*)malloc(sizeof(int) * (list.maxSize + len));
    if (!list.data)  return false;

    for (int i = 0; i < list.length; i++)  list.data[i] = p[i];
    free(p);
    list.maxSize += len;

    return true;
}

// 按位查找，可以是从 0 开始的索引，也可以是从 1 开始的位序，这里用索引
bool findOfIndex(SeqList &list, int index, int &res) {
    if (index >= list.maxSize || index <= -list.maxSize)  return false;

    // 支持负数索引
    int i = (index + list.maxSize) % list.maxSize;
    res = list.data[i];

    return true;
}

// 按值查找，找到返回索引，找不到返回 -1
int findOfValue(SeqList &list, int value) {
    for (int i = 0; i < list.maxSize; i++) {
        if (list.data[i] == value)  return i;
    }
    return -1;
}

bool pushBack(SeqList &list, int a) {
    if (list.length >= list.maxSize) {
        if (!addSeqListLength(list, 5))  return false;
    }
    list.data[list.length++] = a;
    return true;
}

// 可以是从 0 开始的索引，也可以是从 1 开始的位序，这里用索引
bool insert(SeqList &list, int index, int value) {
    if (index >= list.length || index <= -list.length)  return false;

    if (list.length >= list.maxSize) {
        if (!addSeqListLength(list, 5))  return false;
    }

    // 支持负数索引
    int ind = (index + list.length) % list.length;

    for (int i = list.length - 1; i >= ind; i--)  list.data[i + 1] = list.data[i];
    list.data[ind] = value;
    ++list.length;

    return true;
}


bool popBack(SeqList &list) {
    if (list.length <= 0)  return false;
    --list.length;
    return true;
}

bool remove(SeqList &list, int index) {
    if (list.length <= 0)  return false;
    if (index >= list.length || index <= -list.length)  return false;

    int ind = (index + list.length) % list.length;

    for (int i = ind; i < list.length; i++)  list.data[i] = list.data[i + 1];
    --list.length;

    return true;
}

void deleteSeqList(SeqList &list) {
    free(list.data);
    list.data = NULL;
    list.maxSize = 0;
    list.length = 0;
}

void printSeqList(SeqList &list) {
    for (int i = 0; i < list.length; i++) cout << list.data[i] << " ";
    cout << endl;
}


int main() {
    SeqList list;
    if (!initSeqList(list, 10))  return 0;

    for (int i = 0; i < 15; i++) pushBack(list, i);
    popBack(list);

    insert(list, 10, 123);
    insert(list, 10, 456);
    insert(list, -10, 789);

    remove(list, 2);
    remove(list, -3);

    cout << findOfValue(list, 123) << endl;
    int res;
    findOfIndex(list, 11, res);
    cout << res << endl;

    printSeqList(list);
    deleteSeqList(list);

    return 0;
}
```

### 1.2 链表

（1）单链表

```
// srruct 版

#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, * LinkList;

bool initLinkList(LinkList &list) {
    list = (LNode*)malloc(sizeof(LNode));
    if (!list)  return false;
    list->next = NULL;
    return true;
}

// 判空
bool isEmpty(LinkList &list) {
    return list->next == NULL;
}

// 头插法
bool insertByHead(LinkList &list, int a) {
    LNode *node = (LNode*)malloc(sizeof(LNode));
    if (!node)  return false;

    node->data = a;
    node->next = list->next;
    list->next = node;

    return true;
}

// 尾插法
bool insertByTail(LinkList &list, int a) {
    LNode *p = list;
    LNode *node = (LNode*)malloc(sizeof(LNode));
    if (!node)  return false;

    while (p->next != NULL)  p = p->next;

    node->data = a;
    node->next = NULL;
    p->next = node;

    return true;
}

// 插入
bool insert(LinkList &list, int loc, int a) {
    if (loc <= 0)  return false;

    LNode* p = list;
    for (int i = 0; i < loc - 1; i++) {
        p = p->next;
        if (!p)  return false;
    }

    LNode *node = (LNode*)malloc(sizeof(LNode));
    if (!node)  return false;

    node->data = a;
    node->next = p->next;
    p->next = node;

    return true;
}

// 删除
bool remove(LinkList &list, int loc) {
    if (loc <= 0)  return false;

    LNode* p = list;
    for (int i = 0; i < loc - 1; i++) {
        p = p->next;
        if (!p->next)  return false;
    }

    LNode* q = p->next;
    p->next = q->next;
    free(q);

    return true;
}

// 遍历
void printLinkList(LinkList &list) {
    LNode *p = list;
    while (!isEmpty(p)) {
        p = p->next;
        cout << p->data << " ";
    }
    cout << endl;
}

// 清空
void deleteLinkList(LinkList& list) {
    LNode *p = list;

    while (!isEmpty(p)) {
        LNode *q = p->next;
        p->next = q->next;
        free(q);
    }

    free(list);
    list = NULL;
}

int main() {
    LinkList list = NULL;
    if (!initLinkList(list))  return 0;

    for (int i = 0; i < 3; i++) {
        insertByHead(list, i);
        insertByTail(list, i);
    }

    insert(list, 7, 3);
    remove(list, 7);

    // 2 1 0 0 1 2
    printLinkList(list);

    deleteLinkList(list);

    return 0;
}
```

（2）双链表

多一个方向相反的指针域，可以更方便的实现一些功能，比如翻转链表。

```
typedef struct LNode {
    int data;
    struct LNode *next, *prior;
} LNode, *LinkList;
```

（3）循环链表

链表的最后一个结点的 next 指向头结点或第一个结点，好处是尾插法效率也能达到 O\(1\) 。可以是循环单链表，也可以是循环双链表。

（4）静态链表

用一片连续的空间存储链表，每个结点通过游标 next 存储的数组下标找到下一个元素，每个结点的顺序不一定要按照数组的顺序。

比顺序表的有点事出入删除元素不再需要移动元素。

```
#define MAX_SIZE 10

typedef struct LNode {
    int data;
    // 游标卡尺，0\-1\-2 表示头结点/最后一个结点/空闲结点
    int next;
} StaticLinkList[MAX_SIZE];
```

# 2 栈

只允许同一个端入栈和出栈，先进后出。

（1）顺序存储

栈顶可以在末位元素，也可以在末位元素下一个位置，只是 +1 -1 区别，这里采用栈顶在末位元素：

```
// struct 版

#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct SeqStack {
    int* data;
    int top =, maxSize;
} SeqStack;

bool init(SeqStack& s, int len) {
    s.data = (int*)malloc(sizeof(int) * len);
    if (!s.data)  return false;
    s.maxSize = len;
    s.top = -1;
    return true;
}

int getLenth(SeqStack& s) {
    return  s.top + 1;
}

bool addLenth(SeqStack& s, int len) {
    int* newData = (int*)malloc(sizeof(int) * (len + s.maxSize));
    if (!s.data)  return false;
    for (int i = 0; i < getLenth(s); i++)  newData[i] = s.data[i];

    free(s.data);
    s.data = newData;
    s.maxSize += len;
    return true;
}

bool isEmpty(SeqStack& s) {
    return s.top <= -1;
}

bool isFull(SeqStack& s) {
    return  s.top + 1 >= s.maxSize;
}

bool pushBack(SeqStack& s, int ele) {
    if (isFull(s)) {
        addLenth(s, 5);
        return false;
    }
    s.data[++s.top] = ele;
    return true;
}

bool popBack(SeqStack& s) {
    if (isEmpty(s))  return false;
    --s.top;
    return true;
}

bool getTop(SeqStack& s, int& ele) {
    if (isEmpty(s))  return false;
    ele = s.data[s.top];
    return true;
}

void print(SeqStack& s) {
    int ele;
    while (!isEmpty(s)) {
        getTop(s, ele);
        cout << ele << " ";
        popBack(s);
    }
    if (isEmpty(s))  cout << endl;
}

void deleteSeqStack(SeqStack& s) {
    free(s.data);
    s.top = -1;
}

int main() {
    SeqStack s;
    bool isInit = init(s, 10);
    if (!isInit)  return 0;

    for (int i = 0; i < 40; i++)  if (!pushBack(s, i))  --i;
    for (int i = 0; i < 20; i++)  popBack(s);
    for (int i = 40; i < 45; i++)  if (!pushBack(s, i))  --i;
    cout << "now member length：" << getLenth(s) << endl;
    cout << "SeqStack length：" << s.maxSize << endl;

    print(s);
    deleteSeqStack(s);

    return 0;
}
```

（2）链式存储

为了提高性能，采用头插法：

```
// struct 版

#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct LinkStackNode {
    int data;
    struct LinkStackNode *next;
} LinkStackNode, *LinkStack;

bool init(LinkStack &s) {
    s = (LinkStackNode*)malloc(sizeof(LinkStackNode));
    if (!s)  return false;
    s->next = NULL;
    return true;
}

bool isEmpty(LinkStack &s) {
    return s->next == NULL;
}

// 头插法
bool push(LinkStack &s, int ele) {
    LinkStackNode *node = (LinkStackNode*)malloc(sizeof(LinkStackNode));
    if (!node)  return false;

    node->data = ele;
    node->next = s->next;
    s->next = node;

    return true;
}

bool pop(LinkStack &s) {
    if (isEmpty(s))  return false;

    LinkStackNode *node = s->next;
    s->next = node->next;
    free(node);

    return true;
}

bool getTop(LinkStack &s, int &ele) {
    if (isEmpty(s))  return false;
    ele = s->next->data;
    return true;
}

void print(LinkStack &s) {
    int ele;
    while (!isEmpty(s)) {
        getTop(s, ele);
        cout << ele << " ";
        pop(s);
    }
    if (isEmpty(s))  cout << endl;
}

void deleteLinkStack(LinkStack &s) {
    while (!isEmpty(s)) {
        pop(s);
    }
    free(s);
}

int main() {
    LinkStack s;
    if (!init(s))  return 0;

    for (int i = 0; i < 10; i++)  push(s, i);
    print(s);
    deleteLinkStack(s);

    return 0;
}
```

（3）共享栈

顺序存储的站，如果给的空间太多，就容易造成浪费，共享栈有两个指针，一个向栈顶移动，一个向战战底移动，当两个指针相遇时，栈就满了，充分利用了空间：

```
typedef ShareStack{
    int* data = NULL;
    int top1 = 0, top2 = 0, maxSize = 0;
}
```

（4）栈的应用——括号匹配

```
#include<iostream>
#include<string>
#include<stack>
#include<map>
using namespace std;

map<char, char> bracket({
    pair<char, char>(')', '('),
    pair<char, char>(']', '['),
    pair<char, char>('}', '{'),
});

map<char, int> level({
    pair<char, int>('(', 1),
    pair<char, int>('[', 2),
    pair<char, int>('{', 3),
});

bool func(const string &str) {
    stack<char> s;

    for (int i = 0; i < str.length(); i++) {
        switch (str[i]) {
        case '(':
        case '[':
        case '{':
            if (!s.empty()) {
                if (level[str[i]] > level[s.top()])  return false;
                else  s.push(str[i]);
            }
            else s.push(str[i]);
            break;
        case ')':
        case ']':
        case '}':
            if (s.empty())  return false;
            else if (s.top() != bracket[str[i]]) return false;
            else s.pop();
            break;
        default:
            return false;
        }
    }

    if (!s.empty())  return false;
    return true;
}

int main() {
    string arr[9] = { "", "9", "(", ")", "(())", "[()]", "{[()]}", "(]","([])" };
    for (int i = 0; i < 9; i++)  cout << arr[i] + "：" << func(arr[i]) << endl;
    return 0;
}
```

（4）栈的应用——表达式求值

中缀、后缀、前缀表达式：

* 中缀：2\*\(3\+4\)

* 后缀：2 3 4 \+ \*

* 前缀：\* 2 \+ 3 4

后缀、前缀表达式本身就描述了各个操作数的运算顺序，可以很方便的用代码实现，通常后缀表达式用的多。

由于中缀表达式的有结合律和交换律，生成的后缀、前缀表达式可能不唯一，所以中缀转换成后缀/前缀的原则是：操作数按顺序/逆序，运算符左/右优先，优先指的是相同优先级的子表达式优先计算左边/右边的。

中缀转后缀、后缀表达式求值：

```
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<map>
using namespace std;

map<char, int> level({
    pair<char, int>('(', 0),
    pair<char, int>(')', 0),
    pair<char, int>('+', 1),
    pair<char, int>('-', 1),
    pair<char, int>('*', 2),
    pair<char, int>('/', 2),
    pair<char, int>('~', 3),  // 负号
});

// 遇到 ')' 的出栈函数
void popTag(stack<char> &s, char nowChar, string &suffix) {
    while (!s.empty() && level[s.top()] >= level[nowChar]) {
        suffix = suffix + " " + s.top();
        s.pop();
    }
    s.push(nowChar);
    suffix += " ";
}

/* 中缀转后缀
 * 基础规则
   * 操作数，直接写入后缀表达式
   * '(' 直接入栈
   * 遇到 ')' 就依次出栈并写入后缀表达式，直到把 '(' 出栈
   * 遇到运算符，依次出栈并写入后缀表达式，直到遇到栈顶运算符优先级小于该运算符为止，并将此运算符入栈
   * 遍历结束，依次将栈中剩余运算符全部出栈，并写入后缀表达式
 * 优化 
   * 正负号用在括号里面；负数用一个特殊符号表示，这里用 ~；正号忽略
   * 空格隔开操作数和运算符，以区分多位整数
   * 小数点，前面只能是操作数，且不能在第一个和最后一个；用一个 flag 控制一个操作数只能有一个 '.'
   * 3(2+3) , (2+3)(4+5) ，这种可以加一个 * 号
 * 原中缀表达式的合法格式
   * ')' 如果没有匹配的 '(' ，非法格式 
   * 最后一个必须是操作数或 ')'
   * 算术运算符（正负号除外）和 ')' 左边只能是 ')' 或 操作数，且不能是第一个元素
 */  
bool toSuffix(const string &str, string &result) {
    string suffix = "";
    stack<char> s;
    // 小数点判断
    bool dotFlag = true;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9')  suffix += str[i];
        else if (str[i] == '.' && i != 0 && i != str.length() - 1) {
            if (dotFlag && str[i - 1] > '0' && str[i - 1] < '9') {
                suffix += str[i];
                dotFlag = false;
            }
            else  return false;
        }
        else if (str[i] == '(' && i != str.length() - 1) {
            if (i != 0 && (str[i - 1] >= '0' && str[i - 1] <= '9' || str[i - 1] == ')')) {
                popTag(s, '*', suffix);
            }
            dotFlag = true;
            s.push(str[i]);
        }
        else if (str[i] == ')' && i != 0) {
            dotFlag = true;
            if (str[i - 1] != ')' && (str[i - 1] < '0' || str[i - 1] > '9'))  return false;
            while (!s.empty() && s.top() != '(') {
                suffix = suffix + " " + s.top();
                s.pop();
            }
            if (s.empty())  return false;
            s.pop();
        }
        else if (level.find(str[i]) != level.end() && str[i] != '~' && i != str.length() - 1) {
            dotFlag = true;
            // 正负号
            if (i == 0 && str[i] == '-' || i != 0 && str[i] == '-' && str[i - 1] == '(')  s.push('~');
            else if (i == 0 && str[i] == '+' || i != 0 && str[i] == '+' && str[i - 1] == '(')  continue;
            // + - * /
            else if (i == 0 || i != 0 && str[i - 1] != ')' && (str[i - 1] < '0' || str[i - 1] > '9'))  return false;
            else  popTag(s, str[i], suffix);
        }
        else return false;
    }

    while (!s.empty()) {
        if (s.top() == '(')  return false;
        suffix = suffix + " " + s.top();
        s.pop();

    }

    result = suffix + " ";

    return true;
}

// 后缀表达式求值，非法格式已经在中缀转后缀中检查，所以这里不需要考虑非法格式问题
double suffixComputed(string &suffix) {
    bool isDot = false;
    stack<double> numStack;
    stack<int> intStack;
    queue<int> floatQueue;

    for (string::iterator i = suffix.begin(); i != suffix.end(); i++) {
        if (*i >= '0' && *i <= '9') {
            int num = int(*i) - 48;
            if (!isDot)  intStack.push(num);
            else  floatQueue.push(num);
        }
        else if (*i == '.')  isDot = true;
        else if (*i == ' ') {
            isDot = false;
            if (intStack.empty())  continue;

            double sum = 0.0;

            double n = 1;
            while (!intStack.empty()) {
                sum += intStack.top() * n;
                n *= 10;
                intStack.pop();
            }

            n = 0.1;
            while (!floatQueue.empty()) {
                sum += floatQueue.front() * n;
                n *= 0.1;
                floatQueue.pop();
            }

            numStack.push(sum);
        }
        else if (*i == '~') {
            double num = -numStack.top();
            numStack.pop();
            numStack.push(num);
        }
        else {
            double num1 = numStack.top();
            numStack.pop();
            double num2 = numStack.top();
            numStack.pop();

            switch (*i) {
            case '+':
                numStack.push(num2 + num1);
                break;
            case '-':
                numStack.push(num2 - num1);
                break;
            case '*':
                numStack.push(num2 * num1);
                break;
            case '/':
                numStack.push(num2 / num1);
                break;
            default:
                break;
            }
        }
    }

    return numStack.top();
}

int main() {
    vector<string> middle({
        // 基础测试
        "1+2*3",
        "1+2-3",
        "1+2*3-4+5*6",
        "1*(2+3)-((4-5)/6)+7",
        "2+(3-4)*5",

        // 多位整数和小数测试
        "123+456",
        "10+(24*2)",
        "3.14*(2+6.5)",
        "3.14*(2+6.5)",
        "3..14*2",
        "3.1.4*2",
        ".3*2",
        "3*.2",
        "3.*2",
        "3*2.",
        "3*(.3)",
        "3+(2*3.)",
        "3.14*(2*3)",
        "3.14+3(2.5)",
        "3.14(5.6)",

        // 正负号测试
        "+1",
        "-2",
        "4*(-2-3)",
        "4*(+2+3)",
        "1+~2",
        "1+-2",
        "-2+3",
        "3.14",
        "-3.14",
        "+3.14",
        "-3.14+5.6",

        // 错误格式测试
        "1++2",
        "1 +2",
        "1+2+",
        "+",
        "+2+3",
        "2+3-"

        // 特殊情况下的括号测试
        "1+(",
        "2+()",
        "3+(4",
        "5+(6)",
        "5+)",
        "5+(+)",
        "5+(1++2)",
        "5+(++)",
        "(",
        ")",
        "()",
        "(1+2)",
        "1+(2+3)(4+5)",
        "2+(-3)(4+5)"
    });

    vector<string> suffix;

    for (vector<string>::iterator i = middle.begin(); i != middle.end(); i++) {
        string result = "";
        bool tag = toSuffix(*i, result);
        if (tag)  suffix.push_back(result);
        cout << "中缀: " + *i + "\t\t" << (tag ? "后缀: " + result : "非法格式") << endl;
    }

    cout << endl << endl << endl << endl << endl;

    for (vector<string>::iterator i = suffix.begin(); i != suffix.end(); i++) {
        cout << *i << "\t结果为: " << suffixComputed(*i) << endl;
    }

    return 0;
}
```

中缀转后传的过程中就求值，效率更高：

```
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<map>
using namespace std;

map<char, int> level({
    pair<char, int>('(', 0),
    pair<char, int>(')', 0),
    pair<char, int>('+', 1),
    pair<char, int>('-', 1),
    pair<char, int>('*', 2),
    pair<char, int>('/', 2),
    pair<char, int>('~', 3),  // 负号
});

void tagComputed(stack<char> &tagStack, stack<double> &numStack, char tag) {
    if (tag == '~') {
        double num = -numStack.top();
        numStack.pop();
        numStack.push(num);
    }
    else {
        double num1 = numStack.top();
        numStack.pop();
        double num2 = numStack.top();
        numStack.pop();

        switch (tag) {
        case '+':
            numStack.push(num2 + num1);
            break;
        case '-':
            numStack.push(num2 - num1);
            break;
        case '*':
            numStack.push(num2 * num1);
            break;
        case '/':
            numStack.push(num2 / num1);
            break;
        default:
            break;
        }
    }

    tagStack.pop();
}

double strToNum(stack<int> &intStack, queue<int> &floatQueue) {
    double sum = 0.0;

    double n = 1;
    while (!intStack.empty()) {
        sum += intStack.top() * n;
        n *= 10;
        intStack.pop();
    }

    n = 0.1;
    while (!floatQueue.empty()) {
        sum += floatQueue.front() * n;
        n *= 0.1;
        floatQueue.pop();
    }

    return sum;
}

bool computed(string &mid, double &result) {
    // 运算符栈
    stack<char> tagStack;
    // 操作数栈
    stack<double> numStack;
    // 整数栈
    stack<int> intStack;
    // 小数队列
    queue<int> floatQueue;

    // 小数点判断
    bool isDot = false;


    for (string::iterator i = mid.begin(); i != mid.end(); i++) {
        if (*i >= '0' && *i <= '9') {
            int num = int(*i) - 48;
            if (!isDot)  intStack.push(num);
            else  floatQueue.push(num);
        }
        else if (*i == '.' && i != mid.begin() && i != mid.end() - 1) {
            if (!isDot && *(i - 1) > '0' && *(i - 1) < '9')  isDot = true;
            else  return false;
        }
        // ( ) + - * / ~
        else if (level.find(*i) != level.end()) {
            isDot = false;

            if (!intStack.empty())  numStack.push(strToNum(intStack, floatQueue));

            if (*i == '(' && i != mid.end() - 1) {
                if (i != mid.begin() && (*(i - 1) >= '0' && *(i - 1) <= '9' || *(i - 1) == ')')) {
                    while (!tagStack.empty() && level[tagStack.top()] >= level['*']) {
                        tagComputed(tagStack, numStack, tagStack.top());
                    }
                    tagStack.push('*');
                }
                tagStack.push(*i);
            }
            else if (*i == ')' && i != mid.begin()) {
                if (*(i - 1) != ')' && (*(i - 1) < '0' || *(i - 1) > '9'))  return false;
                while (!tagStack.empty() && tagStack.top() != '(') {
                    tagComputed(tagStack, numStack, tagStack.top());
                }
                if (tagStack.empty())  return false;
                tagStack.pop();
            }
            else if (*i != '~' && i != mid.end() - 1) {
                // 正负号
                if (i == mid.begin() && *i == '-' || i != mid.begin() && *i == '-' && *(i - 1) == '(')  tagStack.push('~');
                else if (i == mid.begin() && *i == '+' || i != mid.begin() && *i == '+' && *(i - 1) == '(')  continue;
                // + - * /
                else if (i == mid.begin() || i != mid.begin() && *(i - 1) != ')' && (*(i - 1) < '0' || *(i - 1) > '9'))  return false;
                else {
                    while (!tagStack.empty() && level[tagStack.top()] >= level[*i]) {
                        tagComputed(tagStack, numStack, tagStack.top());
                    }
                    tagStack.push(*i);

                }
            }
            else  return false;
        }
        else return false;
    }

    if (!intStack.empty())  numStack.push(strToNum(intStack, floatQueue));

    while (!tagStack.empty()) {
        if (tagStack.top() == '(')  return false;
        tagComputed(tagStack, numStack, tagStack.top());
    }

    result = numStack.top();

    return true;
}

int main() {
    vector<string> middle({
        // 基础测试
        "1+2*3",
        "1+2-3",
        "1+2*3-4+5*6",
        "1*(2+3)-((4-5)/6)+7",
        "2+(3-4)*5",

        // 多位整数和小数测试
        "123+456",
        "10+(24*2)",
        "3.14*(2+6.5)",
        "3.14*(2+6.5)",
        "3..14*2",
        "3.1.4*2",
        ".3*2",
        "3*.2",
        "3.*2",
        "3*2.",
        "3*(.3)",
        "3+(2*3.)",
        "3.14*(2*3)",
        "3.14+3(2.5)",
        "3.14(5.6)",

        // 正负号测试
        "+1",
        "-2",
        "4*(-2-3)",
        "4*(+2+3)",
        "1+~2",
        "1+-2",
        "-2+3",
        "3.14",
        "-3.14",
        "+3.14",
        "-3.14+5.6",

        // 错误格式测试
        "1++2",
        "1 +2",
        "1+2+",
        "+",
        "+2+3",
        "2+3-"

        // 特殊情况下的括号测试
        "1+(",
        "2+()",
        "3+(4",
        "5+(6)",
        "5+)",
        "5+(+)",
        "5+(1++2)",
        "5+(++)",
        "(",
        ")",
        "()",
        "(1+2)",
        "1+(2+3)(4+5)",
        "2+(-3)(4+5)"
    });

    for (vector<string>::iterator i = middle.begin(); i != middle.end(); i++) {
        double result = 0.0;
        bool isRight = computed(*i, result);
        cout << *i + " = ";
        if (isRight)  cout << result << endl;
        else cout << "非法格式" << endl;
    }

    return 0;
}
```

## 3 队列

只允许一端入队，另一端出队，先进先出。

（1）顺序存储

顺序存储有个缺点，出队后 front 往后移，前面的空间就无法利用了，所以这里顺序存储的队列用循环队列实现，通过模运算实现 front 、 rear 可以循环从 0 到 maxSize 之间移动。

rear 可以在队尾下一个位置，也可以在队尾，是线上只是一些 +1 -1 的区别，这里采用 rear 在队尾下一个位置的实现方式：

```
// struct 版

#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct SeqQueue {
    int* data;
    int front, rear, maxSize;
} SeqQueue;

bool init(SeqQueue& q, int len) {
    q.data = (int*)malloc(sizeof(int) * len);
    if (!q.data)  return false;
    q.maxSize = len;
    q.front = 0;
    q.rear = 0;
    return true;
}

int getLenth(SeqQueue& q) {
    return (q.rear - q.front + q.maxSize) % q.maxSize;
}

bool addLenth(SeqQueue& q, int len) {
    int* newData = (int*)malloc(sizeof(int) * (len + q.maxSize));
    if (!q.data)  return false;
    for (int i = q.front, j = 0; j < getLenth(q); i = (i + 1) % q.maxSize, j++)  newData[j] = q.data[i];

    free(q.data);
    q.data = newData;
    q.rear = getLenth(q);
    q.front = 0;
    q.maxSize += len;
    return true;
}

bool isEmpty(SeqQueue& q) {
    return q.front == q.rear;
}

bool isFull(SeqQueue& q) {
    /* 关于判断队列已满
     * 循环队列，由于 front == rear 已经作为判空，所以这里判断 rear 在 front 前一个位置就是已满，需要浪费一个空间
     * 如果依旧想使用 front == rear 判断，可以在结构体中定义一个 tag ，当插入时 = 1 ，删除就 = 0 ，由于队列满/空只会是插入/删除造成的，因此配合就可以判断
     * 或者直接结构体中加一个 size ，记录当前队列的元素个数
     */
    return q.front % q.maxSize == (q.rear + 1) % q.maxSize;
    // return q.front == q.rear;
    // return q.maxSize == q.maxSize;
}

bool pushBack(SeqQueue& q, int ele) {
    if (isFull(q)) {
        addLenth(q, 5);
        return false;
    }
    q.data[q.rear] = ele;
    q.rear = (q.rear + 1) % q.maxSize;
    return true;
}

bool popFront(SeqQueue& q) {
    if (isEmpty(q))  return false;
    q.front = (q.front + 1) % q.maxSize;
    return true;
}

bool getFront(SeqQueue& q, int& ele) {
    if (isEmpty(q))  return false;
    ele = q.data[q.front];
    return true;
}

void print(SeqQueue& q) {
    int ele;
    while (!isEmpty(q)) {
        getFront(q, ele);
        cout << ele << " ";
        popFront(q);
    }
    if (isEmpty(q))  cout << endl;
}

void deleteSeqQueue(SeqQueue& q) {
    free(q.data);
    q.front = 0;
    q.rear = 0;
    q.maxSize = 0;
}

int main() {
    SeqQueue q;
    bool isInit = init(q, 10);
    if (!isInit)  return 0;

    for (int i = 0; i < 40; i++)  if (!pushBack(q, i))  --i;
    for (int i = 0; i < 20; i++)  popFront(q);
    for (int i = 40; i < 45; i++)  if (!pushBack(q, i))  --i;
    cout << "now member length：" << getLenth(q) << endl;
    cout << "SeqQueue length：" << q.maxSize << endl;

    print(q);
    deleteSeqQueue(q);

    return 0;
}
```

（2）链式存储

这里采用带头结点的实现方式：

```
// struct 版

#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct LinkQueueNode {
    int data;
    struct LinkQueueNode *next;
} LinkQueueNode;

typedef struct LinkQueue {
    LinkQueueNode *front, *rear;
    int length;
};

bool init(LinkQueue &q) {
    q.front = q.rear = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
    if (!q.front)  return false;
    q.front->next = NULL;
    q.length = 0;
    return true;
}

int getLenth(LinkQueue &q) {
    return q.length;
}

bool isEmpty(LinkQueue &q) {
    return q.front->next == NULL;
}

bool pushBack(LinkQueue &q, int ele) {
    LinkQueueNode *node = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
    if (!node)  return false;
    node->data = ele;
    node->next = NULL;
    q.rear->next = node;
    q.rear = node;
    ++q.length;
    return true;
}

bool popFront(LinkQueue &q) {
    if (isEmpty(q))  return false;
    LinkQueueNode *node = q.front->next;
    q.front->next = node->next;
    free(node);
    --q.length;
    if (isEmpty(q))  q.rear = q.front;
    return true;
}

bool getFront(LinkQueue &q, int &ele) {
    if (isEmpty(q))  return false;
    ele = q.front->next->data;
    return true;
}

void print(LinkQueue& q) {
    int ele;
    while (!isEmpty(q)) {
        getFront(q, ele);
        cout << ele << " ";
        popFront(q);
    }
    if (isEmpty(q)) {
        free(q.front);
        q.front = q.rear = NULL;
        cout << endl;
    }
}

int main() {
    LinkQueue q;
    bool isInit = init(q);
    if (!isInit)  return 0;

    for (int i = 0; i < 10; i++) pushBack(q, i);
    for (int i = 0; i < 5; i++) popFront(q);
    for (int i = 10; i < 20; i++) pushBack(q, i);
    print(q);

    return 0;
}
```

（3）双端队列

有 5 种：

* 允许两端都可以插入、删除

* 输入受限，允许两端出队，一端出队

* 输出受限，允许两端入队，一端出队

* 输入输出首受限，只允许一端入队，另一端出队，即普通队列

* 输入输出都受限，只允许在同一个端入队出队，即变成了栈

可以通过卡特兰数公式计算双端队列的合法输出序列。

## 4 串

即字符串：

* 主串：整个字符串

* 空串：没有一个字符的串

* 子串：主串的子集，空串也是一个子串

通常用顺序存储，如果用链式存储，字符占 1 个字节，next 占 4 或 8 个字节，存储密度就很低，解决方法是一个 node 存储多个字符的子串。

（1）KMP 算法

用于匹配字符串，判断模式串是否是主串的子串：

* 普通的暴力匹配，每次匹配失败都要把主串指针和模式串指针修改为 0 ，效率很低，事件复杂度 O\(m + n\)

* KMP 算法的原则是匹配失败时，主串指针不动，只改变模式串的指针

KMP 算法的原理：匹配失败的位置记为 i ，找到 0 \~ i - 1 之间这个子串的最大公共前缀，公共最大前缀的长度记为 n ，下次直接从模式串的 n 位开始匹配，跳过了中间不可能匹配成功的字符，如：

* "abdabc" 在 'c' 处匹配失败时，最大公共前缀是 "ab" ，响应的后缀也是 "ab" ，下次只需要把前缀移动到后缀的位置即可，n = 2 即 'd' 移动到原来 'c' 的位置

* "aaaac" 在 'c' 处的最大公共前缀是 "aaa" 而不是 "aaaa"

* "ababc" 在第一个 'a' 匹配失败时，n = \-1 ，需要特殊处理，把主串指针都 \+1 ，模式串指针改为 0 

有每个位置的 n 可以得到一个 next 数组，每次陪陪失败只需要找到 next 数组中对于的 n 即可：

* 当从 next 数组中找到 n 并移动后，如果和原来匹配失败的字符相同，则必定是匹配失败的，如 "ababc" ，在第二个 'b' 匹配失败时，n = 1 ，移动后还是 'b' ，再根据第一个 'b' 的 n = 0 移动。因此可以直接把第二个 'b' 的 n 改成和第一个 'b' 的 n 相同，这种优化得到的数组叫 nextval 数组

* 当下标从 0 开始时 ， next 和 nextval 的 next\[0\] = -1 ，next\[1\] = 0；如果是下标从 1 开始，next\[0\] 被浪费，next\[1\] = 0 ，next\[2\] = 1 

以模式串和 next 下标都从 0 开始为例：

```
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// next 数组
bool getNext(const string& T, int *&next) {
    if (T.length() == 0)  return false;
    next = (int*)malloc(sizeof(int) * T.length());
    if (!next)  return false;
    next[0] = -1;

    int i = 0, maxPublicLen = -1;

    // 边遍历边计算最大公共前缀成都 maxPublicLen
    while (i < T.length()) {
        if (maxPublicLen == -1 || T[i] == T[maxPublicLen]) {
            next[++i] = ++maxPublicLen;

            // 这一行代码效果是优化成 nextval 数组
            if(T[i] == T[next[i]])  next[i] = next[next[i]];
        }
        else maxPublicLen = next[maxPublicLen];
    }

    return true;
}

// 找到返回下标，找不到返回 -1
int KMP(const string &str, const string &T) {
    if (T.length() > str.length())  return -1;

    int *next = NULL;
    if (!getNext(T, next))  return -1;

    int i = 0, j = 0;
    while (i < str.length() && j < T.length() && str.length() - i >= T.length() - j) {        
        if (str[i] == T[j]) {
            ++i;
            ++j;
        }
        else {
            j = next[j];

            if (j == -1) {
                ++i;
                j = 0;
            }
        }
    }

    if (j == T.length())  return i - T.length();
    else return -1;
}

int main() {
    int* next = NULL;
    string T = "ababc";
    getNext(T, next);
    for (int i = 0; i < T.length(); i++)  cout << " " << T[i];
    cout << endl;
    for (int i = 0; i < T.length(); i++)  cout << next[i] << " ";

    vector<string> str({
        "ababc",
        "cababc",
        "acaababcasdas",
        "ab",
        "aaaaababc",
        "qwerababczxcv",
        "aaababbb",
        "ababababc"
    });;

    cout << endl << "模式串: " + T << endl;
    for (vector<string>::iterator i = str.begin(); i != str.end(); i++) {
        cout << "珠串: " + *i << "，结果: " << KMP(*i, T) << endl;
    }

    return 0;
}
```

## 5 矩阵

矩阵是二维数组，但有自己的规定：

* 下标可以从 0 开始也可以从 1 开始，矩阵默认是 1 开始

* 可分为行优先存储和列优先存储

特殊矩阵：有一定的规律，可以压缩存储在一维数组中，节省大量空间。

（1）对称矩阵

n \* n 的方针：

* a[i][j] == a[j][i]

* 以左上角和右下角为主对角巷，i == j

* 左下区域为下三角（i > j），右上区域为上三角（i < j）

可以压缩存储在一维数组，节省空间，这里以行优先、存储下三角和主对角线，下标从 0 开始为例：

```
#include<iostream>
using namespace std;

bool compressSynMatrix(const int x[][5], const int row, int*& resArr, int& resLen) {
    if (resArr != NULL)  return false;

    // 等差数列前 n 项和
    resLen = row * (1 + row) / 2.0;

    resArr = (int*)malloc(sizeof(int) * resLen);
    if (resArr == NULL)  return false;

    int index = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < i + 1; j++) {
            if (x[i][j] != x[j][i])  return false;
            resArr[index++] = x[i][j];
        }
    }

    return true;
}

// 找到压缩后的下表
int readArr(int i, int j) {
    // 等差数列前 n 项和
    if (i >= j)  return i * (1 + i) / 2.0 + j;
    else return j * (1 + j) / 2.0 + i;
}

int main() {
    int matrix[5][5] = {
        {1,2,3,4,5},
        {2,1,6,7,4},
        {3,6,1,8,3},
        {4,7,8,1,2},
        {5,4,3,2,1},
    };

    int *arr = NULL, len = 0;

    if (compressSynMatrix(matrix, 5, arr, len)) {
        for (int i = 0; i < len; i++)  cout << arr[i] << " ";
        cout << endl;
        cout << "matrix[0][4] = " << arr[readArr(0, 4)] << endl;
        free(arr);
    }

    return 0;
}
```

（2）三角矩阵

m \* n 的矩阵：

* 若是上三角矩阵，那么上三角区是任意值，下三角都是常量 c 

* 若是下三角矩阵，那么下三角区是任意值，上三角都是常量 c

基本和对称矩阵的压缩存储差不多，只不过要多存一个常量 c 。

（3）三对角矩阵

又叫带状矩阵，像从主对角线向左右扩散 1 个位置的带状区域。

* i - j 的绝对值 > 1 的空间存放 0 ，<= 1 的空间存放任意值

* 首行和最后一行只有 2 个元素，其他行有 3 个元素

（4）稀疏矩阵

非 0 元素远远小于 0 值元素的矩阵，有两种压缩存储的方式：

* struct 定义三元组，存储行、列和值，再用顺序存储三元组

* 十字链表

# 二、树

由唯一的且无前驱的根结点、有后继的分支结点和无后继的叶子结点购成。

* 总结点数 = 总分支数 + 1 = 所有结点的度数之和 \+ 1 

一个结点分出去的分支数称为度。

* 度为 n 的树：度最大为 n ，且至少有一个结点度为 n 

* n 叉树：度最大为 n ，但不一定要有度为 n 的结点，即可以是空树

## 1 二叉树

### 1.1 特性和存储结构

（1）基本概念

除叶子结点外，每个结点都有两个分支的树就是二叉树，即度 \<= 2 。

* 叶子结点数 = 度为 2 结点数 \+ 1 

* 空分支数 = 总结点数 \+ 1

层数即高度为 h 的二叉树，设 h 从 1 开始：

* 完全二叉树：叶子结点只在第 h 层和第 h - 1 层，且第 h 层的叶子结点全部在左边

* 满二叉树：叶子结点只在第 h 层，总结点数 = 2 ^ n - 1 ，第 h 层结点数 = 2 ^ (n - 1)

* 完全二叉树、满二叉树的 h = log2 (x)向下取整 \+ 1 = log2 (x \+ 1)向下取整 ，x 为总结点数

（2）存储结构

顺序结构，适用于完全二叉树，如果是非完全二叉树，需要一个 isEmpty 判断该结点是否是空节点，浪费了大量空间：

```
// struct 版

#include<iostream>
using namespace std;

typedef struct TreeNode {
    int data;
    bool isEmpty = true;
} TreeNode;

typedef struct SeqBinTree {
    TreeNode *data;
    int maxSize;
    int size;
} SeqBinTree;

bool init(SeqBinTree &t, int size) {
    t.data = (TreeNode*)malloc(sizeof(TreeNode) * size);
    if (!t.data)  return false;
    t.maxSize = size;
    t.size = 0;
    return true;
}

bool isTreeNode(SeqBinTree &t, int nodeIndex) {
    return nodeIndex >= 0 && nodeIndex < t.size;
}

bool hasLeftChild(SeqBinTree &t, int nodeIndex) {
    if (!isTreeNode(t, nodeIndex))  return false;
    return nodeIndex * 2 + 1 <= t.size && !t.data[nodeIndex * 2 + 1].isEmpty;
}

bool hasRightChild(SeqBinTree &t, int nodeIndex) {
    if (!isTreeNode(t, nodeIndex))  return false;
    return nodeIndex * 2 + 2 <= t.size && !t.data[nodeIndex * 2 + 2].isEmpty;
}

bool getLeftChild(SeqBinTree &t, int nodeIndex, int &res) {
    if (!hasLeftChild(t, nodeIndex))  return false;
    res = t.data[nodeIndex * 2 + 1].data;
    return true;
}

bool getRightChild(SeqBinTree& t, int nodeIndex, int &res) {
    if (!hasRightChild(t, nodeIndex))  return false;
    res = t.data[nodeIndex * 2 + 2].data;
    return true;
}

bool getFather(SeqBinTree &t, int nodeIndex, int &res) {
    if (!isTreeNode(t, nodeIndex))  return false;
    res = (nodeIndex + 1) / 2 - 1;
    return true;
}

int main() {
    SeqBinTree t;
    if (!init(t, 7))  return 0;

    for (int i = 0; i < 7; i++) {
        t.data[i].data = i;
        t.data[i].isEmpty = false;
        ++t.size;
    }

    int l = -1, r = -1;
    getLeftChild(t, 2, l);
    getRightChild(t, 2, r);
    cout << l << " " << r << endl;

    int f1 = -1, f2 = -1;
    getFather(t, 5, f1);
    getFather(t, 6, f2);
    cout << f1 << " " << f2 << endl;

    return 0;
}
```

l链式存储，也叫二叉链表：

```
// struct 版

#include<iostream>
using namespace std;

typedef struct BinTreeNode {
    int data;
    struct BinTreeNode *left, *right;

    // 也可以加一个指向父结点的指针域，形成三叉链表
    // struct BinTreeNode *father;
} BinTreeNode, *BinTree;

// 插入成二叉排序树，不带头结点
BinTreeNode* insertBST(BinTree t, int data) {
    if (t == NULL) {
        BinTreeNode *node = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    if (data < t->data)  t->left = insertBST(t->left, data);
    else if (data > t->data)  t->right = insertBST(t->right, data);
    else return t;

    return t;
}

// 获取高度
int getTreeHeight(BinTree t) {
    if (t == NULL)  return 0;

    int left = getTreeHeight(t->left) + 1;
    int right = getTreeHeight(t->right) + 1;

    return left > right ? left : right;
}
```

### 1.2 遍历

（1）遍历方式

中序遍历、先序遍历、后序遍历、层序遍历：

```
// struct 版

#include<iostream>
#include<queue>
using namespace std;

typedef struct BinTreeNode {
    int data;
    struct BinTreeNode *left, *right;
} BinTreeNode, *BinTree;

// 中序遍历，左 - 中 - 右
void midVisit(BinTree t) {
    if (t == NULL) return;

    midVisit(t->left);
    cout << t->data << " ";
    midVisit(t->right);
}

// 前序遍历，中 - 左 - 右
void frontVisit(BinTree t) {
    if (t == NULL) return;

    cout << t->data << " ";
    frontVisit(t->left);
    frontVisit(t->right);
}

// 后序遍历，左 - 右 - 中
void behindVisit(BinTree t) {
    if (t == NULL) return;

    behindVisit(t->left);
    behindVisit(t->right);
    cout << t->data << " ";
}

// 层序遍历，借助队列实现
void treeBFS(BinTree t) {
    if (t == NULL)  return;

    queue<BinTreeNode*> q;
    q.push(t);

    while (!q.empty()) {
        cout << q.front()->data << " ";
        if (q.front()->left)  q.push(q.front()->left);
        if (q.front()->right)  q.push(q.front()->right);
        q.pop();
    }
}

int main() {
    return 0;
}
```

也可以用栈实现先/中/后序的非递归遍历：

```
// 前序遍历
void frontIterator(BinTree t) {
    if (t == NULL)  return;

    stack<BinTreeNode*> s;
    s.push(t);

    while (!s.empty()) {
        BinTreeNode* node = s.top();
        s.pop();
        cout << node->data << " ";
        if (node->right)  s.push(node->right);
        if (node->left)  s.push(node->left);
    }
}

// 中序遍历
void midIterator(BinTree t) {
    if (t == NULL)  return;

    stack<BinTreeNode*> s;
    BinTreeNode *node = t;

    while (node || !s.empty()) {
        while (node) {
            s.push(node);
            node = node->left;
        }
        node = s.top();
        s.pop();
        cout << node->data << " ";
        node = node->right;
    }
}

// 后序遍历
void behindIterator(BinTree t) {
    if (t == NULL)  return;

    stack<BinTreeNode*> s;
    BinTreeNode *node = t, *last = NULL;

    while (node || !s.empty()) {
        while (node) {
            s.push(node);
            node = node->left;
        }

        node = s.top();

        if (!node->right || node->right == last) {
            cout << node->data << " ";
            s.pop();
            last = node;
            node = NULL;
        }
        else  node = node->right;
    }
}
```

（2）根据遍历序列构建二叉树

需要中学薛烈 \+ 先/后/层序序列：

```
// struct 版

#include<iostream>
#include<queue>
#include<stack>
#include<map>
#include<vector>
using namespace std;

typedef struct BinTreeNode {
    int data;
    struct BinTreeNode *left, *right;
} BinTreeNode, *BinTree;

// 中序 + 先/后序
BinTree frontOrBehind(
    const vector<int>& list,
    int listStart,
    int listEnd,
    const vector<int>& mid,
    int midStart,
    int midEnd,
    map<int, int>& midMap, 
    bool type = false
) {
    if (listStart > listEnd || midStart > midEnd)  return NULL;

    // 找到根结点在中序的位置，并计算左子树的结点数
    int rootData = list[!type ? listStart : listEnd];
    int rootMidIndex = midMap[rootData];
    int leftSubTreeSize = rootMidIndex - midStart;

    BinTreeNode* node = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    if (!node)  return NULL;

    node->data = rootData;

    node->left = frontOrBehind(
        list, 
        !type ? listStart + 1 : listStart, 
        !type ? listStart + leftSubTreeSize : listStart + leftSubTreeSize - 1,
        mid, 
        midStart, 
        rootMidIndex - 1,
        midMap, 
        type
    );

    node->right = frontOrBehind(
        list, 
        !type ? listStart + leftSubTreeSize + 1 : listStart + leftSubTreeSize,
        !type ? listEnd : listEnd - 1,
        mid, rootMidIndex + 1, 
        midEnd,
        midMap, 
        type
    );

    return node;
}

// 中序 + 层序
BinTree level(const vector<int> &list, map<int, int> &midMap) {
    typedef struct TempBinTreeNode {
        BinTreeNode *node;
        int midStart, midEnd;
        bool hasLeft = false, hasRight = false;
    } TempBinTreeNode;

    BinTree tree = NULL;
    queue<TempBinTreeNode*> q;

    for (int i = 0; i < list.size(); i++) {
        BinTreeNode *node = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        node->data = list[i];
        node->left = NULL;
        node->right = NULL;

        int midStart, midEnd;
        int rootMidIndex = midMap[list[i]];

        if (i == 0) {
            tree = node;
            midStart = 0;
            midEnd = midMap.size() - 1;
        }
        else if (!q.empty()) {
            TempBinTreeNode *p = q.front();

            if (p->hasLeft) {
                p->node->left = node;
                p->hasLeft = false;

                midStart = p->midStart;
                midEnd = midMap[p->node->data] - 1;
            }
            else if (p->hasRight) {
                p->node->right = node;
                p->hasRight = false;

                midStart = midMap[p->node->data] + 1;
                midEnd = p->midEnd - 1;
            }

            if (!p->hasLeft && !p->hasRight) {
                q.pop();
                free(p);
            }
        }


        bool hasLeft = rootMidIndex - midStart != 0;
        bool hasRight = midEnd - rootMidIndex != 0;

        if (hasLeft || hasRight) {
            TempBinTreeNode *tempNode = (TempBinTreeNode*)malloc(sizeof(TempBinTreeNode));
            tempNode->node = node;
            tempNode->midStart = midStart;
            tempNode->midEnd = midEnd;

            if (hasLeft)  tempNode->hasLeft = true;
            if (hasRight) tempNode->hasRight = true;

            q.push(tempNode);
        }
    }

    return tree;
}

/* 由中序序列和前序序列还原成二叉树
 * 前序 + 中序 ，type = false
   * 前序序列的第一个就是根结点，在中序序列找到这个指，左边是左子树，右边是有子树
   * 根据中序序列的左/右子树结点数，找到前序序列的左/右子树
   * 左/右字数递归调用
 * 后序 + 中序 ，type = true
   * 类似前序，只是后序的最后一个元素是根结点
 * 层序 + 中序，isLevel = true ，借助队列实现
   * 每个结点记录是否有左右孩子和左子树到右子树的范围，并入队；若一个孩子都没有，则不入队
   * 根结点直接入队
   * 其他的结点，判断队头是否有左右孩子，并做对应操作；当左右孩子都已连接上孩子结点后，把队头出队
 */
BinTree buildBinTree(vector<int> &list, vector<int> &mid, bool type, bool isLevel = false) {
    if (list.size() == 0 || mid.size() == 0) return NULL;
    if (list.size() != mid.size())  return NULL;

    // 将中序序列存储在 map 中，提高查找效率 （也限制了序列中不能有相同元素）
    map<int, int> midMap;
    for (int i = 0; i < mid.size(); i++) midMap.insert(pair<int, int>(mid[i], i));

    if (isLevel)  return level(list, midMap);
    else  return frontOrBehind(list, 0, list.size() - 1, mid, 0, mid.size() - 1, midMap, type);
}

int main() {
    return 0;
}
```

（3）算术表达式的语法分析树

每个结点存储操作数和运算符，遍历：

* 中序遍历：得到中缀表达式，需要在合适的地方加上括号

* 先序遍历：得到前缀表达式

* 后序遍历：得到后缀表达式

### 1.3 线索二叉树

二叉树的空指针可以利用起来，左空指针指向前驱，有空指针指向后继，二叉树根据先序、中序、后序遍历序列可以分为三种对应的前驱和后继。

线索二叉树中，若左/右指针不空，指向的就是左/右孩子，若为空指针，就是指向前驱和后继承。

```
// struct 版

#include<iostream>
using namespace std;

typedef struct BinTreeNode {
    int data;
    // false 表示没有线索化，指向的是孩子；true 则表示已线索化，指向前驱/后继
    bool ltag, rtag;
    struct BinTreeNode *left, *right, *parent;
} BinTreeNode, *BinTree;

// 线索化 --------------------------------------------------------------------------------
// 线索化
BinTreeNode* toThread(BinTreeNode *node, BinTreeNode *pre) {
    // 设置父指针
    if (node->left)  node->left->parent = node;
    if (node->right)  node->right->parent = node;

    // 前驱
    if (node->left == NULL) {
        node->left = pre;
        node->ltag = true;
    }
    // 后继
    if (pre != NULL && pre->right == NULL) {
        pre->right = node;
        pre->rtag = true;
    }

    return node;
}

// 选择线索化的方式（前序、中序、后序）
void switchThreadType(BinTree t, BinTreeNode* &pre, char type) {
    if (t == NULL)  return;

    switch (type) {
    // 前序
    case 0:
        pre = toThread(t, pre);
        // 前序线索化这里需要特别处理，因为到这里不知道是否已经线索化，需要判断
        if (!t->ltag) switchThreadType(t->left, pre, type);
        switchThreadType(t->right, pre, type);
        break;
    // 中序
    case 1:
        switchThreadType(t->left, pre, type);
        pre = toThread(t, pre);
        switchThreadType(t->right, pre, type);
        break;
    // 后序
    case 2:
        switchThreadType(t->left, pre, type);
        switchThreadType(t->right, pre, type);
        pre = toThread(t, pre);
        break;
    default: 
        break;
    }
}

// 把二叉树转化成线索二叉树
void creatThreadTree(BinTree t, char type) {
    if (t == NULL)  return;
    t->parent = NULL;

    BinTreeNode *pre = NULL;
    switchThreadType(t, pre, type);

    // 处理最后一个结点
    if (type == 0 || type == 1) {
        pre->right = NULL;
        pre->rtag = true;
    }
}

// 遍历线索二叉树 -----------------------------------------------------------------------
void visitThreadTree(BinTree t, char type) {
    if (t == NULL)  return;

    switch (type) {
    // 顺序遍历先序线索二叉树
    case 0:
        // 第一个结点就是根结点
        // 往后遍历
        while (t != NULL) {
            cout << t->data << " ";
            // 后继结点
            if (!t->ltag)  t = t->left;
            else  t = t->right;
        }
        cout << endl;
        break;

    // 逆序遍历先序线索二叉树
    case 1:
        // 最后一个结点
        while (!t->rtag)  t = t->right;
        // 往前遍历
        while (t != NULL) {
            cout << t->data << " ";
            // 前驱结点
            if (t->parent == NULL)  break;
            if (t == t->parent->left)  t = t->parent;
            else if (t == t->parent->right) {
                if (t->parent->ltag)  t = t->parent;
                else {
                    t = t->parent->left;
                    while (!t->ltag || !t->rtag) {
                        if (!t->rtag)  t = t->right;
                        else if (!t->ltag)  t = t->left;
                    }
                }
            }
        }
        cout << endl;
        break;

    // 普通方式，遍历前序线索二叉树
    case 2 :
        cout << t->data << " ";
        if (!t->ltag)  visitThreadTree(t->left, type);
        if (!t->rtag)  visitThreadTree(t->right, type);
        break;

    // 顺序遍历中序线索二叉树
    case 3:
        // 第一个结点
        while (!t->ltag)  t = t->left;
        // 往后遍历
        while (t != NULL) {
            cout << t->data << " ";
            // 后继结点
            if (t->rtag)  t = t->right;
            else {
                t = t->right;
                while (!t->ltag)  t = t->left;
            }
        }
        cout << endl;
        break;

    // 逆序遍历中序线索二叉树
    case 4:
        // 最后一个结点
        while (!t->rtag)  t = t->right;
        // 往前遍历
        while (t != NULL) {
            cout << t->data << " ";
            // 前驱结点
            if (t->ltag)  t = t->left;
            else {
                t = t->left;
                while (!t->rtag)  t = t->right;
            }
        }
        cout << endl;
        break;

    // 普通方式，遍历中序线索二叉树
    case 5:
        if (!t->ltag)  visitThreadTree(t->left, type);
        cout << t->data << " ";
        if (!t->rtag)  visitThreadTree(t->right, type);
        break;

    // 顺序遍历后序线索二叉树
    case 6:
        // 第一个结点
        while (!t->ltag)  t = t->left;
        // 往后遍历
        while (t != NULL) {
            cout << t->data << " ";
            // 后继结点
            if (t->parent == NULL)  break;
            if (t == t->parent->right)  t = t->parent;
            else if (t == t->parent->left) {
                if (t->parent->rtag)  t = t->parent;
                else {
                    t = t->parent->right;
                    while (!t->ltag || !t->rtag) {
                        if (!t->ltag)  t = t->left;
                        else if (!t->rtag)  t = t->right;
                    }
                }
            }
        }
        cout << endl;
        break;

    // 逆序遍历后序线索二叉树
    case 7:
        // 最后一个结点就是根结点
        // 往前遍历
        while (t != NULL) {
            cout << t->data << " ";
            // 前驱结点
            if (!t->rtag)  t = t->right;
            else  t = t->left;
        }
        cout << endl;
        break;

    // 普通方式，遍历后序线索二叉树
    case 8:
        if (!t->ltag)  visitThreadTree(t->left, type);
        if (!t->rtag)  visitThreadTree(t->right, type);
        cout << t->data << " ";
        break;
    default:
        break;
    }
}
int main() {
    return 0;
}
```

### 1.4 哈夫曼树

树的结点可以设置权值，用来表示某种意义，比如表示重要性：

* 结点的带权路径长度：从根结点触发，到某结点若经过 x 条边，结点的权值为 y ，那么该结点的带权路径长度 = x \* y

* 树的带权路径长度：所有叶子结点的带权路径长度之和

哈夫曼树是是用几个叶子结点，构成的树的带权路径长度最短的二叉树，也叫最优二叉树，哈夫曼树肯呢个不唯一。

（1）构建哈夫曼树

```
#include<iostream>
#include<vector>
using namespace std;

typedef struct BinTreeNode {
    int data；
    struct BinTreeNode *left, *right；
} BinTreeNode, *BinTree;


BinTreeNode* newNode(int data, BinTreeNode *left = NULL, BinTreeNode *right = NULL) {
    BinTreeNode* node = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    node->data = data;
    node->left = left;
    node->right = right;
    return node;
}

/* 构建哈夫曼树
 * 若列表中只有一个权值，就只有一个根结点
 * 每次从列表中找到两个最小的权值，构建结点，然后把删除这两个权值，并把它们的和加入列表
 */
BinTree createHuffmenTree(vector<int> list) {
    if (list.empty())  return NULL;

    BinTree huffmenTree = NULL;
    int data1, data2;
    map<int, BinTreeNode*> m;

    while (list.size() > 1) {
        data1 = list[list.size() - 1];
        data2 = list[list.size() - 2];

        // 找到最小的两个权值
        for (int i = list.size() - 3; i >= 0; i--) {
            if (list[i] < data1 || list[i] < data2) {
                int temp;
                if (data1 > data2) {
                    temp = data1;
                    data1 = list[i];
                    list[i] = temp;
                }
                else {
                    temp = data2;
                    data2 = list[i];
                    list[i] = temp;
                }
            }
        }

        // 把这两个权值删除，再把它们的和加入数组
        list.pop_back();
        list.pop_back();
        list.push_back(data1 + data2);

        BinTreeNode *node1 = NULL, *node2 = NULL, *root = NULL;
        map<int, BinTreeNode*>::iterator it;

        it = m.find(data1);
        if (it == m.end())  node1 = newNode(data1);
        else {
            node1 = it->second;
            m.erase(it);
        }

        it = m.find(data2);
        if (it == m.end())  node2 = newNode(data2);
        else {
            node2 = it->second;
            m.erase(it);
        }

        root = newNode(data1 + data2, node1, node2);

        m.insert(pair<int, BinTreeNode*>(data1 + data2, root));
    }

    if (m.empty())  huffmenTree = newNode(list[0]);
    else  huffmenTree = m.begin()->second;

    return huffmenTree;
}

int main() {
    return 0;
}
```

（2）哈夫曼编码

可变长编码，可以用尽量少的开销进行编码：

* 以权值表示某种事物出现的次数，构建出哈夫曼树

* 左子树路径为 0 ，右子树路径为 1 ，从根结点开始到叶子结点的路径形成的 0 1 组合就是这个叶子结点的哈夫曼编码

```
        root
  node        83
 12  52

哈夫曼编码为：    
12：00
52：01
83：1
```

### 1.5 堆

堆是一个顺序存储的完全二叉树：

* 大根堆：任何一个结点都大于它的所有孩子

* 小根堆：任何一个结点都小于它的所有孩子

* 两个孩子没有大小顺序

堆只需要上滤、下滤两个操作就可以完成所有功能：

```
// struct 版

#include<iostream>
using namespace std;

enum HeapType { Big, Small };

typedef struct Heap {
    int *heap;
    int maxSize, length;
    HeapType heapType;
} Heeap;

bool init(Heap *&h, int maxSize, HeapType heapType) {
    if (h != NULL) return false;

    h = (Heap*)malloc(sizeof(Heap));
    h->heap = (int*)malloc(sizeof(int) * maxSize);
    h->maxSize = maxSize;
    h->length = 0;
    h->heapType = heapType;

    return true;
}

// 基础操作 ----------------------------------------------------------------------------------------
// 上滤，一直往上判断是否符合堆的特性，不符合就和父结点交换，直到根结点为止
bool toUp(Heap *h, int nodeIndex) {
    if (h == NULL || h->heap == NULL || nodeIndex <= 0 || nodeIndex >= h->length) return false;

    while (nodeIndex > 0) {
        int parentIndex = (nodeIndex + 1) / 2 - 1;
        if (h->heap[nodeIndex] > h->heap[parentIndex] && h->heapType == Big ||
            h->heap[nodeIndex] < h->heap[parentIndex] && h->heapType == Small
        ) {
            int temp = h->heap[nodeIndex];
            h->heap[nodeIndex] = h->heap[parentIndex];
            h->heap[parentIndex] = temp;

            nodeIndex = parentIndex;
        }
        else break;
    }

    return true;
}

// 下过，和上滤相反，一直往下判断，直到堆底为止
bool toDown(Heap* h, int nodeIndex) {
    if (h == NULL || h->heap == NULL || nodeIndex < 0 || nodeIndex > (h->length - 2) / 2) return false;

    int temp = h->heap[nodeIndex];
    for (int i = 2 * nodeIndex + 1; i < h->length; i = 2 * i + 1) {

        // 找到左右孩子更大的那一个
        if (i < h->length - 1 && (
                h->heap[i] < h->heap[i + 1] && h->heapType == Big || 
                h->heap[i] > h->heap[i + 1] && h->heapType == Small
            )
        )  i++;

        // 检查是否符合堆的特性
        if (temp >= h->heap[i] && h->heapType == Big || temp <= h->heap[i] && h->heapType == Small)    break;
        else {
            h->heap[nodeIndex] = h->heap[i];
            nodeIndex = i;
        }
    }

    h->heap[nodeIndex] = temp;

    return true;
}
// ----------------------------------------------------------------------------------------------------

// 插入、删除 ---------------------------------------------------------------------------
/* 插入
 * 空间复杂度：O(1)
 * 时间复杂度：O(logn)
 */
bool insertHeap(Heap *h, int a) {
    if (h == NULL || h->heap == NULL || h->length >= h->maxSize) return false;

    // 先把插入的元素放到堆尾，再上滤调整
    h->heap[h->length++] = a;
    toUp(h, h->length - 1);

    return true;
}


/* 插入
 * 空间复杂度：O(1)
 * 时间复杂度：O(n)
 */
bool removeHeap(Heap* h, int a) {
    if (h == NULL || h->heap == NULL || h->length <= 0) return false;

    // 查找找到 index
    int nodeIndex = -1;
    for (int i = 0; i < h->length; i++) {
        if (h->heap[i] == a) {
            nodeIndex = i;
            break;
        }
    }
    if (nodeIndex == -1) return false;

    // 先把栈尾的元素覆盖到删除为止，再下滤调整
    h->heap[nodeIndex] = h->heap[h->length - 1];
    h->length--;
    toDown(h, nodeIndex);

    return true;
}
// ------------------------------------------------------------------------------------------

// 将一个非堆序列调整成堆 -------------------------------------------------------------------
/* 自顶向下
 * 空间复杂度：O(n)
 * 时间复杂度：O(nlogn)
 */
Heap* upToDown(Heap *h) {
    if (h == NULL || h->heap == NULL) return h;

    // 插入到一个新的堆
    Heap *newHeap = NULL;
    init(newHeap, h->maxSize, h->heapType);
    for (int i = 0; i < h->length; i++) insertHeap(newHeap, h->heap[i]);

    free(h->heap);
    free(h);

    return newHeap;
}

 /* 自下而上
  * 空间复杂度：O(1)
  * 时间复杂度：O(n)
  */
bool downToUp(Heap *h) {
    if (h == NULL || h->heap == NULL) return false;

    // 建大根堆，从最后一个非叶结点开始，依次下滤调整
    for (int i = (h->length - 2) / 2; i >= 0; i--) toDown(h, i);

    return true;
}

int main() {
    Heap *h = NULL;
    init(h, 10, Big);

    // 测试非堆序列调整成堆 -----------------------------------------------------------------------------
    int arr[10] = { 7,5,6,8,2,4,9,1,3,0 };

    for (int i = 0; i < 10; i++) h->heap[i] = arr[i];
    h->length = 10;

    // h = upToDown(h);
    downToUp(h);
    for (int i = 0; i < 10; i++) cout << h->heap[i] << " ";
    cout << endl << endl;

    free(h->heap);
    free(h);
    h = NULL;
    // -------------------------------------------------------------------------------------------------

    // 测试正常的插入、删除
    init(h, 10, Big);
    for (int i = 0; i < 10; i++) insertHeap(h, i);

    for (int i = 0; i < 10; i++) cout << h->heap[i] << " ";
    cout << endl;

    removeHeap(h, 7);
    removeHeap(h, 9);
    removeHeap(h, 5);
    removeHeap(h, 19);

    for (int i = 0; i < h->length; i++) cout << h->heap[i] << " ";
    cout << endl;

    return 0;
}
```

堆的经典引用：

* 优先队列：每一堂取出根结点入队，再把堆尾覆盖到根结点，堆 length 减 1，根结点下滤调整，最终得到的队列就是一个有序的队列，升序需要小根堆，降序需要大根堆

* 堆排序：和优先队列差不多，只是不需要队列了，每次只需要把根结点和堆尾元素惊交换，再从根结点下滤即可，升序需要大根堆，降序需要小根堆

## 2 二叉排序树

## 2.1 BST

二叉排序树（BST，也叫二叉查找树）：

- 默认情况：左 < 根 < 右，不能有相同元素

- 中序遍历得到一个有序序列

- 平均查找长度 ASL：需要比较的次数平均值，以 2 <- 1 -> 3 这个 BST 为例：
  
  - 查找成功的 ASL：有 3 个结点，查找结点 1 需要 1 步，超找结点 2 和结点 3 都需要 2 步，= ( 1 * 1 + 2 * 2 ) / 3 = 5 / 3
  
  - 查找失败的 ASL：有 4 个空指针，到空指针都需要 2 步，= ( 2 * 4 ) / 4 = 2

### 2.2 AVL

平衡二叉树（AVL，也叫二叉平衡树）：

- 当把一个有序的序列插入到 BST 时，BST 就会是一条线性结构，查找事件复杂度为 O(n) ，为了避免这种情况，可以将 BST 转化为 AVL

- AVL 各个子树的左右高度之差 <= 1，可以保证查找的事件复杂度始终为 O(logn)

- AVL 一定是 BST ，属于包含关系

BST 转化为 AVL ：

- x 结点的平衡因子：x 左子树 h - x 右子树 h ，平衡因子绝对值 <= 1 ，就是平衡的

- 最小不平衡子树：深度最深的不平衡子树
  
  - 插入时只需要把它平衡了，整个树就平衡了
  
  - 删除时把它平衡后，还需要往上找不平衡子树，继续平衡

- 每次插入、删除完成后，检查是否平衡，若不平衡则需要旋转，有 4 种情况，以最小不平衡子树的根结点为 x 为例：
  
  - LL 型：x 左子树 h - x 右子树 h > 1，且 x 左孩子有左孩子，x 右旋
  
  - LR 型：x 左子树 h - x 右子树 h > 1，且 x 左孩子没有左孩子，x 的左孩子先左旋，x 再右旋
  
  - RR 型：x 左子树 h - x 右子树 h > -1，且 x 右孩子有右孩子，x 左旋
  
  - RL 型：x 左子树 h - x 右子树 h > -1，且 x 右孩子没有右孩子，x 的右孩子先右旋，x 再左旋

以下例子是构建一个 AVL ，左 < 右，相同元素用计数器统计：

```
// struct 版

#include<iostream>
using namespace std;

typedef struct BinTreeNode {
    int data, cnt;
    struct BinTreeNode *left, *right;
} BinTreeNode, * BinTree;

// 获取高度
int getTreeHeight(BinTree t) {
    if (t == NULL)  return 0;

    int left = getTreeHeight(t->left) + 1;
    int right = getTreeHeight(t->right) + 1;

    return left > right ? left : right;
}

// 计算平衡因子
int getBF(BinTreeNode *node) {
    if (node == NULL)  return 0;
    return getTreeHeight(node->left) - getTreeHeight(node->right);
}

// 旋转，shaft 为转轴
BinTreeNode* rotate(BinTreeNode *shaft, BinTreeNode* parent, bool direction = false) {
    if (shaft == NULL || parent == NULL)  return shaft;

    // 左旋
    if (!direction) {
        parent->right = shaft->left;
        shaft->left = parent;
    }
    // 右旋
    else {
        parent->left = shaft->right;
        shaft->right = parent;
    }

    return shaft;
}

// 检查并调整
BinTreeNode* checkAVL(BinTreeNode *node, int bf) {
    // LL，右旋
    if (bf > 1 && node->left->left) return rotate(node->left, node, true);
    // LR，node 的左孩子先左旋，node 再右旋，
    else if (bf > 1 && !node->left->left) return rotate(rotate(node->left->right, node->left), node, true);
    // RR，左旋
    else if (bf < -1 && node->right->right) return rotate(node->right, node);
    // RL，node 的右孩子先右旋，node 再左旋，
    else if (bf < -1 && !node->right->right) return rotate(rotate(node->right->left, node->right, true), node);
    else  return node;
}

// 插入
BinTreeNode* insertAVL(BinTree &t, int data, bool &isRotated) {
    if (t == NULL) {
        t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        t->data = data;
        t->cnt = 1;
        t->left = NULL;
        t->right = NULL;

        return t;
    }

    // 构建 BST
    if (data < t->data)  t->left = insertAVL(t->left, data, isRotated);
    else if (data > t->data)  t->right = insertAVL(t->right, data, isRotated);
    else t->cnt++;

    // 插入时只需要调整一次就行
    if (!isRotated) {
        // 转化成 AVL ，边回输边找最小不平衡子树，失衡就旋转调整
        BinTreeNode *temp = t;
        t = checkAVL(t, getBF(t));
        if (temp != t) isRotated = true;
    }
    else return t;
}

typedef struct RemoveType {
    BinTreeNode *node;
    int behindNextData, behindNextCnt;
} RemoveType;

// 删除
RemoveType* removeAVL(BinTree &t, int data, bool isBehindNext = false) {
    RemoveType *rt = NULL;

    if (t == NULL) {
        rt = (RemoveType*)malloc(sizeof(RemoveType));
        rt->node = NULL;
        return rt;
    }

    // 找到了要删除的结点
    if (data == t->data && !isBehindNext || t->left == NULL && isBehindNext) {
        // 如果有两个孩子，就需要中序后继替换
        if (t->left && t->right) {
            rt = removeAVL(t->right, data, true);
            t->right = rt->node;
            t->data = rt->behindNextData;
            t->cnt = rt->behindNextCnt;

            t = checkAVL(t, getBF(t));
            rt->node = t;

            return rt;
        }

        rt = (RemoveType*)malloc(sizeof(RemoveType));
        rt->node = NULL;
        if (isBehindNext) {
            rt->behindNextData = t->data;
            rt->behindNextCnt = t->cnt;
        }

        // 如果没有孩子，直接删除
        if (!t->left && !t->right) free(t);
        // 如果只有一左孩子
        else if (t->left && !t->right) {
            rt->node = t->left;
            free(t);
        }
        // 如果只有一右孩子
        else if (!t->left && t->right) {
            rt->node = t->right;
            free(t);
        }

        return rt;
    }
    else {
        if (!isBehindNext) {
            if (data < t->data) {
                rt = removeAVL(t->left, data);
                t->left = rt->node;
            }
            else if (data > t->data) {
                rt = removeAVL(t->right, data);
                t->right = rt->node;
            }
        }
        else {
            rt = removeAVL(t->left, data, true);
            t->left = rt->node;
        }
    }

    // 转化成 AVL ，边回输边找最小不平衡子树，失衡就旋转调整
    // 删除肯呢个需要往上调整多次
    t = checkAVL(t, getBF(t));
    rt->node = t;

    return rt;
}
// 查找
bool findAVL(BinTree t, int data) {
    if (t == NULL)  return false;

    if (data < t->data)  return  findAVL(t->left, data);
    else if (data > t->data)  return  findAVL(t->right, data);
    else  return true;
}

// 整合，因为旋转可能会修改根结点，整合成一个函数这样比较方便
bool operatorAVL(BinTree &t, char type, int data, int newData = 0) {
    bool isRotated = false;
    RemoveType *rt = NULL;

    switch (type) {
    // 插入
    case 0:
        insertAVL(t, data, isRotated);
        break;
    // 删除
    case 1:
        rt = removeAVL(t, data);
        free(rt);
        break;
    // 修改，如果不存在，就直接插入
    case 2:
        rt = removeAVL(t, data);
        free(rt);
        insertAVL(t, newData, isRotated);
        break;
    // 查找
    case 3:
        return  findAVL(t, data);
    default:
        break;
    }

    return true;
}

int main() {
    return 0;
}
```

### 2.3 RBT

红黑树，与 AVL 相比：

* 查询：都是 O\(logn\)，但 AVL 比 RBT 快一点点，差距非常小

* 插入和删除：AVL 因为需要更加严格的平衡，插入删除的时候大概率需要调整，需要消耗较多的性能，虽然是 O\(logn\)，但 RBT 调整的频率更少，因此 RBT 的 O\(logn\) 更快

牺牲非常小的查询效率就可以大大提升插入和删除的效率，因此实际引用中 RBT 更常用，如 map 和 set ，当然如果插入删除的操作很少，而需要经常查询时，也可以用 AVL 。

RBT 的规则：

* 根 NULL 黑：根结点和 NULL 结点必须是黑色，注意在 RBT 中，说的叶子结点指的是 NULL 结点，这里为了不混淆，就以 NULL 结点代替

* 不红红：父子两个结点不能同时为红色

* 黑路同：从任意结点出发，各个路径到达 NULL 结点，经过的黑结点数量相同

* RBT 时一个 BST

代码：

```
// struct 版

#include<iostream>
using namespace std;

enum Color { Red, Black };

typedef struct BinTreeNode {
    int data, cnt;
    Color color;
    struct BinTreeNode *left, *right, *parent;
} BinTreeNode, *BinTree;

// 旋转，插入、删除均使用 ----------------------------------------------------------------------------
/* 旋转操作，这里 shaft 是转轴，shaft 的 parent 是旋转的结点
 * direction：false 为左旋
  * changeColor：false，此次旋转不变色，变色即 shaft 变黑，shart 的 parent 变红
  * 旋转后就可以直接在这里修改 parent 指向
*/
BinTreeNode* rotate(BinTreeNode *shaft, bool direction, bool changeColor) {
    if (shaft == NULL || shaft->parent == NULL)  return shaft;

    // 变色
    if (changeColor) {
        shaft->color = Black;
        shaft->parent->color = Red;
    }

    // 左旋
    if (!direction) {
        shaft->parent->right = shaft->left;
        shaft->left = shaft->parent;
    }
    // 右旋
    else {
        shaft->parent->left = shaft->right;
        shaft->right = shaft->parent;
    }

    // 修改 parent
    BinTreeNode *parent = shaft->parent;
    shaft->parent = shaft->parent->parent;
    parent->parent = shaft;
    if (parent->left) parent->left->parent = parent;
    if (parent->right) parent->right->parent = parent;

    return shaft;
}
// --------------------------------------------------------------------------------------------------

// 插入 -------------------------------------------------------------------------------------------------
/* 插入时，新结点默认是红色，如果新结点就是根结点，就改成黑色
 * 若违反了不红红，看叔叔结点的颜色：
   * 红：父、叔变黑，爷爷变红（若爷爷是根结点，就变黑）
   * 黑：根据 LL LR RR RL 进行旋转
 */

// 检查红黑树并修复，shaft 是转轴，shaft 的 parent 是待旋转的结点
BinTreeNode* checkRBT(BinTreeNode *shaft) {
    if (shaft == NULL) return shaft;
    if (shaft->parent == NULL) {
        shaft->color = Black;
        return shaft;
    }

    // 如果违反了不红红
    if (shaft->color == Red && (shaft->left && shaft->left->color == Red || shaft->right && shaft->right->color == Red)) {
        // true：LL LR   false：RR RL
        bool LorR = shaft == shaft->parent->left;
        // 叔叔结点
        BinTreeNode *uncle = LorR ? shaft->parent->right : shaft->parent->left;

        // 如果叔叔结点是红色
        if (uncle && uncle->color == Red) {
            shaft->color = Black;
            uncle->color = Black;
            shaft->parent->color = shaft->parent->parent ? Red : Black;
        }
        // 如果叔叔结点是黑色，就要根据 LL LR RR RL 来旋转
        else if (uncle == NULL || uncle->color == Black) {
            // 等旋转结点
            BinTreeNode* node = shaft->parent;

            // LL LR
            if (LorR) {
                // 如果是 LR ，就先让 shaft 左旋，shaft->right 是转轴
                if (shaft->right && shaft->right->color == Red) shaft = rotate(shaft->right, false, false);

                // node 右旋，shaft 是转轴
                rotate(shaft, true, true);
            }
            // RR RL
            else {
                // 如果是 RL ，就先让 shaft 右旋，shaft->left 是转轴

                if (shaft->left && shaft->left->color == Red) shaft = rotate(shaft->left, true, false);
                // node  左旋，shaft 是转轴
                rotate(shaft, false, true);
            }

            return shaft;
        }
    }

    return shaft->parent;
}

// 插入 
BinTreeNode* insertRBT(BinTree &t, int data, BinTreeNode *parent = NULL) {
    if (t == NULL) {
        t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        t->data = data;
        t->cnt = 1;
        t->left = NULL;
        t->right = NULL;
        t->parent = parent;

        // 默认插入红结点，但如果是根结点，就变成黑结点
        if (parent)  t->color = Red;
        else t->color = Black;

        return t;
    }

    // BST
    if (data < t->data)  t->left = insertRBT(t->left, data, t);
    else if (data > t->data)  t->right = insertRBT(t->right, data, t);
    else t->cnt++;

    if (data != t->data) t = checkRBT(data < t->data ? t->left : t->right);

    return t;
}
// -----------------------------------------------------------------------------------------------

// 删除 ------------------------------------------------------------------------------------------
/* w为了方便递归实现，这里定义了一个结构体作为返回类型，同时为了节省性能，将其分配在堆区，记得释放
 * 若删除结点有两个孩子，采用中序后继替换，这样就转化成了删除单孩子或无孩子的情况
 * 若删除结点只有一个孩子，此时必然是 黑->红 ，直接替换值，并 free 孩子
 * 若删除结点没有孩子，此时该结点的颜色若为：
   * 红：直接 free
   * 黑：
     * 若此时就是根结点，直接 free ，返回 NULL
     * 若不是根结点，就需要看兄弟结点的颜色：
       * 黑：看兄弟的孩子，若：
         * 至少有一个红孩子，则根据 LL LR RR RL 进行处理，若有两个红孩子，也是为 LL 或 RR ，具体看代码
         * 两个黑孩子或无孩子（即两个 NULL 黑孩）：兄变红，然后看父的颜色
           * 红或者是根结点：就说明调整完成
           * 黑：将父视为删除结点，看父的兄弟的颜色，进一步处理
       * 红：兄变黑，父变红，再向删除的方向旋转；旋转后再判断新兄弟的颜色，进一步处理
 */

typedef struct RemoveType {
    BinTreeNode *node;
    // 删除黑叶子结点时，调整具有多重情况
    char repairType;
    // true: LL LR ；false: RR RL
    bool LorR;
    // 删除有两个孩子的结点时，需要替换中序后继，这里用来保存中序后继的值
    int behindNextValue, behindNextCnt;
} removeType;

// 当删除的是黑叶结点时，判断属于哪一种类型
char deleteBlackLeafType(BinTreeNode *brother, bool LorR) {
    if (brother == NULL)  return 0;

    // 如果兄弟是黑结点，则需要比较复杂的调整
    if (brother->color == Black) {
        // brother 时叶结点，或者有两个黑结点，type = 5
        if (!brother->left && !brother->right || brother->left && brother->left->color == Black && brother->right && brother->right->color == Black) {
            return 5;
        }
        else if (LorR) {
            if (brother->left && brother->left->color == Red) return 1;
            else if (brother->right && brother->right->color == Red) return 2;

        }
        else if (!LorR) {
            if (brother->right && brother->right->color == Red) return 3;
            else if (brother->left && brother->left->color == Red) return 4;
        }


    }
    // 红 brother
    else return 6;

    return 0;
}

// 删除的是黑色叶子结点时的修复
RemoveType* repairRBT(RemoveType *rt) {
    if (rt == NULL || rt->node == NULL || rt->repairType < 1 || rt->repairType > 6)  return rt;

    // r：兄弟的孩子，s：兄弟，p：兄弟的父
    BinTreeNode *r = NULL, *s = NULL, *p = NULL;
    // 情况 6 备用
    RemoveType *tempRt = NULL;

    switch (rt->repairType) {
    // 黑色 brother 有左红孩子，是 LL ，若有两个红色孩子，也堪称 LL
    case 1:
        r = rt->node->left->left;
        s = rt->node->left; 
        p = rt->node;
        r->color = s->color;
        s->color = p->color;
        p->color = Black;
        rt->node = rotate(s, true, false);
        rt->repairType = 0;
        break;

    // 黑色 brother 至少有一个右红孩子，是 LR
    case 2:
        r = rt->node->left->right; 
        s = rt->node->left; 
        p = rt->node;
        r->color = p->color;
        p->color = Black;
        rt->node = rotate(rotate(r, false, false), true, false);
        rt->repairType = 0;
        break;

    // 黑色 brother 有右红孩子，是 RR ，若有两个红色孩子，也堪称 RR
    case 3:
        r = rt->node->right->right; 
        s = rt->node->right; 
        p = rt->node;
        r->color = s->color;
        s->color = p->color;
        p->color = Black;
        rt->node = rotate(s, false, false);
        rt->repairType = 0;
        break;

    // 黑色 brother 至少有一个左红孩子，是 RL
    case 4:
        r = rt->node->right->left; 
        s = rt->node->right; 
        p = rt->node;
        r->color = p->color;
        p->color = Black;
        rt->node = rotate(rotate(r, true, false), false, false);
        rt->repairType = 0;
        break;

    // 黑色 brother ，且 brother 有两个黑色或 NULL 孩子
    case 5:
        s = rt->LorR ? rt->node->left : rt->node->right;
        p = rt->node;
        s->color = Red;

        // 如果 p 是根结点，就不需要再调整
        if (p->parent != NULL) {
            // 如果是红结点，变黑
            if (p->color == Red) {
                p->color = Black;
                rt->repairType = 0;
            }
            // 如果是黑结点，就需要把 p 看做删除黑叶结点的情况，根据 p 的兄弟颜色做调整
            else {
                rt->LorR = p == p->parent->right;
                rt->repairType = deleteBlackLeafType(rt->LorR ? p->parent->left : p->parent->right, rt->LorR);
            }
        }
        else rt->repairType = 0;

        break;

    // 红色 brother
    case 6:
        // 此时的结构必然是，红兄弟，兄弟两个实体黑孩子，黑色父亲
        // 父兄变色，然后往删除结点的方向旋转，兄弟为转轴
        s = rt->LorR ? rt->node->left : rt->node->right;
        p = rt->node;
        r = rt->LorR ? s->right : s->left;

        // 变色、旋转
        s->color = Black;
        p->color = Red;
        rt->node = rt->LorR ? rotate(s, true, false) : rotate(s, false, false);
        rt->repairType = 0;

        // 旋转后，r 就成为了删除结点新的 brother ，需要再次调整，此时 s 必然是黑色，只有 1 2 3 4 5 的情况，情况 5 的父也必然是红色，所以都只需要调整板一次
        tempRt = (RemoveType*)malloc(sizeof(RemoveType));
        tempRt->node = p;
        tempRt->repairType = deleteBlackLeafType(r, rt->LorR);
        tempRt->LorR = rt->LorR;
        if (tempRt->LorR) rt->node->right = repairRBT(tempRt)->node;
        else rt->node->left = repairRBT(tempRt)->node;
        free(tempRt);

        break;

    default:
        break;
    }

    return rt;
}

// 删除
RemoveType* removeRBT(BinTree &t, int data, bool isFindNext = false) {
    RemoveType *rt = NULL;

    if (t == NULL) {
        rt = (RemoveType*)malloc(sizeof(RemoveType));
        rt->node = NULL;
        rt->repairType = 0;
        return rt;
    }

    // 找到了要删除的结点
    if (data == t->data && !isFindNext || t->left == NULL && isFindNext) {
        // 如果有两个孩子
        if (t->left && t->right) {
            // 替换中序后继，并删除中序后继
            rt = removeRBT(t->right, data, true);
            t->right = rt->node;
            t->data = rt->behindNextValue;
            t->cnt = rt->behindNextValue;

            rt->node = t;
            return repairRBT(rt);
        }

        rt = (RemoveType*)malloc(sizeof(RemoveType));
        rt->node = NULL;
        rt->repairType = 0;
        if (isFindNext) {
            rt->behindNextValue = t->data;
            t->cnt = rt->behindNextCnt;
        }

        // 如果只有左孩子，此时必然是 黑->红
        if (t->left && !t->right) {
            t->data = t->left->data;
            t->cnt = t->left->cnt;
            free(t->left);
            t->left = NULL;
            rt->node = t;
        }
        // 如果只有右孩子，此时必然是 黑->红
        else if (!t->left && t->right) {
            t->data = t->right->data;
            t->cnt = t->right->cnt;
            free(t->right);
            t->right = NULL;
            rt->node = t;
        }
        // 如果没有孩子
        else if (!t->left && !t->right) {
            // 如果此时是根结点，直接删除
            if (t->parent == NULL) {
                free(t);
                t = NULL;
            }
            // 如果是红结点，直接删除
            else if (t->color == Red) free(t);
            // 如果是黑结点，需要看兄弟结点的颜色，此时兄弟必然不是 NULL
            else {
                rt->LorR = t == t->parent->right;;
                rt->repairType = deleteBlackLeafType(rt->LorR ? t->parent->left : t->parent->right, rt->LorR);
            }
        }

        return rt;
    }
    // 按照 BST 寻找
    else if (!isFindNext) {
        if (data < t->data) {
            rt = removeRBT(t->left, data);
            t->left = rt->node;
        }
        else if (data > t->data) {
            rt = removeRBT(t->right, data);
            t->right = rt->node;
        }
    }
    // 找到中序后继
    else {
        rt = removeRBT(t->left, data, true);
        t->left = rt->node;
    }

    rt->node = t;
    rt = repairRBT(rt);
    t = rt->node;

    return rt;
}
// -------------------------------------------------------------------------------------------------

// 查询 ----------------------------------------------------------------------------------------------
bool findRBT(BinTree t, int data) {
    if (t == NULL) return false;

    if (data < t->data) findRBT(t->left, data);
    else if (data > t->data) findRBT(t->right, data);
    else return true;
}
// -----------------------------------------------------------------------------------------------------

// 整合 ---------------------------------------------------------------------------------------------
void operatorRBT(BinTree &t, char type, int data, int newData = 0) {
    RemoveType *rt = NULL;

    switch (type) {
    // 查询
    case 0:
        cout << (findRBT(t, data) ? "找到了" : "未找到") << endl;
        break;
    // 插入
    case 1:
        insertRBT(t, data);
        break;
    // 删除
    case 2:
        rt = removeRBT(t, data);
        free(rt);
        break;
    // 修改
    case 3:
        rt = removeRBT(t, data);
        free(rt);
        insertRBT(t, newData);
        break;
    default:
        break;
    }
}
// --------------------------------------------------------------------------------------------------

// 判断是否是 RBT ，测试用 ---------------------------------------------------------------------------
// 不红红
bool checkRedNodeProperty(BinTreeNode* node) {
    if (node == NULL) return true;

    if (node->color == Red) {
        if ((node->left && node->left->color == Red) || (node->right && node->right->color == Red)) {
            return false;
        }
    }

    return checkRedNodeProperty(node->left) && checkRedNodeProperty(node->right);
}

// 黑路同
int countBlackHeight(BinTreeNode* node) {
    if (node == NULL) return 1;

    int leftBlackHeight = countBlackHeight(node->left);
    int rightBlackHeight = countBlackHeight(node->right);

    if (leftBlackHeight == 0 || rightBlackHeight == 0 || leftBlackHeight != rightBlackHeight) {
        return 0; // 如果子树黑高不一致或有非法黑高
    }

    return leftBlackHeight + (node->color == Black ? 1 : 0);
}

// 判断
bool isRedBlackTree(BinTreeNode* root) {
    if (root == NULL) return true;

    if (root->color != Black) {
        cout << "root is not Black" << endl;
        return false;
    }

    if (!checkRedNodeProperty(root)) {
        cout << "not Red Red" << endl;
        return false;
    }

    if (countBlackHeight(root) == 0) {
        cout << "different Black distance" << endl;
        return false;
    }

    return true;
}
// ---------------------------------------------------------------------------------------------------

int main() {
    return 0;
}
```

### 2.4 哈希表

也叫散列表，典型的用空间换时间的数据结构，通常会采用数组 \+ 链表 \+ 红黑树结合起来的结构。

哈希表是一个数组，CRUD 通过一个哈希函数实现大部分情况下 O\(1\) 的时间复杂度，哈希函数的设计方式主要有：

* 除留取余法：H\(key\) = key % p ，p 为 <= 哈希表长度的最大质数，这是为了保证比较均匀的存储关键字，不过当哈希表长度 \!= p 时，会有几个位置永远不会哈希到

* 直接定址法：如 H(key) = key ，H\(key\) = a \* key + b ，适合存储比较连续的关键字，虽然这种方法不会产生冲突，但是不够连续的关键字会浪费很多空间

* 数字分析法：适合存储比较均匀随机的关键字，如手机号的中间几位用来作为 index

* 平方取中法：取关键字平方的中间几位作为 index

* 更复杂的方法：如字符串的哈希函数

当多个关键字通过哈希函数得到相同的 index 时，就会产生冲突，这些关键字也称为互为同义词，解决冲突的方式主要有：

* 链地址法：也叫拉链法，是最常用的方法，即哈希表数组存储 head ，用一个链表来存储冲突的关键字，当链表达到一定长度时（如 8 个），链表可以转化为一个红黑树，进一步提高性能，使得时间复杂度最坏也只能是 O\(logn\)

* 多重哈希函法：也叫再哈希法，当第一个哈希函数发生冲突时，使用第二个哈希函数

* 公共空间法：哈希表一个 index 存储一个关键字，若发生冲突，则所有的冲突关键字都放在一个公共空间中，通常也是用红黑树

* 开放定址法：哈希表 index 同时向同义词、非同义词开放。
  
  ```
  // di: 增量序列   m: 哈希表长度
  hIndex = (H(key) + di) % m ，
  ```
  
  当发生冲突时，就是用 di 的第一个 d ，若还是冲突了，再使用 di 的下一个 d,di 的设计有 3 种方法：
  
  * 线性探测法：如 di = \{1,2,5,7\} ，这种方法容易造成同义词和非同义词的聚集，喝多关键字都聚集在同一个范围内
  
  * 平方探测法：如 d = \{1,-1,3,-3\} ，要求哈希表长度必须是 4x \+ 3 的质数 ，相比线性探测法好些，不容易聚集，
  
  * 伪随机序列法：增量序列都是伪随机数

装填因子：即哈希表查找失败的 ASL ，= 存储的关键字数 / 哈希表长度，装填因子越大，说明哈希表越饱满

### 2.5 跳表

普通的链表查询需要 O\(n\) ，比较慢，可以用一些空间时间，给链表建立索引，使得链表类似二叉排序树一样进行查询：

```
第 2 层: 1 ----------------> 8
         |                   |
第 1 层: 1 ------> 5 ------> 8 ------> 12
         |         |         |         |
第 0 层: 1 -> 3 -> 5 -> 6 -> 8 -> 9 -> 12
```

其中第 0 层为原始链表，第 n 层为 n 级索引，索引中最少有两个 node ，每次查询从最高层的索引开始查找，再往下查找，非常类似 BST ，CRUD 的时间复杂度都是 O\(logn\) ，不过性能比红黑树差一些：

* 在单线程情况下，性能不如红黑树，原因是跳表的索引是随机生成的

* 多线程情况下，性能优于红黑树

要建立几个索引，用随机数决定。

代码：

```
#include<iostream>
#include<vector>
using namespace std;

// 最多几级索引
#define MAX_LEVEL 7

typedef struct SkipListNode {
    int data;
    struct SkipListNode *next, *down;
} SkipListNode;

typedef struct SkipList {
    SkipListNode *head;
    int level;
} SkipList;

// 创建跳表结点
SkipListNode* createNode(int data, SkipListNode *next = NULL, SkipListNode *down = NULL) {
    SkipListNode *node = (SkipListNode*)malloc(sizeof(SkipListNode));

    node->data = data;
    node->next = next;
    node->down = down;

    return node;
}

// 初始化跳表，带头结点
SkipList* createSkipList() {
    // 设置随机种子
    srand(time(NULL));

    SkipList *list = (SkipList*)malloc(sizeof(SkipList));

    list->head = createNode(INT_MIN);
    list->level = 0;

    return list;
}

// CRUD ------------------------------------------------------------------------------------------------
// 生成随机层数，以确定插入时要建立几级索引
int randomLevel() {
    int level = 0;

    // 每高一级索引，概率就少 50%
    while (rand() % 2 && level < MAX_LEVEL) ++level;

    return level;
}

// 插入
void insertSL(SkipList *list, int data) {
    // 存储要处理的结点和索引，暂定支持 MAX_LEVEL 级索引
    SkipListNode *update[MAX_LEVEL + 1];

    SkipListNode* current = list->head;

    // 从最高层开始寻找插入点
    for (int i = list->level; i >= 0; i--) {
        while (current->next != NULL && current->next->data < data) current = current->next;
        // 如果元素已存在，就不插入了
        if (current->next != NULL && current->next->data == data) return;

        update[i] = current;
        if (current->down != NULL) current = current->down;
    }

    // 确定要新建几层索引
    int level = randomLevel();
    if (level > list->level) {
        for (int i = list->level + 1; i <= level; i++) {
            SkipListNode *newLevel = createNode(INT_MAX, NULL, list->head);
            update[i] = newLevel;
            list->head = newLevel;
        }

        list->level = level;
    }

    // 开始插入，同时建立索引
    SkipListNode* downNode = NULL;
    for (int i = 0; i <= level; i++) {
        SkipListNode *newNode = createNode(data, update[i]->next, downNode);
        update[i]->next = newNode;
        downNode = newNode;
    }
}

// 删除
void deleteSL(SkipList *list, int data) {
    SkipListNode *current = list->head;

    while (current) {
        while (current->next && current->next->data < data) current = current->next;

        // 开始删除，若有索引，也要一并删除
        if (current->next && current->next->data == data) {
            SkipListNode *temp = current->next;
            current->next = current->next->next;
            free(temp);
        }

        current = current->down;
    }

    // 如果最高层为空，降低跳表的层数
    while (list->level > 0 && list->head->next == NULL) {
        list->head = list->head->down;
        list->level--;
    }
}

// 查找
bool searchSL(SkipList *list, int data) {
    SkipListNode *current = list->head;

    while (current) {
        while (current->next && current->next->data < data) current = current->next;
        if (current->next && current->next->data == data) return true;
        current = current->down;
    }

    return false;
}
// ---------------------------------------------------------------------------------------------

void printSL(SkipList *list) {
    SkipListNode *current = list->head;
    while (current->down) current = current->down;

    int row = list->level + 1, col = 0;
    SkipListNode *p = current->next;
    while (p) {
        col++;
        p = p->next;
    }

    int **arr = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++) {
        arr[i] = (int*)malloc(sizeof(int) * col);
        for (int j = 0; j < col; j++) arr[i][j] = INT_MAX;
    }

    p = current->next;
    int i = 0;
    while (p) {
        arr[row - 1][i++] = p->data;
        p = p->next;
    }

    int cnt = 0;
    current = list->head;
    while (current) {
        p = current->next;

        while (p) {
            for (int i = 0; i < col; i++) {
                if (arr[row - 1][i] == p->data) arr[cnt][i] = p->data;
            }
            p = p->next;
        }

        ++cnt;
        current = current->down;
        if (current->down == NULL) break;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (arr[i][j] == INT_MAX) cout << "  ";
            else cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    SkipList *list = createSkipList();

    vector<int> a({ 7,5,4,9,3,6,1,8,2,0 });
    for (int i = 0; i < a.size(); i++) insertSL(list, a[i]);
    printSL(list);
    cout << endl << endl;

    deleteSL(list, 5);
    deleteSL(list, 7);
    printSL(list);
    cout << endl << endl;

    cout << searchSL(list, 4) << " ";
    cout << searchSL(list, 5) << " ";

    return 0;
}
```

### 2.6 B 树、B+ 树

（1）B 树

多叉平衡搜索树。

之前的 AVL 和 RBT ，在数据量小，可以全部加载进内存时，使用就没问题。但是当数据量非常大，已经超过了内存容量时，就不太合适了，如：

- 不能完全加载，那么每次只能从硬盘中取出一个结点进内存，这就是一次硬盘 IO ，而硬盘的速度比内存可能慢百万倍，所以即使有 O(logn) 的性能，也是 logn 的百万倍

- 解决方法是，在相同数据量下，尽量减少树的高度，就能减少硬盘 IO 次数

硬盘 IO 的次数和树高度油管，为了减少树高，就有了 B 树，B 树是一个 m 叉平衡搜索树，也叫 m 阶 B 树，有数据的结点叫内部结点，NULL 结点叫外部结点。不同资料对 B 树的叶子结点定义可能不同，这里就以内部结点的最后一层表示叶子结点。

- B 树一次硬盘 IO 读出一个结点，这个结点有多个数据，因为这个结点已经加载进内存，所以这多个数据查找就很快

B 树特性：

- 多路：每个结点最多有 m 个子树和 m - 1 个数据；最少有 m / 2 (上取证) 个子树（根结点特殊，最少可以有 2 个子树，1 个数据）

- 有序：左孩结点全部数据 < 父结点下一个孩子前的所有数据 > 下一个孩子的全部数据

- 平衡：所有的叶子结点一定在最后一层

代码：

```
// struct 版

#include<iostream>
#include<queue>
using namespace std;

// m 结 B 树，>= 3
#define M 5

typedef struct BTreeNode {
    // 只需要 M - 1 个位置就行，但是在分裂过程中需要多出一个位置，方便操作
    int data[M], dataLength;
    // 只需要 M 个位置就行，但是在分裂过程中需要多出一个位置，方便操作
    struct BTreeNode *children[M + 1], *parent;
    // 是否是叶子结点
    bool isLeaf;
} BTreeNode, *BTree;

BTreeNode* newNode(bool isLeaf) {
    BTreeNode *node = (BTreeNode*)malloc(sizeof(BTreeNode));

    for (int i = 0; i < M + 1; i++) node->children[i] = NULL;
    node->parent = NULL;
    node->dataLength = 0;
    node->isLeaf = isLeaf;

    return node;
}

// 在结点钟找到应该插入的位置
int findPos(BTreeNode* node, int data) {
    if (node == NULL)  return 0;

    int i;
    for (i = 0; i < node->dataLength; i++) {
        if (node->data[i] >= data) break;
    }

    return i;
}

// 插入 -------------------------------------------------------------------------------------------
/* 从一个根结点开始，不断分裂，一个结点最多 m - 1 个数据，m 个分支
 * 由于 B 树的性质，插入的数据一定会在叶子结点，且叶子结点一定在最后一层 
 * 若该结点还有位置，就插入到对应位置
 * 若位置不够了，就出现了上溢出，需要分裂了，以 m / 2 (上取整) 为分界线，左边放到这个结点，中间的一个放到父结点，右边全部移动到右结点
   * 若父结点也上溢出了，则父结点也需要分裂，此时移动数据时需要把孩子结点也移动过去
 */

// 分裂
BTreeNode* splitChild(BTreeNode *oldNode, int oldNodeIndexInParent) {
    if (oldNode == NULL || oldNode->dataLength <= M - 1) return oldNode;

    // parent 和新兄弟
    bool returnTag = oldNode->parent;
    BTreeNode* parent = returnTag ? oldNode->parent : newNode(false);
    BTreeNode *brother = newNode(oldNode->isLeaf);

    // 㱨 data 分界线的下标
    int midIndex = M % 2 == 0 ? M / 2 - 1 : M / 2;

    // 将 oldNode 的后半部分数据移动到 brother
    for (int i = midIndex + 1; i <= oldNode->dataLength; i++) {
        if (i < oldNode->dataLength) brother->data[i - midIndex - 1] = oldNode->data[i];
        // 如果不是叶子结点，就要把 children 也移动过去
        if (!oldNode->isLeaf) {
            brother->children[i - midIndex - 1] = oldNode->children[i];
            brother->children[i - midIndex - 1]->parent = brother;
            oldNode->children[i] = NULL;
        }
    }

    // 修改 oldNode 和 brother 的数据个数
    oldNode->dataLength = midIndex;
    brother->dataLength = M % 2 == 0 ? midIndex + 1 : midIndex;

    // parent 中插入 brother 和上溢出的数据
    for (int i = parent->dataLength + 1; i > oldNodeIndexInParent; i--) {
        parent->children[i] = parent->children[i - 1];
        if (i < parent->dataLength + 1) parent->data[i] = parent->data[i - 1];

    }
    parent->children[oldNodeIndexInParent + 1] = brother;
    parent->children[oldNodeIndexInParent] = oldNode;
    parent->data[oldNodeIndexInParent] = oldNode->data[midIndex];
    parent->dataLength++;

    // 修改 parent 指向
    oldNode->parent = parent;
    brother->parent = parent;

    return returnTag ? oldNode : parent;
}

// 插入
BTreeNode* insertBT(BTree &t, int data, int childrenIndexInParent = 0) {
    if (M < 3) return NULL;

    if (t == NULL) {
        t = newNode(true);
        t->data[0] = data;
        t->dataLength++;

        return t;
    }

    if (t->isLeaf) {
        int pos = findPos(t, data);
        if (pos < t->dataLength&& t->data[pos] == data) return t;

        for (int i = t->dataLength; i > pos; i--) t->data[i] = t->data[i - 1];
        t->data[pos] = data;
        t->dataLength++;
    }
    else {
        int pos = findPos(t, data);
        if (pos < t->dataLength && t->data[pos] == data) return t;

        t->children[pos] = insertBT(t->children[pos], data, pos);
    }

    t = splitChild(t, childrenIndexInParent);
    return t;
}

// -----------------------------------------------------------------------------------------------------

// 删除 --------------------------------------------------------------------------------
/* 不断合并，根结点最少有 1 个数据，2 个分支，其他结点最少有 n = m / 2 (上取整) 个分支，n - 1 个数据
 * 若删除的数据在非叶子结点上，需要中序后继替换
 * 若删除的数据在叶子结点上，直接删除，若删除后数据量小于该结点的最小数据量，则出现了下溢出，此时需要看兄弟：
   * 左右兄弟可以借一个数据，那就接一个给父，父再拉一个下来
   * 若不够借，则需要合并，将父的一个数据移下来再合并，并删除空结点，然后若父也没有数据了，删除父结点
   * 瑞父也出现了下溢出，则需要继续看是否要合并
 */
typedef struct RemoveType {
    BTree node;
    int removeIndex;
    int behindNextData;
};

// 合并
RemoveType* mergeBT(RemoveType *oldNodeRt, int oldNodeIndexInParent, bool needSwap = false) {
    if (oldNodeRt == NULL) return NULL;

    if (needSwap) {
        oldNodeRt->node->parent->data[oldNodeIndexInParent - 1] = oldNodeRt->behindNextData;
    }

    // 不需要处理
    if (NULL || oldNodeRt->removeIndex < 0) return oldNodeRt;

    // oldNode 若需要删除，则 dataLength 此时已经减 1 了

    // 最小数据量
    int minLength = M % 2 == 0 ? M / 2 - 1 : M / 2;

    // 如果没有下溢出
    BTreeNode* oldNode = oldNodeRt->node;
    if (oldNode->dataLength >= minLength || oldNodeRt->node->parent == NULL) {
        for (int i = oldNodeRt->removeIndex; i < oldNode->dataLength; i++) oldNode->data[i] = oldNode->data[i + 1];
        oldNodeRt->removeIndex = -1;

        return oldNodeRt;
    }

    // 如果下溢出了
    BTreeNode *parent = oldNode->parent;

    // 是否有左右兄弟
    bool hasLeftBrother = oldNodeIndexInParent > 0;

    bool hasRightBrother = oldNodeIndexInParent < parent->dataLength;
    BTreeNode* leftBrother = hasLeftBrother ? parent->children[oldNodeIndexInParent - 1] : NULL;
    BTreeNode* rightBrother = hasRightBrother ? parent->children[oldNodeIndexInParent + 1] : NULL;

    // 如果左兄弟够借
    if (hasLeftBrother && parent->children[oldNodeIndexInParent - 1]->dataLength > minLength) {
        // oldNode 空出一个位置
        for (int i = oldNodeRt->removeIndex; i > 0; i--) oldNode->data[i] = oldNode->data[i - 1];

        // parent 拉一个下来
        oldNode->data[0] = parent->data[oldNodeIndexInParent - 1];

        // 如果不是叶子结点，还要把 children 移动过去
        if (!oldNode->isLeaf) {
            oldNode->children[0] = leftBrother->children[leftBrother->dataLength];
            oldNode->children[0]->parent = oldNode;
            leftBrother->children[leftBrother->dataLength] = NULL;
        }
        oldNode->dataLength++;

        // leftBrother 拉一个上 parent
        parent->data[oldNodeIndexInParent - 1] = leftBrother->data[leftBrother->dataLength - 1];
        leftBrother->dataLength--;

        oldNodeRt->removeIndex = -1;
    }
    // 如果右兄弟够借
    else if (hasRightBrother && parent->children[oldNodeIndexInParent + 1]->dataLength > minLength) {
        // oldNode 空出一个位置
        for (int i = oldNodeRt->removeIndex; i < oldNode->dataLength; i++) oldNode->data[i] = oldNode->data[i + 1];

        // parent 拉一个下 oldNode
        oldNode->data[oldNode->dataLength++] = parent->data[oldNodeIndexInParent];

        // 如果不是叶子结点，还要把 children 移动过去
        if (!oldNode->isLeaf) {
            oldNode->children[oldNode->dataLength] = rightBrother->children[0];
            oldNode->children[oldNode->dataLength]->parent = oldNode;
        }

        // rightBrother 拉一个上 parent
        parent->data[oldNodeIndexInParent] = rightBrother->data[0];
        rightBrother->dataLength--;

        // rightBrother 少了一个数据，所以后面的数据和 children 要往前移动
        for (int i = 0; i <= rightBrother->dataLength; i++) {
            if (i < rightBrother->dataLength) rightBrother->data[i] = rightBrother->data[i + 1];
            if (!oldNode->isLeaf) rightBrother->children[i] = rightBrother->children[i + 1];
        }
        if (!oldNode->isLeaf) rightBrother->children[rightBrother->dataLength + 1] = NULL;

        oldNodeRt->removeIndex = -1;
    }
    // 如果都不够借
    else {
        // 如果有左兄弟，就优先和做兄弟合并
        if (hasLeftBrother) {
            // parent 拉一个数据下来
            leftBrother->data[leftBrother->dataLength] = parent->data[oldNodeIndexInParent - 1];

            // 把 oldNode 的数据移动过来
            bool isJump = false;
            for (int i = 0; i < oldNode->dataLength + 1; i++) {
                // 如果不是叶子结点，还要把 children 移动过去
                if (!oldNode->isLeaf) {
                    oldNode->children[i]->parent = leftBrother;
                    leftBrother->children[i + leftBrother->dataLength + 1] = oldNode->children[i];
                    oldNode->children[i] = NULL;
                }

                if (i == oldNodeRt->removeIndex) {
                    isJump = true;
                    continue;
                }

                leftBrother->data[i + leftBrother->dataLength + 1 - isJump] = oldNode->data[i];
            }
            leftBrother->dataLength += 1 + oldNode->dataLength;

            // 删除 oldNode
            free(oldNode);
            oldNode = NULL;
        }
        // 否则，就和右兄弟合并
        else {
            for (int i = oldNodeRt->removeIndex; i < oldNode->dataLength; i++) oldNode->data[i] = oldNode->data[i + 1];

            // parent 拉一个数据下来
            oldNode->data[oldNode->dataLength] = parent->data[oldNodeIndexInParent];

            // 把 rightBrother 的数据移动过来
            for (int i = 0; i <= rightBrother->dataLength; i++) {
                if (i < rightBrother->dataLength) oldNode->data[i + oldNode->dataLength + 1] = rightBrother->data[i];

                // 如果不是叶子结点，还要把 children 移动过来
                if (!oldNode->isLeaf) {
                    rightBrother->children[i]->parent = oldNode;
                    oldNode->children[i + oldNode->dataLength + 1] = rightBrother->children[i];
                    rightBrother->children[i] = NULL;
                }
            }
            oldNode->dataLength += 1 + rightBrother->dataLength;

            // 删除 rightBrother
            free(rightBrother);
            rightBrother = NULL;
        }

        // 因为删除了一个 children， 所以 parent 的 children 也要变动
        for (int i = oldNodeIndexInParent; i < parent->dataLength; i++) parent->children[i] = parent->children[i + 1];
        parent->children[parent->dataLength--] = NULL;

        if (hasLeftBrother) oldNodeRt->node = parent->children[oldNodeIndexInParent];

        // parent 的 children 吃力完毕，data 等递归回到 parent 再处理
        oldNodeRt->removeIndex = hasLeftBrother ? oldNodeIndexInParent - 1 : oldNodeIndexInParent;
    }


    return oldNodeRt;
}

RemoveType* removeBT(BTree &t, int data, int childrenIndexInParent, bool isBehindNext, bool needSwap = false) {
    RemoveType *rt = NULL;

    if (t == NULL) {
        rt = (RemoveType*)malloc(sizeof(RemoveType));
        rt->node = NULL;
        return rt;
    }

    if (t->isLeaf) {
        rt = (RemoveType*)malloc(sizeof(RemoveType));
        rt->node = t;

        if (isBehindNext) {
            rt->behindNextData = t->data[0];
            rt->removeIndex = 0;
            t->dataLength--;

            return mergeBT(rt, childrenIndexInParent, needSwap);;
        }

        int pos;
        for (pos = 0; pos < t->dataLength; pos++) if (t->data[pos] == data) break;

        // 没有要删除的数据
        if (pos >= t->dataLength) return rt;
        // 开始删除
        else {
            rt->removeIndex = pos;
            t->dataLength--;
        }
    }
    else {
        if (!isBehindNext) {
            int pos = findPos(t, data);

            if (pos < t->dataLength && t->data[pos] == data) {
                // 中序替换
                rt = removeBT(t->children[pos + 1], data, pos + 1, true, true);
                t->children[pos + 1] = rt->node;
            }
            else {
                rt = removeBT(t->children[pos], data, pos, false, false);
                t->children[pos] = rt->node;
            }
        }
        else {
            rt = removeBT(t->children[0], data, 0, true, false);
            t->children[0] = rt->node;
        }
    }

    rt->node = t;

    // 根结点处理
    BTreeNode *node = t;
    if (t->parent == NULL && node->dataLength <= 0 && node->children[0] != NULL) {
        node->children[0]->parent = -NULL;
        rt->node = t = node->children[0];
        rt->removeIndex = -1;
        free(node);
        node = NULL;
    }
    else rt = mergeBT(rt, childrenIndexInParent, needSwap);

    return rt;
}
// -----------------------------------------------------------------------------

// 整合 -------------------------------------------------------------------------
void operatorBT(BTree &t, int data, char type = 0) {
    RemoveType *rt = NULL;

    switch (type) {
    case 0:
        insertBT(t, data);
        break;
    case 1:
        rt = removeBT(t, data, 0, false);
        free(rt);
        break;
    case 2:
        rt = removeBT(t, data, 0, false);
        free(rt);
        insertBT(t, data);
        break;
    default: break;
    }
}
// ----------------------------------------------------------------------------

// 遍历
void visitBT(BTree t) {
    if (t == NULL) return;

    queue<BTreeNode*> q;
    q.push(t);

    while (!q.empty()) {
        BTreeNode *node = q.front();
        q.pop();

        for (int i = 0; i <= node->dataLength; i++) {
            if (i < node->dataLength) cout << node->data[i] << " ";
            if (node->children[i] != NULL) q.push(node->children[i]);
        }

        cout << endl;
    }
}

int main() {
    return 0;
}
```

（2）B+ 树

B 树的优化，与 B 树的区别：

* 所有的数据都放在叶子结点，叶子结点之间是一条双链表

* 非叶子结点存放子树中的最大值；B+ 树的数据量 = 分支树

* 有 root 指针可以二分查找；有 head 指针可以顺序查找

优点：

* B+ 树比 B 树数据更加集中，高度小一点

* B 树中找中序前驱和后继，需要递归，性能不不好，且排序也很麻烦；而 B+ 树只需要因为是双链表，只需要 O\(1\) 即可，排序也非常方便

* B 树还是由于找中序后继麻烦，所以查找一个范围内的数据性能差；而 B+ 树能快速查找一个范围内的数据，只需要 root 开始找到初始位置，再从双良表找到结束位置即可

数据库中，常用 B+ 树作为数据结构，叶子结点钟的每个数据即数据库中的索引，指向每一行数据；而非叶子结点事这些索引的索引。

## 3 树和森林

### 3.1 树、森林

（1）存储结构

双亲表示法，顺序结构：

```
typedef struct TreeNode {
    // parent 负数表示是根结点，负数的数值表示有几个结点
    int data, parent;
} TreeNode, *Tree;

Tree tree = (TreeNode*)malloc(sizeof(TreeNode) * 10);
```

孩子表示法，链式结构 \+ 链式结构：

n 个结点的数，需要 n 个元素的数据，加上 m 个孩子的 node 结点，如 3 层的满二叉树，就需要 7 个元素的数组，6 个孩子 node

```
// 用链表存储某结点的所有孩子的下标
typedef struct TreeChildNode {
    int index;
    struct TreeChildNode* child;
} TreeChildNode, *TreeChild;

typedef struct TreeNode {
    int data;
    TreeChild child;
} TreeNode;

TreeNode tree[10];
```

孩子兄弟表示法，链式结构，最常用：

```
typedef struct TreeNode {
    int data;
    struct TreeNode *child, *brother;
} TreeNode, *Tree;
```

（2）与二叉树之间的互相转换和遍历

互相转化，左孩子右兄弟法：

* 树的孩子/兄弟，是转化后的二叉树的左孩子/右孩子

* 二叉树的左孩子/右孩子，是转化后的树的孩子/兄弟

* 森林可以看成多个树的数组，各个树转化成二叉树后，把第一课树的根结点作为转化后的二叉树的根结点，第二课树作为第一棵树的右孩子，以此类推

* 二叉树转化成森林，先把二叉树分为多棵二叉树，每棵二叉树树再转化成树，构成森林

遍历：

* 树木：
  
  * 层序遍历
  
  * 先根遍历，相当于二叉树先序遍历
  
  * 后根遍历，相当于二叉树后序遍历

* 森林：
  
  * 先序遍历，相当于每颗树都是先根遍历
  
  * 中序遍历，相当于每颗树都是后根遍历

代码：

```
// struct 版

#include<iostream>
#include<vector>
using namespace std;

typedef struct TreeNode {
    int data;
    struct TreeNode *child, *brother;
} TreeNode, *Tree;

typedef struct BinTreeNode {
    int data;
    struct BinTreeNode *left, *right;
} BinTreeNode, *BinTree;

TreeNode* newNode(int data, TreeNode *child = NULL, TreeNode *brother = NULL) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->child = child;
    node->brother = brother;
    return node;
}

// 创建树
Tree createTree() {
    /*         1
         2     3      4
       5 6 7  8 9     10
    */
    Tree tree = newNode(1);

    tree->child = newNode(2);
    tree->child->brother = newNode(3);
    tree->child->brother->brother = newNode(4);

    tree->child->child = newNode(5);
    tree->child->child->brother = newNode(6);
    tree->child->child->brother->brother = newNode(7);

    tree->child->brother->child = newNode(8);
    tree->child->brother->child->brother = newNode(9);

    tree->child->brother->brother->child = newNode(10);

    return tree;
}

// 树、森林和二叉树之间互相转化 --------------------------------------------------------------
// 树 -> 二叉树
BinTree treeToBinTree(Tree t) {
    if (t == NULL)  return NULL;

    BinTreeNode *root = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    root->data = t->data;
    root->left = treeToBinTree(t->child);
    root->right = treeToBinTree(t->brother);

    return root;
}

// 二叉树 -> 树
Tree binTreeToTree(BinTree t) {
    if (t == NULL)  return NULL;

    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = t->data;
    root->child = binTreeToTree(t->left);
    root->brother = binTreeToTree(t->right);

    return root;
}

// 森林 -> 二叉树
BinTree forestToBinTree(const vector<Tree> &forest) {
    if (forest.empty())  return NULL;

    BinTreeNode *root = treeToBinTree(forest[0]);
    if (root == NULL)  return NULL;

    BinTreeNode *temp = root;
    for (int i = 1; i < forest.size(); i++) {
        temp->right = treeToBinTree(forest[i]);
        if (temp->right == NULL)  continue;
        else temp = temp->right;
    }

    return root;
}

//  二叉树 -> 森林
vector<Tree> binTreeToForest(BinTree t) {
    if (t == NULL) return vector<Tree>();

    vector<Tree> forest({ binTreeToTree(t) });

    Tree root = forest[0];
    while (root->brother != NULL) {
        forest.push_back(root->brother);
        root->brother = NULL;
        root = forest[forest.size() - 1];
    }

    return forest;
}

// 遍历 --------------------------------------------------------------------------------
/* 树的遍历
 * 先根遍历：等价于转化后二叉树的先序遍历
 * 后根遍历：等价于转化后二叉树的中序遍历
 * 没有中根遍历
 * 二叉树的后序遍历，等价于后根遍历中把孩子逆序
 */
// 先根遍历
void frontRoot(Tree t) {
    if (t == NULL) return;

    cout << t->data << " ";
    frontRoot(t->child);
    frontRoot(t->brother);
}

// 后根遍历
void behindRoot(Tree t) {
    if (t == NULL) return;

    behindRoot(t->child);
    cout << t->data << " ";
    behindRoot(t->brother);
}

/* 森林的遍历
 * 先序遍历：每棵树依次进行先根遍历
 * 中序遍历：每棵树依此进行后根遍历
 */
// 森林的先序遍历
void frontForest(const vector<Tree> &forest) {
    for (int i = 0; i < forest.size(); i++)  frontRoot(forest[i]);
}

// 森林的中序遍历
void midForest(const vector<Tree> &forest) {
    for (int i = 0; i < forest.size(); i++)  behindRoot(forest[i]);
}

int main() {
    Tree t = createTree();
    vector<Tree> f({ t,t });
    BinTree bt = forestToBinTree(binTreeToForest(forestToBinTree(f)));;


    midForest(f);
    cout << endl;
    frontForest(f);

    return 0;
}
```

### 3.2 并查集

集合结构，每个集合是一棵树，多个集合构成一个森林。

并查集通常用双亲表示法的存储结构，实现的操作有：

* 并：合并两个集合，只需要把 b 集合的根结点作为 a 集合新的孩子即可，为了保证树的高度尽量矮，应该把高度小的树连接上高度高的树。

* 查：查询元素在哪一个集合，只需要看往上找到根结点即可，为了优化性能，可以在查询的过程中，把结点都连接到根结点，降低树的高度

* 若并和查都采用了上述的优化方法，查询的时间复杂度优化前后：O\(n2\) -> O\(nlogn\) -> O\(n \* a\) ，a 是一个小常数

```
#include<iostream>
#include<vector>
using namespace std;

typedef struct USSetNode {
    // parent 负数表示是根结点，数值表示有几个结点
    int data, parent;
} USSetNode, *USSet;

// 创建并查集
pair<USSet, int> createUSSet(const vector<int> &list) {
    if (list.empty())  return pair<USSet, int>(NULL, 0);

    int len = list.size();
    USSet s = (USSetNode*)malloc(sizeof(USSetNode) * len);

    for (int i = 0; i < len; i++) {
        s[i].data = list[i];
        s[i].parent = -1;
    }

    return pair<USSet, int>(s, len);
}

// 查
int find(USSet s, int index) {
    int rootIndex = index;
    while (s[rootIndex].parent > -1)  rootIndex = s[rootIndex].parent;

    // 优化
    while (index != rootIndex) {
        int tempIndex = s[index].parent;
        s[index].parent = rootIndex;
        index = tempIndex;
    }

    return rootIndex;
}

// 并
bool uni(USSet s, int aIndex, int bIndex) {
    if (aIndex == bIndex)  return false;

    int aRootIndex = find(s, aIndex), bRootIndex = find(s, bIndex);
    // 小树连接上大树，负数越小，结点越多
    if (s[aRootIndex].parent <= s[bRootIndex].parent) {
        s[aRootIndex].parent += s[bRootIndex].parent;
        s[bRootIndex].parent = aRootIndex;
    }
    else {
        s[bRootIndex].parent += s[aRootIndex].parent;
        s[aRootIndex].parent = bRootIndex;
    }

    return true;
}

int main() {
    vector<int> list({ 1,2,3,4,5,6 });

    pair<USSet, int> uss = createUSSet(list);
    USSet s = uss.first;
    int len = uss.second;

    uni(s, 3, 5);
    uni(s, 3, 0);
    uni(s, 4, 0);

    for (int i = 0; i < len; i++) {
        cout << i << "->" << s[i].parent << " ";
    }

    return 0;
}
```

# 三、图

图由于顶点集 V 和边集 E 构成，顶点的个数是图的阶数。图不能是空图，即 V 不能为空，但是 E 可以为空。

子图：子 V 和子 E 组成

生成子图：包含原图所有 V 的子图

分类：

* 是否有方向：无向图、有向图。
  
  * 无向图的边叫无向边，也叫边，用小括号表示，在存储时需要存两份，
  
  * 有向图的边叫有向边，也叫弧（弧尾顶点 -\> 弧头顶点），用尖括号表示，分为出边和入边，存储时出边和入边需要各存一份

* 边是否有权值：无权图、带权图（也叫网），权值：
  
  * 0：表示 V -\> V ，可以是顶点自身，也可以是顶点自身形成了回路
  
  * 无穷：表示两个顶点之间没有边，通常用数据类型的最大值表示无穷，无穷计算时注意需要考虑二进制位上溢出的问题

* 是否复杂：简单图，无重复边且无自己到自己的环；反之是多重图

* 完全图：
  
  * 无向完全图：任意两个顶点之间都有边
  
  * 有向完全图：任意两个顶点都有方向相反的边

* 边的数量：稀疏图、稠密图

* 是否连通：
  
  * 非连通图：所有顶点不完全连在一起，会形成 n 个子图，连通分量为 n
  
  * 连通图：所有顶点连在一起，连通分量为 1，至少会有 n - 1 条边
    
    * 子图能包含所有顶点，且连通的叫极小连通子图，也叫生成树
  
  * 强连通图：有向图从任意顶点触发，所有顶点连在一起，连通分量为 1，至少有 n 条边
    
    * 子图中能够做多强连通的几个顶点形成极大连通子图

顶点的度：

* 有向图分为出度和入度，分别等于出边数和入边数，顶点的度 = 出度 + 入度，且出度和 = 入度和

* 无向图顶点的度 = 边数 \* 2

路径：多个顶点连城的一条路径：

* 无向图的路径没有方向

* 有向图的路径有方向

* 回路：也叫环，路径形成了回路，无向图没有方向，而有向图的回路有方向
  
  * 简单路径：路径序列中所有顶点不重复
  
  * 简单回路：除第一个顶点和最后一个顶点外，其他顶点不重复

* 路径长度：无权图的路径长度 = 边数

* 带权路径长度：带权图中某条路径的边权值之和

* 顶点之间的距离：两个顶点最短的路径长度，若没有路径，就用无穷表示

## 1 存储结构

### 1.1 邻接矩阵

顺序存储，空间复杂度 O\(V ^ 2\) ：

* 无向图是对称矩阵，可以压缩存储；有向图则不行

* 不适合存储边很少的图，是一个稀疏矩阵，浪费空间

```
// struct 版

#include<iostream>
#include<vector>
using namespace std;

/* 邻接矩阵
 * vertex：一维数组，顶点集，这里顶点存放字母，所以用 char
 * edge：二维数组，边集
   * 无权图中用 0 表示没有边，1 表示有，可以用 bool，如：
     {{0, 1, 1},
      {1, 0, 1},
      {1, 1, 0}}
   * 带权图中，数字表示权值，0 表示自己连自己的边，无穷大表示没有边（无穷大可以用数据类型的最大值表示，如 char 的 127）
     {{0, 2, 3},
      {2, 0, 4},
      {3, 4, 0}}
   * 无向图是一个对称矩阵
     {{0, 1, 1},
      {1, 0, 1},
      {1, 1, 0}}
   * 有向图是一个普通矩阵，只有各个顶点都有互相出入的边才会成为对称矩阵
     {{0, 1, 1},
      {0, 0, 1},
      {1, 0, 0}}
 */
typedef struct MartixGraph {
    int vexSize;
    char *vertex;
    bool **edge;
} MartixGraph;

// 初始化
bool initMartixGraph(MartixGraph *&g, vector<char> v) {
    if (g != NULL) return false;

    g = (MartixGraph*)malloc(sizeof(MartixGraph));
    g->vexSize = v.size();
    g->vertex = (char*)malloc(sizeof(char) * v.size());
    g->edge = (bool**)malloc(sizeof(bool*) * v.size());

    for (int i = 0; i < v.size(); i++) {
        g->vertex[i] = v[i];
        g->edge[i] = (bool*)malloc(sizeof(bool) * v.size());
        for (int j = 0; j < v.size(); j++) g->edge[i][j] = 0;
    }

    return true;
}

// 插入、删除边
bool operatorEdge(MartixGraph* g, int i, int j, bool type = false) {
    if (g == NULL || i >= g->vexSize || j >= g->vexSize || i < 0 || j < 0) return false;

    // 插入
    if (!type) g->edge[i][j] = g->edge[j][i] = 1;
    // 删除
    else g->edge[i][j] = g->edge[j][i] = 0;

    return true;
}

/* 插入、删除顶点
 * 插入：吃石化时可以 init 预留多余空间；不然每次插入都要重新 malloc 内存
 * 删除：可以在 struct 定义一个 bool 表示是否删除，删除设为 true ，插入设为 false；不然每次删除往前都要移动后面的元素
 */

 /* 求某个顶点的度数，type 为：
  * false：无向图的读，有向图的出度
  * true：有向图的入度
  * 检查是否存在边，获取权值，这些操作都差不多，就不写了
  */
int getDegree(MartixGraph* g, int vertex, bool type = false) {
    int sum = 0;

    for (int i = 0; i < g->vexSize; i++) {
        if (!type && g->edge[vertex][i]) ++sum;
        else if (type && g->edge[i][vertex]) ++sum;
    }

    return sum;
}

// 打印图
void print(MartixGraph *g) {
    if (g == NULL) return;

    for (int i = 0; i < g->vexSize; i++) {
        for (int j = 0; j < g->vexSize; j++) cout << g->edge[i][j] << " ";
        cout << endl;
    }
}

int main() {
    MartixGraph* g = NULL;

    initMartixGraph(g, vector<char>({ 'A','B','C','D' }));
    operatorEdge(g, 3, 0);

    cout << getDegree(g, 3) << endl;

    print(g);

    return 0;
}
```

此外，矩阵的 n 次方运算得到的新矩阵，其中的每个元素的值表示 i 到 j 有几个长度为 n 的路径。

### 1.2 邻接表

顺序存储 \+ 链式存储，和树的孩子表示法类似，因为树其实就是一个有向图。

空间复杂度：

* 无向图：O\(V \+ 2 \* E\) ，因为同一条边需要两个顶点各存一份

* 有向图：O\(V \+ E\)

比起临街矩阵，空间复杂度更小，但缺点就是找入边要遍历其他各个顶点，效率不高。

以不带权的无向图为例：

```
// struct 版

#include<iostream>
#include<vector>
using namespace std;

/* 邻接表
 * 顺序存储各个顶点
 * 每个顶点用链表存储和这个顶点相连的各个顶点的边
 */
typedef struct EdgeNode {
    // 可以加入权值的变量
    // 出边，存储相连顶点的 index
    int outIndex;
    EdgeNode* next;
} EdgeNode;

typedef struct VertexNode {
    char vexName;
    EdgeNode *head;
} VertexNode;

typedef struct TableGraph {
    int vexSize;
    VertexNode *vertex;
} TableGraph;

// 初始化
bool initTableGraph(TableGraph *&g, vector<char> v) {
    if (g != NULL) return false;

    g = (TableGraph*)malloc(sizeof(TableGraph));
    g->vexSize = v.size();
    g->vertex = (VertexNode*)malloc(sizeof(VertexNode) * v.size());

    for (int i = 0; i < v.size(); i++) {
        g->vertex[i].vexName = v[i];
        g->vertex[i].head = NULL;
    }

    return true;
}

// 插入、删除边
bool operatorEdge(TableGraph *g, int i, int j, bool type = false) {
    if (g == NULL || i >= g->vexSize || j >= g->vexSize || i < 0 || j < 0) return false;

    // 插入，头插法
    if (!type) {
        EdgeNode *e1 = (EdgeNode*)malloc(sizeof(EdgeNode));
        EdgeNode *e2 = (EdgeNode*)malloc(sizeof(EdgeNode));
        e1->outIndex = j;
        e2->outIndex = i;

        e1->next = g->vertex[i].head;
        e2->next = g->vertex[j].head;
        g->vertex[i].head = e1;
        g->vertex[j].head = e2;
    }
    // 删除
    else {
        EdgeNode *e1 = g->vertex[i].head, *e2 = g->vertex[j].head, *e1Pre = NULL, *e2Pre = NULL;

        while (e1 != NULL) {
            if (e1->outIndex == j) {
                if (e1Pre == NULL) g->vertex[i].head = e1->next;
                else e1Pre->next = e1->next;

                break;
            }

            e1Pre = e1;
            e1 = e1->next;
        }

        if (e1 == NULL) return false;

        free(e1);
        while (e2 != NULL) {
            if (e2->outIndex == i) {
                if (e2Pre == NULL) g->vertex[j].head = e2->next;
                else e2Pre->next = e2->next;

                free(e2);
                break;
            }

            e2Pre = e2;
            e2 = e2->next;
        }
    }

    return true;
}

/* 插入、删除顶点
 * 插入：吃石化时可以 init 预留多余空间；不然每次插入都要重新 malloc 内存
 * 可以在 struct 定义一个 bool 表示是否删除，删除设为 true ，插入设为 false；不然每次删除往前都要移动后面的元素
 */

/* 检查是否存在边，获取权值，这些操作都差不多，就不写了
 * 找入边比较麻烦，需要遍历各个顶点的链表
 */

int main() {
    TableGraph *g = NULL;
    initTableGraph(g, vector<char>({ 'A','B','C','D' }));

    operatorEdge(g, 0, 1);
    operatorEdge(g, 0, 2);
    operatorEdge(g, 2, 1);
    print(g);
    cout << endl;

    operatorEdge(g, 0, 1, true);
    print(g);
    cout << endl;

    return 0;
}
```

逆邻接表：存储的是入边，也就是找出边麻烦。

### 1.3 十字链表

相当于邻接表 \+ 逆邻接表的结合。

只适用于有向图，空间复杂度 O\(V \+ E\) 

邻接表的优化，新增一个入边的链表，使查找入边非常方便。

```
// struct 版

#include<iostream>
#include<vector>
using namespace std;

/* 十字链表
 * outIndex：出边指向的顶点 index
 * inIndex：入边指向的顶点 index
 */
typedef struct EdgeNode {
    int outIndex, inIndex;
    EdgeNode *outNext, *inNext;
} EdgeNode;

typedef struct VertexNode {
    char vexName;
    EdgeNode *outHead, *inHead;
} VertexNode;

typedef struct Orthogonal {
    int vexSize;
    VertexNode *vertex;
} Orthogonal;

// 初始化
bool initOrthogonal(Orthogonal *&g, vector<char> v) {
    if (g != NULL || v.empty()) return false;

    g = (Orthogonal*)malloc(sizeof(Orthogonal));
    g->vexSize = v.size();
    g->vertex = (VertexNode*)malloc(sizeof(VertexNode) * v.size());

    for (int i = 0; i < v.size(); i++) {
        g->vertex[i].vexName = v[i];
        g->vertex[i].outHead = NULL;
        g->vertex[i].inHead = NULL;
    }

    return true;
}

// 插入、删除边
bool operatorEdge(Orthogonal *g, int i, int j, bool type = false) {
    if (g == NULL || i >= g->vexSize || j >= g->vexSize || i < 0 || j < 0) return false;

    // 插入，头插法，插入出边的同时也要给链接的顶点插入入边，但为了节省空间，只用一个 node
    // 可以加入重复边的判断，不过效率会变低
    if (!type) {
        EdgeNode *node = (EdgeNode*)malloc(sizeof(EdgeNode));
        node->outIndex = j;
        node->inIndex = i;

        node->outNext = g->vertex[i].outHead;
        node->inNext = g->vertex[j].inHead;

        g->vertex[i].outHead = node;
        g->vertex[j].inHead = node;
    }
    // 删除
    else {
        EdgeNode *outNode = g->vertex[i].outHead, *inNode = g->vertex[j].inHead, *outPre = NULL, *inPre = NULL;

        // 删除出边
        while (outNode != NULL) {
            if (outNode->outIndex == j) {
                if (outPre == NULL) g->vertex[i].outHead = outNode->outNext;
                else outPre->outNext = outNode->outNext;

                break;
            }

            outPre = outNode;
            outNode = outNode->outNext;
        }

        if (outNode == NULL) return false;

        // 删除入边
        while (inNode != NULL) {
            if (inNode == outNode) {
                if (inPre == NULL) g->vertex[j].inHead = inNode->inNext;
                else inPre->inNext = inNode->inNext;

                // 因为此时 inNode == outNode，所以 free 一个就行
                free(inNode);
                break;
            }

            inPre = inNode;
            inNode = inNode->inNext;
        }
    }

    return true;
}

void print(Orthogonal *g) {
    if (g == NULL) return;

    for (int i = 0; i < g->vexSize; i++) {
        cout << g->vertex[i].vexName << ": ";
        cout << endl << "out: ";

        EdgeNode *outHead = g->vertex[i].outHead, *inHead = g->vertex[i].inHead;
        while(outHead != NULL) {
            cout << outHead->outIndex << " ";
            outHead = outHead->outNext;
        }
        cout << endl << "in: ";

        while (inHead != NULL) {
            cout << inHead->inIndex << " ";
            inHead = inHead-> inNext;
        }
        cout << endl;
    }
}

int main() {
    Orthogonal *g = NULL;
    initOrthogonal(g, vector<char>({ 'A','B','C','D' }));

    operatorEdge(g, 0, 1);
    operatorEdge(g, 0, 2);
    operatorEdge(g, 1, 2);

    print(g);

    return 0;
}
```

### 1.4 邻接多重表

只能存储无向图，空间复杂度 O\(V \+ E\)，类似于十字链表，区别只是：

* 十字链表每个顶点有两条链表，分别指向出边和入边；邻接多重表只有一条链表，不过边 struct 一样有两个方向

* 在遍历链表的时候，每个 node 都需要判断初始顶点是否是该顶点，才能决定走哪一个方向

```
// struct 版

#include<iostream>
#include<vector>
using namespace std;

/* 邻接多重表
 * outIndex：结束顶点
 * inIndex：初始顶点
 */
typedef struct EdgeNode {
    int outIndex, inIndex;
    EdgeNode *outNext, *inNext;
} EdgeNode;

typedef struct VertexNode {
    char vexName;
    EdgeNode *head;
} VertexNode;

typedef struct MultipleTable {
    int vexSize;
    VertexNode *vertex;
} Multiple;

// 初始化
bool initMultipleTable(MultipleTable *&g, vector<char> v) {
    if (g != NULL || v.empty()) return false;

    g = (MultipleTable*)malloc(sizeof(MultipleTable));
    g->vexSize = v.size();
    g->vertex = (VertexNode*)malloc(sizeof(VertexNode) * v.size());

    for (int i = 0; i < v.size(); i++) {
        g->vertex[i].vexName = v[i];
        g->vertex[i].head = NULL;
    }

    return true;
}

// 插入、删除边
bool operatorEdge(MultipleTable *g, int i, int j, bool type = false) {
    if (g == NULL || i >= g->vexSize || j >= g->vexSize || i < 0 || j < 0) return false;

    // 插入
    // 可以加入重复边的判断，但是效率会变低，此外，无向图 i,j 和 j,i 也属于重复，这里就不判断了
    if (!type) {
        EdgeNode *node = (EdgeNode*)malloc(sizeof(EdgeNode));
        node->outIndex = j;
        node->inIndex = i;

        node->outNext = g->vertex[i].head;
        node->inNext = g->vertex[j].head;

        g->vertex[i].head = node;
        g->vertex[j].head = node;
    }
    // 删除
    else {
        EdgeNode *outNode = g->vertex[i].head, *inNode = g->vertex[j].head, *outPre = NULL, *inPre = NULL;
        bool isOut, preIsOut;

        // 删除这个顶点的边
        // 删除 i,j 和 j,i 都有效，因为属于同一个边
        while (outNode != NULL) {
            if (outNode->outIndex == j && outNode->inIndex == i ||
                outNode->inIndex == j && outNode->outIndex == i) {
                isOut = i == outNode->inIndex;

                if (outPre == NULL) {
                    if (isOut) g->vertex[i].head = outNode->outNext;
                    else g->vertex[i].head = outNode->inNext;
                }
                else {
                    EdgeNode *next = isOut ? outNode->outNext : outNode->inNext;
                    if (preIsOut) outPre->outNext = next;
                    else outPre->inNext = next;
                }

                break;
            }

            outPre = outNode;
            preIsOut = i == outPre->inIndex;
            outNode = preIsOut ? outNode->outNext : outNode->inNext;
        }

        if (outNode == NULL) return false;

        // 删除另一个顶点的边
        while (inNode != NULL) {
            if (inNode == outNode) {
                isOut = j == inNode->inIndex;

                if (inPre == NULL) {
                    if (isOut) g->vertex[j].head = inNode->outNext;
                    else g->vertex[j].head = inNode->inNext;
                }
                else {
                    EdgeNode *next = isOut ? inNode->outNext : inNode->inNext;
                    if (preIsOut) inPre->outNext = next;
                    else inPre->inNext = next;
                }

                // 因为此时 inNode == outNode，所以 free 一个就行
                free(inNode);
                break;
            }

            inPre = inNode;
            preIsOut = j == inPre->inIndex;
            inNode = preIsOut ? inNode->outNext : inNode->inNext;
        }
    }

    return true;
}

void print(MultipleTable *g) {
    if (g == NULL) return;

    for (int i = 0; i < g->vexSize; i++) {
        cout << g->vertex[i].vexName << ": ";
        EdgeNode *head = g->vertex[i].head;
        while (head != NULL) {
            bool isOut = i == head->inIndex;
            cout << (isOut ? "o->" : "i->") << (isOut ? head->outIndex : head->inIndex) << " ";
            head = isOut ? head->outNext : head->inNext;
        }
        cout << endl;
    }
}

int main() {
    MultipleTable *g = NULL;
    initMultipleTable(g, vector<char>({ 'A','B','C','D' }));

    operatorEdge(g, 0, 1);
    operatorEdge(g, 0, 2);
    operatorEdge(g, 1, 2);
    operatorEdge(g, 3, 1);
    print(g);
    cout << endl;

    operatorEdge(g, 1, 0, true);
    operatorEdge(g, 1, 3, true);
    operatorEdge(g, 0, 2, true);
    operatorEdge(g, 1, 2, true);
    print(g);
    cout << endl;

    return 0;
}
```

## 2 遍历

遍历方式：

* 广度优先遍历 BFS ：类似于树的层序遍历，因为树就是一个图。思想是从一个顶点触发，向周围扩散：
  
  * 空间复杂度：bool 数组 \+ queue ，总体是 O\(V\)
  
  * 时间复杂度：邻接矩阵 O\(V ^ 2\) ，邻接表 O\(V + E\)

* 深度优先遍历 DFS ：类似树的先序、中序、后序遍历。思想是从一个顶点触发，优先访问最深处的顶点：
  
  * 空间复杂度：bool 数组 + 递归深度 ，总体是 O\(V\)
  
  * 时间复杂度：邻接矩阵 O\(V ^ 2\) ，邻接表 O\(V \+ E\)

注意事项：

* 为了防止重复遍历同一个顶点，用一个 bool 数组存储某顶点是否已遍历。

* 无向图可能不是连通图，有向图可能不是强连通图，所以 BFS ，DFS 都有可能不止执行一次，因此需要 for 遍历顶点，false 就遍历

* 从不同的顶点开始，可以得到不同的遍历序列

不同存储结构的遍历在实现上思路上差不多，但实现方式多种多样，为了方便，就以二维数组为例，注意要考虑有环的图：

```
// struct 版

#include<iostream>
#include<queue>
using namespace std;

char vertex[3] = { 'A','B','C' };

int g[3][3] = {
    {0,1,0},
    {0,0,1},
    {1,0,0},
};

void BFS(int g[][3], bool isVisited[], int n, int start) {
    queue<int> q;
    q.push(start);
    isVisited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        cout << vertex[node] << " ";
        q.pop();

        for (int i = 0; i < n; i++) {
            if (g[node][i] == 1 && !isVisited[i]) {
                q.push(i);
                isVisited[i] = true;
            }

        }
    }

}

void DFS(int g[][3], bool isVisited[], int n, int start, int next = -1) {
    // 从 start 顶点开始
    isVisited[next < 0 ? start : next] = true;

    for (int i = 0; i < n; i++) {
        if (g[next < 0 ? start : next][i] == 1 && !isVisited[i]) {
            DFS(g, isVisited, n, start, i);
            cout << vertex[i] << " ";
        }
    }

    if (next < 0) cout << vertex[start] << " ";
}

void visit(int g[][3], int n, bool type = false) {
    bool *isVisited = (bool*)malloc(sizeof(bool) * n);
    for (int i = 0; i < n; i++) isVisited[i] = false;

    for (int i = 0; i < n; i++) {
        if (!isVisited[i]) {
            if (!type) BFS(g, isVisited, n, i);
            else DFS(g, isVisited, n, i);
        }
    }

    free(isVisited);

    cout << endl;
}

int main() {
    cout << "BFS: ";
    visit(g, 3);
    cout << "DFS: ";
    visit(g, 3, true);
    return 0;
}
```

## 3 应用

### 3.1 最小生成树 MST

MST 是一个带权无向连通图。

生成树：

* 一个无向l连通图中，若有一个子图包含全部顶点，且边 = V \- 1 ，那么这个子图就是该无向连通图的生成树，生成树可能不止一个

* 一个无向图，若不连通，则只会有生成森林

* BFS ，DFS 会得到对应的生成树、生成森林

最小生成树：

* 一个带权无向连通图中，权值之和最小的生成树就是最小生成树，可能不止一个

* 妥若带权无向连通图没有环，则最小生成树就是它本身

算法：

* Prim 算法（普雷姆）：
  
  * 从任意顶点开始构造生成树 t ，每次找到距离 t 权值最小的 edge 并把对应的顶点加入 t ，直到全部顶点加入到 t 。
  
  * 时间复杂度：O\(V ^ 2\) ，适合边多的图。

* Kruskal 算法（克鲁斯卡尔）：
  
  * 每次从未选取的，权值最小且至少有一个顶点未加入 t 的边，将未加入的顶点加入 t ，直到所有顶点加入 t 。
  
  * 时间复杂度：O\(E \* logE\) ，适合边少的图。适合邻接表、邻接多重表

代码：

```
// struct 版

#include<iostream>
#include<vector>
#include<Algorithm>
using namespace std;

#define MAX_NUM 65535 * 65535

unsigned int g[5][5] = {
    {0,3,2,4,MAX_NUM},
    {3,0,5,8,6},
    {2,5,0,1,MAX_NUM},
    {4,8,1,0,7},
    {MAX_NUM,6,MAX_NUM,7,0}
};

// Prim ------------------------------------------------------------------------------
/* Prim
 * 需要三个辅助数组
   * isReday：是否已经加入生成树
   * cost：生成树到各个顶点的最小权值边，MAX_NUM 为无穷，表示两个顶点没有边
   * start：链接该顶点的初始顶点
 * 从任意顶点开始，设为 true
 * 遍历这个顶点的各个边，若有到另一个顶点的权值小于生成树原来到这个顶点的权值，就记录在 cost ，并修改 start
 * 在上面的遍历过程的同时找到最小权值，并确定下一个顶点，设为 true
 */
unsigned int Prim(unsigned int g[][5], unsigned int n, unsigned int startVex) {
    if (n < 1 || n > 5) return 0;

    unsigned int sum = 0, nextVex = startVex;

    bool *isReady = (bool*)malloc(sizeof(bool) * n);
    unsigned int *cost = (unsigned int*)malloc(sizeof(unsigned int) * n);
    unsigned int *start = (unsigned int*)malloc(sizeof(unsigned int) * n);

    // 初始化
    for (int i = 0; i < n; i++) {
        isReady[i] = false;
        cost[i] = MAX_NUM;
        start[i] = startVex;
    }

    // 开始
    isReady[nextVex] = true;
    cost[nextVex] = 0;
    for (int i = 0; i < n - 1; i++) {
        // 遍历的过程中就找最小权值，确定下一个顶点
        unsigned int tempMin = MAX_NUM, minIndex = nextVex;

        for (int j = 0; j < n; j++) {
            // 如果该顶点还未加入生成树
            if (!isReady[j]) {
                // 如果有生成树到该顶点更小权值的边，就记录下来
                if (g[nextVex][j] < cost[j]) {
                    cost[j] = g[nextVex][j];
                    start[j] = nextVex;
                }

                // 找最小权值
                if (cost[j] < tempMin) {
                    tempMin = cost[j];
                    minIndex = j;
                }
            }
        }

        // 找到了此次要找的边
        cout << start[minIndex] << " -> " << minIndex << " cost: " << cost[minIndex] << endl;
        sum += cost[minIndex];

        isReady[minIndex] = true;
        nextVex = minIndex;
    }

    free(isReady);
    free(cost);
    free(start);

    return sum;
}
// ------------------------------------------------------------------------------

// Kruskal -------------------------------------------------------------------------
/* Kruskal ，适合邻接表，邻接矩阵回答道 O(n2)，这里用矩阵只是为了方便
 * 遍历所有边，每个边存储在 EdgeNode ，然后排序
 * 从小到大开始酒便利 EdgeNode 数组，若 startVex 、endVex 其中有一个未加入并查集，就可以加入
 */

// 存储边的信息
typedef struct EdgeNode {
    unsigned int cost, startVex, endVex;
} EdgeNode;

// 排序的比较函数
bool comp(EdgeNode a, EdgeNode b) {
    return a.cost < b.cost;
}

// 并查集
typedef struct USSetNode {
    int data, parent;
} USSetNode;

// 查
int find(vector<USSetNode> &s, int index) {
    int rootIndex = index;
    while (s[rootIndex].parent > -1)  rootIndex = s[rootIndex].parent;

    while (index != rootIndex) {
        int tempIndex = s[index].parent;
        s[index].parent = rootIndex;
        index = tempIndex;
    }

    return rootIndex;
}

// 并
bool uni(vector<USSetNode> &s, int aIndex, int bIndex) {
    if (aIndex == bIndex)  return false;

    int aRootIndex = find(s, aIndex), bRootIndex = find(s, bIndex);

    if (s[aRootIndex].parent <= s[bRootIndex].parent) {
        s[aRootIndex].parent += s[bRootIndex].parent;
        s[bRootIndex].parent = aRootIndex;
    }
    else {
        s[bRootIndex].parent += s[aRootIndex].parent;
        s[aRootIndex].parent = bRootIndex;
    }

    return true;
}

unsigned int Kruskal(unsigned g[][5], int n) {
    if (n < 1 || n > 5) return 0;

    unsigned int sum = 0;
    vector<EdgeNode> arr;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] != 0 && g[i][j] != MAX_NUM) {
                EdgeNode node;
                node.cost = g[i][j];
                node.startVex = i;
                node.endVex = j;
                arr.push_back(node);
            }
        }
    }

    sort(arr.begin(), arr.end(), comp);

    vector<USSetNode> s;
    for (int i = 0; i < n; i++) {
        USSetNode usn;
        usn.data = i;
        usn.parent = -1;
        s.push_back(usn);
    }

    int root = find(s, arr[0].startVex);
    for (int i = 0; i < arr.size(); i++) {
        int v1 = find(s, arr[i].startVex);
        int v2 = find(s, arr[i].endVex);

        if (uni(s, root, v1) || uni(s, root, v2)) {
            sum += arr[i].cost;
            cout << v1 << " -> " << v2 << " cost: " << arr[i].cost << endl;

            if (s[root].parent <= -n) break;
        }
    }

    return sum;
}
// -----------------------------------------------------------------------------------

int main() {
    for (int i = 0; i < 5; i++) {
        cout << Prim(g, 5, i) << endl;
    }
    return 0;
}
```

### 3.2 最短路径

无向图、有向图均可，最短路基即带权路径长度最小。

分为：

* 单源最短路径：用 BFS 或 Dijkstra 求某个顶点到其他各个顶点的最短路径

* 各个顶点之间的最短路径：用 Floyd 求得，所有顶点都用单源最短路径求一遍也能得到各个顶点之间的最短路径

算法：

* BFS 实现：只适用于无权图，无权图的权值也可以看做是 1
  
  空间复杂度：O\(V\)  ，时间复杂度：O\(V ^ 2\)  或 O\(V \+ E\)

* Dijkstra 算法（迪杰斯特拉）：带权图、无权图均可，过程类似于 Prim 算法，只是在求 cost 数组中实现不同，缺点是无法处理有负数权值的图（但 Prim 可以处理负权值）。
  
  空间复杂度：O(V) ，时间复杂度：O(V ^ 2)

* Floyd 算法（弗洛伊德）：带权图、无权图均可，使用动态规划思想，可以处理负权值，但是无法处理有负权值的环。
  
  需要两个辅助矩阵
  
  * cost：存储各个顶点之间的最短路径
  
  * pre：各个顶点的直接前驱
  
  cost 初始时即邻接矩阵本身，两个顶点直接相连，pre 为 -1 ，之后每一次允许通过中间顶点相连。
  
  空间复杂度：O(V ^ 2) ，时间复杂度：O(V ^ 3) 

代码：

```
// struct 版

#include<iostream>
#include<vector>
#include<queue>
#include<Algorithm>
using namespace std;

#define MAX_NUM 65535 * 65535

unsigned int g[5][5] = {
    {0,3,2,4,MAX_NUM},
    {3,0,5,8,6},
    {2,5,0,1,MAX_NUM},
    {4,8,1,0,7},
    {MAX_NUM,6,MAX_NUM,7,0}
};

// 从 pre 还原路径 -------------------------------------------------------------------
void printArrPre(int pre[], int n, int start, int end, bool type = false) {
    if (start == end || start < 0 || end >= n) return;

    int p = pre[end];
    if (p != start && !type || p != -1 && type) {
        printArrPre(pre, n, start, p, type);
        cout << " -> " << end;

    }
    else cout << start << " -> " << end;

    return;
}
// -----------------------------------------------------------------------------------

// BFS 实现单源最短路径 ------------------------------------------------------------
/* 辅助数组
 * isVisited：防止重复遍历，因为是求单源最短路径，如果是非连通图也不用多次 BFS 了，直接设为无穷即可
 * cost：目前的最短路径
 * pre：直接前驱
 */
bool boolG[5][5] = {
    {0,1,0,0,0},
    {1,0,1,0,0},
    {0,1,0,1,1},
    {0,0,1,0,1},
    {0,0,1,1,0},
};

void BFSMinCost(bool g[][5], int n, int startVex) {
    queue<int> q;
    q.push(startVex);

    bool *isVisited = (bool*)malloc(sizeof(bool) * n);
    int *cost = (int*)malloc(sizeof(int) * n);
    int *pre = (int*)malloc(sizeof(int) * n);

    // 初始化
    for (int i = 0; i < n; i++) {
        isVisited[i] = false;
        cost[i] = MAX_NUM;
        pre[i] = -1;
    }
    isVisited[startVex] = true;
    cost[startVex] = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (g[v][i] && !isVisited[i]) {
                pre[i] = v;
                cost[i] = cost[pre[i]] + 1;
                q.push(i);
                isVisited[i] = true;

            }
        }
    }

    // 打印结果
    for (int i = 0; i < n; i++) {
        printArrPre(pre, n, startVex, i);
        if (i != startVex) cout << " cost: " << cost[i] << endl;
    }

    free(isVisited);
    free(cost);
    free(pre);
}
// -------------------------------------------------------------------------------

// Dijkstra ------------------------------------------------------------------------------
/* Dijkstra
 * 需要三个辅助数组
   * isReday：是否已经处理完毕
   * cost：目前的最短路径
   * pre：直接前驱
 * 每次从 nextVex 顶点找 isReady 为 false 的顶点 x ，若到 x 顶点的权值 + nextVex 的路径长度 < 原来记录 x 的那路径长度，就记录下来
 * 同时寻找路径长度最小的顶点，设为 true ，下一次从这个顶点开始
 */
void Dijkstra(unsigned int g[][5], unsigned int n, unsigned int startVex) {
    if (n < 1 || n > 5) return;

    unsigned int sum = 0, nextVex = startVex;

    bool *isReady = (bool*)malloc(sizeof(bool) * n);
    unsigned int *cost = (unsigned int*)malloc(sizeof(unsigned int) * n);
    int *pre = (int*)malloc(sizeof(int) * n);

    // 初始化
    for (int i = 0; i < n; i++) {
        isReady[i] = false;
        cost[i] = MAX_NUM;
        pre[i] = -1;
    }

    // 开始
    isReady[nextVex] = true;
    cost[nextVex] = 0;
    for (int i = 0; i < n - 1; i++) {
        // 遍历的过程中就找最小路径，确定下一个顶点
        unsigned int tempMin = MAX_NUM, minIndex = nextVex;

        for (int j = 0; j < n; j++) {
            // 如果该顶点还未处理
            if (!isReady[j]) {
                // 如果有更短的路径，就记录下来
                // unsigned int 最大值假发会丢失位，使得结果变小，所以要去掉
                if (g[nextVex][j] != MAX_NUM && (g[nextVex][j] + cost[nextVex] < cost[j])) {
                    cost[j] = g[nextVex][j] + cost[nextVex];
                    pre[j] = nextVex;
                }

                // 找最小权值
                if (cost[j] < tempMin) {
                    tempMin = cost[j];
                    minIndex = j;
                }
            }
        }

        isReady[minIndex] = true;
        nextVex = minIndex;
    }

    // 打印结果
    for (int i = 0; i < n; i++) {
        printArrPre(pre, n, startVex, i);
        if (i != startVex) cout << " cost: " << cost[i] << endl;
    }


    free(isReady);
    free(cost);
    free(pre);
}
// ------------------------------------------------------------------------------

// Floyd ------------------------------------------------------------------------
void Floyd(unsigned int g[][5], int n) {
    unsigned int cost[5][5];
    int pre[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cost[i][j] = g[i][j];
            pre[i][j] = -1;
        }
    }

    // 开始
    // 每次将 k 作为中间顶点
    for (int k = 0; k < n; k++) {
        // 遍历图
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (cost[i][k] == MAX_NUM || cost[k][j] == MAX_NUM) continue;
                if (cost[i][k] + cost[k][j] < cost[i][j]) {
                    cost[i][j] = cost[i][k] + cost[k][j];
                    pre[i][j] = k;
                }
            }
        }
    }

    // 打印结果
    for (int i = 0; i < n; i++) {
        cout << "vertex: " << i << endl;

        for (int j = 0; j < n; j++) {
            if (i != j) printArrPre(pre[i], n, i, j, true);
            cout << " cost: " << cost[i][j] << endl;
        }

        cout << endl;
    }
}
// -----------------------------------------------------------------------------

int main() {
    Dijkstra(g, 5, 0);
    cout << endl;
    BFSMinCost(boolG, 5, 4);
    cout << endl;

    cout << "-------------------------------------------------------" << endl << endl;
    Floyd(g, 5);
    return 0;
}
```

### 3.3 DAG 图

有向无环图。

（1）DAG 图描述表达式

二叉树可以表示一个算术表达式，二叉树本质上也是一个 DAG 图。

不过 DAG 图可以减少二叉树算术表达式重复的结点，如：

\(x \+ y\) \* \(\(x \+ y\) \- x\) 

二叉树：

```
        *
       / \
      /   \
     /     \
   |/       \|
   +         -
  / \       / \
|/   \|   |/   \|
x     y   +     y
         / \
       |/   \|
       x     y
```

DAG 图：

```
        *
       / \
      /   \
     /     \
   |/       \|
   +  <----  -
  / \       /
|/   \|    /
x     y <-|
```

算术表达式的二叉树和 DAG 图都可能不唯一。

（2）拓扑排序

若 DAG 图中的顶点表示一些活动，这个 DAG 图就成为了 AOV 网。

拓扑排序即在 AOV 网中，每次从入度为 0 的顶点开始去掉这个顶点，继续找下一个入度为 0 的顶点，直到点点全部消失为止，形成的一个顶点序列，拓扑排序可能不唯一。

逆拓扑排序，即反转的拓扑排序，每次从出度为 0 的顶点开始找。

代码：

```
// struct 版

#include<iostream>
#include<queue>
using namespace std;

char vertex[5] = { 'A','B','C','D','E' };

bool g[5][5] = {
    {0,1,0,0,0},
    {0,0,0,0,1},
    {0,0,0,1,0},
    {0,1,0,0,0},
    {0,0,0,0,1},
};

/* 方法一，拓扑、逆拓扑均可，以拓扑为例
 * 辅助数组：inEdgeSum 存储各个边的入度，res 存储拓扑排序序列 
 * 用现行结构存储入度为 0 的顶点，这里用队列
 * 若队列非空，出队，并把链接的顶点的入度都 - 1
 * 空间复杂度：O(V)
 * 时间复杂度：邻接矩阵 O(V ^ 2) ，邻接表 O(V + E)
 */
void TopoLogicalSort(bool g[][5], int n) {
    int *inEdgeSum = (int*)malloc(sizeof(int) * n);
    int *res = (int*)malloc(sizeof(int) * n);
    queue<int> vex;
    int cnt = 0;

    // 初始化
    for (int i = 0; i < n; i++) {
        inEdgeSum[i] = 0;

        bool hasInEdge = false;
        for (int j = 0; j < n; j++) {
            if (g[j][i]) {
                ++inEdgeSum[i];
                hasInEdge = true;
            }
        }

        if (!hasInEdge) vex.push(i);
    }

    // 开始
    while (!vex.empty()) {
        int v = vex.front();
        vex.pop();

        res[cnt++] = v;

        // 去掉了 v 顶点，要减少 v 链接的顶点的入度
        for (int i = 0; i < n; i++) {
            if (g[v][i]) {
                inEdgeSum[i]--;
                if (inEdgeSum[i] == 0) vex.push(i);
            }
        }
    }

    // 如果 cnt != n ，说明途中有环
    if (cnt != n) cout << "失败" << endl;
    else {
        for (int i = 0; i < n; i++) cout << vertex[res[i]] << " ";
        cout << endl;
    }

    free(inEdgeSum);
    free(res);
}

/* 方法二
 * 利用 DFS ，拓扑、逆拓扑均可，以逆拓扑为例（正拓扑只需要加一个辅助栈）
 *  这个算法也可以用来判断图中是否有环
 */
bool DFS(bool g[][5], bool isVisited[], bool lastIsVisited[], queue<int> &res, int n, int start, int next = -1) {
    bool isOK = true;

    // 从 start 顶点开始
    isVisited[next < 0 ? start : next] = true;

    for (int i = 0; i < n; i++) {
        if (g[next < 0 ? start : next][i] == 1) {
            /* 判断是否有环
             * 如果是强连通图。 只需一次 DFS ，就不用那么麻烦了，直接判断 isVisited[i] 是否是 true 即可
             * 但如果是非连通图，需要多次 DFS ，就需要记录上次 DFS 的顶点，防止错判
             */
            if (isVisited[i] && !lastIsVisited[i]) return false;
            else if (!isVisited[i]) {
                isOK = DFS(g, isVisited, lastIsVisited, res, n, start, i);
                res.push(i);
            }
        }
    }

    if (next < 0) res.push(start);

    return isOK;
}

void visit(bool g[][5], int n) {
    queue<int> res;
    bool isOK = false;

    bool *isVisited = (bool*)malloc(sizeof(bool) * n);
    bool *lastIsVisited = (bool*)malloc(sizeof(bool) * n);
    for (int i = 0; i < n; i++) {
        isVisited[i] = false;
        lastIsVisited[i] = false;
    }

    for (int i = 0; i < n; i++) {
        if (!isVisited[i]) {
            isOK = DFS(g, isVisited, lastIsVisited, res, n, i);
            for (int k = 0; k < n; k++) lastIsVisited[k] = isVisited[k];

            if (!isOK) {
                cout << "失败" << endl;
                return;
            }
        }
    }

    while (!res.empty()) {
        cout << vertex[res.front()] << " ";
        res.pop();
    }

    free(isVisited);
    free(lastIsVisited);

    cout << endl;
}

int main() {
    TopoLogicalSort(g, 5);
    visit(g, 5);

    return 0;
}
```

（3）关键路径

AOE 网，每条边表示一个活动，边的权值表示完成这个活动的时间开销；顶点表示某个瞬间的事件。

* 只有完成一个顶点的事件，才能开始这个顶点出边的活动；只有所有入边的活动完成了，才能开始汇入的顶点的事件

* 从同一个顶点出来的活动可以同时进行

* AOE 网有且只有一个入度为 0 的顶点，叫做开始顶点（源点）；有且只有一个结束顶点（汇点）

从开始顶点到结束顶点，带权路径长度最大的路径，就是关键路径：

* 关键路径长度：完成整个工程所需要的最少时间

* 关键活动：关键路径上的活动，延长关键活动的时间就会延长整个工程的完成时间；减少关键活动的时间就会减少整个工程的时间，不过减少到一定程度可能会变成非关键活动

* 可能会有多条关键路径
  
  * 延长当个关键路径上的活动，就会变成只有一条关键路径
  
  * 减少关键活动的时间，就会变成非关键路径
  
  * 若想保持多条关键路径，可以延长/减少这几条关键路径共荣的关键活动的时间

求关键路径，找到所有时间余量为 0 的活动即可：

* 事件的最早发生时间：源点默认为 0 ，其余顶点 = 前一个顶点的最早发发生间 + 边权值，若有多条路径，则取最大值

* 活动的最早开始时间：= 弧尾顶点的最早发生时间

* 事件的最晚发生时间：汇点默认 = 汇点的最早发生时间 ，其余顶点 = 后一个顶点的最晚发发生间 - 边权值，若有多条路径，则取最小值

* 活动的最迟开始时间：= 弧尾顶点的最晚发生时间

* 时间余量：= 活动的最迟开始时间 - 活动的最早开始时间

代码：

```
// struct 版

#include<iostream>
#include<queue>
using namespace std;

#define MAX_NUM 65535 * 65535

char vertex[5] = { 'A','B','C','D','E' };

unsigned int g[5][5] = {
    {0,5,3,4,MAX_NUM},
    {MAX_NUM,0,MAX_NUM,MAX_NUM,2},
    {MAX_NUM,1,0,MAX_NUM,MAX_NUM},
    {MAX_NUM,MAX_NUM,MAX_NUM,0,2},
    {MAX_NUM,MAX_NUM,MAX_NUM,MAX_NUM,0},
};

// 拓扑排序
bool TopoLogicalSort(unsigned int g[][5], int n, int res[]) {
    int *inEdgeSum = (int*)malloc(sizeof(int) * n);
    queue<int> vex;
    int cnt = 0;

    // 初始化
    for (int i = 0; i < n; i++) {
        inEdgeSum[i] = 0;

        bool hasInEdge = false;
        for (int j = 0; j < n; j++) {
            if (g[j][i] && g[j][i] != MAX_NUM) {
                ++inEdgeSum[i];
                hasInEdge = true;
            }
        }

        if (!hasInEdge) vex.push(i);
    }

    // 开始
    while (!vex.empty()) {
        int v = vex.front();
        vex.pop();

        res[cnt++] = v;

        // 去掉了 v 顶点，要减少 v 链接的顶点的入度
        for (int i = 0; i < n; i++) {
            if (g[v][i]) {
                inEdgeSum[i]--;
                if (inEdgeSum[i] == 0) vex.push(i);
            }
        }
    }

    free(inEdgeSum);

    // 如果 cnt != n ，说明途中有环
    if (cnt != n) return false;
    else return true;
}

/* 关键路径
 * 空间复杂度：O(V)
 * 时间复杂度：邻接矩阵 O(V ^ 2) ，邻接表：O(V + E)
 */
bool criticalPath(unsigned int g[][5], int n) {
    // 准备一个拓扑排序序列
    int *topo = (int*)malloc(sizeof(int) * n);
    if (!TopoLogicalSort(g, n, topo)) return false;

    // 计算事件的最早发生时间
    unsigned int *early = (unsigned int*)malloc(sizeof(unsigned int) * n);
    for (int i = 0; i < n; i++) early[i] = 0;
    for (int i = 0; i < n; i++) {
        int v = topo[i];

        for (int j = 0; j < n; j++) {
            if (j != v && g[v][j] != MAX_NUM) {
                if (early[j] < early[v] + g[v][j]) early[j] = early[v] + g[v][j];
            }
        }
    }

    // 计算事件的最晚发生时间
    unsigned int *late = (unsigned int*)malloc(sizeof(unsigned int) * n);
    for (int i = 0; i < n; i++) late[i] = early[n - 1];
    for (int i = n - 1; i >= 0; i--) {
        int v = topo[i];

        for (int j = 0; j < n; j++) {
            if (j != v && g[j][v] != MAX_NUM) {
                if (late[j] > late[v] - g[j][v]) late[j] = late[v] - g[j][v];
            }
        }
    }

    // 计算时间余量，并得出关键路径
    for (int i = 0; i < n; i++) {
        int v = topo[i];
        if (early[v] == late[v]) cout << vertex[v] << " ";
    }
    cout << endl;

    free(topo);
    free(early);
    free(late);

    return true;
}

int main() {
    criticalPath(g, 5);
    return 0;
}
```

# 四、基础算法

## 1 查找

基本概念：

* 查找表：也叫记录，存储待查找元素的数据结构，不仅限于胡表、树、图都行
  
  * 静态查找表：只有查找操作
  
  * 动态查找表：CRUD

* 关键字：唯一区分各个元素的标识

* 查找长度：某个元素查找需要比较的次数

* 平均查找长度 ASL ：各种情况的查找长度平均下来就是 ASL ，分为查找成功的 ASL 和查找失败的 ASL

* 查找判定树：查找比较时形成的二叉树

分类：

* 顺序查找：也叫线性查找，如 KMP 算法
  
  * 一般时间复杂度是 O\(n\)
  
  * 查找判定树是一个只有右孩子的二叉树，左孩子为查找失败
  
  * 成功 ASL ：\(1 \+ 2 \+ \.\.\. n\) \* n = \(n \+ 1\) / 2
  
  * 失败 ASL ：= n，若是有序查找表可以优化到 \(1 \+ 2 \+ \.\.\. n\) \* n = \(n \+ 1\) / 2 ，若是有概率的查找表，可以优化成每个元素按概率降序排序，速度更快

* 二分查找：也叫折半查找，如 BST 、AVL 、RBT ，线性结构也可以用，但要求必须是有序的顺序表：
  
  ```
  int midSearch(int a[], int n, int key) {
      int low = 0, high = n - 1, mid;
  
      while (low < high) {
          mid = (low + high) / 2;
  
          if (a[mid] == key) return mid;
          else if (a[mid] < key) low = mid + 1;
          else high = mid - 1;
      }
  
      return -1;
  }
  ```
  
  * 时间复杂度一般是 O\(logn\)
  
  * 查找判定树是一个 ASL ，且是完全二叉树，且每层的根结点时每次二分查找的 mid 元素，若查找表元素个数：
    
    * 奇数：左子树结点数 = 有子树结点数
    
    * 偶数：左子树结点数 \+ 1 = 有子树结点数
  
  * 21

* 分块查找：也叫索引-顺序查找，索引可以顺序查找也可以二分查找，二分查找的索引如 B Tree 、B+ Tree

* 散列查找：如哈希表

* BFS 和 DFS：如树和图的遍历

## 2 排序

分为内部排序和外部排序：

* 内部排序：只在内存中排序

* 外部排序：排序元素太多，内存放不下，需要不断从硬盘中读取部分元素进行排序，因此外部排序还需要考虑硬盘 IO 次数

和查找算法不同，排序算法中用来排序的关键字可能会重复，因此排序算法的指标还有稳定性，稳定指的是相同大小的元素在排序前后相对位置不变。

平均时间复杂度 = \(最好 \+ 最坏\) / 2

### 2.1 内部排序

（1）交换排序

```
#include<iostream>
using namespace std;

/* 冒泡排序
 * 思想：不断比较相邻元素，把最大值放在最右边，剩下的元素继续下一趟，通需要 n - 1 趟，每堂比较 n - 1 - i 次
 * 优化：越是有序，效率越高，因此若排序过程中发现已经有序，就停止排序
 * 空间复杂度：O(1)
 * 时间复杂度：最好: O(n) ，最坏: O(n2) 平均: O(n2)
 * 稳定性：稳定
 * 适用于顺序结构、链式结构
 */
void barbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // 若排序过程中发现已经有序，就直接结束
        bool flag = false;

        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                flag = true;

                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }

        if (flag == false)    break;
    }
}


/* 快速排序
 * 思想：用一个基准元素（通常是第一个元素）
   * 把比基准小的放在基准左边，反之放在右边，然后递归调用左右两部分
   * low 空就左移 high ，直到找到比基准小的元素并交换给 low ，然后 high 就空了，可以右移 low ，重复此过程准时到 low == high
 * 越是有序效率越高
 * 空间复杂度：最好: O(logn) ，最坏: O(n)
 * 时间复杂度：最好: O(nlogn) ，最坏: O(n2) 平均: O(nlogn)
 * 稳定性：不稳定
 * 适用于顺序结构、链式结构
 */
void partition(int a[], int low, int high) {
    if (low >= high) return;

    // 基准元素
    int pivot = a[low];

    int l = low, h = high;

    while (l < h) {
        //左移 high
        while (l < h && a[h] >= pivot) --h;
        a[l] = a[h];

        // 右移 low
        while (l < h && a[l] <= pivot) ++l;
        a[h] = a[l];
    }

    // 此时 l == h ，且左小右大
    a[l] = pivot;
    int mid = l;

    partition(a, low,mid - 1);
    partition(a, mid + 1, high);
}

void quickSort(int a[], int n) {
    if (n <= 1) return;
    partition(a, 0, n - 1);
}

int main() {
    int a[10] = { 7,6,4,8,2,3,9,1,5 };
    quickSort(a, 10);
    for (int i = 0; i < 10; i++) cout << a[i] << " ";
    return 0;
}
```

（2）插入排序

```
#include<iostream>
using namespace std;

/* 直接插入排序
 * 思想：每次把元素插入到左边已经有序的序列中，插入前需要移动元素空出位置
 * 越有序效率越高
 * 空间复杂度：O(1)
 * 时间复杂度：最好: O(n) ，最坏: O(n2) 平均: O(n2)
 * 稳定性：稳定
 * 适用于顺序结构、链式结构，由于需要移动元素，所以更适合链式结构
 */
void directInsertSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) {
            int temp = a[i], j;
            for (j = i - 1; j >= 0 && a[j] > temp; j--) a[j + 1] = a[j];
            a[j + 1] = temp;
        }
    }
}

/* 折半插入排序
 * 与直接插入排序的区别只是用折半查找找到要插入的位置
 * 由于用了折半查找，就不适用于链式结构了
 */
void binaryInsertSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) {
            int temp = a[i], j;
            int low = 0, high = i - 1, mid;

            while (low <= high) {
                mid = (low + high) / 2;
                if (a[mid] > temp) high = mid - 1;
                else               low = mid + 1;
            }

            for (j = i - 1; j >= high + 1; j--) a[j + 1] = a[j];
            a[high + 1] = temp;
        }
    }
}

/* 希尔排序
 * 思想：设置一个 d 序列（推荐是 2 的 n 次方，如 8 4 2 1）
   * 每一堂划分 n 个子表，每个子表间隔 d ,对每一个子表都执行直接插入排序，每堂使得整个表逐渐有序
 * 越有序效率越高
 * 空间复杂度：O(1)
 * 时间复杂度：取决于 d 的设置，大概在 O(n1.3) 左右
 * 稳定性：不稳定
 * 只适用于顺序结构
 */
void shellSort(int a[], int n) {
    for (int d = n / 2; d >= 1; d /= 2) {
        for (int i = d; i < n; i++) {
            if (a[i] < a[i - d]) {
                int temp = a[i], j;
                for (j = i - d; j >= 0 && a[j] > temp; j -= d) a[j + d] = a[j];
                a[j + d] = temp;
            }
        }
    }
}

int main() {
    int a[10] = { 7,6,4,8,2,3,9,1,5 };
    shellSort(a, 10);
    for (int i = 0; i < 10; i++) cout << a[i] << " ";
    return 0;
}
```

（3）选择排序

```
#include<iostream>
using namespace std;

/* 简单选择排序
 * 每次选择最小值放在最左边
 * 空间复杂度：O(1)
 * 时间复杂度：任何情况都是 O(n2)
 * 稳定性：不稳定
 * 适用于顺序结构、链式结构
 */
void selectSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) min = a[j] < a[min] ? j : min;

        if (min != i) {
            int temp = a[min];
            a[min] = a[i];
            a[i] = temp;
        }
    }
}

/* 堆排序
 * 先把排序表调整成大跟堆，然后每一堂根结点和最后一个元素交换，然后去掉最后一个元素形成新的大根堆，并调整
 * 空间复杂度：O(1)
 * 时间复杂度：任何情况都是一样的，建堆需要 O(n) ，排序需要 O(nlogn) ，总体是 O(nlogn)
 * 稳定性：不稳定
 * 只适用于顺序结构
 */
// 下滤
void heapAdjust(int a[], int n, int k) {
    int temp = a[k];
    for (int i = 2 * k + 1; i < n; i = 2 * i + 1) {
        // 找到左右孩子更大的那一个
        if (i < n - 1 && a[i] < a[i + 1])    i++;

        // 检查是否符合大根堆的特性
        if (temp >= a[i])    break;
        else {
            a[k] = a[i];
            k = i;
        }
    }

    a[k] = temp;
}

void heapSort(int a[], int n) {
    // 建大根堆，从最后一个非叶结点开始
    for (int i = (n - 2) / 2; i >= 0; i--) heapAdjust(a, n, i);

    // 开始排序，每次把根结点和最后一个元素交换，然后大根堆去掉最后一个元素，并调整新大根堆，重复此步骤
    for (int i = n - 1; i >= 0; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapAdjust(a, i, 0);
    }
}

int main() {
    int a[10] = { 7,6,4,8,2,3,9,1,5 };
    heapSort(a, 10);
    for (int i = 0; i < 10; i++) cout << a[i] << " ";
    return 0;
}
```

（4）归并排序

```
#include<iostream>
using namespace std;

/* 归并排序
 * 思想：使用分治法：
   * 将排序表划分成若干个子表，直到 low >= hihe 为止，划分出 n 个子表
   * 使用二路归并，两个字表合并成新的表并排好序，以后就都是两个已经有序的字表合并了
 * 空间复杂度：辅助数组 n + 递归深度 logn ，总体 O(n)
 * 时间复杂度：任何情况都一样，归并树每层展总排序需要 O(n) ，共 O(logn) 层 ，筒体 O(nlogn)
 * 稳定性：稳定
 * 适用于顺序结构、链式结构
 */
void toSort(int a[], int temp[], int low, int high) {
    if (low >= high) return;

    // 划分子表
    int mid = (low + high) / 2;
    toSort(a, temp, low, mid);
    toSort(a, temp, mid + 1, high);

    // 合两个有序子表并并排序
    int left, right, i;
    for (i = low; i <= high; i++)    temp[i] = a[i];
    for (left = low, right = mid + 1, i = low; left <= mid && right <= high; i++) {
        // 从左右两部分中找到更小的元素，放在前面
        if (temp[left] <= temp[right])    a[i] = temp[left++];
        else a[i] = temp[right++];
    }

    // 结束后若 left ， right 其中一个还未到结尾，就直接拷贝过来
    while (left <= mid)    a[i++] = temp[left++];
    while (right <= high)    a[i++] = temp[right++];
}

void mergeSort(int a[], int n) {
    int* temp = (int*)malloc(sizeof(int) * n);
    toSort(a, temp, 0, n - 1);
    free(temp);
}

int main() {
    int a[10] = { 7,6,4,8,2,3,9,1,5 };
    mergeSort(a, 10);
    for (int i = 0; i < 10; i++) cout << a[i] << " ";
    return 0;
}
```

（5）桶排序

```
#include<iostream>
#include<queue>
using namespace std;

/* 基数排序
 * 唯一不需要直接比较的排序算法，但只适用于元素都是数字的序列
   * 将数码拆分d元组（如千百十个），每一位起取值范围是0到 r - 1，r 称为基数，十进制数的 r = 10
   * 需要 r 个辅助队列，按权重从小到大分配和收集（十进制个位权重最小），共 d 趟
   * 分配：每个元素按照个位的数值，入相应索引的队
   * 收集：按顺序各个队列出兑，一依次放到排序序列中
   * 下一次就以百位为基准，每一堂的分配收集，都可以得到这个位的有序序列
   * 使用二路归并，两个字表合并成新的表并排好序，以后就都是两个已经有序的字表合并了
 * 空间复杂度：r 个队列，O(r) ~ O(n)
 * 时间复杂度：任何情况都一样，分配 O(n) ，收集(顺: O(n) ，链: O(r))，共 d 轮，总体 O(d(n + r))
 * 稳定性：稳定
 * 适用于顺序结构、链式结构，链式结构更适合。序列中 n 越大，d 和 r 越小越好
 */

void radixSort(int a[], int n) {
    // 找到最大值，才能知道要几轮
    int max = a[0], exp = 1;
    for (int i = 1; i < n; i++) max = a[i] > max ? a[i] : max;

    // 辅助队列
    queue<int> qArr[10];

    // 使用计数排序按位排序
    while (max / exp > 0) {
        // 分配给各个队列
        for (int i = 0; i < n; i++) qArr[(a[i] / exp) % 10].push(a[i]);

        // 从队列中收集各个元素
        int index = 0;
        for (int i = 0; i < n; i++) {
            while (!qArr[i].empty()) {
                a[index++] = qArr[i].front();
                qArr[i].pop();
            }
        }

        exp *= 10;
    }
}

int main() {
    int a[10] = { 7,26,14,85,82,3,9,1,5 };
    radixSort(a, 10);
    for (int i = 0; i < 10; i++) cout << a[i] << " ";
    return 0;
}
```

（6）Tim 排序

最快的排序算法，二分插入排序和归并排序的结合：

* 时间复杂度：O\(n\) 到 O\(nlogn\)

* 空间复杂度：O\(n/2\)

* 稳定性：稳定

过程：

* 设置一个最小值 MIN\_RUN\_LEN ，一般是 32 ，数组长度小于这个值时，直接用二分插入排序

* TimSort 需要划分出一个个分区 Run ，run 的长度通过 MIN\_RUN\_LEN 和数组长度综合计算出最小 Run 长度（16 到 32 之间）

* 构造 Run ：遍历数组，找出连续单调递增或单调递减的区间，若顺序和排序结果相反，直接反转这个区间即可，若区间长度小于最小 Run 长度，使用二分插入排序直到插入到最小 Run 长度，最后将 Run 入栈

* 合并：当栈长度大于 1 时，需要合并，a、b、c 分别代表倒数第三个到栈顶的 Run 的长度，若：
  
  * \>= 3 个：若 a a \<= b \+ c ，b 和 min\(a, c\) 合并，否则不合并
  
  * 栈只有 2 个 Run ：若 b \<= c ，就合并，否则不合并

* 合并过程：排除 Run1 已经有序的前半部分和 Run2 已经有序的后半部分，只处理中间无序的部分，拷贝中间部分中 Run1 剩余的，Run2 剩余的更小的那一个部分到 temp ，用类似插入的方式进行排序

* 遍历完数组时，若栈长度 \> 1 ，就合并栈中所有的 Run

代码：（还需优化，目前速度：quick \< merge \< tim \< heap \< shell）

```
#include<iostream>
#include<stack>
using namespace std;

// 分区 run 的最小长度
#define MIN_TIM 32

// 分区 run
typedef struct Run {
    int start, end;
} Run;

// 反转 run
void reverseRun(int a[], int start, int end) {
    while (start < end) {
        int temp = a[start];
        a[start] = a[end];
        a[end] = temp;

        ++start;
        --end;
    }
}

// 返回已经有序的子序列长度
int countAlreadyFinishLength(int a[], int start, int end) {
    if (start >= end) return 0;
    else if (start == end) return 1;

    int i = start;

    // 如果 run 时降序的，就反转
    if (a[i++] > a[i + 1]) {
        // 为了保证排序稳定性，这里只能是 > ，因为需要反转
        while (i < end && a[i] > a[i + 1]) ++i;
        reverseRun(a, start, i);
    }
    else  while (i < end && a[i] <= a[i + 1]) ++i;


    return i - start + 1;
}

// 二分插入排序，skip: 跳过已经有序的元素
void binaryInsertSort(int a[], int start, int end, int skip = 0) {
    if (start >= end || start + skip >= end) return;

    for (int i = start + skip + 1; i <= end; i++) {
        if (a[i - 1] > a[i]) {
            int temp = a[i], j;
            int low = start, high = i - 1, mid;

            while (low <= high) {
                mid = (low + high) / 2;
                if (a[mid] > temp) high = mid - 1;
                else               low = mid + 1;
            }

            for (j = i - 1; j >= high + 1; j--) a[j + 1] = a[j];
            a[high + 1] = temp;
        }
    }
}

// 根据数组长度计算出合适的分区 run 的大小，一般再 16 - 32 之间
int getMinRunLenth(int n) {
    if (n < 0) return 0;

    int r = 0;
    while (n >= MIN_TIM) {
        r |= (n & 1);
        n >>= 1;
    }

    return n + r;
}

// 合并 2 个 run
// run1 的所有 index 必须小于 run2 所有的 index
void toMergeRun(int a[], stack<Run>& runStack, Run& run1, Run& run2) {
    /* 比起常规的归并排序，做了一些优化，以 2 个 run 为例：{1,2,10,20} {6,7,15,30}
     * 只需要找到 2 个 run 中间无序的部分进行排序即可，这里是 {1,2, {10,20,6,7,15}, 30}
     * {10,20,6,7,15} 可以发现，{6,7} 只需要插入到 10 之前，{15} 只需要插入到 20 之前，即可完成 2 个 run 的合并
     */
    int newStart = run1.start, newEnd = run2.end;

    // 找到中间部分的 newStart ，即 run1 中第一个 > run2 start 的位置，如 {1,2,10,20} {6,7,15,30} 中就是元素 10
    while (newStart < run2.start && a[run2.start] >= a[newStart]) ++newStart;
    // 如果找不到，说明两个 run 已经是有序的了，如 {1,2} {5,8}
    if (newStart == run2.start) return;

    // 找到中间弗恩的 newEnd ，即 run2 中第一个 < run1 end 的位置，如 {1,2,10,20} {6,7,15,30} 中就是元素 15
    while (newEnd > run1.end && a[newEnd] >= a[run1.end]) --newEnd;

    // 合并时可能会覆盖原有位置的元素，所以需要一个临时空间，为了提高性能，需选择元素较少的那部分拷贝到临时空间
    int leftLen = run1.end - newStart + 1, rightLen = newEnd - run2.start + 1;
    int tempSize = leftLen <= rightLen ? leftLen : rightLen;
    int* temp = (int*)malloc(sizeof(int) * tempSize);

    // 开始合并 [newStart, run1.end], [run2.start, newEnd] 这两个部分，这一步还可以做更复杂的优化，这里就不做了
    if (leftLen <= rightLen) {
        for (int i = newStart; i <= run1.end; i++) temp[i - newStart] = a[i];

        int tempPtr = 0, leftPtr = newStart, rightPtr = run2.start;
        int cnt1 = 0, cnt2 = 0;
        while (1) {
            if (a[rightPtr] < temp[tempPtr]) {
                a[leftPtr++] = a[rightPtr++];
                if (rightPtr > newEnd) break;

                ++cnt1;
                cnt2 = 0;
            }
            else {
                a[leftPtr++] = temp[tempPtr++];
                if (tempPtr > tempSize - 1) break;

                ++cnt2;
                cnt1 = 0;
            }
        }

        while (tempPtr < tempSize)  a[leftPtr++] = temp[tempPtr++];
    }
    else {
        for (int i = run2.start; i <= newEnd; i++) temp[i - run2.start] = a[i];

        int tempPtr = tempSize - 1, leftPtr = run1.end, rightPtr = newEnd;
        while (1) {
            if (a[leftPtr] > temp[tempPtr]) {
                a[rightPtr--] = a[leftPtr--];
                if (leftPtr < newStart) break;
            }
            else {
                a[rightPtr--] = temp[tempPtr--];
                if (tempPtr < 0) break;
            }
        }

        while (tempPtr >= 0) a[rightPtr--] = temp[tempPtr--];
    }

    free(temp);
}

// 栈中找到要合并的 run
void mergeRun(int a[], stack<Run> &runStack, bool isEnd = false) {
    // 栈可以保证前一个 run 的 index 必然全部小于后一个 run 的所有 index
    while (runStack.size() > 1) {
        // 取出两个 run
        Run run2 = runStack.top();
        runStack.pop();
        Run run1 = runStack.top();
        runStack.pop();

        // 计算两个 run 的长度
        int run0_len = runStack.size() > 0 ? runStack.top().end - runStack.top().start + 1 : 0;
        int run1_len = run1.end - run1.start + 1;
        int run2_len = run2.end - run2.start + 1;

        // 若 runStack 至至少有 3 个 run ，且 run0_len <= run1_len + run2_len ，就需要合并
        if (runStack.size() > 0 && run0_len <= run1_len + run2_len) {
            // 比较 run0 和 run2 长度，更小的 run 和 run1 合并
            if (run2_len >= run0_len) {
                Run run0 = runStack.top();
                runStack.pop(); toMergeRun(a, runStack, run0, run1);
                runStack.push({ run0.start,run1.end });
                runStack.push(run2);
            }
            else {
                toMergeRun(a, runStack, run1, run2);
                runStack.push({ run1.start,run2.end });
            }
        }
        // 若 run1_len <= run2_len ，就合并这两个 run
        else if (run1_len <= run2_len || isEnd) {
            toMergeRun(a, runStack, run1, run2);
            runStack.push({ run1.start,run2.end });
        }
        // 不需要合并
        else {
            runStack.push(run1);
            runStack.push(run2);
            break;
        }
    }
}

// Tim 排序
void timSort(int a[], int n) {
    // 无需排序
    if (n <= 1) return;

    // 如果长度 < MIN_TIM ，直接用 binaryInsertSort 就好了，元素更多时再用 TimSort
    if (n < MIN_TIM) {
        // 直接从非有序的地方开始排序，提高效率
        int alreadyFinishLength = countAlreadyFinishLength(a, 0, n - 1);
        binaryInsertSort(a, alreadyFinishLength - 1, n - 1);
        return;
    }

    // 确定 run 的最小长度
    int minRunLen = getMinRunLenth(n);

    // 构造 run
    int remainLen = n, start = 0, end = n - 1;
    stack<Run> runStack;
    while (remainLen > 0) {
        // 找到连续有序的长度
        int runLen = countAlreadyFinishLength(a, start, end);

        // 如果 runLen 不够最小长度，就用 binaryInsertSort 插入，直到达到 minRunLen
        if (runLen < minRunLen) {
            // 如果剩余的元素个数已经不够 minRunLen 了，就使用剩余元素个数作为长度
            int len = remainLen < minRunLen ? remainLen : minRunLen;
            binaryInsertSort(a, start, start + len - 1, runLen - 1);
            runLen = len;
        }

        // 将 run 入栈，并看是否需要合并
        runStack.push({ start, start + runLen - 1 });
        mergeRun(a, runStack);

        // 下一个
        start += runLen;
        remainLen -= runLen;
    }

    // 若栈中海油 run ，就全部合并，直到只有一个 run ，就结束排序
    mergeRun(a, runStack, true);
}

int main() {
    srand(time(0));

    long long len = 10000;
    int *a = (int*)malloc(sizeof(int) * len);

    for (int i = 0; i < len; i++) {
        int n1 = rand(), n2 = rand() * rand();
        a[i] = n1 + n2;
    }

    timSort(a, len);

    free(a);

    return 0;
}
```

### 2.2 外部排序

使用归并排序的西乡：

* 内存中至少需要 2 个输入缓冲区， 1 个输出缓冲区，缓冲区至少能容纳一个磁盘块的大小，一个磁盘块有若干数据元素

* 一开始，先构造出初始归并段，如每 2 个磁盘块就构造成一个归并段：
  
  * 从硬盘中读入 2 个磁盘块进入内存的 2 个输入缓冲区，使用任意的内部排序算法把这两个缓冲区排好序，再依次进入输出缓冲区，再写回硬盘
  
  * 重复此过程，直到所有归并段构造完成

* 有了归并段，就可以开始归并排序，和内部归并排序不同的是，归并段的大小必然大于输入缓冲区的大小，所以要分段读取一个归并段：
  
  * 第一个归并段的第一部分和第二个归并段的第一部分分别读入输入缓冲区 A 和输入缓冲区 B
  
  * 两个输入缓冲区的元素比较大小，依次放入输出缓冲区，输出缓冲区满了就写回硬盘
  
  * 一旦某个输入缓冲区空了，就读入对应归并段的下一部分，若此归并段已读取完毕，就换成另一个归并段的下一部分
  
  * 在写回硬盘的过程中，可能要写入的位置还未读入输入缓冲区，就会造成覆盖数据，为了防止这种情况，硬盘就需要一片新的空间存储数据

由于外部排序涉及硬盘 IO ，代码不好实现，这里精良用代码模拟这个过程，不考虑性能，以一个磁盘块有 3 个元素，使用 2 和输入缓冲区，1 个输出缓冲区，缓冲区大小为一个磁盘块为例：

```
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

// 内部排序，这里用快速排序
void quickSort(int a[], int low, int high) {
    if (low >= high) return;

    // 基准元素
    int pivot = a[low];

    int l = low, h = high;

    while (l < h) {
        //左移 high
        while (l < h && a[h] >= pivot) --h;
        a[l] = a[h];

        // 右移 low
        while (l < h && a[l] <= pivot) ++l;
        a[h] = a[l];
    }

    // 此时 l == h ，且左小右大
    a[l] = pivot;

    quickSort(a, low, l - 1);
    quickSort(a, l + 1, high);
}

void outSort(int a[], int n) {
    if (n < 2) return;

    // 归并段
    queue<vector<int>> segment;

    // 输入、输出缓冲区
    int in[6], out[3];
    int ai = 0, bi = 0, oi = 0;

    // 构造初始归并锻
    for (int i = 0; i < n; i++) {
        if (ai < 6) in[ai++] = a[i];
        if (ai >= 6 || i == n - 1) {
            // 内部排序
            quickSort(in, 0, ai - 1);

            // 放入输出缓冲区
            vector<int> seg;
            int cnt = 0;
            for (int j = 0; j < ai; j++) {
                if (oi < 3) out[oi++] = in[j];
                if (oi >= 3 || j == ai - 1) {
                    // 把这个归并锻写回硬盘
                    for (int k = 0; k < oi; k++) {
                        a[i - (ai - 1) + cnt * 3 + k] = out[k];
                        seg.push_back(out[k]);
                    }

                    if (cnt % 2 != 0 || i == n - 1) {
                        segment.push(vector<int>(seg));
                        seg.clear();
                    }

                    ++cnt;
                    oi = 0;
                }
            }

            ai = 0;
        }
    }

    // 归并排序
    int *temp = (int*)malloc(sizeof(int) * n);
    int ti = 0;
    vector<int> newSeg;
    int newSegSize;

    while (segment.size() > 1) {
        // 两个待合并的归并段
        vector<int> v1 = segment.front();
        segment.pop();
        vector<int> v2 = segment.front();
        segment.pop();

        newSegSize = v1.size() + v2.size();
        ai = oi = 0;
        bi = 3;

        // v1 的以一个磁盘快放到输入缓冲区 A ，v2 的第一个磁盘块放到输入缓冲区 B
        int v1Cnt = 1, v2Cnt = 1;
        for (int i = 0; i < 3 && i < v1.size(); i++) in[ai++] = v1[i];
        for (int i = 0; i < 3 && i < v2.size(); i++) in[bi++] = v2[i];

        // 归并到输出缓冲区
        int left, right;
        bool isEnd = false;
        for (left = 0, right = 3, oi = 0; left < ai && right < bi && oi < 3; oi++) {
            if (!isEnd) {
                if (in[left] <= in[right])    out[oi] = in[left++];
                else out[oi] = in[right++];
            }

            // 写入硬盘
            if (oi >= 2 || isEnd) {
                for (int i = 0; i <= oi; i++) temp[ti++] = out[i];
                oi = -1;

                if (isEnd) break;
            }

            // 如果输入缓冲区有一个空了，就补上
            if (left >= ai) {
                if (v1Cnt * 3 < v1.size()) {
                    ai = 0;
                    left = 0;
                    for (int i = v1Cnt * 3; i < v1Cnt * 3 + 3 && i < v1.size(); i++) in[ai++] = v1[i];
                    ++v1Cnt;
                }
                else if (v2Cnt * 3 < v2.size()) {
                    ai = 0;
                    left = 0;
                    for (int i = v2Cnt * 3; i < v2Cnt * 3 + 3 && i < v2.size(); i++) in[ai++] = v2[i];
                    ++v2Cnt;
                }
                else isEnd = true;
            }

            if (right >= 6) {
                if (v2Cnt * 3 < v2.size()) {
                    bi = 3;
                    right = 3;
                    for (int i = v2Cnt * 3; i < v2Cnt * 3 + 3 && i < v2.size(); i++) in[bi++] = v2[i];
                    ++v2Cnt;
                }
                else if (v1Cnt * 3 < v1.size()) {
                    bi = 3;
                    right = 3;
                    for (int i = v1Cnt * 3; i < v1Cnt * 3 + 3 && i < v1.size(); i++) in[bi++] = v1[i];
                    ++v1Cnt;
                }
                else isEnd = true;
            }
        }

        // 处理剩下的没排序的元素，这里为了方便就省略进入输出缓冲区的步骤了
        for (int i = 0; i < oi; i++) temp[ti++] = out[i];
        while (left < ai)    temp[ti++] = in[left++];
        while (right < bi)    temp[ti++] = in[right++];

        // 硬盘需要一定的辅助空间来存放排序后的数据，因为排序过程中，部分归并段可能会覆盖未排序的位置，这里为了方便直接用 n 的空间，实际上会有更好的方法
        for (int i = 0; i < n; i++) a[i] = temp[i];

        int ind = ti;
        if (ti + newSegSize >= n) ti = 0;

        // 合并成新的归并段
        for (int i = ind - 1; i >= ind - newSegSize; i--) newSeg.insert(newSeg.begin(), temp[i]);
        segment.push(newSeg);
        newSeg.clear();
    }

    if (n <= 3) for (int i = 0; i < n; i++) temp[ti++] = segment.front()[i];

    free(temp);
}

int main() {
    int a[30] = { 7,6,4,8,2,3,9,1,5,0,12,65,98,76,46,32,48,51,41,21,78,98,67,94,83,38,72,32,19,18 };
    outSort(a, 30);
    for (int i = 0; i < 30; i++) cout << a[i] << " ";
    return 0;
}
```

大概需要 logn 数量级的趟归并，每一样都需要 n 次读取 n 次写入，总共大概需要 2nlogn 次硬盘 IO ，减少次数可以减少归并趟数，有两个方法：

* 败者树 \-\-\-\-\- 增加缓冲区的数量：n 个输入缓冲区就能实现 n 路归并，但同事也会增加内存的空间消耗，也增加比较大小的次数，n 路归并就需要 n - 1 次比较，可以通过败者树减少比较次数：
  
  ```
  #include<iostream>
  #include<vector>
  using namespace std;
  
  /* n 苦归并，最多需要大小 n - 1 的数组存储败者树失败的结点，1 个空间存储冠军归并段 index，共需 n 个空间，以 5 路归并为例 
   * 除冠军结点外，结点存储的是比较失败（这里是升序，更大的就是失败）的归并段 index
   * 最开始需要 n - 1 次比较，构造出初始败者树，并选出冠军
   * 取出冠军后，之后冠军归并段内下一个元素进行比较，只需要 logn 数量级的比较
   * 比较时，由于归并段自己内部是有序的，基于已有的败者树，只需要先和兄弟比较，然后一直往上蹭比较，过程中结点修改新的败者，最终选出新的冠军
   */
  
  // 归并段
  vector<vector<int>> segment({
      {3,4,5},
      {5,7,8},
      {9,10,12},
      {1,4,7},
      {5,6,9},
  });
  
  /* 初始败者树
      冠军 index = 3
           (0)
           / \
          /   \
         /     \
        /       \
      (2)       (4)
      / \       / \
     /   \     1   5
   (1)    9    4   6
   / \    10   7   9
  3   5  =12
  4   7
  5   8
  
   */
  
  int t[5] = { 3, 0,2,4,1 };
  
  int main() {
      return 0;
  }
  ```
- 置换-选择排序 ----- 减少归并段的数量：可以通过增加归并段的长度实现，这里使用置换-选择排序来构造初始归并段：
  
  ```
  #include<iostream>
  #include<queue>
  #include<vector>
  using namespace std;
  
  /* 以输入缓冲区大小为 3 个元素为例
   * 每次找出缓冲区中的最小值，加入到归并段中，记录此值在 minMax；在此最小值的位置读入硬盘的下一个元素
   * 若下一次有最小值 < minMax，则把这个元素标记为 true， 是要放入下一个归并段的；在缓冲区剩余的元素中继续找最小值
   * 若缓冲区中所有元素都 < minMax ，则这个归并段完成，开始下一个归并段的构造
   */
  queue<vector<int>> getSegment(int a[], int n) {
      // 存储归并段
      queue<vector<int>> segment;
      vector<int> seg;
  
      if (n <= 3) {
          // 直接用内部排序1
          return segment;
      }
  
      // 输入缓冲区，为了方便就省略输出缓冲区了
      int in[3];
      for (int i = 0; i < (n >= 3 ? 3 : n); i++) in[i] = a[i];
  
      // 存储上一次加入归并段的值
      int minMax = in[0];
  
      // 记录是否是要加入下一个归并段的
      bool isStop[3] = { false,false,false };
      int startIndex = 0;
  
      for (int i = 3; i < n; i++) {
          int min = in[startIndex], minIndex = startIndex >= 2 ? 2 : 0;
  
          // 找最小值
          for (int j = startIndex + 1; j < 3; j++) {
              if (in[j] < min && !isStop[j]) {
                  min = in[j];
                  minIndex = j;
              }
          }
  
          if (a[i] < minMax) isStop[minIndex] = true;
          minMax = min;
          in[minIndex] = a[i];
          a[i - 3] = min;
          seg.push_back(min);
  
          // 判断此次归并段是否已构造完成
          bool isAllStore = true;
          for (int j = 0; j < 3; j++) {
              if (!isStop[j]) {
                  isAllStore = false;
                  startIndex = j;
                  break;
              }
          }
  
          // 构造下一个归并段
          if (isAllStore) {
              segment.push(seg);
              seg.clear();
              startIndex = 0;
              minMax = a[i];
  
              for (int j = 0; j < 3; j++) isStop[j] = false;
          }
      }
  
      // 处理剩下的元素
      vector<int> newSeg;
      for (int i = 0; i < 3; i++) {
          int min = in[0], minIndex = 0;
  
          // 找最小值
          for (int j = 1; j < 3 - i; j++) {
              if (in[j] < min) {
                  min = in[j];
                  minIndex = j;
              }
          }
  
          // 放入对应的归并段
          if (!isStop[minIndex]) seg.push_back(min);
          else newSeg.push_back(min);
  
          // 抵触掉已处理元素
          if (minIndex != 2) {
              in[minIndex] = in[2];
              isStop[minIndex] = isStop[2];
          }
      }
  
      segment.push(seg);
      if (!newSeg.empty()) segment.push(newSeg);
  
      return segment;
  }
  
  int main() {
      int a[10] = { 7,6,8,2,5,9,3,1,4 };
      queue<vector<int>> segment = getSegment(a, 10);
  
      while (!segment.empty()) {
          for (int i = 0; i < segment.front().size(); i++) cout << segment.front()[i] << " ";
          cout << endl;
          segment.pop();
      }
  
      return 0;
  }
  ```
* 最佳归并树：置换-选择排序构造的初始归并段，每个长度都可能不同，而采用适合的归并方法可以进一步减少归并次数，归并段长度看做叶子结点的权值，形成带权路径长度最小的就是最佳归并书，二录归并其实就是哈夫曼树。
  
  k 路归并，k \>= 3 时，可能会形成非严格的 k 叉树（严格 k 叉树：所有结点的度只能是 0 或 k），解决方法是填充若干个权值为 0 的结点再构造最佳归并树，数量 = ：
  
  ```
  // k: k 叉   n: 归并段数  res: 虚结点数
  (n + res -1) % (k - 1) = 0
  ```

### 2.3 乱序算法

也叫洗牌算法，只需要遍历数组，每一个元素和随机一个元素交换即可：

```
#include<iostream>
using namespace std;

/* 乱序算法
 * 空间复杂度：O(1)
 * 时间复杂度：O(n)
 */
void disSort(int a[], int n) {
    // 随机种子
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        int r = rand() % n;
        int temp = a[r];
        a[r] = a[i];
        a[i] = temp;
    }

}

int main() {
    int a[10] = { 7,26,14,85,82,3,9,1,5 };
    disSort(a, 10);
    for (int i = 0; i < 10; i++) cout << a[i] << " ";
    return 0;
}
```

# 五、算法思想

## 1 递归

## 2 回输

## 3 分治

## 4 贪心

## 5 动态规划
