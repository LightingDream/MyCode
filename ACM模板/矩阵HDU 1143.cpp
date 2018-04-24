#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;

const int maxtrix_size = 10;
const ll mod = 1e9 + 7;

template <class T>
struct Matrix
{
	Matrix<int> res;
	T mat[maxtrix_size][maxtrix_size];
	int row, col;
	Matrix(){}
    Matrix(int r, int c):row(r),col(c){}
	void clr()
	{
		memset(mat, 0, sizeof mat);
	}
	void E()
	{
		clr();
		for (int i = 0; i < row; ++i) mat[i][i] = 1;
	}
	void add(T &a, T b) const
	{
	 	a = a + b;
	}
	Matrix<T> operator * (const Matrix<T> rhs) const
	{
		Matrix<T>res(row, rhs.col);
		res.clr();
		for (int i = 0; i < res.row; ++i)
			for (int j = 0; j < res.col; ++j)
				for (int k = 0; k < col; ++k)
					add(res.mat[i][j], mat[i][k] * rhs.mat[k][j]);
		return res;
	}
	Matrix<T> operator ^ (T b) const
	{
		Matrix<T>res(row, col);
		res.E();
		Matrix<ll>a = *this;
		while (b)
		{
			if (b & 1) res = res * a;
			a = a * a;
			b >>= 1;
		}
		return res;
	}
	void debug() const
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				printf("%lld ", mat[i][j]);
			}
			puts("");
		}
	}
};
int main() {
	ll f[] = { 1, 3, 11 };
	int n;
	while (~scanf("%d", &n), ~n)
	{
		Matrix<ll> tmp(3,3);
		tmp.clr();                                //¹¹Ôìµ×Êý¾ØÕó
		tmp.mat[0][0] = 4;
		tmp.mat[0][1] = -1;
		tmp.mat[1][0] = 1;
		tmp.mat[2][1] = 1;
		if (n & 1)
			puts("0");
		else {
			if (n <= 4) {
				printf("%lld\n", f[n / 2]);
			}
			else {
				Matrix<ll> res = tmp ^ ((n - 4) >> 1);     
				ll ans = 11 * res.mat[0][0] + 3 * res.mat[0][1] + res.mat[0][2];
				printf("%lld\n", ans);
			}
		}//ans
	}
	return 0;
}