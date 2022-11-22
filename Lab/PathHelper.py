import os

class PathHelper():
    _basePath = ""

    def __init__(self, basePath):
        self._basePath = basePath

    def CombinePath(self, basePath, path):
        return os.path.join(basePath, path) 

    def CombinePath(self, path):
        return os.path.join(self._basePath, path) 