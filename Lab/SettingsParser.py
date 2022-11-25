from Lab.PathHelper import PathHelper

class SettingsParser():
    Domains = ""
    Reformulators = []
    RunModes = []
    SettingsContent = ""
    _pathHelper : PathHelper

    def __init__(self, pathHelper : PathHelper):
        self._pathHelper = pathHelper

    def Parse(self, fileContent):
        for line in fileContent:
            if "domain" in line:
                self.Domains = line.split("=")[1].strip("\n").split(":")
            elif "downwardpath" in line or "validatorpath" in line or "translatorpath" in line or "h2path" in line:
                argument = line.split("=")
                self.SettingsContent += argument[0] + "=" + self._pathHelper.CombinePath(argument[1]) 
            elif "reformulator=" in line:
                self.Reformulators = line.split("=")[1].strip("\n").split(",")
            elif "runDirect=" in line:
                self.RunModes = line.split("=")[1].strip("\n").split(",")
            elif "EXTERNAL" not in line:
                self.SettingsContent += line