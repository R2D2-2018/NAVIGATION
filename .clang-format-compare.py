## @file      .clang-format-compare.py
#  @brief     Tool for comparing source files with a formatted variant in order to detect clang-formatting
#  @author    Julian van Doorn
#  @license   See LICENSE

from subprocess import *
from xml.etree import ElementTree
from os import getcwd, path, walk
from glob import glob
from sys import exit, argv

def isClangFormatted(fileDir):
    pargs = [
        "clang-format",
        path.join(fileDir),
        "--output-replacements-xml"
    ]

    raw_xml = Popen(pargs, stdout=PIPE).communicate()[0]

    tree = ElementTree.fromstring(raw_xml) # if replacements is zero, that means it is already clang-formatted

    return len(tree) == 0

def getUnformattedFiles(folderDirs, filePatterns):
    fileDirs = []

    for dir in folderDirs:
        for pattern in filePatterns:
            fileDirs += [y for x in walk(dir) for y in glob(path.join(x[0], pattern))]

    unformattedFiles = []

    for dir in fileDirs:
        if not isClangFormatted(dir):
            unformattedFiles.append(dir)

    return unformattedFiles

def main():
    unformattedFiles = getUnformattedFiles(argv[1:], ["*.cpp", "*.hpp"])

    if len(unformattedFiles) > 0:
        print("The following source files are not clang-formatted:")

        for dir in unformattedFiles:
            print(dir)

        exit(1)

    print("All source files are clang-formatted!")

    exit(0)

if __name__ == "__main__":
    main()
