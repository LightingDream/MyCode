#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;


struct Page
{
	int flag;
	int id;
	int mainId;
	int updateFlag;
	int address;
	Page(int id, int flag, int mainId, int updateFlag, int address)
	{
		this->id = id;
		this->flag = flag;
		this->mainId = mainId;
		this->updateFlag = updateFlag;
		this->address = address;
	}
	Page(){}
	void in()
	{
		scanf("%d%d%d%d", &id, &flag, &mainId, &updateFlag);
		cin >> hex >> address;
	}
	int getAbsoluteAddress()
	{
        return mainId * (1 << 12) + address;
	}
};

namespace Solve
{
	string cmd;
	char OP[] = "store";
	Page pageList[15];												//页表
	int len;
	void init()
	{

		printf("***************************************************************\n\n");
		printf("|        请求分页虚拟存储管理中的硬件地址变换过程模拟	      |\n\n");
		printf("***************************************************************\n\n");
		printf("初始化(输入页个数): \n");
		scanf("%d", &len);
		printf("各页初始信息:(页号, 标志, 主存块号, 修改位, 外存地址)\n");
		for(int i = 0; i < len; ++i) pageList[i].in();

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
	int op_menu()
	{
		printf("***************************************************************\n\n");
		printf("			1.输指令	-1.退出系统				\n\n");
		printf("***************************************************************\n");
		int op;
		scanf("%d", &op);
		return op;
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
	void Work()
	{
		printf("输入指令: \n");
		getchar();
		getline(cin, cmd);
        char t_op[15];
		int pageNum, address;
		//puts(cmd.c_str());
		//printf("%d\n", pageNum);
		getInfo(t_op, pageNum, address);
		Page &p = pageList[pageNum];
		if(p.flag == 1)
		{
		//    printf("%d %d\n", p. mainId, address);
            printf("绝对地址: %d\n", HexTran(p.mainId * 64 + address));                                                                //生成并输出绝对地址
			if(!strcmp(t_op, OP))	p.updateFlag = 1;						//存指令
		}else
		{
			printf("产生缺页中断!\n");
		//	DealWithMissPage();												//缺页处理
		}
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
    Solve::work();
	return 0;
}
