#include <iostream>

using namespace std;


int rep[11][2];//sin* sss+
int N;

// long long abs(long long a){
// 	return a<0?-1*a:a;
// }

long long min(long long a,long long b){
	a = abs(a);
	b = abs(b);
	return a<b?a:b;
}

long long recipe(int idx,long long sin, long long sss){
	if (idx >= N) {
		if (sin==0 && sss ==0)
			return -1;
		
		return abs(sin-sss);
	}
	
	long long tmp = recipe(idx+1,sin,sss);
	
	if (sin == 0) sin = rep[idx][0];
	else sin *= rep[idx][0];
	sss += rep[idx][1];
	
	long long tmp2 = recipe(idx+1,sin,sss);
	
	if (tmp != -1){
	return min(tmp,tmp2); //추가		
	}
	return tmp2;
}

int main(){
	cin >> N;
	
	int sin, sss;
	for(int i=0;i<N;i++){
		cin >> rep[i][0] >> rep[i][1];
	}
	
	cout << recipe(0,0,0);
	return 0;
}