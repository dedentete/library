import glob

output = open("cpp.json", "w")
files = glob.glob("*/*.cpp")
output.write("{\n")

for i in range(len(files)):
    lines = open(files[i], "r").readlines()
    tmp = files[i].split("/")
    name = tmp[1].replace(".cpp","")
    output.write("    \"" + name + "\":{\n")
    output.write("        \"prefix\": \"" + name + "\",\n")
    output.write("        \"body\": [\n")
    for line in lines:
        line = line.replace('"', '\\\"')
    for j in range(len(lines) - 1):
        output.write("            \"" + lines[j].replace('"', '\\"').replace("\n","") + "\",\n")
    output.write("            \"" + lines[len(lines) - 1].replace('"', '\\"').replace("\n","") + "\"\n")
    output.write("        ],\n")
    output.write("        \"description\": \"" + name + "\"\n")
    if(i == len(files) - 1):
        output.write("    }\n")
    else:
        output.write("    },\n")
output.write("}")
output.close