

imageFileNamePrefix = '/path/to/frames/'


av_files=dir([imageFileNamePrefix '*.jpg');
noOfFrameImages =length(av_files)
imageFileNamePrefix
featureHist = getHistogramFeature(imageFileNamePrefix, noOfFrameImages);
cutHist = cutDetect(featureHist);
Hist=cutHist(:,1);

cuts=[0; Hist]
save cut_detected.mat cuts



