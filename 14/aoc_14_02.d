import std.file;
import std.stdio;
import std.string;
import std.regex;
import std.conv;

const string INPUT_FILE = "input";

string[string] rules;

long[string] pairsCount;

void main() {
    auto f = File(INPUT_FILE);

    string templ = f.readln().strip();

    const reg = regex(r"(\w+) -> (\w+)");

    while (!f.eof()) {
        string ln = f.readln().strip();

        if (ln == "") continue;

        auto m = matchAll(ln, reg);

        rules[m.front[1]] = m.front[2];
    }

    writeln("template: ", templ);

    for (int i = 0; i < templ.length - 1; i++) { // stfu
        string rule = rules[templ[i..i+2]];
        pairsCount[templ[i] ~ rule]++;
        pairsCount[rule ~ templ[i+1]]++;
    }

    long[string] newPairsCount;
    foreach (s; 0..39) {
        newPairsCount.clear();

        foreach (pair, count; pairsCount) {
            string rule = rules[pair];
            newPairsCount[pair[0] ~ rule] += count;
            newPairsCount[rule ~ pair[1]] += count;
        }

        pairsCount = newPairsCount.dup;
    }

    long[char] countChars;
    countChars[templ[$-1]] = 1;

    foreach (pair, count; pairsCount) {
        countChars[pair[0]] += count;
    }

    long max = long.min;
    long min = long.max;

    foreach (ch, count; countChars) {
        if (count > max) max = count;
        if (count < min) min = count;

        writeln(ch, ": ", count);
    }

    writeln(max - min);
}
