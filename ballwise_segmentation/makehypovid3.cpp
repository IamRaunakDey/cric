#include<stdio.h>
#include<string.h>
#include<iostream>
#define avgadlen 0
using namespace std;

main(int argc, char * argv[])
{
int onerunlen, tworunslen, threerunslen, FOURlen, SIXlen, noballlen, norunlen, OUTlen, widelen,TIMElen,EXTRAlen;
float **onerunmod, **tworunsmod, **threerunsmod, **FOURmod, **SIXmod, **noballmod, **norunmod, **OUTmod, **widemod,**TIMEmod,**EXTRAmod;

//cout<<"YES1"<<endl;
FILE *  fp = fopen("../models/TIME_model_both_innings", "r");
fscanf(fp, "%d ", &TIMElen);
TIMEmod = new float*[TIMElen];
for(int i=0;i<TIMElen;i++)
{
	TIMEmod[i] = new float[7];
	for(int j=0;j<7;j++)
		fscanf(fp, "%f ", &TIMEmod[i][j]);
}
fclose(fp);
  fp = fopen("../models/EXTRA_model_one_innings", "r");
fscanf(fp, "%d ", &EXTRAlen);
EXTRAmod = new float*[EXTRAlen];
for(int i=0;i<EXTRAlen;i++)
{
        EXTRAmod[i] = new float[7];
        for(int j=0;j<7;j++)
                fscanf(fp, "%f ", &EXTRAmod[i][j]);
}
fclose(fp);


  fp = fopen("../models/1_run_model_both_innings", "r");
fscanf(fp, "%d ", &onerunlen);
onerunmod = new float*[onerunlen];
for(int i=0;i<onerunlen;i++)
{
	onerunmod[i] = new float[7];
	for(int j=0;j<7;j++)
		fscanf(fp, "%f ", &onerunmod[i][j]);
}
fclose(fp);
//cout<<"YES"<<endl;

 fp = fopen("../models/2_run_model_both_innings", "r");
fscanf(fp, "%d ", &tworunslen);
tworunsmod = new float*[tworunslen];
for(int i=0;i<tworunslen;i++)
{
	tworunsmod[i] = new float[7];
	for(int j=0;j<7;j++)
		fscanf(fp, "%f ", &tworunsmod[i][j]);
}
fclose(fp);
//cout<<"YES"<<endl;

 fp = fopen("../models/3_run_model_both_innings", "r");
fscanf(fp, "%d ", &threerunslen);
threerunsmod = new float*[threerunslen];
for(int i=0;i<threerunslen;i++)
{
	threerunsmod[i] = new float[7];
	for(int j=0;j<7;j++)
	fscanf(fp, "%f ", &threerunsmod[i][j]);
}
fclose(fp);
 fp = fopen("../models/FOUR_model_both_innings", "r");
fscanf(fp, "%d ", &FOURlen);
FOURmod = new float*[FOURlen];
for(int i=0;i<FOURlen;i++)
{
	FOURmod[i] = new float[7];
	for(int j=0;j<7;j++)
	fscanf(fp, "%f ", &FOURmod[i][j]);
}
fclose(fp);
 fp = fopen("../models/SIX_model_both_innings", "r");
fscanf(fp, "%d ", &SIXlen);
SIXmod = new float*[SIXlen];
for(int i=0;i<SIXlen;i++)
{
	SIXmod[i] = new float[7];
	for(int j=0;j<7;j++)
	fscanf(fp, "%f ", &SIXmod[i][j]);
}
fclose(fp);
 fp = fopen("../models/no_ball_model_both_innings", "r");
fscanf(fp, "%d ", &noballlen);
noballmod = new float*[noballlen];
for(int i=0;i<noballlen;i++)
{
	noballmod[i] = new float[7];
	for(int j=0;j<7;j++)
	fscanf(fp, "%f ", &noballmod[i][j]);
}
fclose(fp);
 fp = fopen("../models/no_run_model_both_innings", "r");
fscanf(fp, "%d ", &norunlen);
norunmod = new float*[norunlen];
for(int i=0;i<norunlen;i++)
{
	norunmod[i] = new float[7];
	for(int j=0;j<7;j++)
	fscanf(fp, "%f ", &norunmod[i][j]);
}
fclose(fp);
//cout<<"YES"<<endl;

 fp = fopen("../models/OUT_model_both_innings", "r");
fscanf(fp, "%d ", &OUTlen);
OUTmod = new float*[OUTlen];
for(int i=0;i<OUTlen;i++)
{
	OUTmod[i] = new float[7];
	for(int j=0;j<7;j++)
	fscanf(fp, "%f ", &OUTmod[i][j]);
}
fclose(fp);
//cout<<"YES"<<endl;

 fp = fopen("../models/wide_model_both_innings", "r");
fscanf(fp, "%d ", &widelen);
widemod = new float*[widelen];
for(int i=0;i<widelen;i++)
{
	widemod[i] = new float[7];
	for(int j=0;j<7;j++)
	fscanf(fp, "%f ", &widemod[i][j]);
}
fclose(fp);
//cout<<"YES"<<endl;


fp = fopen(argv[1], "r");
FILE * out = fopen(argv[2], "w"); //this will store the hypothetical video
FILE * out2 = fopen(argv[3], "w"); // this will contain the beg-end of scenes in hypo vid
char outcome[400][12], ballstr[400][10];
int begshot[400], begframe[400], endframe[400], ballpos = 0;
//int ballpos = 0;
//cout<<"YES"<<endl;
/*
while(!feof(fp))
{
	fscanf(fp,"%s %s %d %d %d ", ballstr[ballpos], outcome[ballpos], &begshot[ballpos], &begframe[ballpos], &endframe[ballpos]);
	if(strstr(ballstr[ballpos], "40."))
		break;
	ballpos++;
}
*/
ballpos =0;
while(!feof(fp))
{
	fscanf(fp,"%s %s %d %d %d ", ballstr[ballpos], outcome[ballpos], &begshot[ballpos], &begframe[ballpos], &endframe[ballpos]);
	//cout<<ballstr[ballpos]<<" "<<outcome[ballpos]<<endl;
	ballpos++;
}

fclose(fp);

float **hypovid = new float*[600000];
int framepos = 0;
int *gtvid = new int[600000], gtframepos = 0;
for(int i=0;i<ballpos;i++)
{

// hypovid generation

//cout<<outcome[i]<<" ";
	if(!strcmp(outcome[i], "1_run"))
	{
	
		fprintf(out2, "%d %d\n", framepos, framepos+onerunlen);
		for(int m=0;m<onerunlen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = onerunmod[m][k];
		}
		framepos += onerunlen;//cout<<" "<<outcome[i]<<" 1 ";
	}
	else
	if(!strcmp(outcome[i], "2_runs"))
	{
		fprintf(out2, "%d %d\n", framepos, framepos+tworunslen);
		for(int m=0;m<tworunslen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = tworunsmod[m][k];
		}
		framepos += tworunslen;	//cout<<" 2 ";

	}
	else
	if(!strcmp(outcome[i], "3_runs"))
	{
		fprintf(out2, "%d %d\n", framepos, framepos+threerunslen);
		for(int m=0;m<threerunslen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = threerunsmod[m][k];
		}
		framepos += threerunslen;//	cout<<" 3 ";

	}
	else
	if(strstr(outcome[i], "FOUR"))
	{
		fprintf(out2, "%d %d\n", framepos, framepos+FOURlen);
		for(int m=0;m<FOURlen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = FOURmod[m][k];
		}
		framepos += FOURlen;	//cout<<" 4 ";

	}
	else
	if(strstr(outcome[i], "SIX"))
	{
		fprintf(out2, "%d %d\n", framepos, framepos+SIXlen);
		for(int m=0;m<SIXlen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = SIXmod[m][k];
		}
		framepos += SIXlen;	//cout<<" 5 ";

	}
	else
	if(strstr(outcome[i], "OUT"))
	{
		fprintf(out2, "%d %d\n", framepos, framepos+OUTlen);
		for(int m=0;m<OUTlen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = OUTmod[m][k];
		}
		framepos += OUTlen;	//cout<<" 6";

	}
	else
	if(strstr(outcome[i], "no_ball"))
	{
		fprintf(out2, "%d %d\n", framepos, framepos+noballlen);
		for(int m=0;m<noballlen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = noballmod[m][k];
		}
		framepos += noballlen;	//cout<<" 7 ";

	}
	else
	if(!strcmp(outcome[i], "no_run"))
	{
		fprintf(out2, "%d %d\n", framepos, framepos+norunlen);
		for(int m=0;m<norunlen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = norunmod[m][k];
		}
		framepos += norunlen;	//cout<<" 8 ";

	}
	else
	if(strstr(outcome[i], "wide"))
	{
		fprintf(out2, "%d %d\n", framepos, framepos+widelen);
		for(int m=0;m<widelen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = widemod[m][k];
		}
		framepos += widelen;	//cout<<" 9 ";

	}
	else
	if(strstr(outcome[i], "1_"))
	{
		fprintf(out2, "%d %d\n", framepos, framepos+onerunlen);
		for(int m=0;m<onerunlen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = onerunmod[m][k];
		}
		framepos += onerunlen;//	cout<<" 10 ";

	}
	else
	if(strstr(outcome[i], "2_"))
	{
		fprintf(out2, "%d %d\n", framepos, framepos+tworunslen);
		for(int m=0;m<tworunslen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = tworunsmod[m][k];
		}
		framepos += tworunslen;//	cout<<" 11 ";

	}
	else
	if(strstr(outcome[i], "3_"))
	{
		fprintf(out2, "%d %d\n", framepos, framepos+threerunslen);
		for(int m=0;m<threerunslen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = threerunsmod[m][k];
		}
		framepos += threerunslen;//	cout<<" 12 ";

	}
	else
	if(strstr(outcome[i], "TIME"))
	{
	//cout<<"timeout";
		fprintf(out2, "%d %d\n", framepos, framepos+TIMElen);
		for(int m=0;m<TIMElen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				hypovid[framepos+m][k] = TIMEmod[m][k];
		}
		framepos += TIMElen;//	cout<<" 12 ";

	}
	else
 if(strstr(outcome[i],"EXTRA"))
{
fprintf(out2, "%d %d\n", framepos, framepos+EXTRAlen);
                for(int m=0;m<EXTRAlen;m++)
                {
                        hypovid[framepos + m] = new float[7];
                        for(int k=0;k<7;k++)
                                hypovid[framepos+m][k] = EXTRAmod[m][k];
                }
                framepos += EXTRAlen;//  cout<<" 12 ";

}

else
		cout<<"Didnt find match for: "<<outcome[i]<<endl;	
		
/*
	if(strstr(ballstr[i+1], ".1") && !strstr(ballstr[i+1], "(")) // the bracket takes care of cases where the first ball could also be an extra
	{
		for(int m=0;m<avgadlen;m++)
		{
			hypovid[framepos + m] = new float[7];
			for(int k=0;k<7;k++)
				if(k == 4)
					hypovid[framepos+m][k] = 2;
				else
					hypovid[framepos+m][k] = 0;
					
		}
		framepos += avgadlen;
	}
*/
//	cout<<ballstr[i]<<"\t"<<framepos<<endl;

}

fprintf(out, "%d\n", framepos);

for(int l=0;l<framepos;l++)
{
	for(int k=0;k<7;k++)
		fprintf(out, "%f ", hypovid[l][k]);
	fprintf(out, "\n");
}

fclose(out);
fclose(out2);

}

