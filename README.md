# P7
## Requirements
### Catch2
Catch2 is used for testing.
In order to install run the following

```bash
cd ~/bin
    && git clone https://github.com/catchorg/Catch2.git
    && cd Catch2
    && cmake -Bbuild -H. -DBUILD_TESTING=OFF
    && sudo cmake --build build/ --target install
```

This downloads the library, builds it, and installs it to path

### Fast Downward
Fast Downward is used as a planner for this project.
Install it by running the following commands:
```bash
sudo apt install cmake g++ git make python3
    && git clone https://github.com/aibasel/downward.git
    && cd downward
    && ./build.py
```

### VAL
VAL is used for validating Fast Downward plans.
Install it by running the following commands:
```bash
sudo apt install g++ make flex bison 
    && git clone https://github.com/KCL-Planning/VAL.git 
    && cd VAL 
    && git checkout a5565396007eee73ac36527fbf904142b3077c74 
    && make clean 
    && sed -i 's/-Werror //g' Makefile 
    && make
```

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
        "-v $HOME/downward-projects/VAL/validate"
      ],
      "env": {}
    }
  ]
}
```
