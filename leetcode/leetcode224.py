class ElemType:

    def __init__(self, data = None):
        self.__data = data
        self.__next = None

    def get_data(self):
        return self.__data

    def set_next(self, next):
        #if isinstance(next, ElemType):
        self.__next = next

    def get_next(self):
        return self.__next


class Stack:

    def __init__(self):
        self.__head = ElemType()
        self.__len = 0

    def is_empty(self):
        return self.__len == 0

    def push(self, data):
        elem = ElemType(data)
        elem.set_next(self.__head.get_next())
        self.__head.set_next(elem)
        self.__len += 1

    def pop(self):
        x = ElemType()
        if isinstance(self.__head.get_next(), ElemType):
            x = self.__head.get_next()
        self.__head.set_next(x.get_next())
        self.__len -= 1

    def top(self):
        x = ElemType()
        if isinstance(self.__head.get_next(), ElemType):
            x = self.__head.get_next()
        return (x.get_data())

    def size(self):
        return self.__len

    def print_sta(self):
        cur = self.__head.get_next()
        while cur is not  None:
            print(cur.get_data())
            cur = cur.get_next()
    pass


class Queue(object):

    def __init__(self):
        self.__front__ = ElemType()
        self.__rear__ = self.__front__
        self.__len__ = 0

    def is_empty(self):
        return self.__len__ == 0

    def size(self):
        return self.__len__

    def push(self, data):
        elem = ElemType(data)
        self.__rear__.set_next(elem)
        self.__rear__ = elem
        self.__len__ += 1

    def pop(self):
        self.__front__.set_next(self.__front__.get_next().get_next())
        if self.__front__.get_next() is None:
            self.__rear__ = self.__front__
        self.__len__ -= 1

    def front(self):
        return self.__front__.get_next().get_data()

    def print_que(self):
        cur = self.__front__.get_next()
        while cur is not  None:
            print(cur.get_data())
            cur = cur.get_next()
    pass


def init_proir():
    prior['('] = -1
    prior[')'] = -1
    prior['+'] = prior.get('+', 0) + 1
    prior['-'] = prior.get('-', 0) + 1
    prior['*'] = prior.get('*', 0) + 2
    prior['/'] = prior.get('/', 0) + 2
    pass

sta = Stack()
que = Queue()
prior = {}

def isdigit(x):
    return x >= '0' and x <= '9'


def deal_with_operator(s):
    if s in ['(', ')']:
        if s == '(':
            sta.push(s)
        else:
            while sta.top() != '(':
                que.push(sta.top())
                sta.pop()
            sta.pop()
    else:
        while sta.is_empty() == False and sta.top() != '(' and prior[sta.top()] >= prior[s]:
            que.push(sta.top())
            sta.pop()
        sta.push(s)
    pass


def cal(op1, op2, op):
    if op == '+': 
        return op1 + op2
    if op == '-':
        return op1 - op2
    if op == '*': 
        return op1 * op2
    if op == '/': 
        return op1 * 1.0 / op2


def clear_space(Str):
    res = ''
    for ch in Str:
        if ch != ' ':
            res = res + ch
    return res

class Solution:
    def calculate(self, Str):
        init_proir()
        Str = clear_space(Str)
        in_num = False
        cur_op = ''
        cur_num = ''
        for ch in Str:
            if isdigit(ch):
                if in_num == False and cur_op != '':
                    deal_with_operator(cur_op)
                    cur_op = ''
                in_num = True
                cur_num = cur_num + ch
                pass
            else:
                if in_num == True:
                    que.push(cur_num)
                    cur_num = ''
                in_num = False
                cur_op = cur_op  + ch
                if prior.get(cur_op) is not None:
                    deal_with_operator(cur_op)
                    cur_op = ''
        if cur_num != '':
            que.push(cur_num)
        while sta.is_empty() == False:
            que.push(sta.top())
            sta.pop()
        while que.is_empty() == False:
            symbol = que.front()
            que.pop()
            if prior.get(symbol) is not None:
                op2 = sta.top()
                if isinstance(op2, str):
                    op2 = int(op2)
                sta.pop()
                op1 = sta.top()
                if isinstance(op1, str):
                    op1 = int(op1)
                sta.pop()
                sta.push(cal(op1, op2, symbol))
                pass
            else:
                sta.push(symbol)
        res = sta.top()
        sta.pop()
        return res


print Solution().calculate('(1+(4+5+2)-3)+(6+8)')