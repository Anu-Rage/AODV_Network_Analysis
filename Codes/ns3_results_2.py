import pandas as pd
import matplotlib.pyplot as plt

# Load the data
data = pd.read_csv('transmission_range_results.csv')

# Plot settings
plt.style.use('seaborn-darkgrid')

# Plot 1: Transmission Range vs Overall PDR
plt.figure(figsize=(10, 6))
plt.plot(data['TransmissionRange'], data['OverallPDR'], marker='o', color='b', label='Overall PDR')
plt.xlabel('Transmission Range (meters)')
plt.ylabel('Packet Delivery Ratio (%)')
plt.title('Transmission Range vs Packet Delivery Ratio')
plt.legend()
plt.savefig('TransmissionRange_vs_OverallPDR.png')  # Save the plot
plt.show()

# Plot 2: Transmission Range vs Average Throughput (in kbps)
plt.figure(figsize=(10, 6))
plt.plot(data['TransmissionRange'], data['AverageThroughput'], marker='o', color='g', label='Average Throughput')
plt.xlabel('Transmission Range (meters)')
plt.ylabel('Throughput (kbps)')
plt.title('Transmission Range vs Average Throughput')
plt.legend()
plt.savefig('TransmissionRange_vs_AverageThroughput.png')  # Save the plot
plt.show()

# Plot 3: Transmission Range vs Overall End-to-End Delay
plt.figure(figsize=(10, 6))
plt.plot(data['TransmissionRange'], data['OverallEndToEndDelay'], marker='o', color='r', label='Overall End-to-End Delay')
plt.xlabel('Transmission Range (meters)')
plt.ylabel('End-to-End Delay (seconds)')
plt.title('Transmission Range vs End-to-End Delay')
plt.legend()
plt.savefig('TransmissionRange_vs_EndToEndDelay.png')  # Save the plot
plt.show()