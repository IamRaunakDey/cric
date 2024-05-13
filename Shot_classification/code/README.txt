Code for Shot Segmentation and Classification

1.) cut_detect1.m denotes sample usage of the shot segmentation algorithm
Generates a CSV containing cut frame numbers

2.) cutDetect.m : 
% This funtion takes dissimilarity distribution as input, and output the
% shot boundary. It detects the shot cuts with adaptive threshold
% algorithm

3.) getHistogramFeature
% This function is used to read frame image of a video and calculate the
% distance function based on intensity histogram. It take the frame
% filename's prefix and the total framenumber as input parameter.

4.)  BOW for each shot using VLFEAT SIFT feature.
Steps
1.) Randomly Sample sift feature across large corpus
2.) use K Means to cluster into Groups.
3.) Represent Each shot by a Feature vector of Length K.

File : 'bow.m'

5.) Linear Chain CRF

Please refer https://www.cs.ubc.ca/~schmidtm/Software/UGM/chain.html
or http://vision.csd.uwo.ca/code/gco-v3.0.zip



