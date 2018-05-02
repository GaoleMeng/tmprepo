# Domain Transition Detection

Detect and visulize the domain changes occur around SIGIR conference

## Algorithm Explaination

The final goal of this algorithm is to compute the 2D embedding of the papers points around SIGIR conference. To accomplish this, we need to construct a reference graph <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;G&space;=&space;(V,&space;E)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;G&space;=&space;(V,&space;E)" title="G = (V, E)" /></a> and use largeVis to compute the graph embedding in two-dimensional space.

1. Treat each paper in [Aminer](https://aminer.org/open-academic-graph) as a point, two paper are connected with a directed edge if one cites another.

2. BFS the graph starting from all papers belong to SIGIR, which create a subset of all paper points. The set of paper nodes is denoted as <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;V_{papers}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;V_{papers}" title="V_{papers}" /></a>. We then construct all the conference that <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;V_{papers}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;V_{papers}" title="V_{papers}" /></a> has touched, which is to say <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;S_{conf}&space;=&space;\{&space;conf|v\in&space;V_{paper}\&space;\wedge\&space;v\&space;belongs\&space;to\&space;conf\}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;S_{conf}&space;=&space;\{&space;conf|v\in&space;V_{paper}\&space;\wedge\&space;v\&space;belongs\&space;to\&space;conf\}" title="S_{conf} = \{ conf|v\in V_{paper}\ \wedge\ v\ belongs\ to\ conf\}" /></a>.

3. Since that this may introduce too much possible conferences around SIGIR, like if only one paper in <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;V_{papers}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;V_{papers}" title="V_{papers}" /></a> belongs Nature, we still need to include Nature in <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;S_{conf}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;S_{conf}" title="S_{conf}" /></a>. So we need to continue on filtering out more conferences in <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;S_{conf}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;S_{conf}" title="S_{conf}" /></a> by introducing an important score of each conference. The score of conference <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;c" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;c" title="c" /></a> is computed as <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;score_c&space;=&space;\frac{\&hash;points\&space;in\&space;V_{papers}\&space;belongs\&space;to\&space;c}{\&hash;total\&space;points\&space;belongs\&space;to\&space;c}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;score_c&space;=&space;\frac{\&hash;points\&space;in\&space;V_{papers}\&space;belongs\&space;to\&space;c}{\&hash;total\&space;points\&space;belongs\&space;to\&space;c}" title="score_c = \frac{\#points\ in\ V_{papers}\ belongs\ to\ c}{\#total\ points\ belongs\ to\ c}" /></a>. The intuition is simple, if the points in <a href="https://www.codecogs.com/eqnedit.php?latex=\inline&space;c" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\inline&space;c" title="c" /></a> that BFS can touch is not enough, we then consider this conference as irrelevent to the SIGIR.

<div align="center">
<img src="image.png" width="500" style="margin-left:auto;margin-right:auto">
</div>

4. 

