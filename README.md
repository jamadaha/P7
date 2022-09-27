# P7
## Requirements
### Catch2
Catch2 is used for testing.
In order to install run the following

<code>
cd ~/bin && git clone https://github.com/catchorg/Catch2.git &&
cd Catch2 &&
cmake -Bbuild -H. -DBUILD_TESTING=OFF &&
sudo cmake --build build/ --target install
</code>

This downloads the library, builds it, and installs it to path

## Launch
### VSCode
These are for debugging in VSCode. They aren't needed for anything else.
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${command:cmake.launchTargetPath}",
            "args": ["-h"],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [
                {
                    "name": "PATH",
                    "value": "${env:PATH}:${command:cmake.getLaunchTargetDirectory}"
                },
                {
                    "name": "OTHER_VALUE",
                    "value": "Something something"
                }
            ],
            "console": "externalTerminal",
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

### Visual Studio
To launch in Visual Studio:
`launch.vs.json`
```json
{
  "version": "0.2.1",
  "defaults": {},
  "configurations": [
    {
      "type": "cppgdb",
      "name": "P7",
      "project": "CMakeLists.txt",
      "projectTarget": "",
      "comment": "",
      "debuggerConfiguration": "gdb",
      "args": [
        "-d Data/gripper.pddl",
        "-p Data/gripper-4.pddl",
        "-f $HOME/downward-projects/downward/fast-downward.py"
      ],
      "env": {}
    }
  ]
}
```
