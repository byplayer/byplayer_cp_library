import re
import sys

if len(sys.argv) != 3:
    print('usage replace_obj_path target_file obj_dir')
    sys.exit(1)

file_name = sys.argv[1]
base_dir = sys.argv[2]

with open(file_name) as f:
    data_lines = f.read()

data_lines = re.sub(r"^(.*\.o):", f'{base_dir}/\\1:', data_lines)

with open(file_name, mode="w") as f:
    f.write(data_lines)
