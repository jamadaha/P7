import multiprocessing

class LabSettingsParser():
    _labSettingsFileName = "settingsLab.ini"
    SettingsCollection = []
    PlotsAttributes = []
    Threads = -1

    def ParseSettingsFile(self):
        linesLab = []
        with open(self._labSettingsFileName, 'r') as file:
            for line in file.readlines():
                if not line.lstrip(" ").startswith(";"):
                    linesLab.append(line)

        # Parse Lab setting
        for line in linesLab:
            if "SettingsCollection" in line:
                self.SettingsCollection = line.split("=")[1].strip("\n").split(",")
            if "PlotsAttributes" in line:
                self.PlotsAttributes = line.split("=")[1].strip("\n").split(",")
            elif "Threads" in line:
                self.Threads = int(line.split("=")[1].strip("\n"))

        if self.Threads == -1:
            self.Threads = multiprocessing.cpu_count()