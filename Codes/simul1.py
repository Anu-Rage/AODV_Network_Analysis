import subprocess
import csv
import time

# Define the range of transmission ranges
start_range = 10  # Starting transmission range
end_range = 100   # Ending transmission range
step_range = 5   # Step for transmission range
node_count = 100  # Fixed number of nodes

# Open the CSV file for writing
with open('transmission_range_results.csv', mode='w', newline='') as results_file:
    results_writer = csv.writer(results_file)
    results_writer.writerow(["TransmissionRange", "OverallPDR", "AverageThroughput", "OverallEndToEndDelay"])  # CSV header

    # Iterate over the specified range of transmission ranges
    for transmission_range in range(start_range, end_range + 1, step_range):
        print(f"Running simulation with transmission range: {transmission_range}...")

        # Run the ns-3 simulation program
        # Modify the command to include the transmission range argument
        command = f"./waf --run 'aodv_m_test --size={node_count} --transmissionRange={transmission_range}'"  # Adjust as necessary for your build environment
        result = subprocess.run(command, shell=True, capture_output=True, text=True)

        # Check for errors in running the simulation
        if result.returncode != 0:
            print(f"Error running simulation with transmission range {transmission_range}:\n{result.stderr}")
            continue

        # Wait for a moment to ensure results are written before reading the file
        time.sleep(1)

        # Read the results from the generated results.csv file
        try:
            with open('results.csv', mode='r') as file:
                reader = csv.reader(file)
                for row in reader:
                    if row[0] == str(node_count):  # Match the node count
                        # Write the results to the consolidated CSV
                        results_writer.writerow([transmission_range] + row[1:])  # Append the transmission range to the row
                        break
        except FileNotFoundError:
            print("Error: The results.csv file was not found. Please ensure your simulation writes results correctly.")

print("Simulation completed. Results saved to transmission_range_results.csv.")

