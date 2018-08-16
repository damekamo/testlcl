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

mt19937 mrn(524548);//(unsigned)time(nullptr));  //854
const int MX=43;
array<array<ll, MX+5>, MX+5> cmb;

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

inline VI dsp(uint64_t n){
	VI rt;
	rep(i, 45) if(n >>i &1) rt.push_back(i);
	return rt;
}

inline uint64_t mkey(int a, int b, int c){
	return  1LL<<a | 1LL<<b | 1LL<<c;
}



void f3(){
	unordered_map<uint64_t, int> ump; 
	ump.reserve(14000);
	vector<uint64_t> lvm, sdq;
	const uint64_t dls = 1LL<<61;
	chtime cht;
	rep2(i,0,43) rep2(j,i+1,43) rep2(k,j+1,43){
		ump[mkey(i, j, k)] = 0;
	}
	dbg(sz(ump));
	
	for(auto x: ump) sdq.push_back(x.first);
	int ct=0, ct2=0;

	auto adui = [&](uint64_t s){
		lvm.push_back(s);
		auto zk =dsp(s);
		rep(a,6) rep2(b,a+1,6) rep2(c,b+1,6) ump[mkey(zk[a],zk[b],zk[c])]++;
	};
	auto fspx = [&](int ersu){

		if(sz(sdq) ==0) return;
		if(sz(sdq) <=10){
			uint64_t uw=0;
			rep(i, sz(sdq)){
				auto uk = sdq[i];
				if( __builtin_popcountll(uw|uk) >6){
					rep(j, 43){
						if(!(1LL<<j & uw)){uw |= 1LL<<j;}
						if(__builtin_popcountll(uw) >=6) break;
					}
					adui(uw);
					uw =0; 
				}
				uw |= uk;
				if(__builtin_popcountll(uw) ==6){
						adui(uw);
						uw =0; 
				}
			}
			if(uw !=0){
				rep(j, 43){
					if(!(1LL<<j & uw)){uw |= 1LL<<j;}
					if(__builtin_popcountll(uw) >=6) break;
				}
				adui(uw); uw=0;
			}
			rep(i, sz(sdq)){
				if(ump[sdq[i]] >0) sdq[i] = dls;
			}
			sdq.erase(remove(all(sdq),dls), sdq.end());

			return;
		}
		
		rep(i, sz(sdq)) rep2(j, i+1,sz(sdq)){
			ct++;
			
			uint64_t nuw = sdq[i] |sdq[j];
			int pcnt = __builtin_popcountll(nuw);
			if(ersu < 15 &&  pcnt < 6) continue;
			if(sdq[i] == dls || sdq[j] == dls) continue;
			if(ump[sdq[i]] >0 || ump[sdq[j]]>0 ) continue;
			if( pcnt < 6){
				rep(j, 43){
					if(!(1LL<<j & nuw)){nuw |= 1LL<<j;}
					if(__builtin_popcountll(nuw) >=6) break;
				}
			}
			auto wv = dsp(nuw);
			ct2++;
			int nct=0;
			rep(a,6) rep2(b,a+1,6) rep2(c,b+1,6){
				if(ump[mkey(wv[a],wv[b],wv[c])] > 0) nct++;
				if(nct > ersu) goto lpout2;
			}
			lpout2:;
			if(nct <= ersu){
				lvm.push_back(nuw);
				rep(a,6) rep2(b,a+1,6) rep2(c,b+1,6) ump[mkey(wv[a],wv[b],wv[c])]++;
				sdq[i] = sdq[j] = dls;
			}
		}
		rep(i, sz(sdq)){
			if(ump[sdq[i]] >0) sdq[i] = dls;
		}
		sdq.erase(remove(all(sdq),dls), sdq.end());

	};
	VI seq(20); iota(all(seq), 0);  // best 869
	for(auto x: /*seq*/ {0,3,6,9,12,15,16,17,18,19} ){
		fspx(x);
		dbg("lv",x,"  lvm",sz(lvm),"sz(sdq)",sz(sdq),"tim=",cht.gtm());
	}
	
	for(auto x: lvm){
		rep(i, 45) if(x>>i &1) printf(" %2d", i); printf("\n");
	}
	int umct=0;
	for(auto x: ump){
		if(x.second ==0) umct++;
	}
	dbg("umct=",umct,"sz=",sz(ump));
	for(auto x: ump){
		if(x.second ==0){
			rep(i,50) if(x.first>>i&1) printf(" %2d", i); printf("\n");
		}
	}
	//for(auto x :sdq) cout<<x <<" "; puts("");

// 再確認
	auto smp = ump;
	for(auto x: smp) x.second=0;
	for(auto x: lvm){
		auto wwv = dsp(x);
		assert(sz(wwv) ==6);
		rep(a,6) rep2(b,a+1,6) rep2(c,b+1,6) smp[mkey(wwv[a],wwv[b],wwv[c])]++;
	}
	for(auto x: smp){
		if(x.first ==dls) continue;
		if(x.second ==0){
			rep(i,50) if(x.first>>i&1) cout<<i <<" ";cout<<"  :"<<x.first<<"\n";
		}
	}
}
int cmo=0;
void f2(){
	const int BZ = 43;
	unordered_map<uint64_t, int> ump; 
	ump.reserve(14000);
	vector<uint64_t> lvm, sdq, bsv;
	const uint64_t dls = 1LL<<61;
	chtime cht;
	rep2(i,0,BZ) rep2(j,i+1,BZ) rep2(k,j+1,BZ){
		ump[mkey(i, j, k)] = 0;
	}
	dbg(sz(ump));
	VI sq(BZ, 2);
	rep(i,6) sq[i] = 1;
	vector<vector<int8_t>> DZ; DZ.reserve(14000);
	do {
		vector<int8_t> cv;
		rep(i,BZ) if(sq[i]==1) cv.push_back(i);
		DZ.push_back(cv);
	} while ( next_permutation(all(sq)) );

	
	for(auto x: ump) sdq.push_back(x.first);
	int ct=0, ct2=0;

	auto adui = [&](uint64_t s){
		lvm.push_back(s);
		auto zk =dsp(s);
		rep(a,6) rep2(b,a+1,6) rep2(c,b+1,6) ump[mkey(zk[a],zk[b],zk[c])]++;
	};

	auto fspx = [&](int ersu){

		ct=0; ct2=0;
		lvm.clear();
		for(auto& x: ump) x.second=0;
		if(cmo++ >0)shuffle(all(DZ), mrn);
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
		int uct=0;
		for(auto& x: ump) if(x.second==0) uct++;
		dbg("uct=",uct);

		
	};
	int bst=987654321;
	
	rep(g, 4){
		fspx(1);
		if(sz(lvm) < bst){
			bsv = lvm; bst = sz(lvm);
		}
		dbg("lv02 ct=",ct,ct2,"  lvm",sz(lvm),"bst=",bst,"tim=",cht.gtm());
	}
	vector<vector<int>> v2;
	for(auto x: bsv){
		auto  cv = dsp(x);
		v2.push_back(cv);
	}
	//for(auto& xv : v2) sort(xv.rbegin(), xv.rend());
	//sort(v2.rbegin(), v2.rend());
	for(auto xl: v2){for(auto x :xl) printf("%2d ",x); puts("");}

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
			for(auto x : cv) printf("%d ",x); puts("");
		}

	} while ( next_permutation(all(sq)) );
	//---->確認

	VI sct(BZ, 0);
	for(auto x: bsv){
		rep(i,BZ) if(x>>i &1) sct[i]++;
	}
	for(auto x : sct) printf("%d ",x); puts("  <--sct");
}

int main()
{
	//fnc(); 
	f2();
}
