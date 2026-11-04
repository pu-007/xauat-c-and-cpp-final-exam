#!/usr/bin/env python3
"""用ASan/UBSan重编译并复用完整测试集；不覆盖普通build。"""
from pathlib import Path
import os,subprocess
R=Path(__file__).resolve().parents[1]
for language,compiler,standard,suffix in [('c','gcc','c99','c'),('cpp','g++','c++11','cpp')]:
    folder=R/'build/sanitize'/language;folder.mkdir(parents=True,exist_ok=True)
    for path in sorted((R/'src'/language).glob('*.'+suffix)):
        subprocess.run([compiler,f'-std={standard}','-O1','-g','-Wall','-Wextra','-Wpedantic','-Werror','-fsanitize=address,undefined','-fno-omit-frame-pointer','-fno-pie','-no-pie',str(path),'-lm','-o',str(folder/path.stem)],check=True)
env=os.environ.copy();env['COURSE_BIN']=str(R/'build/sanitize');env['ASAN_OPTIONS']='detect_leaks=1:halt_on_error=1';env['UBSAN_OPTIONS']='halt_on_error=1'
subprocess.run(['python3',str(R/'tests/run.py')],env=env,check=True)

subprocess.run(['python3',str(R/'tests/labs.py')],env=env,check=True)
