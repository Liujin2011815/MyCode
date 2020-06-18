N=50000;    %信号数
K=4;        %每个信号采样4个点
Ns=K*N;     %总的采样点数
w=[0.5,zeros(1,N-1)];   %环路滤波器输出寄存器，初值设置为0.5
n=[0.7,zeros(1,Ns-1)];  %NCO寄存器，初值设置为0.7
n_temp=[n(1),zeros(1,Ns-1)];
u=[0.6,zeros(1,2*N-1)]; %NCO输出时的定时分数间隔寄存器，初值设置为0.6
yI=zeros(1,2*N);        %I支路内插后的输出信号
yQ=zeros(1,2*N);        %Q支路内插后的输出信号
time_error=zeros(1,N);  %定时误差寄存器
i=1;                    %用来表示Ts的时间序号，指示n,n_temp,nco
k=1;                    %用来表示Ti时间序号，指示u,yI,yQ
ms=1;                   %用来表示T的时间序号，指示a,b和w
strobe=zeros(1,Ns);
%环路滤波器系数
c1=5.41*10^(-3);
c2=3.82*10^(-6);

%仿真输入测试的BPSK信号
bitstream=randi([0,1],1,N);
psk2=pskmod(bitstream,2);
xI=zeros(1,Ns);
xQ=zeros(1,Ns);
xI(1:8:8*N)=real(psk2);
xQ(1:8:8*N)=imag(psk2);   %8倍插值

%截短后的平方根升余弦滚降滤波器
h1=rcosfir(0.8,[-8,8],4,1,'sqrt');
hw=kaiser(65,3.97);
hh=h1.*hw.';
aI1=conv(xI,h1);
bQ1=conv(xQ,h1);
L=length(aI1);
%仿真输入信号
aI=[aI1(22:2:L),0,0];
bQ=[bQ1(22:2:L),0,0];      %2倍抽取

ns=length(aI)-2;
while(i<ns)
    n_temp(i+1)=n(i)-w(ms);
%      n_temp(i+1)=n(i)-0.5;
    if(n_temp(i+1)>0)
        n(i+1)=n_temp(i+1);
    else
        n(i+1)=mod(n_temp(i+1),1);
        %内插滤波器模块
        FI1=0.5*aI(i+2)-0.5*aI(i+1)-0.5*aI(i)+0.5*aI(i-1);
        FI2=1.5*aI(i+1)-0.5*aI(i+2)-0.5*aI(i)-0.5*aI(i-1);
        FI3=aI(i);
        yI(k)=(FI1*u(k)+FI2)*u(k)+FI3;
        FQ1=0.5*bQ(i+2)-0.5*bQ(i+1)-0.5*bQ(i)+0.5*bQ(i-1);
        FQ2=1.5*bQ(i+1)-0.5*bQ(i+2)-0.5*bQ(i)-0.5*bQ(i-1);
        FQ3=bQ(i);
        yQ(k)=(FQ1*u(k)+FQ2)*u(k)+FQ3;
        strobe(k)=mod(k,2);  
        
        %时钟误差提取模块，采用的是Gardner算法
        if(strobe(k)==0)
            %取出插值数据
            %ik(ms)=yI(k);
            %qk(ms)=yQ(k)；
             
            %每个数据符号计算一次时钟误差
            if(k>2)
              % Ia=(yI(k)+yI(k-2))/2;
              % Qa=(yQ(k)+yQ(k-2))/2;
               time_error(ms)=yI(k-1)*(yI(k)-yI(k-2))+yQ(k-1)*(yQ(k)-yQ(k-2));
            else
                time_error(ms)=(yI(k-1)*yI(k)+yQ(k-1)*yQ(k));
            end
            %环路滤波器,每个数据符号计算一次环路滤波器输出
            if(ms>1)
                w(ms+1)=w(ms)+c1*(time_error(ms)-time_error(ms-1))+c2*time_error(ms-1);
                %w(ms+1)=w(ms)+c1*(time_error(ms)-time_error(ms-1));
            else
                w(ms+1)=w(ms)+c1*time_error(ms)+c2*time_error(ms);
            end
            ms=ms+1;
        end
          k=k+1;
          u(k)=n(i)/w(ms);
          %u(k) = 0.5* n(i);%%近视运算
    end
    i=i+1;
end

figure;
subplot(311);plot(u);xlabel('运算点数');ylabel('分数间隔');
subplot(312);plot(time_error);xlabel('运算点数');ylabel('定时误差');
subplot(313);plot(w);xlabel('运算点数');ylabel('环路滤波器输出');




