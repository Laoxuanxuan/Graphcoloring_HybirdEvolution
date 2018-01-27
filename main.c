#include"head.h"
void main()
{
	srand((unsigned int)time(NULL));
	clock_t stt = clock();
	int k;
	k = 48;
	
	int ver[P][N + 1];//����P�鶥�㣬ÿ��N���������±�Ϊ������ţ�����ֵΪ������ɫ
	int Arc[N + 1][N + 1];//�洢����Ϣ���ڽӾ���

	int i, j, l;
	for (i = 1; i <= N; i++)
	{
		for(j = 0; j < P; j++)
			ver[j][i] = random(k) + 1;//�����������ɫ
		for (j = 1; j <= N; j++)
			Arc[i][j] = 0;//��ʼ���ڽӾ���
	}
	char *graph = "DSJC500.5.col";
	initial(Arc, graph);

	int fs[P], bestfssofar[P];
	int Vconflict[P][N + 1];
	int Conflict_loc[P][N + 1];
	int Adjcol[P][N + 1][MAX_K];//����Adjacent-Color Table
	int Tabutable[P][N + 1][MAX_K];//������ɱ�
	int gen = 1;//�����Ĵ��� 
	long int step[P];//��¼��������
	for (i = 0; i < P; i++)
	{
		fs[i] = Countfs(Arc, ver[i], N);
		bestfssofar[i] = fs[i];
		initial_conflict(ver[i], Arc, Vconflict[i], Conflict_loc[i]);
		Creat_Adjcol(Arc, ver[i], N, k, Adjcol[i]);//��ʼ��Adjacent-Color Table
		for (l = 1; l <= N; l++)
			for (j = 1; j <= k; j++)
				Tabutable[i][l][j] = 0;//��ʼ�����ɱ�
		step[i] = 1;
	}//����ÿ����Ⱥ�ĳ�ʼ��ͻ���ͳ�ͻ����
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
		Creat_Adjcol(Arc, ver[t], N, k, Adjcol[t]);//��ʼ��Adjacent-Color Table
		for (l = 1; l <= N; l++)
			for (j = 1; j <= k; j++)
				Tabutable[t][l][j] = 0;//��ʼ�����ɱ�
		step[t] = 1;
		if(gen % 100 == 0)
			printf("��%d���������\n", gen);
		gen++;
	}
}