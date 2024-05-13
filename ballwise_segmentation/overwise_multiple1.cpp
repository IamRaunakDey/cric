#include<stdio.h>
#include <sstream>
#include<cstdio>
#include<cstdlib>

#include<string.h>
#include<iostream>
#include<string>
#define avgadlen 1120
using namespace std;

std::string exec(char* cmd) {
	FILE* pipe = popen(cmd, "r");
	if (!pipe) return "ERROR";
	char buffer[128];
	std::string result = "";
	while(!feof(pipe)) {
		if(fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return result;
}
float maxacc=0;
int maxi1,maxi2,maxi3,maxi4,maxi5,maxi6,maxi7;

main(int argc, char * argv[])
{
	char dummystr[100];
	FILE * fp=fopen("score_m1i1", "r");
	for(int m=0;m<7;m++)
		fscanf(fp, "%s ", dummystr);
	float ** scores = new float*[600000];

	int pos =0, numframes;
	float a1=0,a2=0,a3=0,a4=0,a5=0,a6=0,a7=0;
	while(!feof(fp))
	{
		scores[pos] = new float[7];
		for(int m=0;m<7;m++)
		{
			fscanf(fp, "%f ", &scores[pos][m]);
			a1=max(a1,scores[pos][0]);a2=max(a2,scores[pos][1]);a3=max(a3,scores[pos][2]);a4=max(a4,scores[pos][3]);
			a5=max(a5,scores[pos][4]);a6=max(a6,scores[pos][5]);a7=max(a7,scores[pos][6]);

		}


		pos++;
	}
	cout<<a1<<" "<<a2<<" "<<a3<<" "<<a4<<" "<<a5<<" "<<a6<<" "<<a7<<endl;
	//cout<<pos<<endl;
	int limit=atoi(argv[2]);
	cout<<"Limit: "<<limit<<endl;
	
	   for(int i1=1;i1<=11;i1+=2)
	   {
	   for(int i2=1;i2<=11;i2+=2)
	   {
	   for(int i3=1;i3<=11;i3+=2)
	   {
	   for(int i4=1;i4<=11;i4+=2)
	   {
	   for(int i5=1;i5<=11;i5+=2)
	   {
	   for(int i6=1;i6<=11;i6+=2)
	   {
	   for(int i7=1;i7<=11;i7+=2)
	   {
	   

	//	0 0 0 2 2 2 10
	//
	/*
	int i1=1;
	int 	i2=1;
	int 	i3=1;
	int 	i4=3;
	int 		i5=1;
	int 		i6=9;
	int 		i7=7;
*/
	float total_acc=0;


	cout<<i1/a1<<" "<<i2/a2<<" "<<i3/a3<<" "<<i4/a4<<" "<<i5<<" "<<i6/a6<<" "<<i7/a7<<" "<<endl;
cout<<i1<<" "<<i2<<" "<<i3<<" "<<i4<<" "<<i5<<" "<<i6<<" "<<i7<<endl;
	int count=0;
	char outcome[400][12], ballstr[400][10];
	int begshot[400],begframe[400],endframe[400];
	int ballpos=0;
	fp = fopen(argv[1], "r");
	int strt=0,end=0;

	int counter=0;								
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %d %d %d ", ballstr[ballpos], outcome[ballpos], &begshot[ballpos], &begframe[ballpos], &endframe[ballpos]);
		//									if(strstr(ballstr[ballpos],"ADVT"))
		//									continue;	
		//cout<<ballstr[ballpos]<<" "<<outcome[ballpos]<<" "<<begshot[ballpos]<<" "<<begframe[ballpos]<<" "<<endframe[ballpos]<<endl;
		ballpos++;

		if(strstr(ballstr[ballpos-1],".6"))
		{
			counter++;
		}
		if(counter==limit)
		{
			counter=0;
			strt=begframe[0];
			end=endframe[ballpos-1];
			char outfile[100]="outfile";
			sprintf(outfile,"%s%d",outfile,count);
			//cout<<"outfile: "<<outfile<<endl;
			//	cout<<count<<" "<<strt<<" "<<end<<" "<<end-strt<<" "<<outfile<<endl;
			FILE * out = fopen(outfile, "w"); // this will store final ball-wise segmentation
			for(int i=0;i<ballpos;i++)
				fprintf(out,"%s %s %d %d %d\n", ballstr[i], outcome[i], begshot[i], begframe[i], endframe[i]);

			fclose (out);

			char gen[100]="sed -n '";
			sprintf(gen,"%s%d,%dp' score_m1i1 > score_%d",gen,strt,end,count);
			cout<<gen<<endl;
			system(gen);
			system("g++ -o makehypovid3 makehypovid3.cpp");

			char make[100]="./makehypovid3 ";
			sprintf(make,"%s outfile%d hypovid_temp%d hypovid_begend%d",make,count,count,count);
			cout<<make<<endl;
			system(make);
			system("g++ -o rundp6 rundp6.cpp");

			system("chmod 777 rundp6");
			char rundp[1000]="./rundp6 ";
			char rundp1[1000];

			sprintf(rundp,"%s score_%d hypovid_temp%d hypovid_begend%d seg_%d %f %f %f %f %d %f %f",rundp,count,count,count,count,i1/a1,i2/a2,i3/a3,i4/a4,i5,i6/a6,i7/a7);
			//sprintf(rundp1,"%s hypovid_temp%d score_%d hypovid_begend%d seg_1_%d",rundp,count,count,count,count);
			cout<<rundp<<" "<<endl;
			system(rundp);
			//system(rundp1);
			system("g++ -o accu accu.cpp");

			char acc[100]="./accu ";
			sprintf(acc,"%s %s seg_%d",acc,outfile,count);
			//char acc1[100];
			//sprintf(acc1,"%s %s seg_1_%d >> accu2",acc,outfile,count);
			//cout<<acc<<endl;
			string result=exec(acc);
			//system(acc);
			//system(acc1);
			//	cout<<result<<endl;
			ballpos=0;
			double temp = ::atof(result.c_str());
			total_acc+=temp;
			cout<<temp<<" ";
			cout<<endl;
			//cout<<count<<" ";
			count++;

			//break;

			//break;
		}


	}
	cout<<endl;

	cout<<count<<endl;
	cout<<total_acc/count<<endl;
	FILE * o1 = fopen("weights.txt", "a");
	fprintf(o1, "\nAccuracy: %f\n",total_acc/count);
	fclose(o1);
	if(total_acc/count>=maxacc)
	{
		maxacc=total_acc/count;
		maxi1=i1;maxi2=i2;maxi3=i3;maxi4=i4;maxi5=i5;maxi6=i6;maxi7=i7;
	}
	cout<<"Maximum:"<<maxacc<<" "<<maxi1<<" "<<maxi2<<" "<<maxi3<<" "<<maxi4<<" "<<maxi5<<" "<<maxi6<<" "<<maxi7<<endl;
cout<<i1/a1<<":"<<i2/a2<<":"<<i3/a3<<":"<<i4/a4<<":"<<i5<<":"<<i6/a6<<":"<<i7/a7<<endl;

}}}}}}}
return 0;
}

