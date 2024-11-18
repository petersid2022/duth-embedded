clear;
clc;
row=352;%140;
col=288;%170;
row=200;%140;
col=200;%170;
color=0;


%fin=fopen('akiyo_cif_0_yuv444.yuv','r');
%fin=fopen('akiyo1.y','r');
fin=fopen('sunflower_200x200_444.yuv','r');

if (color==1)
    I=fread(fin,3*row*col,'uint8=>uint8');
    Z = reshape(I,row,col,3);
    Z1=Z(:,:,1)';
    Z2=Z(:,:,2)';
    Z3=Z(:,:,3)';
    Z=cat(3,Z1,Z2,Z3);
    rgb=ycbcr2rgb(Z);
    figure(1)
    imshow(Z);
    fclose(fin);
else
    I=fread(fin,row*col,'uint8=>uint8');
    fclose(fin)
    fout=fopen('sunflower_200x200_BIN.yuv','w');
    Z = reshape(I, row, col);
    figure(1),
%     Z(Z==1)=255;
    Z(Z<=128)=0;
    Z(Z>128)=255;
    imshow(Z,[]);
    fwrite(fout,Z(:));
    fclose(fout);

end
