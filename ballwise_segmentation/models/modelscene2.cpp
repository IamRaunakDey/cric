#include<iostream>
#include<string.h>
#include<cstdio>

using namespace std;

main(int argc, char *argv[])
{
	char ballstr[10], outcome[10], category[10] = "wide", dummystr[100];
	strcpy(category, argv[1]);
	int begshot, begframe, endframe, category_length = 0, category_nums = 0, can_length;
	float ** scores = new float*[600000], model[8000][7];
	for(int i=0;i<600000;i++)
		scores[i] = new float[7];


	FILE * fp = fopen("m1_i2_1.txt", "r");
	while(!feof(fp))
	{
		fscanf(fp, "%s %s %d %d %d ", ballstr, outcome, &begshot, &begframe, &endframe);
		if(strstr(outcome, category))
		{
			if(strstr(ballstr, ".6")) // ignoring end of over balls	
				continue;
			category_length += endframe - begframe;
			category_nums ++;
		}

	}
	fclose(fp);


//	cout<<category_nums<<endl;
//	cout<<"Canonical length = "<<float(category_length)/category_nums<<endl;
	can_length = category_length/category_nums;
	cout<<can_length<<endl;

	fp = fopen("score_m1i2", "r");
	for(int m=0;m<7;m++)
		fscanf(fp, "%s ", dummystr);
	int pos =0;
	while(!feof(fp))
	{
		for(int m=0;m<7;m++)
			fscanf(fp, "%f ", &scores[pos][m]);
		pos++;
	}

	fclose(fp);	
	

	category_nums = 0;
	fp = fopen("m1_i2_1.txt", "r");
	while(!feof(fp))
	{
		fscanf(fp, "%s %s %d %d %d ", ballstr, outcome, &begshot, &begframe, &endframe);
		if(strstr(outcome, category))
		{
			if(strstr(ballstr, ".6")) // ignoring end of over balls	
				continue;
	//	cout<<ballstr<<" "<<outcome<<" "<<begshot<<" "<<begframe<<" "<<endframe<<endl;
		//			cout<<"yes"<<endl;

			for(int l=0;l<can_length;l++)
			{
			         int k = begframe + (int)(l*(endframe - begframe)/can_length);

			         for(int m=0;m<7;m++)
			                 model[l][m] += scores[k][m];
					
			}
			category_nums ++;
		//cout<<ballstr<<" "<<outcome<<" "<<begshot<<" "<<begframe<<" "<<endframe<<endl;

		}

	}
	fclose(fp);




	
	
	for(int i=0;i<can_length;i++, cout<<endl)
		for(int j=0;j<7;j++)
			cout<<model[i][j]/category_nums<<" ";
}
