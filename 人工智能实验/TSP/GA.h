#ifndef _GA_H_
#define _GA_H_
    typedef double ld;
    #define GROUP_NUM 40        //种群个数
    #define CITY_NUM  10       //城市个数
    #define Cross_Rate  0.8     //杂交概率
    #define Mutation_Rate 0.01  //突变概率
    #define Generate_NUM 100   //代数

    struct Graph
    {
        int arc[CITY_NUM][CITY_NUM];
    }G;                         //图

    struct TSP_Solution
    {
        int Path_Length;        //路径长度
        ld Select_Rate;         //选择概率
        int Path[CITY_NUM + 1];     //路径(包括起点)
    };

    TSP_Solution Group_Solution[GROUP_NUM];     //种群(父代)
    TSP_Solution Son_Solution[GROUP_NUM];       //子代
#endif