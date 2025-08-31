d=dir('*psmsa');
for l=1:length(d)
  x=load(d(l).name);
  plot(x(:,1),x(:,2))
  hold on
end
xlim([0 7])
xlabel('energy (keV)')
ylabel('photons (a.u)')
text(1.15,44000,'Mg')
text(1.50,44000,'Al')
text(1.70,44000,'Si')
text(2.00,44000,'P')
