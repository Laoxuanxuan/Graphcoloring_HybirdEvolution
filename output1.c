#include"head.h"
void Output(int gen, int k, char *graph, clock_t stt, int *ver);
void Output(int gen, int k, char *graph, clock_t stt, int *ver)
{
	clock_t  ett = clock();
	int i;
	FILE* fp = NULL;
	errno_t err = 0;
	err = fopen_s(&fp, "Result.txt", "a");
	if (err == 0)
	{
		struct tm *local;
		time_t t;
		t = time(NULL);
		local = localtime(&t);
		int year = 2018;// local->tm_year;
		int mon = local->tm_mon + 1;
		int day = local->tm_mday;
		int hour = local->tm_hour;
		int min = local->tm_min;
		int sec = local->tm_sec;
		double cost_sec = ((double)ett - (double)stt) / CLOCKS_PER_SEC;
		fprintf(fp, "\nʱ�䣺%d.%d.%d.%d.%d.%d\t������%s\t��ɫ����%d\t��ʱ���룩��%.3lf\t������%d\t��Ⱥ����%d\t���ɲ�����%d\n", year, mon, day, hour, min, sec, graph, k, cost_sec, gen, P, S);
		for (i = 1; i <= N; i++)
			fprintf(fp, "%d ", ver[i]);
		fprintf(fp, "\n");
		fclose(fp);
		exit(1);
	}
}