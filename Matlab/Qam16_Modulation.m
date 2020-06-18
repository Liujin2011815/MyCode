clear all;close all;

ps=80*10^6;    %码速率为  80MHz 
a=0.2;         %成形滤波器系数
Fs=1.2*10^9;   %采样速率 1.2GHz
fc=6*10^7;     %载波频率   60MHz
N=32000;       %随机数据的长度
Z=100;		   %数据0的长度
M=16;		   %进制
AND = N+Z;	   %仿真数据的长度

t=0:1/Fs:(AND*Fs/ps-1)/Fs;   %产生长度为AND,频率为1/Fs的时间序列
s=randi([0,M-1],N,1);        %产生随机16进制数据作为原始数据
zer=zeros(Z,1);		
s=[zer;s];					 %在数据前端拼接一段0元

qamiq = qammod(s,M);		 %基带数据16qam调制

I=real(qamiq);				 %I路
Q=imag(qamiq);				 %Q路

%对编码数据以Fs频率采样
Ads_i=upsample(I,Fs/ps);
Ads_q=upsample(Q,Fs/ps);
Ads_i=Ads_i';
Ads_q=Ads_q';

%设计平方根升余弦滤波器
rate=Fs/ps;
T=1;
n_T=20;
Ads_i = [Ads_i, Ads_i(1:rate * n_T * 2)];
Ads_q = [Ads_q, Ads_q(1:rate * n_T * 2)];
Shape_b = rcosfir(a,n_T,rate,T,'normal');

%对采样后的数据进行升余弦滤波;
%rcos_Ads_i=filter(Ads_i,1,[Shape_b,zeros(1,N*rate-rate * n_T * 2-1)]);
%rcos_Ads_q=filter(Ads_q,1,[Shape_b,zeros(1,N*rate-rate * n_T * 2-1)]);
rcos_Ads_i=filter(Shape_b,1,Ads_i);
rcos_Ads_q=filter(Shape_b,1,Ads_q);
rcos_Ads_i=rcos_Ads_i((rate * n_T * 2):(AND*rate+rate * n_T * 2-1));
rcos_Ads_q=rcos_Ads_q((rate * n_T * 2):(AND*rate+rate * n_T * 2-1));

%产生同相正交两路载频信号
f0_i=cos(2*pi*fc*t); 
f0_q=sin(2*pi*fc*t);       
 
%产生16QAM已调信号
qam16x =rcos_Ads_i.*f0_i+rcos_Ads_q.*f0_q;
qam16_csv=0.1*qam16x;

%绘制频域图
%x=(1:AND*rate);
%figure;
%plot(x,abs(fft(qam16x)));

%讲数据输出到.csv 文件
Tb_qam16=table(qam16_csv');
writetable(Tb_qam16,'C:\Users\JIN LIU\Desktop\Qam16_60M_Center_80M_Symbol.csv');


