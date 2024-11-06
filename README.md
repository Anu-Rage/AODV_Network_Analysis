# Performance Analysis of AODV Protocol in MANETs: Impact of Node Density and Transmission Range on Packet Delivery Ratio and Throughput using NS-3
This project uses ns-3 to analyze AODV in MANETs, with 100 nodes positioned via manet.csv. By varying transmission range and node density, we measure packet delivery ratio and throughput. Using ns3::FlowMonitor, we assess AODV’s adaptability to network changes, highlighting its efficiency in dynamic routing.

### Manual
Prerequisites:
a.	NS-3 Installation: Make sure NS-3 (version 3.35 or compatible) is installed on your system. You can download it from the NS-3 website.
b.	Environment Setup:
o	Your experiment files (e.g., aodv_m_test.cc) and manet.csv file with node positions should be located in the scratch directory within your NS-3 installation.
o	Ensure manet.csv is correctly formatted with columns for node numbers, x-coordinates, and y-coordinates.
Experiment Files:
•	Simulation File: aodv_m_test.cc - the primary source code for the AODV simulation.
•	Node Position File: manet.csv - CSV file defining X-Y positions for each node.

Steps to Run the Experiment:
a.	Navigate to NS-3 Directory: Open a terminal and navigate to the root directory of your NS-3 installation:
b.	Place Files in the Scratch Directory: Ensure aodv_m_test.cc and manet.csv are in the scratch directory:
c.	Build the Simulation File: Run the following command to compile the code:
./waf build --run scratch/aodv_m_test
o	If the build completes without errors, it will automatically run the simulation.
o	If there are errors, check for missing libraries or syntax issues in the code.

d.	Configure Command-Line Parameters: Optional parameters can be set directly in the command line:
o	Example: Adjusting node count, transmission range, and simulation time.
./waf --run "scratch/aodv_m_test --size=100 --transmissionRange=50 --time=10"


o	Parameters available:
	--size: Number of nodes (default is 100).
	--transmissionRange: Transmission range in meters (default is 50).
	--time: Total simulation time in seconds (default is 10).

e.	Output Files: The simulation generates several output files:
o	PCAP Traces (if enabled): Stored as aodv-xx.pcap files.
o	NetAnim File: aodv_simulation.xml - use this file for network animation with NetAnim.
o	Flow Monitor XML: flow-monitor-results.xml - for detailed flow statistics.
o	CSV Results: results.csv - containing Packet Delivery Ratio (PDR), average throughput, and end-to-end delay.

f.	Analyze Results:
o	After the simulation completes, open the results.csv file to view the analyzed results.

g.	Run Simulation:
Running simulation by varying number of nodes and transmission range:
o	Keep the simul.py in the ns 3.35 directory and run the python file by command:
                                pyhton3 simul.py 

o	It will give a file results.csv which will contain the dataset for further analysis for varying nodes. Rename the file to results_by_varying_nodes.csv and save it.

o	Similarly keep the simul1.py in the ns 3.35 directory and run the python file by command
o	
python3 simul1.py

o	It will give a file transmission_range_results.csv which will contain the dataset for further analysis for varying nodes



h.	To obtain the graph:
o	To get the graphs of No. of nodes vs. PDR, No. of nodes vs. Average throughput, and No. of nodes vs. end to end delay run ns3_results_1.py file.

o	To get the graphs of Transmission_range vs. PDR, Transmission_range vs. Average throughput, and Transmission_range vs. end to end delay run ns3_results_2.py file.


### References:
•	https://www.researchgate.net/publication/325512294_STATIC_NETWORK_PERFORMANCE_OPTIMISATION_USING_DUAL_INTERLEAVE_ROUTING_ALGORITHM

•	https://www.researchgate.net/publication/330180796_Comparison_of_AODV_DSR_and_DSDV_routing_protocols_in_a_wireless_network

•	https://www.nsnam.org/documentation/
