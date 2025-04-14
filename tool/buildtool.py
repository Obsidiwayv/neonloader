import json
import os.path
import platform
import subprocess
import shutil

from tool.formatter import format_compile_commands
from tool.variables import StringVariables

RED = '\033[91m'
GREEN = '\033[92m'
BLUE = '\033[94m'
MAGENTA = '\033[95m'
RESET = '\033[0m'  # This resets the color back to default

def colorize(color, text):
    return f"{color}{text}{RESET}"

def project(proj_profile: str, build_dir, proj_name, proj_type):
    source_files_list = open(f"./{proj_profile}SOURCES", "r").read().split("\n")
    json_config = json.load(open(f"./{proj_profile}{proj_name}.config.json", "r"))
    print(f"Found {proj_name}.config.json at {colorize(MAGENTA, proj_profile)}")

    str_variables = StringVariables(build_dir, proj_name)

    def is_windows():
        return platform.system() == "Windows"

    def libs():
        if 'libs' in json_config:
            if 'windows' in json_config["libs"]:
                windows_libs = []
                for lib in json_config["libs"]["windows"]:
                    # Will append `-I` to the library
                    windows_libs.append(f"-l{lib}")
                if is_windows():
                    return str.join(" ", windows_libs)
        else:
            return ""

    llvm_source = "C:/Program Files/LLVM"
    compiler_file_type = ".exe"

    if not is_windows():
        llvm_source = ""
        compiler_file_type = ""

    if not os.path.exists(llvm_source):
        raise Exception(colorize(RED, "Building requires LLVM!"))

    llvm_executable = f'"{llvm_source}/bin/clang++{compiler_file_type}"'
    #LLVM_AR_EXECUTABLE = f'"{llvm_source}/bin/llvm-ar{compiler_file_type}"'
    print(f"Using {colorize(BLUE, llvm_executable)}")

    def include_paths():
        if 'includes' in json_config:
            includes = []
            for inc in json_config["includes"]:
                includes.append(f"-I{proj_profile.removeprefix("/")}{inc}")
            return str.join(" ", includes)
        else:
            return ""


    if not os.path.exists(build_dir):
        os.mkdir(build_dir)

    if not os.path.exists(f"{build_dir}/cmd"):
        os.mkdir(f"{build_dir}/cmd")

    #if not os.path.exists("bin"):
    #    os.mkdir("bin")

    ext_commands = []

    if proj_type == "library":
        if is_windows():
            #cache_path = f"{build_dir}/obj"
            ext_commands.append("-shared")
            compiler_file_type = ".dll"

            #if not os.path.exists(cache_path):
            #    os.mkdir(cache_path)

            #print(f"Using {colorize(BLUE, LLVM_AR_EXECUTABLE)} for lib archiving")
            #obj_files = []
            #for source_file in source_files:
            #    stripped_source_name = f"{cache_path}/{source_file.split("/")[-1].removesuffix('.cpp')}.obj"
            #    subprocess.call(f"{llvm_executable} -o {stripped_source_name} -c {source_file} {include_paths()}")
            #    obj_files.append(stripped_source_name)
            #subprocess.call(f"{LLVM_AR_EXECUTABLE} rcs bin/{proj_name}.lib {str.join(" ", obj_files)}")
    else:
        if is_windows():
            ext_commands.append("-Wl,/NOIMPLIB")

    source_files = []
    for source in source_files_list:
        if source.startswith("search"):
            source_folder = source.split(",")[1]
            for _, _, files in os.walk(source_folder):
                for source_file in files:
                    source_files.append(f"{source_folder}/{source_file}")
            source = source.replace(f"search:{source_folder}", "")
        else:
            source_files.append(source)

    if "win32" in json_config:
        if json_config["win32"]:
            ext_commands.append("-Wl,/Subsystem:windows")

    commands = [
        f"{llvm_executable} -o {build_dir}/{proj_name}{compiler_file_type}",
        include_paths(),
        # compile_commands.json will be created for clion and zed integration
        f"{str.join(" ", source_files)} {libs()} -MJ {build_dir}/cmd/co.out{proj_profile.replace("/", ".")}json",
        f"-std=c++17"
    ] + ext_commands

    print(str.join(" ", commands))

    subprocess.call(str.join(" ", commands))

    if "assets" in json_config:
        for asset in json_config["assets"]:
            shutil.copy(asset, f"{build_dir}/{asset.split("/")[-1]}")
            print(f"Copied {colorize(MAGENTA, asset)}")

    format_compile_commands(build_dir)