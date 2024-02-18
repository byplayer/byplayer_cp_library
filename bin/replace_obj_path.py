import re
import sys

if len(sys.argv) != 4:
    print('usage replace_obj_path base_file target_file obj_dir')
    sys.exit(1)

base_fname = sys.argv[1]
target_fname = sys.argv[2]
base_dir = sys.argv[3]

with open(base_fname) as f:
    data_lines = f.read()

data_lines = re.sub(r"^(.*\.o):", f'{base_dir}/\\1:', data_lines)

with open(target_fname, mode="w") as f:
    f.write(data_lines)
