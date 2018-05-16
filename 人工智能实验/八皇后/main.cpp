#include <cstdio>
#include <cstring>
using namespace std;

struct Node
{
    int a[10];
    bool col[10], line[18], tline[18];
    //a��ŵ�ǰ�з��õĻʺ�λ��
    //col�����Ǹ��ڵ��г�ͻ, line��tline�������б�ߵĳ�ͻ
    Node()
    {
        memset(a, 0, sizeof a);
        memset(col, 0, sizeof col);
        memset(line, 0, sizeof line);
        memset(tline, 0,sizeof tline);
    }
};

struct OpenNode
{
    Node node;
    int fa;                                 //���ڵ���
    int dep;                                //��ǰ�ڵ��ѷ��õĻʺ����(��ʶΪ0)
    OpenNode * next;
    OpenNode(){}
    OpenNode(int f, int d, Node newNode)
    {
        node = newNode;
        fa = f;
        dep = d;
        next = NULL;
    }
};

struct ClosedNode
{
    OpenNode node;
    int id;
    ClosedNode * next;
    ClosedNode(OpenNode * v, int idnum)
    {
        id = idnum;
        node = *v;
        next = NULL;
    }
};


namespace EightQueens
{
    ClosedNode * closedList = NULL;                         //Closed��
    OpenNode * openList = NULL;                             //Open��
    int cnt = 0;                                            //�������ɱ��
    void addClosed(ClosedNode * node)                       //��ӵ�Closed����
    {
        if(closedList == NULL)
        {
            closedList = node;
            return;
        }
        ClosedNode * tmp = closedList;
        while(tmp->next) tmp = tmp->next;
        tmp->next = node;
    }
    void addOpen(OpenNode * node)                           //��ӵ�Open����
    {
        if(openList == NULL)
        {
            openList = node;
            return;
        }
        OpenNode * tmp = openList;
        while(tmp->next) tmp = tmp->next;
        tmp->next = node;
    }
    void bfs()                                              //�����������
    {
        OpenNode * init = new OpenNode(0, 0, Node());       //��ʶ�ڵ�
        openList = init;
        int ans = 0;                                        //������
        while(openList)
        {
            OpenNode * now = openList;
            openList = openList->next;                      //�ƶ�Open��
            ClosedNode * tmp = new ClosedNode(now, ++cnt);  //����Closed�����
            addClosed(tmp);
            if(tmp->node.dep == 8)                          //�������,����ʺ�
            {
                ++ans;
                printf("*************************\n");
                for(int i = 1; i <= 8; ++i)
                {
                    for(int j = 1; j <= 8; ++j)
                    printf("%d ", tmp->node.node.a[i] == j ? 1 : 0);
                    printf("\n\n");
                }
                printf("*************************\n\n");
            }
            else
            {
                int currentRow = tmp->node.dep + 1;                 //��չ�ڵ�
                for(int i = 1; i <= 8; ++i)
                    if(!now->node.col[i] && !now->node.line[i+currentRow] && !now->node.tline[7+i-currentRow])       //����б��
                    {
                        OpenNode * temp = new OpenNode(tmp->id, now->dep + 1, now->node);
                        temp->node.a[currentRow] = i;
                        temp->node.col[i] = 1;
                        temp->node.line[i + currentRow] = 1;
                        temp->node.tline[7 + i-currentRow] = 1;
                        addOpen(temp);
                    }
            }
        }
        printf("%d\n", ans);
    }
}

int main()
{
    EightQueens::bfs();
    return 0;
}
