package com;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

//메모리:14380kb 시간:132ms
public class A17478 {
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

	static StringBuilder sb = new StringBuilder();
	
	static int N;
	
	static void rec_ (int cnt) {
		for(int i=0;i<cnt;i++) {
			sb.append("____");
		}
	}
	static void rec (int cnt) {
		
		rec_(cnt);sb.append("\"재귀함수가 뭔가요?\"\n");
		rec_(cnt);sb.append("\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.\n");
		rec_(cnt);sb.append("마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.\n");
		rec_(cnt);sb.append("그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"\n");
				if (cnt+1<N) rec(cnt+1);
				else {		
					rec_(cnt+1);sb.append("\"재귀함수가 뭔가요?\"\n");
					rec_(cnt+1);sb.append("\"재귀함수는 자기 자신을 호출하는 함수라네\"\n");
					rec_(cnt+1);sb.append("라고 답변하였지.\n");
				}
		rec_(cnt);sb.append("라고 답변하였지.\n");
	}
	
	public static void main(String[] args) throws IOException{
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		sb.append("어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다.\n");
		
		rec(0);
		
		System.out.println(sb);
	}

}
