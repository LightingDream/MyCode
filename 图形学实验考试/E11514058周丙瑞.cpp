/**
    E11514058 周丙瑞
**/

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

int poly[] = {100, 500, 500, 400, 300, 200, 100, 500};         /**原多边形坐标**/
int newPoly[8];                                                /**新多边形坐标**/

inline int Min(int a, int b)
{
    return a <= b ? a : b;
}

struct Matrix
{
    double mat[3][3];
    int row, col;

    Matrix(){}
    Matrix(int row, int col)
    {
        this->row = row;
        this->col = col;
    }

    void clr()
    {
        for(int i = 0; i < row; ++i)
                for(int j = 0; j < col; ++j)
                        mat[i][j] = 0;
    }
    //零矩阵
    void E()
    {
        clr();
        for(int i = 0; i < Min(row, col); ++i) mat[i][i] = 1;
    }
    //单位矩阵

    Matrix operator * (const Matrix &rhs) const
    {
        Matrix ret(row, rhs.col);
        ret.clr();

        for(int i = 0; i < row; ++i)
                for(int j = 0; j < rhs.col; ++j)
                        for(int k = 0; k < col; ++k)
                                ret.mat[i][j] += mat[i][k] * rhs.mat[k][j];
        return ret;
    }
    //矩阵乘法
};

Matrix mov(3, 3), rotate(3, 3), tran(3, 3), rotate_inv(3, 3), mov_inv(3, 3);
//变换矩阵
void initMatrix()
{
    mov.E();
    rotate.E();
    tran.E();
    rotate_inv.E();
    mov_inv.E();
}
//初始化变换矩阵
int main()
{
        initMatrix();


        initgraph(600, 600);
        drawpoly(4, poly);
        getch();
        //原多边形
        printf("输入直线(Ax+By+C=0)<-(A, B, C): \n");
        int A, B, C;
        scanf("%d%d%d", &A, &B, &C);

        if(A == 0 && B)
        {
                int y = (int)(-1.0 * C / B + 0.5);
                for(int x = 0; x < 600; ++x)
                        putpixel(x, y, RED);
                //画直线
                mov.mat[2][1] = 1.0 * C / B;
                mov_inv.mat[2][1] = -1.0 * C / B;
                tran.mat[1][1] = -1;
                //给变换矩阵赋值
        }else
        {
                if(A && B == 0)
                {
                        int x = (int)(-1.0 * C / A + 0.5);
                        for(int y = 0; y < 600; ++y)
                                putpixel(x, y, RED);

                        mov.mat[2][0] = 1.0 * C / A;
                        mov_inv.mat[2][0] = -1.0 * C / A;
                        tran.mat[0][0] = -1;

                }else
                {

                        for(int x = 0; x < 600; ++x)
                        {
                                int y = (int)((-1.0 * C - A * x) / B + 0.5);
                                putpixel(x, y, RED);
                        }

                        mov.mat[2][0] = 1.0 * C / A;
                        mov_inv.mat[2][0] = -1.0 * C / A;
                        tran.mat[1][1] = -1;


                        double angle = atan(- 1.0 * A / B);
                        double COS = cos(angle);
                        double SIN = sin(angle);
                        rotate.mat[0][0] = rotate.mat[1][1] = COS;
                        rotate.mat[0][1] = -SIN;
                        rotate.mat[1][0] = SIN;

                        rotate_inv.mat[0][0] = rotate_inv.mat[1][1] = COS;
                        rotate_inv.mat[0][1] = SIN;
                        rotate_inv.mat[1][0] = -SIN;
                }
        }

        Matrix T = mov * rotate * tran * rotate_inv * mov_inv;
        //合成

        Matrix polyMatrix(3, 3);
        for(int i = 0; i < 3; ++i)
        {
                polyMatrix.mat[i][0] = poly[i * 2];
                polyMatrix.mat[i][1] = poly[i * 2 + 1];
                polyMatrix.mat[i][2] = 1;
        }
        //原其次坐标矩阵
        polyMatrix = polyMatrix * T;

        for(int i = 0; i < 3; ++i)
        {
                newPoly[i * 2] = (int)(polyMatrix.mat[i][0] + 0.5);
                newPoly[i * 2 + 1] = (int)(polyMatrix.mat[i][1] + 0.5);
        }
        newPoly[6] = newPoly[0];
        newPoly[7] = newPoly[1];
        //齐次坐标存数组

        drawpoly(4, newPoly);
        //对称多边形
        getch();
        closegraph();
        return 0;
}
