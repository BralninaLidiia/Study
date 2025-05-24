#!/bin/bash
#начальное считывание из params.txt
p_input=$(head -n 2 params.txt | tail -n 1)
t_input=$(head -n 5 params.txt | tail -n 1)
p_output=$(head -n 8 params.txt | tail -n 1)
G=$(head -n 11 params.txt | tail -n 1)
alpha=$(head -n 14 params.txt | tail -n 1)
betta=$(head -n 17 params.txt | tail -n 1)

#вывод полученных параметров в консоль
echo "Параметры, полученные из params.txt:"
echo p_input = $p_input
echo t_input = $t_input
echo p_output = $p_output
echo G = $G
echo alpha = $alpha
echo betta = $betta

#изменение файла Mesh.py
cd /home/chrt/OpenFOAM/chrt-v2406/run
sed -i "17s/.*/P_input = ${p_input}\;/;18s/.*/T_input = ${t_input}\;/;19s/.*/P_output = ${p_output}\;/;20s/.*/G = ${G}\;/;21s/.*/alpha_ = ${alpha}\;/;22s/.*/betta_ = ${betta}\;/" geometry/Mesh.py

#запуск Mesh.py, расчет недостающих параметров
cd /home/chrt/SALOME-9.14.0-native-UB24.04-SRC
./salome -t /home/chrt/OpenFOAM/chrt-v2406/run/geometry/Mesh.py

#получение недостающих параметров
cd /home/chrt/OpenFOAM/chrt-v2406/run/nozzle_1
width=$(head -n 20 params.txt | tail -n 1)
height=$(head -n 23 params.txt | tail -n 1)

#остаточное редактирование файлов
sed -i "19s/.*/internalField uniform ${p_output}\;/;26s/.*/\tvalue uniform\t${p_input}\;/;39s/.*/\tvalue uniform\t${p_output}\;/" p.org
sed -i "19s/.*/internalField uniform ${t_input}\;/;26s/.*/\tvalue uniform\t${t_input}\;/;39s/.*/\tvalue uniform\t${t_input}\;/" 0/T
sed -i "19s/.*/	volScalarFieldValue p ${p_output}/;26s/.*/	box (0 0 -1)(${width} ${height} 1);/;29s/.*/\t	volScalarFieldValue p ${p_input}/" system/setFieldsDict
