#include"head.h"
void main()
{
	srand((unsigned int)time(NULL));
	clock_t stt = clock();
	int k;
	k = 48;
	
	int ver[P][N + 1];//定义P组顶点，每组N个，数组下标为顶点序号，数组值为顶点颜色
	int Arc[N + 1][N + 1];//存储边信息的邻接矩阵

	int i, j, l;
	for (i = 1; i <= N; i++)
	{
		for(j = 0; j < P; j++)
			ver[j][i] = random(k) + 1;//随机给顶点颜色
		for (j = 1; j <= N; j++)
			Arc[i][j] = 0;//初始化邻接矩阵
	}
	char *graph = "DSJC500.5.col";
	initial(Arc, graph);

	int fs[P], bestfssofar[P];
	int Vconflict[P][N + 1];
	int Conflict_loc[P][N + 1];
	int Adjcol[P][N + 1][MAX_K];//定义Adjacent-Color Table
	int Tabutable[P][N + 1][MAX_K];//定义禁忌表
	int gen = 1;//进化的代数 
	long int step[P];//记录迭代次数
	for (i = 0; i < P; i++)
	{
		fs[i] = Countfs(Arc, ver[i], N);
		bestfssofar[i] = fs[i];
		initial_conflict(ver[i], Arc, Vconflict[i], Conflict_loc[i]);
		Creat_Adjcol(Arc, ver[i], N, k, Adjcol[i]);//初始化Adjacent-Color Table
		for (l = 1; l <= N; l++)
			for (j = 1; j <= k; j++)
				Tabutable[i][l][j] = 0;//初始化禁忌表
		step[i] = 1;
	}//计算每个种群的初始冲突数和冲突顶点
	int t, s;
	while (1)
	{
		for (i = 0; i < P; i++)
		{
			s = 1;
			while (s <= S)
			{
				if (fs[i] == 0)
					Output(gen, k, graph, stt, ver[i]);
				Neiaction(Arc, ver[i], N, k, Adjcol[i], Tabutable[i], &fs[i], step[i], &bestfssofar[i], Vconflict[i], Conflict_loc[i]); 
				step[i]++;
				s++;
			}
		}
		
		t = update_ver(ver, k);
		fs[t] = Countfs(Arc, ver[t], N);
		bestfssofar[t] = fs[t];
		initial_conflict(ver[t], Arc, Vconflict[t], Conflict_loc[t]);
		Creat_Adjcol(Arc, ver[t], N, k, Adjcol[t]);//初始化Adjacent-Color Table
		for (l = 1; l <= N; l++)
			for (j = 1; j <= k; j++)
				Tabutable[t][l][j] = 0;//初始化禁忌表
		step[t] = 1;
		if(gen % 100 == 0)
			printf("第%d代进化完成\n", gen);
		gen++;
	}
}