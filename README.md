# P7
## Requirements
You can run `./installScript` in bash or install each requirement yourself.

### Catch2
Catch2 is used for testing.
In order to install run the following

```bash
git clone https://github.com/catchorg/Catch2.git Catch2 && cd Catch2 && cmake -Bbuild -H. -DBUILD_TESTING=OFF && sudo cmake --build build/ --target install && cd ..
```

This downloads the library, builds it, and installs it to path

### Fast Downward
Fast Downward is used as a planner for this project.
Install it by running the following commands:
```bash
sudo apt install cmake g++ git make python3 && git clone https://github.com/aibasel/downward.git && cd downward && ./build.py
```

### VAL
VAL is used for validating Fast Downward plans.
Install it by running the following commands:
```bash
sudo apt install g++ make flex bison && git clone https://github.com/KCL-Planning/VAL.git && cd VAL && git checkout a5565396007eee73ac36527fbf904142b3077c74 && make clean && sed -i 's/-Werror //g' Makefile && make
```

### Lab
Lab is used for evaluating solvers on benchmark sets.
Install it by running the following command:
```bash
sudo apt install python3-pip && pip install lab
```

## Launch
### VSCode
These are for debugging in VSCode.
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug",
            "type": "cppdbg",
            "request": "launch",
            // Resolved by CMake Tools:
            "program": "${command:cmake.launchTargetPath}",
            "args": [
                "settings.ini"
            ],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}/build",
            "environment": [
                {
                    // add the directory where our target was built to the PATHs
                    // it gets resolved by CMake Tools:
                    "name": "PATH",
                    "value": "${env:PATH}:${command:cmake.getLaunchTargetDirectory}"
                }
            ],
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }, {
            "name": "Release",
            "type": "cppdbg",
            "request": "launch",
            // Resolved by CMake Tools:
            "program": "${command:cmake.launchTargetPath}",
            "args": [
                "settingsFast.ini"
                ],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}/build",
            "environment": [
                {
                    // add the directory where our target was built to the PATHs
                    // it gets resolved by CMake Tools:
                    "name": "PATH",
                    "value": "${env:PATH}:${command:cmake.getLaunchTargetDirectory}"
                }
            ],
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }, {
            "name": "Lab",
            "type": "cppdbg",
            "request": "launch",
            // Resolved by CMake Tools:
            "program": "${command:cmake.launchTargetPath}",
            "args": [
                "'--all'",
                "--benchmarks '${workspaceFolder}/Data/Classical tracks/Gripper/'",
                "--domain 'gripper_domain.pddl'",
                "--problem 'gripper_problem.pddl'",
                "--downward '${workspaceFolder}/P7Requirements/downward/fast-downward.py'",
                "--validate '${workspaceFolder}/P7Requirements/VAL/validate'",
                "--reformulator RandomWalker",
                "--timelimit=1000"
            ],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [
                {
                    // add the directory where our target was built to the PATHs
                    // it gets resolved by CMake Tools:
                    "name": "PATH",
                    "value": "${env:PATH}:${command:cmake.getLaunchTargetDirectory}"
                }
            ],
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
To launch in Visual Studio (Note: This is the inferior version):
`launch.vs.json`
```json
{
  "version": "0.2.1",
  "defaults": {
  },
  "configurations": [
    {
      "type": "cppgdb",
      "name": "P7 Debug",
      "project": "CMakeLists.txt",
      "projectTarget": "P7",
      "debuggerConfiguration": "gdb",
      "cwd": "/root/.vs/P7/build",
      "args": [
        "settings.ini"
      ],
      "env": {
      }
    },
    {
      "type": "cppgdb",
      "name": "P7 Fast",
      "project": "CMakeLists.txt",
      "projectTarget": "P7",
      "debuggerConfiguration": "gdb",
      "cwd": "/root/.vs/P7/build",
      "args": [
        "settingsFast.ini"
      ],
      "env": {
      }
    },
    {
      "type": "cppgdb",
      "name": "P7 With Lab",
      "project": "CMakeLists.txt",
      "projectTarget": "P7Lab",
      "debuggerConfiguration": "gdb",
      "cwd": "/root/.vs/P7/build",
      "args": [
        "'--all'",
        "--settings 'settingsLab.ini'"
      ],
      "env": {
      }
    },
    {
      "type": "cppgdb",
      "name": "P7 With Lab (Multiple benchmarks)",
      "project": "CMakeLists.txt",
      "projectTarget": "P7Lab",
      "comment": "P7 with Lab",
      "debuggerConfiguration": "gdb",
      "cwd": "/root/.vs/P7/build",
      "args": [
        "'--all'",
        "--settings 'settingsLabMultiple.ini'"
      ],
      "env": {
      }
    },
    {
        "type": "cppgdb",
        "name": "P7 Stresstest",
        "project": "CMakeLists.txt",
        "projectTarget": "P7Lab",
        "comment": "Test all benchmarks",
        "debuggerConfiguration": "gdb",
        "cwd": "/home/pc/.vs/P7/build",
        "args": [
            "'--all'",
            "--settings 'settingsStress.ini'"
        ],
        "env": {
        }
    }
  ]
}
```
