#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
using namespace std;

typedef vector<int> VI;
typedef vector< pair<int, int> > VPII;
#define fi first
#define se second
#define pb push_back
#define mp make_pair

struct FreeArea                                                         /**空闲区结构**/
{
    int address;
    int len;
    int state;
    FreeArea * next;
    FreeArea * pre;
    FreeArea(int _address, int _len, int _state)
    {
        address = _address;
        len = _len;
        state = _state;
        next = NULL;
        pre = NULL;
    }
    void print()
    {
        printf("| %2d\t%2d |\n", address, len);
    }
};


namespace Solve
{

    const int N = 3;
    int cnt = N;
    FreeArea * head = NULL;
    VPII arrange;                                                       /**分配的作业队列(地址,大小)*/
    VI wait;
    VPII::iterator arrangeIt;
    VI::iterator waitIt;

    void Add(FreeArea * p)
    {
        if(head == NULL)
        {
            head = p;
            return;
        }
        FreeArea * cur = head;
        while(cur->next) cur = cur->next;
        cur->next = p, p->pre = cur;
    }

    void Input()
    {
        int address, len, state;
        printf("输入空闲分区信息:\n起始地址\t大小\t状态\n");
        for(int i = 0; i < N; ++i)
        {
            scanf("%d%d%d", &address, &len, &state);
            if(state == 0) arrange.pb(mp(address, len));
            else Add(new FreeArea(address, len, state));
        }
    }

    void Move()
    {
        for(int i = 0; i < cnt - 1; ++i)                                  /**空表目(state == 0)移到后面**/
        {
            FreeArea * cur = head;
            while(cur->next)
            {
                if(cur->state == 0 && cur->next->state == 1)
                {
                    FreeArea * tmp = cur->next;
                    cur->next = cur->next->next;
                    if(cur->next) cur->next->pre = cur;
                    tmp->pre = cur->pre;
                    if(cur->pre) cur->pre->next = tmp;
                    else head = tmp;
                    tmp->next = cur;
                    cur->pre = tmp;
                    cur = tmp;
                }
                cur = cur->next;
            }
        }
    }

    void First_Adjust()
    {
        FreeArea * cur = head;                                           /**按照起始地址从低到高排序**/
        for(int i = 0; i < cnt - 1; ++i)
        {
            FreeArea * cur = head;
            while(cur->next)
            {
                if(cur->address > cur->next->address)
                {
                    FreeArea * tmp = cur->next;
                    cur->next = cur->next->next;
                    if(cur->next) cur->next->pre = cur;
                    tmp->pre = cur->pre;
                    if(cur->pre) cur->pre->next = tmp;
                    else head = tmp;
                    tmp->next = cur;
                    cur->pre = tmp;
                    cur = tmp;
                }
                cur = cur->next;
            }
        }
        Move();
    }

    void Print()
    {
        FreeArea * cur = head;
        printf("*************************空闲区***************************\n");
        while(cur && cur->state == 1)
        {
            cur->print();
            cur = cur->next;
        }
        puts("");
        printf("************************************************************\n\n");

        printf("*************************已分配*****************************\n");
        for(int i = 0; i < arrange.size(); ++i) printf("| %2d\t%2d |\n", arrange[i].fi, arrange[i].se);
        puts("");
        printf("************************************************************\n\n");

         printf("*************************等待中*****************************\n");
        for(int i = 0; i < wait.size(); ++i) printf("| %2d |\n", wait[i]);
        puts("");
        printf("************************************************************\n\n");
    }

    int op_menu()
    {
        printf("*************************操作选项***************************\n");
        printf("|                  1. 作业申请     2. 释放                 |\n");
        printf("|                 -1. Quit                                 |\n");
        printf("************************************************************\n");
        printf("选项: \n");
        int op;
        scanf("%d", &op);
        return op;
    }

    int Arrange(int len)
    {
        FreeArea * cur = head;
        while(cur)
        {
            if(cur->state == 0) break;
            if(cur->len >= len)
            {
                arrange.pb(mp(cur->address, len));
                cur->address += len;
                cur->len -= len;
                if(cur->len == 0) cur->state = 0;
                return cur->address - len;
            }
            cur = cur->next;
        }
        return -1;
    }

    int setFree(int address, int len)
    {
        int f = 0;
        for(arrangeIt = arrange.begin(); arrangeIt != arrange.end(); ++arrangeIt)
            if((*arrangeIt).fi == address && (*arrangeIt).se == len)
            {
                f = 1;
                arrange.erase(arrangeIt);
                break;
            }
        if(f)
        {
            Add(new FreeArea(address, len, 1));
            ++cnt;
            First_Adjust();
            FreeArea * cur = head;                   /**合并**/
            while(cur->next && cur->next->state == 1)
            {
                if(cur->address + cur->len == cur->next->address)
                {
                    cur->len += cur->next->len;
                    cur->next = cur->next->next;
                    if(cur->next) cur->next->pre = cur;
                    --cnt;
                }
                else cur = cur->next;
            }
        }
        return f;
    }

    void FF()                                       /**首次适应**/
    {
        int op = op_menu();
        while(~op)
        {
            if(op == 1)
            {
                printf("输入申请量: \n");
                int len;
                scanf("%d", &len);
                if(Arrange(len) == -1) wait.pb(len);
                else First_Adjust();
            }else
            {
                printf("输入释放区的起始地址和大小: \n");
                int address, len;
                scanf("%d%d", &address, &len);
                int res = setFree(address, len);
                if(res)                                            /**释放成功**/
                {
                    for(waitIt = wait.begin(); waitIt != wait.end(); ++waitIt)
                        if(~Arrange(*waitIt))
                        {
                            printf("等待队列分配!\n\n");
                            wait.erase(waitIt);
                            --waitIt;
                        }                                           /**分配等待队列， 成功移出队列**/
                }
            }
            First_Adjust();
            Print();
            op = op_menu();
        }
        printf("END\n");
    }

    void Work()
    {
        printf("Init: \n");
        Input();                                           /**初始输入**/
        First_Adjust();
        Print();
        FF();
    }
}
int main()
{
    freopen("in.txt", "r", stdin);
    Solve::Work();
    return 0;
}
/**test data(首次适应)
200 70 1
400 80 1
500 100 1
1
80
1 70
1 70
2
500 70
-1
**/
