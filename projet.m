clear all
close all


M=load('-ascii','halil3.txt');

[ l c ] = size(M);
x=M(1,:);
for k=2 : l
  y=M(k,:);
plot(x,y,'r')
xlabel('x')
ylabel('y(x,t)')
axis([0 0.2 -0.2 0.2 ]);
title('propagation avec déformation initiale à vitesse nulle')
%legend('Divergence du systeme')

pause(0.00000000000000000005)


end

