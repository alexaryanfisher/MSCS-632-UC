## Python Statistics Calculator

import math
from collections import Counter


class StatsCalculator:
    # Initialize the calculator with a list of numbers
    def __init__(self, numbers):
        self.numbers = numbers

    # Calculate the mean of the numbers
    def get_mean(self):
        # Error checking for list is empty.
        if not self.numbers:
            return math.nan
        return sum(self.numbers) / len(self.numbers)

    # Calculate the median of the numbers
    def get_median(self):
        # Error checking for list is empty.
        if not self.numbers:
            return math.nan
        # Sort the numbers
        sorted_nums = sorted(self.numbers)
        n = len(sorted_nums)
        mid = n // 2
        # If even amount of numbers, average the two middle numbers.
        if n % 2 == 0:
            return (sorted_nums[mid - 1] + sorted_nums[mid]) / 2
        else:
        # if odd amount of numbers, return the middle number.
            return sorted_nums[mid]

    # Calculate the mode of the numbers
    def get_mode(self):
        # Error checking for list is empty.
        if not self.numbers:
            return []
        count = Counter(self.numbers)
        maxcount = max(count.values())
        return [num for num, count in count.items() if count == maxcount]
    
    # Show the original numbers and calculated mean, median, and mode.
    def show_results(self):
        mean = self.get_mean()
        median = self.get_median()
        modes = self.get_mode()
        # Print the results
        print("Numbers: ", self.numbers)
        if math.isnan(mean):
            print("Mean: No numbers provided. Empty list.")
        else:
            print("Mean: ", mean)
        if math.isnan(median):
            print("Median: No numbers provided. Empty list.")
        else:
            print("Median: ", median)
        if not modes:
            print("Mode: No numbers provided. Empty list.")
        else:
            print("Mode(s): ", modes)

# Main Function
if __name__ == "__main__":
    numbers = [1, 2, 2, 2, 3, 5, 5, 5, 5, 7]
    calculator = StatsCalculator(numbers)
    calculator.show_results()