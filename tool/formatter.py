import os


def format_compile_commands(output_dir):
    json_array = "["
    for _, _, files in os.walk(output_dir):
        for file in files:
            if file.endswith(".json"):
                json_file = open(f"{output_dir}/cmd/{file}").read()
                json_array += json_file

    with open(f"compile_commands.json", "w") as file:
        file.write(f"{json_array[:-2]}]")
