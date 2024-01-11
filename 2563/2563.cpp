#include <iostream>

using namespace std;

int main(){
	int N;
	int map[101][101]={0,};
	int x,y;
	int ans=0;	
	
	cin >> N;
	for(int k=0;k<N;k++){
		cin >> x >> y;
		for(int i=x;i<x+10;i++){
			for(int j=y;j<y+10;j++){
				if (i<101 && j <101) map[i][j]=1;
			}
		}
	}

	for(int i=0;i<101;i++){
		for(int j=0;j<101;j++){
			if (map[i][j]) ans++;
		}
	}
	
	cout << ans;

	return 0;
}