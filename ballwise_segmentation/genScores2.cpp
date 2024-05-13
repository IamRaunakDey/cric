/* input parameters order : 
 * ground pitch sky scorecard team1 team2 videopath
 */



#include "highgui.h"
#include "cv.h"
#include <iostream>
#include <vector>
#include <fstream>

#include <cstring>


using namespace std;

vector <float> loadHistogram( char* fileName );

int main( int argc, char** argv )
{

	vector <float> groundHistogram, pitchHistogram, skyHistogram, scorecardHistogram, playerHistogramSL, playerHistogramSA;

//	groundHistogram = loadHistogram( "2_ground_m1i1_8" );
//	pitchHistogram = loadHistogram( "2_pitch_m1i1_8" );
//	skyHistogram = loadHistogram( "2_sky_m1i1_8" );
//	scorecardHistogram = loadHistogram( "2_scoreCard" );
//	playerHistogramSL = loadHistogram( "SL_player_m1i1_8" );
//	playerHistogramSA = loadHistogram( "SA_player_m1i1_8" );

	groundHistogram = loadHistogram( argv[1] );
	pitchHistogram = loadHistogram( argv[2] );
	skyHistogram = loadHistogram( argv[3] );
	scorecardHistogram = loadHistogram( argv[4] );
	playerHistogramSL = loadHistogram( argv[5] );
	playerHistogramSA = loadHistogram( argv[6] );

	IplImage *img;
//	CvCapture *stream = NULL;
//	stream = cvCreateFileCapture( "/pocketneutron/kps/match1_innings1.mpg" );
//	stream = cvCaptureFromAVI( argv[7] );
//	stream = cvCreateFileCapture( argv[7] );
//	cout << stream << endl;

	int scorecard_flag = 0;

	long int frameCounter = 0;

//	cvNamedWindow( "Window1", CV_WINDOW_AUTOSIZE );
		
	cout << "ground  pitch  sky  scorecard  scorecard_flag  " << argv[5] << "  " << argv[6] << endl;

	//cout << argv[1] << argv[2] << argv[3] << argv[4] << argv[5] << argv[6] << argv[7] << endl;



	char str[1000];
	int frame_number;

    for(frame_number=1;;frame_number++)
    {

         sprintf(str, "%s/%d.jpg", argv[7], frame_number);
	//sprintf(str, "/Pulsar2/rahul.anand/oldc/back/m1_i1/m1_i1/%d.jpg", frame_number);
//	cout<<frame_number<<" "<<str<<endl;

//	if(frame_number %1000 ==0)
  //          {cout<<str<<endl;}
        img = cvLoadImage( str, 1 );
		if( !img )
		{
//			cout << "Exit" << endl;
			break;
		}
		
		/*if( !cvGrabFrame( stream ) )
		{
			break;
		}
		img = cvRetrieveFrame( stream );*/

		frameCounter ++;

		CvScalar s;
		int height = img->height;
		int width = img->width;
		int p,q;
		int rpix, gpix, bpix, rbin, gbin, bbin, binNo;

		float ground_score = 0.0, pitch_score = 0.0, sky_score = 0.0, scorecard_score = 0.0, SL_player_score = 0.0, SA_player_score = 0.0;


		/* mark the score-card */
		scorecard_flag = 0; /* score-card present at the bottom */
//cout<<height<<width<<endl;
	//	for( p = 255; p <= 282; p++ )
				for( p = 309; p <= 344; p++ )

		{
	//				for( q = 8; q <= 346; q++ )

			for( q = 129; q <= 225; q++ )
			{
				s = cvGet2D( img, p, q );

				rpix = int( s.val[2] );
				gpix = int( s.val[1] );
				bpix = int( s.val[0] );

				rbin = rpix/32;
				gbin = gpix/32;
				bbin = bpix/32;

				binNo = rbin + (gbin + bbin*8)*8;

				if( scorecardHistogram[binNo] > 0.0000000 )
				{
					scorecard_score += scorecardHistogram[binNo];
				}
			}
		}
if(scorecard_score > 250)
scorecard_flag=0;
else
scorecard_flag=2;
		

		/* mark the ground, pitch and sky */

		for( p = 1; p <= 350; p++ )
		{
			for( q = 1; q <= 630; q++ )
			{
//cout<<p<<" "<<q<<endl;
//cout<<height<<" "<<width<<endl;
				s = cvGet2D( img, p, q );

				rpix = int( s.val[2] );
				gpix = int( s.val[1] );
				bpix = int( s.val[0] );

				rbin = rpix/32;
				gbin = gpix/32;
				bbin = bpix/32;

				binNo = rbin + (gbin + bbin*8)*8;
				float thresh=0.013974;
				/* ground */
				if( groundHistogram[binNo] > thresh )
				{
					ground_score += groundHistogram[binNo];
				}


				/* SL player */
				if( playerHistogramSL[binNo] > thresh )
				{
					SL_player_score += playerHistogramSL[binNo];
					//s.val[2] = 255;
					//s.val[1] = 0;
					//s.val[0] = 255;
				}

				/* SA player */
				if( playerHistogramSA[binNo] > thresh )
				{
					SA_player_score += playerHistogramSA[binNo];
					//s.val[2] = 255;
					//s.val[1] = 0;
					//s.val[0] = 255;
				}

				/* pitch */
				if( pitchHistogram[binNo] > thresh )
				{
					pitch_score += pitchHistogram[binNo];
				}

				/* sky */				
				if( skyHistogram[binNo] > thresh )
				{
					sky_score += skyHistogram[binNo];
				}
				cvSet2D( img, p, q, s );

			}
		}
float sum=height*width;
sum=1;
		cout <<ground_score/sum << " " << pitch_score/sum << " " << sky_score/sum << " " << scorecard_score/sum<< " "<< scorecard_flag << " " << SL_player_score/sum << " " << SA_player_score/sum <<  endl;
		//cout <<frame_number<<"\t "<< scorecard_score<< " "<< scorecard_flag <<endl;

//		cvShowImage( "Window1", img );
//		char ch = cvWaitKey( 0 );
//		if( ch == ' ' )
//			continue;
//		if( ch == 27 )
//			break;

	cvReleaseImage(&img);
	}

//	cvDestroyWindow( "Window1" );
	
//	cvReleaseCapture( &stream );

	cout << frameCounter << endl;

	return 0;
}


vector <float> loadHistogram( char* fileName )
{
	ifstream f;
	float val;
	vector <float> result;
float sizefactor=(640*360.0)/(480*352);
	f.open( fileName );

	for( int i = 0; i < 512; i++ )
	{
		f >> val;
		result.push_back( val/sizefactor );
	}

	f.close();
	
	return result;
}
