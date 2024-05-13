
#include<iostream>
#include<string.h>
#include<cstdio>

using namespace std;

main(int argc, char *argv[])
{
	//cout<<"YES"<<endl;

	char ballstr[10], outcome[10], category[10] = "wide", dummystr[100];
//	strcpy(category, argv[1]);
	int begshot, begframe1[1000], endframe1[1000],begframe2[1000], endframe2[1000], category_length = 0, category_nums = 0, can_length,dummy;
	float ** scores = new float*[600000], model[5000][7];
	//cout<<"YES"<<endl;

	FILE *fp = fopen(argv[1],"r");
	FILE *fp1;

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

		fscanf(fp, "%d %d ",&begframe2[j], &endframe2[j]);
		//	cout<<i<<" "<<begframe2[i]<<" "<<endframe2[i]<<endl;
			j++;
//cout<<ftell(fp)<<endl;
	}
		fclose(fp);

	//int j=0;
	i--;
	j--;
//	cout<<i<<" "<<j<<endl;
	int corr=0,wrong=0;
if(endframe1[i]==0)
endframe1[i]=begframe1[i];
//cout<<begframe1[1]<<" "<<endframe1[i]<<endl;	
//cout<<i<<" "<<endframe1[i]-begframe1[1]<<endl;
int diff=endframe1[i]-begframe1[1];
	for(int k=1;k<endframe1[i]-begframe1[1];k++)
	{
	//	cout<<k<<" ";
		int pos1=-1,pos2=0;
		for(int l=0;l<=i;l++)
		{
			if(((k+begframe1[1])>=begframe1[l]) && ((k+begframe1[1])<=endframe1[l]))
			{
			pos1=l;
			break;
			}
		}
		if(pos1==-1)
		cout<<"error"<<k+begframe1[1]<<" "<<pos1<<endl;
		for(int l=1;l<=j;l++)
		{
			if(k>=begframe2[l] && k<=endframe2[l])
			{
			pos2=l;
			if(l==pos1)
			break;
			}
		}
		if(pos1==pos2)
		corr++;
		else
		wrong++;
	//cout<<k<<" "<<pos1<<" "<<pos2<<endl;
		
	}
	//cout<<corr<<" "<<wrong<<endl;
	cout<<100.0*corr/(corr+wrong)<<endl;



}
