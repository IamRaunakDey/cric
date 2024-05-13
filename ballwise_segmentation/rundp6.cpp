#include<stdio.h>
#include<iostream>
#define UP 0
#define LEFT 1
#define DIAG 2
#define NORM 1000000
#include <cstdlib>

using namespace std;

main(int argc, char * argv[])
{
//FILE * fp = fopen("Score_M1I1.framewise.txt.norm", "r");
FILE * fp = fopen(argv[1], "r");
char ballstr[10], outcome[10], category[10] = "wide", dummystr[100];
int begshot, begframe, endframe;
float ** scores = new float*[600000];
double weights[7] = {atof(argv[5]),atof(argv[6]),atof(argv[7]),atof(argv[8]),atof(argv[9]),atof(argv[10]),atof(argv[11])};

//double weights[7]={x[0]*0.000001,x[1]*0.000001,x[2]*0.000001,x[3]*0.000001,x[4]*1,x[5]*0.000001,x[6]*0.000001};
//for(int i=0;i<7;i++)
//cout<<x[i]<<" ";
//for(int i=0;i<7;i++)
//cout<<weights[i]<<" ";
//cout<<endl;

for(int m=0;m<7;m++)
	fscanf(fp, "%s ", dummystr);

int pos =0, numframes;
while(!feof(fp))
{
	scores[pos] = new float[7];
	for(int m=0;m<7;m++)
	{
		fscanf(fp, "%f ", &scores[pos][m]);
		//float norm=1000000;
		scores[pos][m]=scores[pos][m]*weights[m];
		//cout<<scores[pos][m]<<" ";
		}
		//cout<<endl;
		
	pos++;
}

fclose(fp);

numframes = pos;


//fp = fopen("m1i1_hypovid2", "r");
fp = fopen(argv[2], "r");
int hyp_numframes;
fscanf(fp, "%d ", &hyp_numframes);
float ** hypovid = new float*[hyp_numframes];
for(int i=0;i<hyp_numframes;i++)
	hypovid[i] = new float[7];

for(int i=0;i<hyp_numframes;i++)
{
	hypovid[i] = new float[7];
        for(int m=0;m<7;m++)
		{
                fscanf(fp, "%f ", &hypovid[i][m]);
				hypovid[i][m]=hypovid[i][m]*weights[m];
		}
}
fclose(fp);

//till 9.6
//cout<<numframes<<" "<<hyp_numframes<<endl;
if(numframes<hyp_numframes)
hyp_numframes=numframes;
//cout<<numframes<<" "<<hyp_numframes<<endl;

//numframes =48000 ;
//hyp_numframes =48000 ;

// till 19.6
//numframes = 130524; 
//hyp_numframes = 131856;

//cout<<"Loaded"<<endl;

float *D_prev = new float[numframes];
float *D_cur = new float[numframes];

bool ** I0 = new bool *[numframes];
bool ** I1 = new bool *[numframes];
for(int i=0;i<numframes;i++)
{
	I0[i] = new bool[hyp_numframes];
	I1[i] = new bool[hyp_numframes];
}
//cout<<"Done allocating Memory... "<<endl;

//float occost = 4000000000;
//float occost = 0.1;
float occost = 0.2;

for(int i=0;i<numframes;i++)
{
	D_prev[i]= occost * i;
	I0[i][0] = 0, I1[i][0] = 1; //UP;
}

for(int j=0;j<hyp_numframes;j++)
{
//	D[0][j] = occost*j;
	I0[0][j] = 1, I1[0][j] = 0; // = LEFT;
}

float d;	
for(int i=1;i<numframes;i++)
{
	if(i%1000 == 0)
	{
		//fprintf(stderr, "%d\n", i);
		fflush(stderr);
	}
	D_cur[0] = occost * i;
	for(int j=1;j<hyp_numframes;j++)
	{
//cout<<j<<endl;

		d = 0;
		for(int m=0;m<7;m++)
		{
		
			d += (scores[i][m] - hypovid[j][m]) * (scores[i][m] - hypovid[j][m]);
			//weights of m = w[m]*d
//cout<<d<<endl;
		}
		//	cout<<"Prev"<<d<<" "<<j<<" "<<i<<endl;
			//float norm=10000000000;
			//d=d;
			

		if(D_prev[j-1] + d  <= D_prev[j]+occost  && D_prev[j-1]+d  <= D_cur[j-1]+occost)
		{
		//	cout<<1<<endl;;
			D_cur[j] = D_prev[j-1] + d, I0[i][j] = 0, I1[i][j] = 0; // = DIAG;
			
			}
		else
		if(D_prev[j]+occost <= D_prev[j-1]+d && D_prev[j]+occost <= D_cur[j-1]+occost)			
			{
			
			D_cur[j] = D_prev[j] + occost;
		//	cout<<2<<endl;;
		//	cout<<i<<" "<<j<<" "<<numframes<<" "<<hyp_numframes<<endl;
			 I0[i][j] = 0;
		//	cout<<i<<" "<<j<<endl;

			 I1[i][j] = 1; //UP;		
			}
		else
		if(D_cur[j-1]+occost <= D_prev[j-1]+d && D_cur[j-1]+occost <= D_prev[j]+occost)
			{
			//cout<<3<<endl;;
			D_cur[j] = D_cur[j-1] + occost, I0[i][j] = 1, I1[i][j] = 0;// = LEFT;		
			}
		
		//cout<<I0[i][j]<<" ";		
		//cout<<"Post"<<d<<" "<<j<<" "<<i<<endl;	
	}

	float * temp = D_prev;
	D_prev = D_cur;
	D_cur = temp;
//	cout<<endl;
}





int curi = numframes-1;
int curj = hyp_numframes-1;
int bt_pos = 0;

int *backtrack_real = new int[numframes*2];
int *backtrack_hypo = new int[numframes*2];



while(curi >0 && curj > 0)
{
	backtrack_real[bt_pos] = curi;
	backtrack_hypo[bt_pos] = curj;
	bt_pos++;

	if(I0[curi][curj] == 0 && I1[curi][curj] == 0) // DIAG)
		curi --, curj--;
	else if(I0[curi][curj] == 1, I1[curi][curj] == 0) //LEFT)
		curj--;
	else
		curi --;
	
}

//for(int i=0;i<bt_pos;i++)
//{
//fprintf(stderr, "%d, %d\n ", backtrack_real[i],backtrack_hypo[i]);
//		fflush(stderr);
//}



FILE * fp2 = fopen(argv[3], "r");// this is the marker file for the hypovid
FILE * out = fopen(argv[4], "w"); // this will store final ball-wise segmentation

int beg, end, bt_beg, bt_end;
while(!feof(fp2))
{
	fscanf(fp2, "%d %d ", &beg, &end);
	bt_beg = 0, bt_end = 0;

	for(int m=bt_pos-1;m>0;m--)
		if(backtrack_hypo[m] == beg)
		{
			bt_beg = backtrack_real[m];
			break;
		}

	for(int m=bt_pos-1;m>0;m--)
		if(backtrack_hypo[m] == end)
		{
			bt_end = backtrack_real[m];
						break;
		}
//fprintf(stderr, "%d, %d\n ", bt_beg,bt_end);
//if(bt_beg==bt_end)
//continue;
if(bt_end==0)
bt_end=numframes;
	fprintf(out, "%d %d\n", bt_beg, bt_end);
	

}

fclose(fp2);
fclose(out);


}
