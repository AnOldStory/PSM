package com;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

//메모리 : 16204kb 시간: 152ms
public class A2615 {
	static int arr[][];
	static boolean visited[][][]; //x y i 
	static int[] dx= {1,0,1,-1};
	static int[] dy= {0,1,1,1};
	
	static boolean valid(int x,int y) {
		if (0<=x && x<19&&0<=y&& y<19) return true;
		return false;
	}
	
	static int dir(int x,int y,int i,int color,int streak) {
		if (color != arr[x][y]||visited[x][y][i]==true) return streak;
		visited[x][y][i]=true;
		if (valid(x+dx[i],y+dy[i])) {
			return dir(x+dx[i],y+dy[i],i,color,streak+1);
		}
		return streak+1;
	}
	
	static boolean check(int x,int y) {
		for(int i=0;i<4;i++) {
			int dxx = x+dx[i];
			int dyy = y+dy[i];
			if (valid(dxx,dyy)) {
				if (dir(dxx,dyy,i,arr[x][y],1)==5) {

					return true;
				};
			}
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		StringBuilder sb = new StringBuilder();
		
//		st = new StringTokenizer(br.readLine());
		
		arr = new int[19][19];
		visited = new boolean[19][19][4];
		
		for(int i=0;i<19;i++) {
			st = new StringTokenizer(br.readLine());
			for(int j=0;j<19;j++) {
				arr[i][j]=Integer.parseInt(st.nextToken());
			}
		}

		for(int j=0;j<19;j++) {
			for(int i=0;i<19;i++) {
				if (arr[i][j]!=0) if (check(i,j)) {
					sb.append(""+arr[i][j]+'\n');
					sb.append(""+(i+1)+" "+(j+1));
					System.out.println(sb);
					return;
				}
			}
		}
		
		
		System.out.println("0");
	}

}
