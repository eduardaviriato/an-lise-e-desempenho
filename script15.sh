#!/bin/bash
n1='1.000020'
n2='1.001'
n3='1.011'
n4='1.024'
n5='1.100'
n6='1.000'
n7='1.001'
n8='1.002'
n9='1.003'
n10='1.024'
n11='1.0012'
n12='1.0002'
n13='1.0001'
n14='1.0000'


CONTADOR=0


while [  $CONTADOR -lt 30 ]; do
	./waf
	./waf --run scratch/ns315| tail -n +5 >> ../../../NS3_15.txt;
	s=$(echo $n1+0.000004 |bc)
	n02=$(echo $n2+0.003 |bc)
	n03=$(echo $n3+0.002 |bc)
	n04=$(echo $n4+0.004 |bc)
	n05=$(echo $n5+0.005 |bc)
	n06=$(echo $n6+0.006 |bc)
	n07=$(echo $n7+0.007 |bc)
	n08=$(echo $n8+0.008 |bc)
	n09=$(echo $n9+0.009 |bc)
	n010=$(echo $n10+0.010 |bc)
	n011=$(echo $n11+0.008 |bc)
	n012=$(echo $n12+0.002 |bc)
	n013=$(echo $n13+0.004 |bc)
	n014=$(echo $n14+0.003 |bc)

	#echo $s
	sed -i 's/onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n1')));/onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$s')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n2')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n02')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n3')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n03')));/
' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/test.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n4')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n04')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n5')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n05')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n6')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n06')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n7')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n07')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n8')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n08')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n9')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n09')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n10')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n010')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n11')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n011')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n12')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n012')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n13')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n013')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc
	sed -i 's/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n14')));/  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds ('$n014')));/' /home/ns3/repos/ns-3-allinone/ns-3-dev/scratch/ns315.cc

	
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
	n10=$n010
	n11=$n011
	n12=$n012
	n13=$n013
	n14=$n014

      let CONTADOR=CONTADOR+1;
	echo $CONTADOR 
done 
