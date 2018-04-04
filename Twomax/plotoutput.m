clear all;
close all;
load('output.txt')

hold on

plot(output(:,1),'g')
hold on

plot(output(:,2),'r')
xlabel('Iteration')
ylabel('Fitness')
legend('Fitness','Average Fitness')
