#pragma GCC optimize ("O3")
#pragma GCC target ("avx")
#include <bits/stdc++.h>

#define rep2(x,fr,to) for(int (x)=(fr);(x)<(to);(x)++)
#define rep(x,to) for(int (x)=0;(x)<(to);(x)++)
#define repr(x,fr,to) for(int (x)=(fr);(x)>=(to);(x)--)
#define all(c) (c).begin(),(c).end()
#define sz(v) (int)(v).size()

using namespace std;
typedef long long ll; typedef vector<int> VI; typedef pair<int,int> pii;

const int mod = (int)1e9 + 7;
void dbg(){ cout << "\n"; } template <typename T,typename ...T2>
void dbg(const T& fst, const T2&...rst){ cout << fst << ": "; dbg(rst...); }

struct chtime{  
	chrono::system_clock::time_point ctm;
	chtime() { rstt();}
	void rstt() { ctm=chrono::system_clock::now();}
	uint64_t gtm(){
		auto ptm = chrono::system_clock::now() - ctm;
		return chrono::duration_cast<chrono::milliseconds>(ptm).count();
	}
	void disp(){ cerr << gtm() <<"\n";}
};

mt19937 mrn(4524548);//(unsigned)time(nullptr));  //524548
const int MX=43;
array<array<ll, MX+5>, MX+5> cmb;
void mk_ini_dt(vector<uint64_t>& );

void fnc(){
	for(int i=0; i<MX+5; i++)  cmb[i][0] = 1;
	for(int i=1; i<MX+5; i++) for(int j=1; j<=i;j++) 
		cmb[i][j] = cmb[i-1][j] + cmb[i-1][j-1];

	
	ll sm = 0;
	for(int i=0 ; i<=6; i++){
		ll w = cmb[6][i] * cmb[MX-6][6-i]; //当たりがi個の組み合わせ数
		sm += w;
		printf("%d : %6lld\n", i, w);
	}
	
	printf("\n%lld\n", cmb[MX][6]);
	
	printf("\n%lld\n", cmb[MX][3]);

}

vector<uint64_t> mkdy(){
	vector<VI> dt(6,VI(7)), v;
	
	rep(j,7) rep(i,6) dt[i][j] = i+j*6;
	for(auto xl: dt){for(auto x :xl) printf("%d, ",x); puts("");}

	VI wv;
	rep(i,42){
		wv.push_back(i);
		if(i%6==5){v.push_back(wv); wv.clear();}
	}
	
	wv.clear();
	rep(i,42){
		wv.push_back(dt[i/7][i%7]);
		if(i%6==5){v.push_back(wv); wv.clear();}
	}
	
	wv.clear();
	rep(i,7) rep(j,6){
		wv.push_back(dt[j][(i+j)%7]);
		if(j%6==5){v.push_back(wv); wv.clear();}
	}
	
	wv.clear();
	rep(i,7) rep(j,6){
		wv.push_back(dt[j][(i-j+7)%7]);
		if(j%6==5){v.push_back(wv); wv.clear();}
	}

	for(auto xl: v){for(auto x :xl) printf("%2d, ",x); puts("");} puts("\n\n");

	vector<uint64_t> rtn;
	for(auto& x: v){
		uint64_t usu =0;
		rep(i, 6) usu |= 1LL<<x[i];
		rtn.push_back(usu);
	}
	return rtn;
}

inline VI dsp(uint64_t n){
	VI rt;
	rep(i, 45) if(n >>i &1) rt.push_back(i);
	return rt;
}

inline uint64_t mkey(int a, int b, int c){
	return  1LL<<a | 1LL<<b | 1LL<<c;
}



int cmo=0;
void f2(){
	const int BZ = 43;
	unordered_map<uint64_t, int> ump; 
	ump.reserve(14000);
	vector<uint64_t> lvm, sdq, bsv;
	const uint64_t dls = 1LL<<61;
	chtime cht;
	auto adui = [&](uint64_t s){
		lvm.push_back(s);
		auto zk =dsp(s);
		rep(a,6) rep2(b,a+1,6) rep2(c,b+1,6) ump[mkey(zk[a],zk[b],zk[c])]++;
	};
	rep2(i,0,BZ) rep2(j,i+1,BZ) rep2(k,j+1,BZ){
		ump[mkey(i, j, k)] = 0;
	}
	dbg(sz(ump));
	//auto rcv = mkdy();
	vector<uint64_t> rcv; mk_ini_dt(rcv);
	for(auto x: rcv) adui(x);
	//for(auto xs: rcv){
	//	auto zzz=dsp(xs);
	//	cout <<"{ ";
	//	rep(i,6) cout << zzz[i] <<(i==5? " }, ": ","); 
	//}
	VI sq(BZ, 2);
	rep(i,6) sq[i] = 1;
	vector<vector<int8_t>> DZ; DZ.reserve(14000);
	do {
		vector<int8_t> cv;
		rep(i,BZ) if(sq[i]==1) cv.push_back(i);
		rep(a,6) rep2(b,a+1,6) rep2(c,b+1,6){
			if(ump[mkey(cv[a],cv[b],cv[c])] > 0) goto lpoutLZ;
		}
		DZ.push_back(cv);
		lpoutLZ:;
	} while ( next_permutation(all(sq)) );

	int ct=0, ct2=0;


	auto fspx = [&](int ersu){

		ct=0; ct2=0;
		lvm.clear();
		for(auto& x: ump) x.second=0;
		//
		for(auto x: rcv) adui(x);
		//
		if(cmo++ >0) shuffle(all(DZ), mrn);
		rep(g, sz(DZ)){
			ct++;
			auto& cv = DZ[g];
			int gct=0;
			rep(a,6) rep2(b,a+1,6) rep2(c,b+1,6){
				if(ump[mkey(cv[a],cv[b],cv[c])] > 0) gct++;
				if(gct >= ersu) goto lpoutZ;
			}
			lpoutZ:;
			if(gct < ersu){
				uint64_t xz=0;
				rep(i, 6) xz |= 1LL<<cv[i];
				lvm.push_back(xz);
				rep(a,6) rep2(b,a+1,6) rep2(c,b+1,6) ump[mkey(cv[a],cv[b],cv[c])]++;
				
			}
			
			
		}
		for(auto& x: ump) if(x.second==0) ct2++;

		
	};
	int bst=987654321;
	rep(g, 10){
		int ww = mrn() % 1000;
		fspx(1);
		if(sz(lvm) < bst){
			bsv = lvm; bst = sz(lvm);
		}
		dbg("lv02 ct=",ct,"  lvm",sz(lvm),"bst=",bst,
		"tim=",cht.gtm(), "uct=", ct2, g);
	}
	vector<vector<int>> v2;
	for(auto x: bsv){
		auto  cv = dsp(x);
		v2.push_back(cv);
	}
	//for(auto& xv : v2) sort(xv.rbegin(), xv.rend());
	sort(v2.begin(), v2.end());
	ofstream ofs( "lt6.txt", ios::out | ios::app );
	ofs <<"---- start(bst = "<<bst <<")----\n";
	char bf[50];
	for(auto xl: v2) rep(j,6){
		sprintf(bf, "%02d", xl[j]);
		ofs << bf << (j<5? " ":"\n");
	}
	ofs <<"---- end ----\n\n";

	//確認--->

	ump.clear();
	for(auto x: bsv){
		auto zk =dsp(x);
		rep(a,6) rep2(b,a+1,6) rep2(c,b+1,6) ump[mkey(zk[a],zk[b],zk[c])]++;
	}
	sq.assign(43, 2);
	rep(i,6) sq[i] = 1;
	do {
		vector<int8_t> cv;
		rep(i,43) if(sq[i]==1) cv.push_back(i);
		int gct=0;
		rep(a,6) rep2(b,a+1,6) rep2(c,b+1,6){
			if(ump[mkey(cv[a],cv[b],cv[c])] > 0) gct++;
			if(gct >= 1) goto lpoutXX;
		}
		lpoutXX:;
		if(gct==0){
			for(auto x : cv) printf("%d ",x); puts(" ng");
		}

	} while ( next_permutation(all(sq)) );
	//---->確認
	/*
	
	for(auto& x: ump){
		VI uk;
		if(x.second >1){
			uk = dsp(x.first);
			for(auto z :uk) printf("%d ",z); printf(" : %d\n", x.second);
		}
	}
	
	VI sct(BZ, 0);
	vector<VI> wct(43, VI(43));
	for(auto x: bsv){
		//rep(i,BZ) if(x>>i &1) sct[i]++;
		auto wv = dsp(x);
		rep(i, 6){
			sct[wv[i]]++;
			rep2(j,i+1,6) wct[wv[i]][wv[j]]++;
		}
	}
	for(auto x : sct) printf("%d ",x); puts("  <--sct");
	rep(i,43){ printf("%d::  ",i);rep2(j,i+1,43) printf("%d:%d ", j, wct[i][j]); puts("");}
	*/
}

void f3(){
	const int BZ = 43;
	unordered_map<uint64_t, int> ump; 
	ump.reserve(14000);
	vector<array<int8_t,3>> sq; sq.reserve(14000);
	vector<uint64_t> lvm, sdq, bsv;
	const uint64_t dls = 1LL<<61;
	rep2(i,0,BZ) rep2(j,i+1,BZ) rep2(k,j+1,BZ){
		ump[mkey(i, j, k)] = 0;
		sq.emplace_back(array<int8_t,3>{(int8_t)i,(int8_t)j,(int8_t)k});
	}
	int cr=0;
	vector<int> mxst(BZ+2);
	rep(i, sz(sq)){
		if(sq[i][0] == cr){ mxst[cr] =  i; cr++;}
	}
	for(auto x :mxst) printf("%d, ",x); puts("\n");
	dbg("sz(sq)=",sz(sq));
	int ct=0;
	int pz=sz(sq);
	auto wsq=sq;
	shuffle(all(wsq), mrn);
	rep(i, pz){
		int cmx = wsq[i][2];
		if(cmx >39) continue;
		printf("\n%d[%d:%d:%d]i::  ",i,wsq[i][0],wsq[i][1],wsq[i][2]);
		rep2(j, mxst[cmx+1], pz){
			ct++;
			printf("%d[%d:%d:%d]  ",j,sq[j][0],sq[j][1],sq[j][2]);
			
		}
	}
	dbg("ct=",ct);
}

int main()
{
	//fnc(); 
	//f2();
	f3();
}

void mk_ini_dt(vector<uint64_t>& adv){

	const vector<VI> idt={
		{ 0,1,2,3,4,5 }, { 6,7,8,9,10,11 }, { 12,13,14,15,16,17 },
		{ 18,19,20,21,22,23 }, { 24,25,26,27,28,29 }, { 30,31,32,33,34,35 },
		{ 36,37,38,39,40,41 },
		{ 0,6,12,18,24,30 }, { 1,7,13,19,25,36 },{ 2,8,14,20,31,37 },
		{ 3,9,15,26,32,38 }, { 4,10,21,27,33,39 },
		{ 5,16,22,28,34,40 }, { 11,17,23,29,35,41 },
		{ 0,7,14,21,28,35}, { 6,13,20,27,34,41 }, { 5,12,19,26,33,40 },
		{ 4,11,18,25,32,39 }, { 3,10,17,24,31,38 },
		{ 2,9,16,23,30,37 }, { 1,8,15,22,29,36 },
		{ 0,17,22,27,32,37 }, { 1,6,23,28,33,38 }, { 2,7,12,29,34,39 },
		{ 3,8,13,18,35,40 }, { 4,9,14,19,24,41 },
		{ 5,10,15,20,25,30 }, { 11,16,21,26,31,36 }, 
	



	};
	
	for(auto x: idt){
		uint64_t uk = 0;
		rep(j,6) uk |= 1LL << x[j];
		adv.push_back(uk);
	}
}