Description of code and Usage Instructions

1.) Generating Histogram Scores for each frame in a video.
Compile : 'g++ genScores2.cpp -I /usr/local/include/opencv/ -L /usr/local/lib/ -Wl,-rpath,/usr/local/lib/ -lcxcore -lcv -lhighgui -lavcodec -o genScores2'
Usage : './genScores2 other_histograms/2_ground_m1i1_8 other_histograms/2_pitch_m1i1_8 other_histograms/2_sky_m1i1_8 other_histograms/2_scoreCard other_histograms/player_mi other_histograms/player_csk'
sample output : 'score_m1i1'


2.) Generate Hypothetical video using "outcomes" from Cricinfo
Compile : 'g++ -o makehypovid3 makehypovid3.cpp'
Usage : './makehypovid3 outfile0 hypovid_temp0 hypovid_begend0'
outfile0: Commentary file in specified format
hypovid_temp0 : Histogram score for each frame generated using commentary
hypovid_begend0 : Ball Boundaries Learnt
sample output : 'score_m1i1'

3.)  Dynamic programming alignment
Compile : 'g++ -o rundp6 rundp6.cpp'
Usage : './rundp6 score_m1i1 hypovid_temp0 hypovid_begend0 seg_1 weight1 weight2 weight3 weight4 weight5 weight6 weight7'
Output : seg_1 contains the Ball Boundaries using Dynamic Programming Alignment

Utility Functions:

1.) Accuracy :
Compile : 'g++ -o accu accu.cpp'
Usage : './accu GT Predicted'
./accu outfile0 seg_0
Description: Get framelevel accuracy of predicted boundaries.Each frame is checked if it falls into correct ball.

2.) overwise_multiple.cpp
Compile : 'g++ -o overwise overwise_multiple.cpp'
Usage : './overwise m1_i1_1.txt overs'
Description: Will process N overs at a time and return best accuracy by varying the weights.

Learning Models for Different Outcomes

The models can be learned for different cricket outcomes such as noball,wide,one run etc and so on.

1.) models/modelscene2.cpp
Learning model using Commentary and Histogram scores from one match
Uses two files : score_m1i2 and m1_i2_1.txt

Sample usage: models/model2.sh

2.) models/modelscene.cpp
Learns model using Both innings of a Match.


















