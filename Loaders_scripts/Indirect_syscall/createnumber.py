
import string

# Create a combined character set of all lowercase, uppercase letters, and digits
char_set = string.ascii_lowercase + string.ascii_uppercase + string.digits + "." + "\\" + ":"

# Function to convert a string into a list of character positions
def string_to_positions(input_string):
    positions = []
    for char in input_string:
        if char in char_set:
            position = char_set.index(char)  # Get the index of the character in the char_set
            positions.append(position)
        else:
            raise ValueError(f"Character '{char}' not found in the character set.")
    return positions

# Example usage
function_name = "msedge.exe" #please give the function name that you want to encode
positions = string_to_positions(function_name)

# Output the result
print("Character positions for '{}':".format(function_name))
print(positions)
