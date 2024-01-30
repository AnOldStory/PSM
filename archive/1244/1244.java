package com;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

// 메모리:14544KB 시간:140ms
public class A1244 {
	static int N;
	static int arr[];
	
	static public void tog(int i) {
		arr[i]=(arr[i]+1)%2;
	}
	
	static public boolean valid(int l,int r) {
		if (0<=l&&l<N && 0<=r&&r<N) {
			return true;
		}
		return false;
	}
	
	static public void male(int num) {
		for(int i=num;i<=N;i+=num) {
			tog(i-1);
		}
	}
	
	static public void female(int num) {
		tog(num-1);
		for(int i=1;i<=N;i++) {
			int l = num-i-1;
			int r = num+i-1;
			if (valid(l,r)) {
				if (arr[l]==arr[r]) {
					tog(l);
					tog(r);
				} else {
					break;
				}
			} else {
				break;
			}
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;
		
		N = Integer.parseInt(br.readLine()); //switch size
		arr = new int[N];
		
		
		st = new StringTokenizer(br.readLine()); //switch
		for(int i=0;i<N;i++) {
			arr[i]=Integer.parseInt(st.nextToken());
		}
		
		int temp = Integer.parseInt(br.readLine()); // order size
		int x,num;
		for(int i=0;i<temp;i++) {
			st = new StringTokenizer(br.readLine());  //order
			x=Integer.parseInt(st.nextToken());
			num=Integer.parseInt(st.nextToken());
			if (x==1) {
				male(num);
			}
			else if (x==2) {
				female(num);
			}		
		}
		
		
		
		for(int i=0;i<N;i++) {
			if (i!=0 && i%20==0) {
				System.out.println();
			}
			System.out.print(arr[i]+" ");
		}
	
	}
}
