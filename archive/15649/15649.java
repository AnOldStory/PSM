package com;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

//메모리: 23440kb 시간: 252ms
public class A15649 {
	static int N, M; // N까지 , M개 선택
	static StringBuilder sb = new StringBuilder();
	static int[] now;
	static boolean[] visited;

	static void choose(int cnt) {
		if (cnt == M) {
			for (int i : now) {
				sb.append(i).append(' ');
			}
			sb.append('\n');
			return;
		}
		for (int i = 0; i < N; i++) {
			if (!visited[i]) {
				visited[i] = true;
				now[cnt] = i + 1;
				choose(cnt + 1);
				visited[i] = false;
			}
		}
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());

		now = new int[M];
		visited = new boolean[N];
		choose(0);
		System.out.println(sb);
	}
}
