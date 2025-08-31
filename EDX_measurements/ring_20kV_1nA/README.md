For plotting all charts, execute the command
```bash
gnuplot -p -e 'set xrange [0:7];set xlabel "energy (keV)";set ylabel "photons";plot for [file in system("ls *psmsa")] file u 1:2 w l'
```
