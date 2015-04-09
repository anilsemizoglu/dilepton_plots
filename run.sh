echo "hello"
screen -S tt root -b -q runbaby_mctt.C
screen -S wz    root -b -q runbaby_mcwz.C
screen -S data  root -b -q runbaby_data.C
screen -S dy    root -b -q runbaby_mcdy.C
echo "end"
