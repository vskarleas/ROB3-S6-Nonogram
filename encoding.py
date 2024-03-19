def replace_hyphens(filename):
  """Reads a text file, replaces hyphens with spaces, and saves the modified content to the same file."""
  with open(filename, 'r') as f:
    content = f.read()
  modified_content = content.replace('-', ' ')
  with open(filename, 'w') as f:
    f.write(modified_content)

# Example usage
filename = "instances/photo.txt"
replace_hyphens(filename)
print(f"Replaced hyphens with spaces in {filename}")
