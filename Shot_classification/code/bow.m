run  /path/to/vlfeat/toolbox/vl_setup
load descriptornew.mat
K = 300;
descriptor=descriptor(:,1:400);
[C, A] = vl_kmeans (descriptor, K, 'verbose', 'algorithm', 'elkan');
vocab = C;
model = vl_kdtreebuild (vocab);
cluster = K;
numWords = size (vocab, 2);
imageFileNamePrefix = strcat ('/path/to/frames');
load cut_detected.mat;
total_matrix = zeros (size(cuts,1), K + 1);
for i= 1:size (cuts, 1) - 1
    i
    descriptor =[];
    for j = cuts (i, 1):cuts (i + 1, 1)
        if (j == 0)
            continue;
        end
        fname =[imageFileNamePrefix num2str(j) '.jpg'];
        Img = imread (fname);
        Img = single (rgb2gray (Img));
        [drop, descrs] = vl_sift (Img);
        descriptor =[descriptor single(descrs)];
    end
    bins = double (vl_kdtreequery (model, vocab, single (descriptor)));
    histss = histnorm (bins, numWords);    
    total_matrix (i,:) =[histss];       
end

