import pandas as pd
import matplotlib.pyplot as plt

# Load the data
data = pd.read_csv('results_by_varying_nodes.csv')

# Plot settings
plt.style.use('seaborn-darkgrid')

# Plot 1: Number of Nodes vs Overall PDR
plt.figure(figsize=(10, 6))
plt.plot(data['NumberOfNodes'], data['OverallPDR'], marker='o', color='b', label='Overall PDR')
plt.xlabel('Number of Nodes')
plt.ylabel('Packet Delivery Ratio (%)')
plt.title('Number of Nodes vs Packet Delivery Ratio')
plt.legend()
plt.savefig('NumberOfNodes_vs_OverallPDR.png')  # Save the plot
plt.show()

# Plot 2: Number of Nodes vs Average Throughput (in kbps)
plt.figure(figsize=(10, 6))
plt.plot(data['NumberOfNodes'], data['AverageThroughput'], marker='o', color='g', label='Average Throughput')
plt.xlabel('Number of Nodes')
plt.ylabel('Throughput (kbps)')
plt.title('Number of Nodes vs Average Throughput')
plt.legend()
plt.savefig('NumberOfNodes_vs_AverageThroughput.png')  # Save the plot
plt.show()

# Plot 3: Number of Nodes vs Overall End-to-End Delay
plt.figure(figsize=(10, 6))
plt.plot(data['NumberOfNodes'], data['OverallEndToEndDelay'], marker='o', color='r', label='Overall End-to-End Delay')
plt.xlabel('Number of Nodes')
plt.ylabel('End-to-End Delay (seconds)')
plt.title('Number of Nodes vs End-to-End Delay')
plt.legend()
plt.savefig('NumberOfNodes_vs_EndToEndDelay.png')  # Save the plot
plt.show()