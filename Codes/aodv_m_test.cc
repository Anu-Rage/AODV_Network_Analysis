#include <iostream>
#include <ostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include "ns3/aodv-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/v4ping-helper.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

class AodvExample 
{
public:
  AodvExample ();
  bool Configure (int argc, char **argv);
  void Run ();
  void Report (std::ostream & os);
  void AnalyzeResults();

private:
  uint32_t size;
  double totalTime;
  double transmissionRange;
  bool pcap;
  bool printRoutes;

  NodeContainer nodes;
  NetDeviceContainer devices;
  Ipv4InterfaceContainer interfaces;
  FlowMonitorHelper flowMonitor;
  Ptr<FlowMonitor> monitor;

  void CreateNodes ();
  void CreateDevices ();
  void InstallInternetStack ();
  void InstallApplications ();
  void SetNodePositions(const std::string &filename);
};

int main (int argc, char **argv)
{
  AodvExample test;
  if (!test.Configure (argc, argv))
    NS_FATAL_ERROR ("Configuration failed. Aborted.");

  test.Run ();
  test.Report (std::cout);
  return 0;
}

//-----------------------------------------------------------------------------

AodvExample::AodvExample () :
  size (100), // Set the number of nodes
  totalTime (10),
  transmissionRange (50),
  pcap (true),
  printRoutes (true)
{
}

bool
AodvExample::Configure (int argc, char **argv)
{
  CommandLine cmd (__FILE__);
  cmd.AddValue ("pcap", "Write PCAP traces.", pcap);
  cmd.AddValue ("printRoutes", "Print routing table dumps.", printRoutes);
  cmd.AddValue ("size", "Number of nodes.", size);
  cmd.AddValue ("time", "Simulation time, s.", totalTime);
  cmd.AddValue ("transmissionRange", "Transmission range, meters.", transmissionRange);  // Add transmission range option
  cmd.Parse (argc, argv);
  return true;
}

void
AodvExample::Run ()
{
  CreateNodes ();
  CreateDevices ();
  InstallInternetStack ();
  InstallApplications ();
  
  AnimationInterface anim ("aodv_simulation.xml");  // Output XML file for NetAnim visualization

  monitor = flowMonitor.InstallAll();

  std::cout << "Starting simulation for " << totalTime << " s ...\n";
  Simulator::Stop (Seconds (totalTime));
  Simulator::Run ();
  monitor->SerializeToXmlFile("flow-monitor-results.xml", true, true);
  
  // Analyze results for PDR and throughput
  AnalyzeResults();  // Call to analyze results after simulation
  
  Simulator::Destroy ();
}

void
AodvExample::Report (std::ostream &os)
{ 
  // Add code to report the results
}


void AodvExample::AnalyzeResults()
{
    std::ofstream resultsFile("results.csv");

    double totalPacketsSent = 0;
    double totalPacketsReceived = 0;
    double totalDelay = 0;
    double totalThroughput = 0;
    int flowCount = 0;

    // Iterate through all flows and collect metrics
    for (const auto& flow : monitor->GetFlowStats())
    {
        totalPacketsSent += flow.second.txPackets;     // Total packets sent
        totalPacketsReceived += flow.second.rxPackets;  // Total packets received
        totalDelay += flow.second.delaySum.GetSeconds(); // Total delay

        // Calculate throughput for this flow in kbps
        double flowThroughput = (flow.second.rxPackets * 1024 * 8) / (totalTime * 1000); 
        totalThroughput += flowThroughput;
        flowCount++;
    }

    // Calculate overall PDR
    double overallPDR = (totalPacketsSent > 0) ? (totalPacketsReceived / totalPacketsSent) * 100 : 0;

    // Calculate average throughput per flow
    double averageThroughput = (flowCount > 0) ? (totalThroughput / flowCount) : 0;

    // Calculate overall end-to-end delay (average per received packet)
    double overallEndToEndDelay = (totalPacketsReceived > 0) ? (totalDelay / totalPacketsReceived) : 0;

    // Output the overall results to the CSV
    resultsFile << size << "," << overallPDR << "," << averageThroughput << "," << overallEndToEndDelay << "\n";

    resultsFile.close();
    std::cout << "Overall results written to results.csv\n";
}

void
AodvExample::CreateNodes ()
{
  std::cout << "Creating " << size << " nodes.\n";
  nodes.Create (size);

  // Read node positions from CSV
  SetNodePositions("./scratch/manet.csv");

  // Name nodes
  for (uint32_t i = 0; i < size; ++i)
    {
      std::ostringstream os;
      os << "node-" << i;
      Names::Add (os.str (), nodes.Get (i));
    }
}

void
AodvExample::SetNodePositions(const std::string &filename)
{
  std::ifstream file(filename);
  std::string line;
  uint32_t nodeNo;
  double x, y;

  if (file.is_open()) {
    std::cout << "Reading node positions from file: " << filename << std::endl;
    while (std::getline(file, line)) {
      std::stringstream ss(line);
      std::string token;
      
      // Read node number
      if (std::getline(ss, token, ',')) {
        std::stringstream(token) >> nodeNo;
      } else {
        std::cerr << "Error parsing node number from line: " << line << std::endl;
        continue;
      }

      // Read x-coordinate
      if (std::getline(ss, token, ',')) {
        std::stringstream(token) >> x;
      } else {
        std::cerr << "Error parsing x-coordinate from line: " << line << std::endl;
        continue;
      }

      // Read y-coordinate
      if (std::getline(ss, token, ',')) {
        std::stringstream(token) >> y;
      } else {
        std::cerr << "Error parsing y-coordinate from line: " << line << std::endl;
        continue;
      }

      // Check node number and set position
      if (nodeNo < size) {
        std::cout << "Setting position for node " << nodeNo << " at (x: " << x << ", y: " << y << ")" << std::endl;

        MobilityHelper mobility;
        mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
        mobility.Install(nodes.Get(nodeNo));
        nodes.Get(nodeNo)->GetObject<MobilityModel>()->SetPosition(Vector(x, y, 0));
      } else {
        std::cerr << "Error: Node number " << nodeNo << " exceeds the number of nodes (" << size << ")." << std::endl;
      }
    }
    file.close();
  } else {
    std::cerr << "Unable to open file: " << filename << std::endl;
  }
}

void
AodvExample::CreateDevices ()
{
  WifiMacHelper wifiMac;
  wifiMac.SetType ("ns3::AdhocWifiMac");
  YansWifiPhyHelper wifiPhy;
  YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
  
  // Set the propagation loss model
  wifiChannel.AddPropagationLoss("ns3::RangePropagationLossModel","MaxRange", DoubleValue (transmissionRange));
  wifiPhy.SetChannel (wifiChannel.Create ());

  // Set the PHY parameters for a higher throughput
  wifiPhy.Set ("TxPowerStart", DoubleValue(20)); // Transmission power in dBm
  wifiPhy.Set ("TxPowerEnd", DoubleValue(20));   // Keep constant for simulation

  // Create Wifi devices
  WifiHelper wifi;
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                "DataMode", StringValue ("OfdmRate54Mbps"),  // Use a suitable data rate for 500 Mbps
                                "ControlMode", StringValue("OfdmRate54Mbps")); // Set control mode to the same

  devices = wifi.Install (wifiPhy, wifiMac, nodes);

  if (pcap)
  {
      wifiPhy.EnablePcapAll (std::string ("aodv"));
  }
}

void
AodvExample::InstallInternetStack ()
{
  AodvHelper aodv;
  InternetStackHelper stack;
  stack.SetRoutingHelper (aodv);
  stack.Install (nodes);
  
  Ipv4AddressHelper address;
  address.SetBase ("10.0.0.0", "255.0.0.0");
  interfaces = address.Assign (devices);

  if (printRoutes)
    {
      Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> ("aodv.routes", std::ios::out);
      aodv.PrintRoutingTableAllAt (Seconds (8), routingStream);
    }
}

void
AodvExample::InstallApplications ()
{
  V4PingHelper ping (interfaces.GetAddress (size - 1));
  ping.SetAttribute ("Verbose", BooleanValue (true));
  ApplicationContainer p = ping.Install (nodes.Get (0));
  p.Start (Seconds (0));
  p.Stop (Seconds (totalTime) - Seconds (0.001));
}
