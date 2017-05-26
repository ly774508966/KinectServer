#include <math.h>
/***********************************************************************************
ϵ��������޷���������ֹ�������Ŀǰ��������ܲ����ƣ������ܺܺõؽ���������
ԭ�������������ʽ��ͬһ�г���һ��ϵ��������ʽ�Ľⲻ��
��Ȼ�����������⣬����һ���������⣬Ҳ��ͬ����˼·�����ڶ���������Ĵ����ܲ����ƣ��д��Ż�
����Ϊ��λ����
***********************************************************************************/
//�Ѷ�ά��������һά�����ת����Ҳ����ֱ���ö�ά���飬ֻ���ҵ�ϰ���ǲ��ö�ά����
#define ParaBuffer(Buffer,Row,Col) (*(Buffer + (Row) * (SizeSrc + 1) + (Col)))
#define WEISHU 3//����ά��
/***********************************************************************************
��ӡϵ������ֻ���ڵ��ԣ����߱����㹦��
����һ��N����ϣ�����ϵ�������С�ǣ�N + 1���У�N + 2����
double* Para��ϵ������洢��ַ
int SizeSrc��ϵ�������С��SizeSrc���У�SizeSrc + 1����
***********************************************************************************/
static int PrintPara(double* Para, int SizeSrc)
{
	//int i, j;
	//for (i = 0; i < SizeSrc; i++)
	//{
	//	for (j = 0; j <= SizeSrc; j++)
	//		/*{
	//		double temp = ParaBuffer(Para, i, j);
	//		}*/
	//		printf("%10.6lf ", ParaBuffer(Para, i, j));
	//	printf("\r\n");
	//}
	//printf("\r\n");
	return 0;
}

static int ParalimitRow(double* Para, int SizeSrc, int Row)
{
	int i;
	double Max, Min, Temp;
	for (Max = abs(ParaBuffer(Para, Row, 0)), Min = Max, i = SizeSrc; i; i--)
	{
		Temp = abs(ParaBuffer(Para, Row, i));
		if (Max < Temp)
			Max = Temp;
		if (Min > Temp)
			Min = Temp;
	}
	Max = (Max + Min) * 0.000005;
	for (i = SizeSrc; i >= 0; i--)
		ParaBuffer(Para, Row, i) /= Max;
	return 0;
}

/***********************************************************************************
ͬ�ϣ��Ծ���Ϊ��λ����
***********************************************************************************/
static int Paralimit(double* Para, int SizeSrc)
{
	int i;
	for (i = 0; i < SizeSrc; i++)
		if (ParalimitRow(Para, SizeSrc, i))
			return -1;
	return 0;
}

/***********************************************************************************
ϵ����������ʽ�任
***********************************************************************************/
static int ParaPreDealA(double* Para, int SizeSrc, int Size)
{
	int i, j;
	for (Size -= 1, i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
			ParaBuffer(Para, i, j) = ParaBuffer(Para, i, j) * ParaBuffer(Para, Size, Size) - ParaBuffer(Para, Size, j) * ParaBuffer(Para, i, Size);
		ParaBuffer(Para, i, SizeSrc) = ParaBuffer(Para, i, SizeSrc) * ParaBuffer(Para, Size, Size) - ParaBuffer(Para, Size, SizeSrc) * ParaBuffer(Para, i, Size);
		ParaBuffer(Para, i, Size) = 0;
		ParalimitRow(Para, SizeSrc, i);
	}
	return 0;
}

/***********************************************************************************
ϵ����������ʽ�任����ParaPreDealA���
��ɵ�һ�α任���任�����Ǿ���
***********************************************************************************/
static int ParaDealA(double* Para, int SizeSrc)
{
	int i;
	for (i = SizeSrc; i; i--)
		if (ParaPreDealA(Para, SizeSrc, i))
			return -1;
	return 0;
}

/***********************************************************************************
ϵ����������ʽ�任
***********************************************************************************/
static int ParaPreDealB(double* Para, int SizeSrc, int OffSet)
{
	int i, j;
	for (i = OffSet + 1; i < SizeSrc; i++)
	{
		for (j = OffSet + 1; j <= i; j++)
			ParaBuffer(Para, i, j) *= ParaBuffer(Para, OffSet, OffSet);
		ParaBuffer(Para, i, SizeSrc) = ParaBuffer(Para, i, SizeSrc) * ParaBuffer(Para, OffSet, OffSet) - ParaBuffer(Para, i, OffSet) * ParaBuffer(Para, OffSet, SizeSrc);
		ParaBuffer(Para, i, OffSet) = 0;
		ParalimitRow(Para, SizeSrc, i);
	}
	return 0;
}

/***********************************************************************************
ϵ����������ʽ�任����ParaPreDealB���
��ɵ�һ�α任���任�ɶԽǾ��󣬱任���
***********************************************************************************/
static int ParaDealB(double* Para, int SizeSrc)
{
	int i;
	for (i = 0; i < SizeSrc; i++)
		if (ParaPreDealB(Para, SizeSrc, i))
			return -1;
	for (i = 0; i < SizeSrc; i++)
	{
		if (ParaBuffer(Para, i, i))
		{
			ParaBuffer(Para, i, SizeSrc) /= ParaBuffer(Para, i, i);
			ParaBuffer(Para, i, i) = 1.0;
		}
	}
	return 0;
}

/***********************************************************************************
ϵ������任
***********************************************************************************/
static int ParaDeal(double* Para, int SizeSrc)
{
	PrintPara(Para, SizeSrc);
	Paralimit(Para, SizeSrc);
	PrintPara(Para, SizeSrc);
	if (ParaDealA(Para, SizeSrc))
		return -1;
	PrintPara(Para, SizeSrc);
	if (ParaDealB(Para, SizeSrc))
		return -1;
	return 0;
}

/***********************************************************************************
��С���˷��ĵ�һ�����Ǵ�XY���������ȡϵ������
double* Para��ϵ�������ַ
const double* X��X���ݵ�ַ
const double* Y��Y���ݵ�ַ
int Amount��XY��������
int SizeSrc��ϵ�������С��SizeSrc���У�SizeSrc + 1����
***********************************************************************************/
static int GetParaBuffer(double* Para, const double* X, const double* Y, int Amount, int SizeSrc)
{
	int i, j;
	for (i = 0; i < SizeSrc; i++)
		for (ParaBuffer(Para, 0, i) = 0, j = 0; j < Amount; j++)
			ParaBuffer(Para, 0, i) += pow(*(X + j), 2 * (SizeSrc - 1) - i);
	for (i = 1; i < SizeSrc; i++)
		for (ParaBuffer(Para, i, SizeSrc - 1) = 0, j = 0; j < Amount; j++)
			ParaBuffer(Para, i, SizeSrc - 1) += pow(*(X + j), SizeSrc - 1 - i);
	for (i = 0; i < SizeSrc; i++)
		for (ParaBuffer(Para, i, SizeSrc) = 0, j = 0; j < Amount; j++)
			ParaBuffer(Para, i, SizeSrc) += (*(Y + j)) * pow(*(X + j), SizeSrc - 1 - i);
	for (i = 1; i < SizeSrc; i++)
		for (j = 0; j < SizeSrc - 1; j++)
			ParaBuffer(Para, i, j) = ParaBuffer(Para, i - 1, j + 1);
	return 0;
}

/***********************************************************************************
�����������
***********************************************************************************/
int CalNihe(const double* BufferX, const double* BufferY, int Amount, int SizeSrc, double* ParaResK)
{
	double* ParaK = (double*)malloc(SizeSrc * (SizeSrc + 1) * sizeof(double));
	GetParaBuffer(ParaK, BufferX, BufferY, Amount, SizeSrc);
	ParaDeal(ParaK, SizeSrc);
	for (Amount = 0; Amount < SizeSrc; Amount++, ParaResK++)
		*ParaResK = ParaBuffer(ParaK, Amount, SizeSrc);
	free(ParaK);
	return 0;
}