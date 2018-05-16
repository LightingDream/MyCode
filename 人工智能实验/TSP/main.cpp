#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <algorithm>
#include <stdlib.h>
#include "GA.h"

namespace TSP
{
    int Start_Point;
    bool vis[CITY_NUM + 1];
    int Father_Cross[CITY_NUM];
    int Mother_Cross[CITY_NUM];
    void Show()
    {
        printf("---------------GA求解TSP--------------------\n");
        printf(" 参数: \n");
        printf("【城市个数】: %d\n", CITY_NUM);
        printf("【种群个数】: %d\n", GROUP_NUM);
        printf("【杂交概率】: %f\n", Cross_Rate);
        printf("【变异概率】: %f\n", Mutation_Rate);
        printf("【遗传代数】: %d\n", Generate_NUM);
        printf("-------------------------------------------\n\n");
    }
    void Init_Graph()
    {
        printf("无向图: \n");
        srand(time(NULL));
        for(int i = 0; i < CITY_NUM; ++i)
            for(int j = 0; j < CITY_NUM; ++j)
            {
                G.arc[i][j] = rand() % 100 + 1;
                printf("%d%s", G.arc[i][j], j == CITY_NUM - 1 ? "\n" : " ");
            }
        printf("选择起点(0->%d): \n", CITY_NUM - 1);
        scanf("%d", &Start_Point);
    }
    void Calculate_Select_Rate()
    {

        ld sum = 0;
        for(int Group_Index = 0; Group_Index < GROUP_NUM; ++Group_Index)
        {
            Group_Solution[Group_Index].Select_Rate = 1.0 / Group_Solution[Group_Index].Path_Length;
            sum +=  Group_Solution[Group_Index].Select_Rate;
        }

        for(int Group_Index = 0; Group_Index < GROUP_NUM; ++Group_Index)
            Group_Solution[Group_Index].Select_Rate /= sum;
    }
    void Init_Group()                                       //初始化种群
    {
        for(int Group_Index = 0; Group_Index < GROUP_NUM; ++Group_Index)
        {
             memset(vis, 0, sizeof vis);
             vis[Start_Point] = 1;
             TSP_Solution &solution = Group_Solution[Group_Index];
             solution.Path[0] = solution.Path[CITY_NUM] = Start_Point;
             solution.Path_Length = 0;
             for(int i = 1; i < CITY_NUM; ++i)
             {
                int index = rand() % CITY_NUM;
                while(vis[index]) index = rand() % CITY_NUM;
                vis[index] = 1;
                solution.Path[i] = index;
                solution.Path_Length += G.arc[solution.Path[i - 1]][solution.Path[i]];
             }
            solution.Path_Length += G.arc[solution.Path[CITY_NUM - 1]][solution.Path[CITY_NUM]];
        }
        Calculate_Select_Rate();
    }
    void Output_Group()
    {
        TSP_Solution Best;
        Best.Path_Length = 0x7fffffff;

        for(int i = 0; i < GROUP_NUM; ++i)
        {
            TSP_Solution &solution = Group_Solution[i];
            printf("【路径】: \n");
            for(int j = 0; j < CITY_NUM + 1; ++j)
                printf("%d%s", solution.Path[j], j == CITY_NUM ? "\n" : "->");
            printf("【路径长度】: %d 【选择概率】：%f\n\n", solution.Path_Length, solution.Select_Rate);
            if(Best.Path_Length > solution.Path_Length) Best = solution;
        }

        printf("当前最优: \n");
        printf("【路径】: \n");
        for(int j = 0; j < CITY_NUM + 1; ++j)
            printf("%d%s", Best.Path[j], j == CITY_NUM ? "\n" : "->");
        printf("【路径长度】: %d 【选择概率】：%f\n\n", Best.Path_Length, Best.Select_Rate);
        printf("--------------------------------------------\n\n");

    }
    int GA_Select()
    {
        ld Rand_Rate = 1.0 * (rand() % 100) / 100;
        ld sum = 0;
        for(int i = 0; i < GROUP_NUM; ++i)
        {
            sum += Group_Solution[i].Select_Rate;
            if(Rand_Rate < sum) return i;
        }
    }
    void Swap(int &a, int &b)
    {
        int tmp = b;
        b = a;
        a = tmp;
    }
    int * getConflict(int cur[], int model[], int len, int &Conflict_Len)
    {
        int * res = new int[CITY_NUM];
        Conflict_Len = 0;
        for(int i = 0; i < len; ++i)
        {
            bool flag = 0;
            for(int j = 0; j < len; ++j)
                if(cur[i] == model[j])
                {
                    flag = 1;
                    break;
                }
            if(!flag) res[Conflict_Len++] = cur[i];
        }
        return res;
    }
    void GA_Cross(int Father_Index, int Mother_Index)
    {
            int l = rand() % (CITY_NUM - 1) + 1;
            int r = rand() % (CITY_NUM - 1) + 1;
            if(l > r) Swap(l, r);
            TSP_Solution &father = Son_Solution[Father_Index];
            TSP_Solution &mother = Son_Solution[Mother_Index];
            int Cross_Length = r - l + 1, Conflict_Length;
            for(int i = l; i <= r; ++i)
            {
                Father_Cross[i - l] = father.Path[i];
                Mother_Cross[i - l] = mother.Path[i];
            }
            int * f_conflict = getConflict(Father_Cross, Mother_Cross, Cross_Length, Conflict_Length);
            int * m_conflict = getConflict(Mother_Cross, Father_Cross, Cross_Length, Conflict_Length);
            for(int i = 0; i < Conflict_Length; ++i)
            {
                for(int j = 1; j < CITY_NUM; ++j)
                    if(father.Path[j] == m_conflict[i])
                    {
                        father.Path[j] = f_conflict[i];
                        break;
                    }
                for(int j = 1; j < CITY_NUM; ++j)
                    if(mother.Path[j] == f_conflict[i])
                    {
                        mother.Path[j] = m_conflict[i];
                        break;
                    }
            }
            for(int i = l; i <= r; ++i)
                Swap(father.Path[i], mother.Path[i]);
    }
    void GA_Mutate(TSP_Solution &tsp)
    {
        int l = rand() % (CITY_NUM - 1) + 1;
        int r = rand() % (CITY_NUM - 1) + 1;
        while(l == r) r = rand() % (CITY_NUM - 1) + 1;
        Swap(tsp.Path[l], tsp.Path[r]);
    }
    void Work()
    {
        int Current_Generate_Num = 0;
        while(Current_Generate_Num < Generate_NUM)          //迭代
        {
            printf("第%d代种群: \n\n", Current_Generate_Num);
            Output_Group();

            int M = GROUP_NUM >> 1;                         //成对选择次数
            int Son_Index = 0;
            while(M--)
            {

                int Father_Index = GA_Select();             //选择
                int Mother_Index = GA_Select();
                while(Mother_Index == Father_Index) Mother_Index = GA_Select();
                Son_Solution[Son_Index++] = Group_Solution[Father_Index];
                Son_Solution[Son_Index++] = Group_Solution[Mother_Index];
                ld cross_rate = (rand() % 100 + 0.0) / 100;
                if(cross_rate < Cross_Rate)                 //杂交
                    GA_Cross(Son_Index - 2, Son_Index - 1);
            }

            for(int i = 0; i < Son_Index; ++i)
            {
                ld mutation_rate = (rand() % 100 + 0.0) / 100;
                if(mutation_rate < Mutation_Rate)                  //突变
                    GA_Mutate(Son_Solution[i]);
            }
            for(int i = 0; i < GROUP_NUM; ++i)
                Group_Solution[i] = Son_Solution[i];
            ++Current_Generate_Num;
        }
        printf("第%d代种群: \n\n", Current_Generate_Num);
        Output_Group();
    }
    void work()
    {
        Show();
        Init_Graph();
        Init_Group();
        Work();
    }
}

int main()
{
   // freopen("ce.out", "w", stdout);
    TSP::work();
    return 0;
}
