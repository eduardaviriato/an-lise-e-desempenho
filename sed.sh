#!/bin/bash
n1='1.000000'
n2='1.001'
n3='1.000'
n4='1.000'
CONTADOR=0


while [  $CONTADOR -lt 30 ]; do
	./waf
	./waf --run scratch/test| tail -n +5 >> ../../../NS3.txt;
	s=$(echo $n1+0.000004 |bc)
	n02=$(echo $n2+0.003 |bc)
	n03=$(echo $n3+0.002 |bc)
	n04=$(echo $n4+0.005 |bc)
	#echo $s
	sed -i 's/onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n1')));/ onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$s')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/test.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n2')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n02')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/test.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n3')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n03')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/test.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n4')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n04')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/test.cc
	#sed -i 's/  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$cl')));/  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$cl1')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/test.cc
	#sed -i 's/  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$cl2')));/  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$cl02')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/test.cc

	#echo $s
	n1=$s
	n2=$n02
	n3=$n03
	n4=$n04
      let CONTADOR=CONTADOR+1;
	echo $CONTADOR 
done 

