#!/bin/bash
n1='1.000000'
n2='1.001'
n3='1.011'
n4='1.001'
n5='1.000'
n6='1.000'
n7='1.001'
n8='1.002'
n9='1.003'


CONTADOR=0


while [  $CONTADOR -lt 30 ]; do
	./waf
	./waf --run scratch/ns3_10| tail -n +5 >> ../../../NS3_10.txt;
	s=$(echo $n1+0.000004 |bc)
	n02=$(echo $n2+0.003 |bc)
	n03=$(echo $n3+0.002 |bc)
	n04=$(echo $n4+0.004 |bc)
	n05=$(echo $n5+0.005 |bc)
	n06=$(echo $n6+0.006 |bc)
	n07=$(echo $n7+0.007 |bc)
	n08=$(echo $n8+0.008 |bc)
	n09=$(echo $n9+0.009 |bc)

	#echo $s
	sed -i 's/onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n1')));/onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$s')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns3_10.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n2')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n02')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns3_10.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n3')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n03')));/
' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/test.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n4')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n04')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns3_10.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n5')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n05')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns3_10.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n6')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n06')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns3_10.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n7')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n07')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns3_10.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n8')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n08')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns3_10.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n9')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n09')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns3_10.cc

	
	#echo $s
	n1=$s
	n2=$n02
	n3=$n03
	n4=$n04
	n5=$n05
	n6=$n06
	n7=$n07
	n8=$n08
	n9=$n09

      let CONTADOR=CONTADOR+1;
	echo $CONTADOR 
done 
