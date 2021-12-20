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

printf "Day4 Part1: "
cat day4/input.txt | bazelisk run //day4:part1 2>/dev/null

printf "Day4 Part2: "
cat day4/input.txt | bazelisk run //day4:part2 2>/dev/null

printf "Day5 Part1: "
cat day5/input.txt | bazelisk run //day5:part1 2>/dev/null

printf "Day5 Part2: "
cat day5/input.txt | bazelisk run //day5:part2 2>/dev/null

printf "Day6 Part1: "
cat day6/input.txt | bazelisk run //day6:part1 80 2>/dev/null

printf "Day6 Part2: "
cat day6/input.txt | bazelisk run //day6:part2 256 2>/dev/null

printf "Day7 Part1: "
cat day7/input.txt | bazelisk run //day7:part1 2>/dev/null

printf "Day7 Part2: "
cat day7/input.txt | bazelisk run //day7:part2 2>/dev/null

printf "Day8 Part1: "
cat day8/input.txt | bazelisk run //day8:part1 2>/dev/null

printf "Day8 Part2: "
cat day8/input.txt | bazelisk run //day8:part2 2>/dev/null

printf "Day9 Part1: "
cat day9/input.txt | bazelisk run //day9:part1 2>/dev/null