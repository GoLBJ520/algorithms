/**
* Copyright(c)
* All rights reserved.
* Author : hzs
* Description : cpp
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;
ll qmul(ll a,ll b,ll c)
{
    ll ret=0;
    while (b)
    {
        if (b & 1)
            ret = (ret + a) % c;
        b >>= 1;
        a = (a << 1) % c;
    }
    return ret;
}
ll qp(ll a,ll b,ll c)
{
    ll ret = 1;
    while (b)
    {
        if (b & 1)
            ret = qmul(ret, a, c);
            a = qmul(a, a, c);
        b >>= 1;
       // a = qmul(a, a, c);
    }
    return ret % c;
}

struct Matrix
{
	ll m[2][2];
}I;
Matrix mul(Matrix b, Matrix c) {
	Matrix ans;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			ans.m[i][j] = 0;
			for (int p = 0; p < 2; p++) {
				// 费马小定降幂
				ans.m[i][j] = (ans.m[i][j] + b.m[i][p] * c.m[p][j] % (mod - 1)) % (mod - 1);
			}
		}
	}
	return ans;
}
Matrix qpow(Matrix a, ll b) {
	Matrix ans = I;
	while (b) {
		if (b & 1) ans = mul(ans, a);
		a = mul(a, a);
		b >>= 1;
	}
	return ans;
}
Matrix e, a;
ll b[2][2];
int main(){
    ios::sync_with_stdio(false);
    cout.tie(0), cin.tie(0);
    ll A, B, n;
    while (cin >> A >> B >> n) {
    	if (n == 0) {
    		cout << A % mod<< endl;
    		continue;
    	}
    	else if (n == 1) {
    		cout << B % mod << endl;
    		continue;
    	}
    	else if (n == 2) {
    		cout << A * B % mod << endl;
    		continue;
    	}
    	//else if (n == 3)
    	a.m[0][0] = 1, a.m[0][1] = 1;
    	a.m[1][0] = a.m[1][1] = 0;
    	b[0][1] = b[1][0] = b[1][1] = 1;
    	for (int i = 0; i < 2; i++) {
    		for (int j = 0; j < 2; j++) {
    			e.m[i][j] = b[i][j];
    		}
    	}
    	// for (int i = 0;  i< 2; i++) {
    	// 	for (int j = 0; j < 2; j++) {
    	// 		cout << e.m[i][j] << " ";
    	// 	}
    	// 	cout << endl;
    	// }
    	I.m[0][0] = I.m[1][1] = 1;
    	e = qpow(e, n - 2);
    	ll ans;
    	e = mul(a, e);
    	// for (int i = 0;  i< 2; i++) {
    	// 	for (int j = 0; j < 2; j++) {
    	// 		cout << e.m[i][j] << " ";
    	// 	}
    	// 	cout << endl;
    	// }
    	ans = qp(A, e.m[0][0], mod) * qp(B, e.m[0][1], mod) % mod;
    	cout << ans << endl;
    }
    return 0;
}