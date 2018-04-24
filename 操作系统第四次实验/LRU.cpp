#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> VI;
typedef VI::iterator VIT;

struct Page
{
	int id;
	int mainId;
	int updateFlag;
	int address;
	int flag;
	Page(int id, int address)
	{
	    this->flag = 0;
		this->id = id;
		this->mainId = -1;                  /**初始化-1表示不在主存**/
		this->updateFlag = 0;
		this->address = address;
	}
	Page(){}
	void in()
	{
		scanf("%d", &id);
		cin >> hex >> address;
		mainId = -1;
		updateFlag = 0;
		flag = 0;
		cout << id << " ";
		cout << hex << address << endl;
	}
	void out()
	{
	    printf("|%d\t%d\t%d\t%d\t%d|\n", id, flag, mainId, updateFlag, address);
	}
	void init()
	{
	    mainId = -1;
	    updateFlag = 0;
	    flag = 0;
	}
};

namespace LRU
{
	Page pageList[15];                                                          /**页表**/
	const int N = 4;                											/**作业最大分配块数**/
	VI memoryList;                                                              /**主存分块表**/
	VIT it;
	int len;
	string cmd;
	void init()
	{
	    freopen("ce.in", "r", stdin);
		printf("***************************************************************\n\n");
		printf("|        LRU算法实现分页管理的缺页调度	      |\n\n");
		printf("|           作业最大分配块数: %d	              |\n\n", N);
		printf("***************************************************************\n\n");
		printf("初始化作业(输入页个数): \n");
		scanf("%d", &len);
		printf("%d\n", len);
		printf("各页初始信息:(页号, 外存地址)\n");
		for(int i = 0; i < len; ++i) pageList[i].in();
		freopen("/dev/tty", "r", stdin);
	}
	int HexTran(int x)
	{
	    int ret = 0;
	    int v = 1;
        for(int i = 0; i < 4; ++i)
        {
            int tmp = 0;
            for(int j = 4 * i; j < 4 * i + 4; ++j)
                tmp += (x & (1 << j) ? 1 : 0) << (j - 4 * i);
            ret += tmp * v;
            v *= 10;
        }
        return ret;
	}
	void getInfo(char a[], int &pageNum, int &address)
	{
		int i = 0;
		while(cmd[i] != ' ')
		{
			a[i] = cmd[i];
			++i;
		}
		a[i] = 0;
		++i;

		pageNum = 0;
		while(cmd[i] != ' ')
		{
			pageNum = 10 * pageNum + cmd[i] - '0';
			++i;
		}
		++i;

		address = 0;
		while(cmd[i])
		{
			address = 16 * address + cmd[i] - '0';
			++i;
		}
	}
	int op_menu()
	{
		printf("***************************************************************\n\n");
		printf("			1.访问页号	-1.退出系统				\n\n");
		printf("***************************************************************\n");
		int op;
		scanf("%d", &op);
		return op;
	}
	VIT Find(int num)
	{
        VIT res = memoryList.begin();
        while(res != memoryList.end())
        {
            if(*res == num) return res;
            ++res;
        }
        return res;
	}
	void Output()
	{
        printf("***************************************************************\n\n");
		printf("|           主存分块表(已分配内存块: %d)	              |\n\n", memoryList.size());
		printf("|");
		for(int i = 0; i < memoryList.size(); ++i)
            printf(" %d", memoryList[i]);
        puts("|");
		printf("***************************************************************\n\n");
		printf("***************************************************************\n\n");
		printf("|页号 标志 主存块号 修改位 外存地址|\n");
		for(int i = 0; i < len; ++i) pageList[i].out();
		printf("***************************************************************\n\n");
	}
	void Work()
	{
		printf("输入指令: \n");
		getchar();
		getline(cin, cmd);
        char t_op[15];
		int num, address;
		getInfo(t_op, num, address);
		VIT it = Find(num);                                              /**在主存分块表中查找该页**/
        if(it != memoryList.end())                                       /**在主存**/
        {
            printf("已在主存!\n");
            pageList[num].updateFlag = 1;
            if(it != --memoryList.end())                                 /**放到栈顶(先删除,在移到尾部)**/
            {
                memoryList.erase(it);
                memoryList.push_back(num);
            }
        }else
        {
            printf("不在主存中!\n");
            if(memoryList.size() == N)                                  /**主存分块表已满**/
            {
                int rm = memoryList[0];
                printf("淘汰%d页\n", rm);
                if(pageList[rm].updateFlag == 1)    printf("调页%d到磁盘\n", rm);
                pageList[num].mainId = pageList[rm].mainId;
                pageList[rm].init();
                memoryList.erase(memoryList.begin());
            }else pageList[num].mainId = memoryList.size();
            pageList[num].flag = 1;
            memoryList.push_back(num);
        }
        printf("绝对地址: %d\n\n", HexTran(pageList[num].mainId * 64 + address));
        Output();
	}
	void work()
	{
		init();
		int op = op_menu();
		while(op != -1)
		{
			Work();
			op = op_menu();
		}
	}
}

int main()
{
    LRU::work();
	return 0;
}

