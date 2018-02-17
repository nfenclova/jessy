# pylint: disable=missing-docstring,invalid-name,unused-argument
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

def FlagsForFile(*args, **kwargs):
    return {
        'flags': [
            '-xc++',
            '-std=c++17',

            '-Wextra',
            '-Werror',
            '-pedantic-errors',

            '--target=x86_64-none-elf',
            '-ffreestanding',
            '-nostdlib',
            '-fno-rtti',
            '-fno-exceptions',

            '-DUNREACHABLE=__builtin_unreachable',

            '-Iinclude',
        ],
        'include_paths_relative_to_dir': SCRIPT_DIR
    }
