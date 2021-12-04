#! /bin/sh

printf "Day1 Part1: "
cat day1/input.txt | bazelisk run //day1:part1 2>/dev/null

printf "Day1 Part2: "
cat day1/input.txt | bazelisk run //day1:part2 2>/dev/null

printf "Day2 Part1: "
cat day2/input.txt | bazelisk run //day2:part1 2>/dev/null

printf "Day2 Part2: "
cat day2/input.txt | bazelisk run //day2:part2 2>/dev/null

printf "Day3 Part1: "
cat day3/input.txt | bazelisk run //day3:part1 --copt="-DBITSIZE=12" 2>/dev/null

printf "Day3 Part2: "
cat day3/input.txt | bazelisk run //day3:part2 --copt="-DBITSIZE=12" 2>/dev/null