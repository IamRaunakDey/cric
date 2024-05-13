
#include<iostream>
#include<string.h>
#include<cstdio>
#include <fstream>      // std::ofstream
using namespace std;

main(int argc, char *argv[])
{
	//cout<<"YES"<<endl;

	char ballstr[10], outcome[10], category[10] = "wide", dummystr[100];
//	strcpy(category, argv[1]);
	int begshot, begframe1[1000], endframe1[1000],begframe2[1000], endframe2[1000], category_length = 0, category_nums = 0, can_length,dummy;
	float ** scores = new float*[600000], model[5000][7];
	//cout<<"YES"<<endl;
long long int shot[10000],seg_shot[10000];
long long int a1[1000][50]={0},a2[1000][50]={0};
	FILE *fp = fopen(argv[1],"r");
	
int i=1;
	while(!feof(fp))
	{

		fscanf(fp, "%s %s %d %d %d ",dummystr, dummystr, &begshot, &begframe1[i], &endframe1[i]);
		//	cout<<i<<" "<<begframe1[i]<<" "<<endframe1[i]<<endl;
			i++;
	}
	fclose(fp);

fp = fopen(argv[2],"r");
	

int j=1;
	while(!feof(fp))
	{

		fscanf(fp, "%lld\n",&shot[j]);
			//cout<<j<<" "<<shot[j]<<endl;
			j++;
		
	}
		fclose(fp);

	
	
	int numballs=j;
fp = fopen(argv[3],"r");
	

int k=1;
	while(!feof(fp))
	{

		fscanf(fp, "%d %d\n",&begframe2[k], &endframe2[k]);
		begframe2[k]+=begframe1[1];
		endframe2[k]+=begframe1[1];

			//cout<<k<<" "<<begframe2[k]<<" "<<endframe2[k]<<endl;
			k++;
		
	}
		fclose(fp);
		
		ofstream outFile("output_100.txt");

	for(int a=1;a<i;a++)
	{
	// 	cout<<a;
		outFile << a; // put on file
	int index=0;


	for(int l=1;l<j;l++)
	{
	if(shot[l]<=endframe1[a] && shot[l] >=begframe1[a])
	{
	a1[a][index++]=shot[l];
	//cout<<l<<" "<<index<<endl;
//	cout<<","<<shot[l];
	outFile <<","<<shot[l];	
	
	}
	}
	outFile<<endl;
	//cout<<endl;
	}
	 outFile.close();

		ofstream out1("output_200.txt");
		for(int k=1;k<i;k++)
	{
	out1<<k;
	 	//cout<<k;
	int index=0;

	for(int l=1;l<j;l++)
	{
	if(shot[l]<=endframe2[k] && shot[l] >=begframe2[k])
	{
	a2[k][index++]=shot[l];
	out1<<","<<shot[l];
	//cout<<","<<shot[l];
	}
	}
	out1<<endl;
//	cout<<endl;
	}
	
	int corr=0,wrong=0;
	for(int l=1;l<i;l++)
	{
//	cout<<l;
	for(int b=0;b<9;b++)
	{
	if(a1[l][b]==0)
	break;
	//cout<<","<<a1[l][b];
	int flag=0;
	for(int c=0;c<100;c++)
	{
	if(a2[l][c]==0)
	break;
	//cout<<a2[l][c]<<" ";
	if(a2[l][c]==a1[l][b])
	{
	flag=1;
	//cout<<"corr"<<" ";
	corr++;
	break;
	}	
	}
	if(flag==0)
	{
	//cout<<"wrong"<<" ";
	wrong++;
	}
	
	
	}
	//cout<<endl;
	}
	

cout<<100.0*corr/(corr+wrong)<<endl;



}
