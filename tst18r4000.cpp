#define LOCAL_HERE
//#define TC_SUBMIT
//#define _CRT_SECURE_NO_WARNINGS 
//#pragma GCC optimize ("O3")
//#pragma GCC target ("avx")
#pragma GCC target ("sse4.2")
//#include <emmintrin.h>
#include <bits/stdc++.h>
#include <sys/time.h>
//-----------------------------------------------------------------------//
// TCO 2018R3 MM
//
// 
//-----------------------------------------------------------------------//
//
//
#define rep2(x,fr,to) for(int (x)=(fr);(x)<(to);(x)++)
#define rep(x,to) for(int (x)=0;(x)<(to);(x)++)
#define repr(x,fr,to) for(int (x)=(fr);(x)>=(to);(x)--)
#define all(c) (c).begin(),(c).end()
#define sz(v) (int)(v).size()
#define cauto(x, v) for(const auto& x: (v))

using namespace std;
typedef int64_t ll;
typedef uint64_t ull;
typedef double DBL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<uint8_t>> V2;
typedef pair<int, int> PII;
typedef pair<int, DBL> PID;
typedef pair<DBL, VI> PDV;

#ifndef TC_SUBMIT
#define _P(...) (void)fprintf(stderr, __VA_ARGS__)
	const double cycles_ini = 2300000.0;
	const double TLMT_ini = 9840.0 ;
	void dbg(){ cerr << "\n"; }  
	template <typename T1,typename ...T2>
	void dbg(const T1& p1, const T2&...pr){ cerr << p1 << ": "; dbg(pr...);}
#else
#define _P(...)
	const double cycles_ini = 2800000.0;
	const double TLMT_ini = 9840.0;
	void dbg(...){  }  
#endif
 
class Timer{
private:
	double get_sec()
	{
		ull crdt = rdtsc();
		double rtn = (double)(crdt - s_rdtsc)/ cycles_per_sec;
		if(rtn > tadj  ){ adjf(); tadj *= 2; }
		return rtn;
	}
	ull s_rdtsc, tadj = 2000;
	double ms_stim, cycles_per_sec;
	ull rdtsc(){
#if defined(_MSC_VER)
		return __rdtsc();
#elif defined(__amd64)
		ull a, d;
		__asm__ volatile ("rdtsc" : "=a" (a), "=d" (d)); 
		return (d<<32) | a;
#else
		ull x;
		__asm__ volatile ("rdtsc" : "=A" (x)); 
		return x;
#endif
	}
	double get_ms(){
#ifdef _MSC_VER
		return (double)GetTickCount(); 
#else
		struct timeval t; gettimeofday(&t, NULL);
		return  (double)t.tv_sec * 1000 + (double)t.tv_usec / 1000;
#endif
	}
	void adjf(){
		double ctim = get_ms();
		cycles_per_sec = (double)(rdtsc() - s_rdtsc)/ (ctim - ms_stim);
	}
 
public:
	//Timer() { start();}
	void start() {
		cycles_per_sec = cycles_ini;
		ms_stim = get_ms();
		s_rdtsc = rdtsc();
	}
	double get_elapsed() { return  get_sec(); }
	double get_cyc(){ return cycles_per_sec; }
};

class xorshift{
public:
	xorshift(){ xorshift(88675123U);}
	xorshift(uint32_t Seed){init(Seed);}
	void init(uint32_t Seed){
		x =123456789U , y= 362436069U, z= 521288629U;
		w=1812433253U * (Seed ^ (Seed >> 30));
		for(int i=0;i<23;i++) next();
	}
	uint32_t  next(){
		uint32_t t = (x ^ (x << 11));
		x = y; y = z; z = w;
		return  w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
	int  next(int Min, int Max){ return (int)(next()% (Max - Min + 1)) + Min; }
private:
	uint32_t x, y, z, w;
};


	mt19937 mran((uint32_t)time(nullptr));
	//int xran(int su){ return mran()%su;};
	xorshift xorran(20180516);//(uint32_t)time(nullptr));//(20171030)
	int xran(int su){ return xorran.next() % su;}
	int xran2(){ return xorran.next() & 0xFFF;}
	//int xran2(){ return mran() & 0xFFF;}

// ---------------------------------------------------------------------------
Timer tm01;
DBL TLMT = TLMT_ini;
DBL CTM;
int H, W;
int csL, csM, csO;
int mxO, mxM;
const char itm[] = {'1', '2', '4', '/', '\\', 'X'};
vector<vector<uint8_t> > BA;
const int DX[]={1,0,-1,0}, DY[]={0,1,0,-1};
const string SDR ="RDLU";
// ---------------------------------------------------------------------------
class CakeSharing {
public:
	vector<string> cut(vector<string> roses, int NP) {
		vector<string> ret(4);
		ret[0] = "2 0 2 10";
		ret[1] = "6 10 6 0";
		ret[2] =  "2 6 6 4";
		ret[3] =  "7 0 9 10";
		return ret;
	}
};
// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
	for (int i = 0; i < v.size(); ++i)
		cin >> v[i];
}

int main() {
	CakeSharing cs;
	int H;
	cin >> H;
	vector<string> roses(H);
	getVector(roses);
	int NP;
	cin >> NP;

	vector<string> ret = cs.cut(roses, NP);
	cout << ret.size() << endl;
	for (int i = 0; i < (int)ret.size(); ++i)
		cout << ret[i] << endl;
	cout.flush();
}
