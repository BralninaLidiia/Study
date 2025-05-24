#!/bin/bash
#начальное считывание из params.txt
lc=$(head -n 2 params.txt | tail -n 1)
lt=$(head -n 5 params.txt | tail -n 1)
lr=$(head -n 8 params.txt | tail -n 1)
lb=$(head -n 11 params.txt | tail -n 1)
d0=$(head -n 14 params.txt | tail -n 1)
dc=$(head -n 17 params.txt | tail -n 1)
ht=$(head -n 20 params.txt | tail -n 1)
hb=$(head -n 23 params.txt | tail -n 1)
U=$(head -n 26 params.txt | tail -n 1)

#вывод полученных параметров в консоль
echo "Параметры, полученные из params.txt:"
echo lc = $lc
echo lt = $lt
echo lr = $lr
echo lb = $lb
echo d0 = $d0
echo dc = $dc
echo ht = $ht
echo hb = $hb
echo U = $U

res=$(awk "BEGIN {print $d0 / sqrt(2)}")
res_foam=$(echo "$res" | tr ',' '.')

x1=$(echo "$lc - $lr - $lt-($lt - $lb)/2" | bc -l)
x1_foam=$(echo $x1 | tr ',' '.')

x2=$(echo "$lc - $lr - $lt - $res_foam/2" | bc -l)
x2_foam=$(echo "$x2" | tr ',' '.')

x3=$(echo "$lc - $lr - $lt + $res_foam/2" | bc -l)
x3_foam=$(echo $x3 | tr ',' '.')

x4=$(echo "$lc - $lr - $lb -($lt - $lb)/2" | bc -l)
x4_foam=$(echo $x4 | tr ',' '.')

x5=$(echo "$lc - $lr - $lb - $res_foam/2" | bc -l)
x5_foam=$(echo $x5 | tr ',' '.')

x6=$(echo "$lc - $lr - $lb + $res_foam/2" | bc -l)
x6_foam=$(echo $x6 | tr ',' '.')

x7=$(echo "$lc - $lr - $lb/2" | bc -l)
x7_foam=$(echo $x7 | tr ',' '.')

x8=$(echo "$lc - $lr - $res_foam/2" | bc -l)
x8_foam=$(echo $x8 | tr ',' '.')

x9=$(echo "$lc - $lr + $res_foam/2" | bc -l)
x9_foam=$(echo $x9 | tr ',' '.')

x10=$(echo "$lc - $lr + $lb/2" | bc -l)
x10_foam=$(echo $x10 | tr ',' '.')

xCenter1=$(echo "$lc - $lr - $lt" | bc -l)
xCenter1_foam=$(echo $xCenter1 | tr ',' '.')

xCenter11=$(echo "$lc - $lr - $lt - $d0/2" | bc -l)
xCenter11_foam=$(echo $xCenter11 | tr ',' '.')

xCenter12=$(echo "$lc - $lr - $lt + $d0/2" | bc -l)
xCenter12_foam=$(echo $xCenter12 | tr ',' '.')

xCenter2=$(echo "$lc - $lr - $lb" | bc -l)
xCenter2_foam=$(echo $xCenter2 | tr ',' '.')

xCenter21=$(echo "$lc - $lr - $lb - $d0/2" | bc -l)
xCenter21_foam=$(echo $xCenter21 | tr ',' '.')

xCenter22=$(echo "$lc - $lr - $lb + $d0/2" | bc -l)
xCenter22_foam=$(echo $xCenter22 | tr ',' '.')

xCenter3=$(echo "$lc - $lr" | bc -l)
xCenter3_foam=$(echo $xCenter3 | tr ',' '.')

xCenter31=$(echo "$lc - $lr - $d0/2" | bc -l)
xCenter31_foam=$(echo $xCenter31 | tr ',' '.')

xCenter32=$(echo "$lc - $lr + $d0/2" | bc -l)
xCenter32_foam=$(echo $xCenter32| tr ',' '.')

y2=$(echo "$dc - $ht - $res_foam/2" | bc -l)
y2_foam=$(echo $y2 | tr ',' '.')

y3=$(echo "$dc - $ht + $res_foam/2" | bc -l)
y3_foam=$(echo $y3 | tr ',' '.')

y4=$(echo "$hb - $res_foam/2" | bc -l)
y4_foam=$(echo $y4 | tr ',' '.')

y5=$(echo "$hb + $res_foam/2" | bc -l)
y5_foam=$(echo $y5 | tr ',' '.')

yCenter13=$(echo "$dc - $ht" | bc -l)
yCenter13_foam=$(echo $yCenter13 | tr ',' '.')

yCenter131=$(echo "$dc - $ht - $d0/2" | bc -l)
yCenter131_foam=$(echo $yCenter131 | tr ',' '.')

yCenter132=$(echo "$dc - $ht + $d0/2" | bc -l)
yCenter132_foam=$(echo $yCenter132 | tr ',' '.')

yCenter2=$(echo "$hb" | bc -l)
yCenter2_foam=$(echo $yCenter2 | tr ',' '.')

yCenter21=$(echo "$hb - $d0/2" | bc -l)
yCenter21_foam=$(echo $yCenter21 | tr ',' '.')

yCenter22=$(echo "$hb + $d0/2" | bc -l)
yCenter22_foam=$(echo $yCenter22 | tr ',' '.')
#редактирование файлов
sed -i "
19s/.*/x1 ${x1_foam};/;
20s/.*/x2 ${x2_foam};/;
21s/.*/x3 ${x3_foam};/;
22s/.*/x4 ${x4_foam};/;
23s/.*/x5 ${x5_foam};/;
24s/.*/x6 ${x6_foam};/;
25s/.*/x7 ${x7_foam};/;
26s/.*/x8 ${x8_foam};/;
27s/.*/x9 ${x9_foam};/;
28s/.*/x10 ${x10_foam};/;
29s/.*/x11 ${lc};/;
30s/.*/xCenter1 ${xCenter1_foam};/;
31s/.*/xCenter11 ${xCenter11_foam};/;
32s/.*/xCenter12 ${xCenter12_foam};/;
33s/.*/xCenter2 ${xCenter2_foam};/;
34s/.*/xCenter21 ${xCenter21_foam};/;
35s/.*/xCenter22 ${xCenter22_foam};/;
36s/.*/xCenter3 ${xCenter3_foam};/;
37s/.*/xCenter31 ${xCenter31_foam};/;
38s/.*/xCenter32 ${xCenter32_foam};/;
40s/.*/y1 ${dc};/;
41s/.*/y2 ${y2_foam};/;
42s/.*/y3 ${y3_foam};/;
43s/.*/y4 ${y4_foam};/;
44s/.*/y5 ${y5_foam};/;
45s/.*/yCenter13 ${yCenter13_foam};/;
46s/.*/yCenter131 ${yCenter131_foam};/;
47s/.*/yCenter132 ${yCenter132_foam};/;
48s/.*/yCenter2 ${yCenter2_foam};/;
49s/.*/yCenter21 ${yCenter21_foam};/;
50s/.*/yCenter22 ${yCenter22_foam};/;
" system/blockMeshDict
sed -i "26s/.*/	value           uniform (${U} 0 0);/;" 0/U
