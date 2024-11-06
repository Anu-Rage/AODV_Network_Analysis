import subprocess
import csv
import time

# Define the range of nodes
start_nodes = 5
end_nodes = 100
step_nodes = 5

# Open the CSV file for writing
with open('results.csv', mode='w', newline='') as results_file:
    results_writer = csv.writer(results_file)
    results_writer.writerow(["NumberOfNodes", "OverallPDR", "AverageThroughput", "OverallEndToEndDelay"])  # CSV header

    # Iterate over the specified range of node counts
    for size in range(start_nodes, end_nodes + 1, step_nodes):
        print(f"Running simulation with {size} nodes...")
        
        # Run the ns-3 simulation program
        # Modify the command to include the size argument
        command = f"./waf --run 'aodv_m_test --size={size}'"  # Adjust as necessary for your build environment
        result = subprocess.run(command, shell=True, capture_output=True, text=True)

        # Check for errors in running the simulation
        if result.returncode != 0:
            print(f"Error running simulation with {size} nodes:\n{result.stderr}")
            continue

        # Wait for a moment to ensure results are written before reading the file
        time.sleep(1)

        # Read the results from the generated CSV file
        try:
            with open('results.csv', mode='r') as file:
                reader = csv.reader(file)
                for row in reader:
                    if row[0] == str(size):  # Match the size from the current iteration
                        # Write the results to the consolidated CSV
                        results_writer.writerow(row)
                        break
        except FileNotFoundError:
            print("Error: The results.csv file was not found. Please ensure your simulation writes results correctly.")

print("Simulation completed. Results saved to results.csv.")


