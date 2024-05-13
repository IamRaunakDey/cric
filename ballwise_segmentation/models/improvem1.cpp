
#include<iostream>
#include<string.h>

using namespace std;

main(int argc, char *argv[])
{
	//cout<<"YES"<<endl;

	char ballstr[10], outcome[10], category[10] = "wide", dummystr[100];
	strcpy(category, argv[1]);
	int begshot, begframe, endframe, category_length = 0, category_nums = 0, can_length,dummy;
	float ** scores = new float*[600000], model[5000][7];
	//cout<<"YES"<<endl;

	category_nums = 0;
	FILE *fp = fopen("m1_i2.txt", "r");
	FILE *fp1;
			//fscanf(fp, "%s %s %d %d %d ", ballstr, outcome, &begshot, &begframe, &endframe);
		//			fscanf(fp, "%s %s %d %d %d ", ballstr, outcome, &begshot, &begframe, &endframe);

//cout<<ballstr<<" "<<outcome<<" "<<begshot<<" "<<begframe<<" "<<endframe;
//cout<<"YES"<<endl;
	while(!feof(fp))
	{
	fpos_t position;

		fscanf(fp, "%s %s %d %d %d ", ballstr, outcome, &begshot, &begframe, &dummy);
	fgetpos (fp, &position);
	if(feof(fp))
	break;
		fscanf(fp, "%s %s %d %d %d ", dummystr, dummystr, &dummy, &endframe, &dummy);
 fsetpos (fp, &position);
		cout<<ballstr<<" "<<outcome<<" "<<begshot<<" "<<begframe<<" "<<endframe-1<<endl;
//cout<<ftell(fp)<<endl;
	}
	fclose(fp);




}
