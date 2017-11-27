#! /bin/sh

# find . -type f -perm +111 | grep -v SHELL_REPOSITORY | grep -v "\.sh\$" | grep -v "\/mk" | grep -v "\/go" | grep -v "\/clean"
find . -type f -name "*~" -o -name ".*.swp" -o -name "core" -o -name "*.class" -o -name "tags*"
find . -type f -name "*.o" -o -name "*.exe" -o -name "*.exe.stackdump"

find . -name "Debug" -print -o -name "Release" -print
find . -name "*.ncb" -print -o -name "*.opt" -print -o -name "*.plg" -print
find . -type f -name ".*"

