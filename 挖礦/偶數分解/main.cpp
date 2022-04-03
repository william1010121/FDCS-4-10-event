#include<bits/stdc++.h>
using namespace std;
#define V vector
#define S second
#define F first
#define MEM(x) memset(x, 0, sizeof(x))
#define ALL(x) begin(x), end(x)
#define REP(i, N, ...) for(int i = 0, ##__VA_ARGS__; i < N; i++)
#define FOR(i, a, b, ...) for(int i = (a), ##__VA_ARGS__; i <= (b); i++)
#define EP emplace
#define EB emplace_back
constexpr int mxN = 8e6;
V<int> vis(mxN, 0);
V<int> prime;


mt19937 gen(time(NULL));

/*
struct rnd_get{


    int vl, vr;
    bool multi;
    set<int> st;

    void (int _vl, int _vr, int _multi = true):vl(_vl), vr(_vr), _multi(multi) {};
};*/

void f_prime() {
	vis[0] = vis[1] = 1;
	for(int i = 2; i * i < mxN; ++i) {
		if( vis[i] ) continue;
		for(int j = i * i; j < mxN; j += i)
			vis[j] = true;
	}
	FOR(i, 3, mxN - 1) {
		if( !vis[i] ) prime.EB(i);
	}
}

pair<int,int> get_one_solution(int val) {
    if(val & 1) {
        cout << "val haven't any solution, it is even\n";
        return {-1, -1};
    }
    pair<int,int> ans;
    for(auto &i : prime) {
        if(val < i) break;
        if( !vis[val-i] ) {
            ans = make_pair(i, val-i);
            return ans;
        }
    }
}
int main () {
	f_prime();
	//cout << prime.size() << endl;
    uniform_int_distribution<int> dis(mxN/3, mxN/2);
    int val = dis(gen) * 2;
    cout << val << '\n';

    //test
    bool going = 0;
    auto a = get_one_solution(val);
    cout << "the one solution is: (" << a.F << ',' << a.S << ")\n";
    do{
        int cnt = 0;
        int pm1, pm2;
        cin >> pm1 >> pm2;
        for(auto &i : prime) cnt += int(pm1 == i), cnt += int(pm2 == i);
        going = !(cnt==2 && pm1+pm2==val);
        if( !going ) cout << "your ans is correct" << endl;
        else cout << "ans false" << endl;
    }while(going);



}
