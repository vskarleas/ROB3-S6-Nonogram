% % This script receives a picture and makes a nonogram puzzle based on it
% and the specified puzzle dimensions
clear all
close all
clc
%% preparing the input image
filename = 'final.png';
im = imread(filename);
if size(im,3) > 1
    im = rgb2gray(im);
end
% scaling down the image
scale = 4;
Sim = size(im);
U = floor(Sim/scale);
p = imresize(im,1/scale);
[m,n] = size(p);
p = histeq(p);
P = imbinarize(p);
if median(P(:)) == 0
    P = 1-P;
end
%% make the puzzle
figure, imshow(P,[])
% counting the cells in rows and columns
[horiz,vert] = countcell(P);
[htxt,vtxt] = maketext(horiz,vert);
emptycellsh = find(cellfun('isempty',htxt));
htxt(emptycellsh) = num2str(0);
emptycellsv = find(cellfun('isempty',vtxt));
vtxt(emptycellsv) = num2str(0);
vtxt = vtxt';

%% prepare excell file 
sheet = string(repmat({''},m+2,n+2));
sheet(1,3:end) = 1:n;
sheet(2,3:end) = vtxt;

sheet(3:end,1) = 1:m;
sheet(3:end,2) = htxt;

writematrix(sheet,filename(1:end-4),'FileType','spreadsheet');
