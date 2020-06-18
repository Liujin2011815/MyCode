N=50000;    %�ź���
K=4;        %ÿ���źŲ���4����
Ns=K*N;     %�ܵĲ�������
w=[0.5,zeros(1,N-1)];   %��·�˲�������Ĵ�������ֵ����Ϊ0.5
n=[0.7,zeros(1,Ns-1)];  %NCO�Ĵ�������ֵ����Ϊ0.7
n_temp=[n(1),zeros(1,Ns-1)];
u=[0.6,zeros(1,2*N-1)]; %NCO���ʱ�Ķ�ʱ��������Ĵ�������ֵ����Ϊ0.6
yI=zeros(1,2*N);        %I֧·�ڲ�������ź�
yQ=zeros(1,2*N);        %Q֧·�ڲ�������ź�
time_error=zeros(1,N);  %��ʱ���Ĵ���
i=1;                    %������ʾTs��ʱ����ţ�ָʾn,n_temp,nco
k=1;                    %������ʾTiʱ����ţ�ָʾu,yI,yQ
ms=1;                   %������ʾT��ʱ����ţ�ָʾa,b��w
strobe=zeros(1,Ns);
%��·�˲���ϵ��
c1=5.41*10^(-3);
c2=3.82*10^(-6);

%����������Ե�BPSK�ź�
bitstream=randi([0,1],1,N);
psk2=pskmod(bitstream,2);
xI=zeros(1,Ns);
xQ=zeros(1,Ns);
xI(1:8:8*N)=real(psk2);
xQ(1:8:8*N)=imag(psk2);   %8����ֵ

%�ض̺��ƽ���������ҹ����˲���
h1=rcosfir(0.8,[-8,8],4,1,'sqrt');
hw=kaiser(65,3.97);
hh=h1.*hw.';
aI1=conv(xI,h1);
bQ1=conv(xQ,h1);
L=length(aI1);
%���������ź�
aI=[aI1(22:2:L),0,0];
bQ=[bQ1(22:2:L),0,0];      %2����ȡ

ns=length(aI)-2;
while(i<ns)
    n_temp(i+1)=n(i)-w(ms);
%      n_temp(i+1)=n(i)-0.5;
    if(n_temp(i+1)>0)
        n(i+1)=n_temp(i+1);
    else
        n(i+1)=mod(n_temp(i+1),1);
        %�ڲ��˲���ģ��
        FI1=0.5*aI(i+2)-0.5*aI(i+1)-0.5*aI(i)+0.5*aI(i-1);
        FI2=1.5*aI(i+1)-0.5*aI(i+2)-0.5*aI(i)-0.5*aI(i-1);
        FI3=aI(i);
        yI(k)=(FI1*u(k)+FI2)*u(k)+FI3;
        FQ1=0.5*bQ(i+2)-0.5*bQ(i+1)-0.5*bQ(i)+0.5*bQ(i-1);
        FQ2=1.5*bQ(i+1)-0.5*bQ(i+2)-0.5*bQ(i)-0.5*bQ(i-1);
        FQ3=bQ(i);
        yQ(k)=(FQ1*u(k)+FQ2)*u(k)+FQ3;
        strobe(k)=mod(k,2);  
        
        %ʱ�������ȡģ�飬���õ���Gardner�㷨
        if(strobe(k)==0)
            %ȡ����ֵ����
            %ik(ms)=yI(k);
            %qk(ms)=yQ(k)��
             
            %ÿ�����ݷ��ż���һ��ʱ�����
            if(k>2)
              % Ia=(yI(k)+yI(k-2))/2;
              % Qa=(yQ(k)+yQ(k-2))/2;
               time_error(ms)=yI(k-1)*(yI(k)-yI(k-2))+yQ(k-1)*(yQ(k)-yQ(k-2));
            else
                time_error(ms)=(yI(k-1)*yI(k)+yQ(k-1)*yQ(k));
            end
            %��·�˲���,ÿ�����ݷ��ż���һ�λ�·�˲������
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
          %u(k) = 0.5* n(i);%%��������
    end
    i=i+1;
end

figure;
subplot(311);plot(u);xlabel('�������');ylabel('�������');
subplot(312);plot(time_error);xlabel('�������');ylabel('��ʱ���');
subplot(313);plot(w);xlabel('�������');ylabel('��·�˲������');




