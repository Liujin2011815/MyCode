clear all;close all;

ps=80*10^6;    %������Ϊ  80MHz 
a=0.2;         %�����˲���ϵ��
Fs=1.2*10^9;   %�������� 1.2GHz
fc=6*10^7;     %�ز�Ƶ��   60MHz
N=32000;       %������ݵĳ���
Z=100;		   %����0�ĳ���
M=16;		   %����
AND = N+Z;	   %�������ݵĳ���

t=0:1/Fs:(AND*Fs/ps-1)/Fs;   %��������ΪAND,Ƶ��Ϊ1/Fs��ʱ������
s=randi([0,M-1],N,1);        %�������16����������Ϊԭʼ����
zer=zeros(Z,1);		
s=[zer;s];					 %������ǰ��ƴ��һ��0Ԫ

qamiq = qammod(s,M);		 %��������16qam����

I=real(qamiq);				 %I·
Q=imag(qamiq);				 %Q·

%�Ա���������FsƵ�ʲ���
Ads_i=upsample(I,Fs/ps);
Ads_q=upsample(Q,Fs/ps);
Ads_i=Ads_i';
Ads_q=Ads_q';

%���ƽ�����������˲���
rate=Fs/ps;
T=1;
n_T=20;
Ads_i = [Ads_i, Ads_i(1:rate * n_T * 2)];
Ads_q = [Ads_q, Ads_q(1:rate * n_T * 2)];
Shape_b = rcosfir(a,n_T,rate,T,'normal');

%�Բ���������ݽ����������˲�;
%rcos_Ads_i=filter(Ads_i,1,[Shape_b,zeros(1,N*rate-rate * n_T * 2-1)]);
%rcos_Ads_q=filter(Ads_q,1,[Shape_b,zeros(1,N*rate-rate * n_T * 2-1)]);
rcos_Ads_i=filter(Shape_b,1,Ads_i);
rcos_Ads_q=filter(Shape_b,1,Ads_q);
rcos_Ads_i=rcos_Ads_i((rate * n_T * 2):(AND*rate+rate * n_T * 2-1));
rcos_Ads_q=rcos_Ads_q((rate * n_T * 2):(AND*rate+rate * n_T * 2-1));

%����ͬ��������·��Ƶ�ź�
f0_i=cos(2*pi*fc*t); 
f0_q=sin(2*pi*fc*t);       
 
%����16QAM�ѵ��ź�
qam16x =rcos_Ads_i.*f0_i+rcos_Ads_q.*f0_q;
qam16_csv=0.1*qam16x;

%����Ƶ��ͼ
%x=(1:AND*rate);
%figure;
%plot(x,abs(fft(qam16x)));

%�����������.csv �ļ�
Tb_qam16=table(qam16_csv');
writetable(Tb_qam16,'C:\Users\JIN LIU\Desktop\Qam16_60M_Center_80M_Symbol.csv');


