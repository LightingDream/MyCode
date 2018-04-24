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

struct FreeArea                                                         /**�������ṹ**/
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
    VPII arrange;                                                       /**�������ҵ����(��ַ,��С)*/
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
        printf("������з�����Ϣ:\n��ʼ��ַ\t��С\t״̬\n");
        for(int i = 0; i < N; ++i)
        {
            scanf("%d%d%d", &address, &len, &state);
            if(state == 0) arrange.pb(mp(address, len));
            else Add(new FreeArea(address, len, state));
        }
    }

    void Move()
    {
        for(int i = 0; i < cnt - 1; ++i)                                  /**�ձ�Ŀ(state == 0)�Ƶ�����**/
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
        FreeArea * cur = head;                                           /**������ʼ��ַ�ӵ͵�������**/
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
        printf("*************************������***************************\n");
        while(cur && cur->state == 1)
        {
            cur->print();
            cur = cur->next;
        }
        puts("");
        printf("************************************************************\n\n");

        printf("*************************�ѷ���*****************************\n");
        for(int i = 0; i < arrange.size(); ++i) printf("| %2d\t%2d |\n", arrange[i].fi, arrange[i].se);
        puts("");
        printf("************************************************************\n\n");

         printf("*************************�ȴ���*****************************\n");
        for(int i = 0; i < wait.size(); ++i) printf("| %2d |\n", wait[i]);
        puts("");
        printf("************************************************************\n\n");
    }

    int op_menu()
    {
        printf("*************************����ѡ��***************************\n");
        printf("|                  1. ��ҵ����     2. �ͷ�                 |\n");
        printf("|                 -1. Quit                                 |\n");
        printf("************************************************************\n");
        printf("ѡ��: \n");
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
            FreeArea * cur = head;                   /**�ϲ�**/
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

    void FF()                                       /**�״���Ӧ**/
    {
        int op = op_menu();
        while(~op)
        {
            if(op == 1)
            {
                printf("����������: \n");
                int len;
                scanf("%d", &len);
                if(Arrange(len) == -1) wait.pb(len);
                else First_Adjust();
            }else
            {
                printf("�����ͷ�������ʼ��ַ�ʹ�С: \n");
                int address, len;
                scanf("%d%d", &address, &len);
                int res = setFree(address, len);
                if(res)                                            /**�ͷųɹ�**/
                {
                    for(waitIt = wait.begin(); waitIt != wait.end(); ++waitIt)
                        if(~Arrange(*waitIt))
                        {
                            printf("�ȴ����з���!\n\n");
                            wait.erase(waitIt);
                            --waitIt;
                        }                                           /**����ȴ����У� �ɹ��Ƴ�����**/
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
        Input();                                           /**��ʼ����**/
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
/**test data(�״���Ӧ)
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
