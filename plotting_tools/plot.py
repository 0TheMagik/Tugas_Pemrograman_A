import pandas as pd
import matplotlib.pyplot as plt

def plot_csv(file_path, x_column, y_column, plot_type='line', title='CSV Plot', xlabel=None, ylabel=None):
    """
    Plot data from a CSV file.
    
    Parameters:
    - file_path: Path to the CSV file
    - x_column: Name of the column for x-axis
    - y_column: Name of the column for y-axis
    - plot_type: Type of plot ('line', 'scatter', 'bar')
    - title: Plot title
    - xlabel: Label for x-axis (defaults to x_column if None)
    - ylabel: Label for y-axis (defaults to y_column if None)
    """
    # Read CSV file
    try:
        data = pd.read_csv(file_path)
    except FileNotFoundError:
        print(f"Error: File {file_path} not found")
        return
    except Exception as e:
        print(f"Error reading CSV: {str(e)}")
        return

    # Verify columns exist
    if x_column not in data.columns or y_column not in data.columns:
        print(f"Error: One or both columns ({x_column}, {y_column}) not found in CSV")
        return

    # Create figure
    plt.figure(figsize=(10, 6))

    # Plot based on plot_type
    if plot_type == 'line':
        plt.plot(data[x_column], data[y_column])
    elif plot_type == 'scatter':
        plt.scatter(data[x_column], data[y_column])
    elif plot_type == 'bar':
        plt.bar(data[x_column], data[y_column])
    else:
        print("Error: Invalid plot_type. Use 'line', 'scatter', or 'bar'")
        return

    # Set labels and title
    plt.title(title)
    plt.xlabel(xlabel if xlabel else x_column)
    plt.ylabel(ylabel if ylabel else y_column)
    
    # Add grid
    plt.grid(True)
    
    # Save plot
    output_file = file_path.replace('.csv', '_plot.png')
    plt.savefig(output_file)
    print(f"Plot saved as {output_file}")
    
    # Close plot to free memory
    plt.close()

# Example usage
if __name__ == "__main__":
    # Example CSV structure:
    # date,value
    # 2023-01,10
    # 2023-02,15
    # 2023-03,13
    plot_csv('sample.csv', 'date', 'value', plot_type='line', title='Sample Data Plot', xlabel='Date', ylabel='Value')