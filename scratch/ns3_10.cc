/*
 * 
 
 *
 * Topology: [node 0] <-- -50 dB --> [node 1] <-- -50 dB --> [node 2]
 */

#include "ns3/command-line.h"
#include "ns3/config.h"
#include "ns3/uinteger.h"
#include "ns3/boolean.h"
#include "ns3/string.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/udp-echo-helper.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/constant-position-mobility-model.h"
#include "ns3/propagation-loss-model.h"
#include "ns3/propagation-delay-model.h"
#include "ns3/on-off-helper.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/ipv4-flow-classifier.h"

using namespace ns3;

/// Run single 10 seconds experiment
void experiment (bool enableCtsRts, std::string wifiManager)
{
  // 0. Enable or disable CTS/RTS
  UintegerValue ctsThr = (enableCtsRts ? UintegerValue (100) : UintegerValue (2200));
  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", ctsThr);

  // 1. Create 10 nodes
  NodeContainer nodes;
  nodes.Create (10);

  // 2. Place nodes somehow, this is required by every wireless simulation
  for (uint8_t i = 0; i < 10; ++i)
    {
      nodes.Get (i)->AggregateObject (CreateObject<ConstantPositionMobilityModel> ());
    }

  // 3. Create propagation loss matrix
  Ptr<MatrixPropagationLossModel> lossModel = CreateObject<MatrixPropagationLossModel> ();
  lossModel->SetDefaultLoss (0); // set default loss to 200 dB (no link)
  lossModel->SetLoss (nodes.Get (1)->GetObject<MobilityModel> (), nodes.Get (0)->GetObject<MobilityModel> (), 0); // set symmetric loss 0 <-> 1 to 50 dB
  lossModel->SetLoss (nodes.Get (1)->GetObject<MobilityModel> (), nodes.Get (2)->GetObject<MobilityModel> (), 0); // set symmetric loss 2 <-> 1 to 50 dB
 lossModel->SetLoss (nodes.Get (1)->GetObject<MobilityModel> (), nodes.Get (3)->GetObject<MobilityModel> (), 0); // set symmetric loss 3 <-> 1 to 50 dB 
 lossModel->SetLoss (nodes.Get (1)->GetObject<MobilityModel> (), nodes.Get (4)->GetObject<MobilityModel> (), 0); // set symmetric loss 4 <-> 1 to 50db
 lossModel->SetLoss (nodes.Get (1)->GetObject<MobilityModel> (), nodes.Get (5)->GetObject<MobilityModel> (), 0); // set symmetric loss 5 <-> 1 to 50
 lossModel->SetLoss (nodes.Get (1)->GetObject<MobilityModel> (), nodes.Get (6)->GetObject<MobilityModel> (), 0); // set symmetric loss 6 <-> 1$
 lossModel->SetLoss (nodes.Get (1)->GetObject<MobilityModel> (), nodes.Get (7)->GetObject<MobilityModel> (), 0); // set symmetric loss 7 <-> 1$
 lossModel->SetLoss (nodes.Get (1)->GetObject<MobilityModel> (), nodes.Get (8)->GetObject<MobilityModel> (), 0); // set symmetric loss 4 <-> 1$
 lossModel->SetLoss (nodes.Get (1)->GetObject<MobilityModel> (), nodes.Get (9)->GetObject<MobilityModel> (), 0); // set symmetric loss 4 <-> 1$

// 4. Create & setup wifi channel
  Ptr<YansWifiChannel> wifiChannel = CreateObject <YansWifiChannel> ();
  wifiChannel->SetPropagationLossModel (lossModel);
  wifiChannel->SetPropagationDelayModel (CreateObject <ConstantSpeedPropagationDelayModel> ());

  // 5. Install wireless devices
  WifiHelper wifi;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
  wifi.SetRemoteStationManager ("ns3::" + wifiManager + "WifiManager");
  YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();
  wifiPhy.SetChannel (wifiChannel);
  WifiMacHelper wifiMac;
  wifiMac.SetType ("ns3::AdhocWifiMac"); // use ad-hoc MAC
  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, nodes);

  // uncomment the following to have athstats output
  // AthstatsHelper athstats;
  // athstats.EnableAthstats(enableCtsRts ? "rtscts-athstats-node" : "basic-athstats-node" , nodes);

  // uncomment the following to have pcap output
  // wifiPhy.EnablePcap (enableCtsRts ? "rtscts-pcap-node" : "basic-pcap-node" , nodes);


  // 6. Install TCP/IP stack & assign IP addresses
  InternetStackHelper internet;
  internet.Install (nodes);
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.0.0.0", "255.0.0.0");
  ipv4.Assign (devices);

  // 7. Install applications: two CBR streams each saturating the channel
  ApplicationContainer cbrApps;
  uint16_t cbrPort = 12345;
  OnOffHelper onOffHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address ("10.0.0.2"), cbrPort));
  onOffHelper.SetAttribute ("PacketSize", UintegerValue (1400));
  onOffHelper.SetAttribute ("OnTime",  StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  onOffHelper.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));

  // flow 1:  node 0 -> node 1
  onOffHelper.SetAttribute ("DataRate", StringValue ("3000000bps"));
  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds (1.000120)));
  cbrApps.Add (onOffHelper.Install (nodes.Get (0)));

  // flow 2:  node 2 -> node 1
  onOffHelper.SetAttribute ("DataRate", StringValue ("3001100bps"));
  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds (1.273)));
  cbrApps.Add (onOffHelper.Install (nodes.Get (2)));
 // flow 3:  node 3 -> node 1
  onOffHelper.SetAttribute ("DataRate", StringValue ("3000000bps"));
  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds (1.011)));
  cbrApps.Add (onOffHelper.Install (nodes.Get (3)));
 // flow 4:  node 4 -> node 1
  onOffHelper.SetAttribute ("DataRate", StringValue ("3000000bps"));
  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds (1.273)));
  cbrApps.Add (onOffHelper.Install (nodes.Get (4)));
 // flow 5:  node 4 -> node 1
  onOffHelper.SetAttribute ("DataRate", StringValue ("3000000bps"));
  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds (1.273)));
  cbrApps.Add (onOffHelper.Install (nodes.Get (5)));
// flow 6:  node 4 -> node 1
  onOffHelper.SetAttribute ("DataRate", StringValue ("3000000bps"));
  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds (1.273)));
  cbrApps.Add (onOffHelper.Install (nodes.Get (6)));
// flow 7:  node 4 -> node 1
  onOffHelper.SetAttribute ("DataRate", StringValue ("3000000bps"));
  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds (1.273)));
  cbrApps.Add (onOffHelper.Install (nodes.Get (7)));
// flow 8:  node 4 -> node 1
  onOffHelper.SetAttribute ("DataRate", StringValue ("3000000bps"));
  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds (1.273)));
  cbrApps.Add (onOffHelper.Install (nodes.Get (8)));
// flow 9:  node 4 -> node 1
  onOffHelper.SetAttribute ("DataRate", StringValue ("3000000bps"));
  onOffHelper.SetAttribute ("StartTime", TimeValue (Seconds (1.273)));
  cbrApps.Add (onOffHelper.Install (nodes.Get (9)));

  /** \internal
   * We also use separate UDP applications that will send a single
   * packet before the CBR flows start.
   * This is a workaround for the lack of perfect ARP, see \bugid{187}
   */
  uint16_t  echoPort = 9;
  UdpEchoClientHelper echoClientHelper (Ipv4Address ("10.0.0.2"), echoPort);
  echoClientHelper.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClientHelper.SetAttribute ("Interval", TimeValue (Seconds (0.1)));
  echoClientHelper.SetAttribute ("PacketSize", UintegerValue (10));
  ApplicationContainer pingApps;

  // again using different start times to workaround Bug 388 and Bug 912
  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds (0.001)));
  pingApps.Add (echoClientHelper.Install (nodes.Get (0)));
  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds (0.004)));
  pingApps.Add (echoClientHelper.Install (nodes.Get (2)));
  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds (0.008)));
  pingApps.Add (echoClientHelper.Install (nodes.Get (3)));
  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds (0.008)));
  pingApps.Add (echoClientHelper.Install (nodes.Get (4)));
  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds (0.008)));
  pingApps.Add (echoClientHelper.Install (nodes.Get (5)));
  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds (0.008)));
  pingApps.Add (echoClientHelper.Install (nodes.Get (6)));
  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds (0.008)));
  pingApps.Add (echoClientHelper.Install (nodes.Get (7)));
  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds (0.008)));
  pingApps.Add (echoClientHelper.Install (nodes.Get (8)));
  echoClientHelper.SetAttribute ("StartTime", TimeValue (Seconds (0.008)));
  pingApps.Add (echoClientHelper.Install (nodes.Get (9)));
  // 8. Install FlowMonitor on all nodes
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll ();

  // 9. Run simulation for 10 seconds
  Simulator::Stop (Seconds (10));
  Simulator::Run ();

  // 10. Print per flow statistics
  monitor->CheckForLostPackets ();
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  FlowMonitor::FlowStatsContainer stats = monitor->GetFlowStats ();
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
    {
      // first 2 FlowIds are for ECHO apps, we don't want to display them
      //
      // Duration for throughput measurement is 9.0 seconds, since
      //   StartTime of the OnOffApplication is at about "second 1"
      // and
      //   Simulator::Stops at "second 10".
      if (i->first > 9)
        {
         // Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
         // std::cout << "Flow " << i->first - 2 << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";
         // std::cout << "  Tx Packets: " << i->second.txPackets << "\n";
         // std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
         // std::cout << "  TxOffered:  " << i->second.txBytes * 8.0 / 9.0 / 1000 / 1000  << " Mbps\n";
         // std::cout << "  Rx Packets: " << i->second.rxPackets << "\n";
         // std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
          std::cout << i->second.rxBytes * 8.0 / 9.0 / 1000 / 1000 << "\n";
        }
    }

  // 11. Cleanup
  Simulator::Destroy ();
}

int main (int argc, char **argv)
{
  std::string wifiManager ("Arf");
  CommandLine cmd;
  cmd.AddValue ("wifiManager", "Set wifi rate manager (Aarf, Aarfcd, Amrr, Arf, Cara, Ideal, Minstrel, Onoe, Rraa)", wifiManager);
  cmd.Parse (argc, argv);

  std::cout << "RTS/CTS disabled:\n" << std::flush;
  std::cout << "Taxa de transmissão:\n";
  experiment (false, wifiManager);
  std::cout << "RTS/CTS enabled:\n";
  std::cout << "Taxa de transmissão:\n";
  experiment (true, wifiManager);
  std::cout << "------------------------------------------------\n";

  return 0;
}
