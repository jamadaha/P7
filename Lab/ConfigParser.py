
class ConfigParser():
    def ParseConfig(fileName):
        fileContent = []
        fileContentPost = []
        with open(fileName, 'r') as file:
            for line in file.readlines():
                if not line.lstrip(" ").startswith(";"):
                    fileContent.append(line)
        for line in fileContent:
            if "EXTERNAL" in line:
                value = line.split(":")[1].strip("\n")
                if "baseSettings.ini" not in value:
                    value = "../LabSettings/" + value
                fileContentPost = ConfigParser.ParseConfig(value) + fileContentPost
            else:
                fileContentPost.append(line)

        return fileContentPost
