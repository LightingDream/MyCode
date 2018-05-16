#include <cstdio>
#include <cstring>
using namespace std;

struct Node
{
    int a[10];
    bool col[10], line[18], tline[18];
    //a存放当前行放置的皇后位置
    //col数组标记父节点列冲突, line和tline标记两条斜线的冲突
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
    int fa;                                 //父节点编号
    int dep;                                //当前节点已放置的皇后深度(初识为0)
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
    ClosedNode * closedList = NULL;                         //Closed表
    OpenNode * openList = NULL;                             //Open表
    int cnt = 0;                                            //用于生成编号
    void addClosed(ClosedNode * node)                       //添加到Closed表中
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
    void addOpen(OpenNode * node)                           //添加到Open表中
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
    void bfs()                                              //广度优先搜索
    {
        OpenNode * init = new OpenNode(0, 0, Node());       //初识节点
        openList = init;
        int ans = 0;                                        //方案数
        while(openList)
        {
            OpenNode * now = openList;
            openList = openList->next;                      //移动Open表
            ClosedNode * tmp = new ClosedNode(now, ++cnt);  //加入Closed表并编号
            addClosed(tmp);
            if(tmp->node.dep == 8)                          //放置完成,输出皇后
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
                int currentRow = tmp->node.dep + 1;                 //扩展节点
                for(int i = 1; i <= 8; ++i)
                    if(!now->node.col[i] && !now->node.line[i+currentRow] && !now->node.tline[7+i-currentRow])       //列与斜线
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
