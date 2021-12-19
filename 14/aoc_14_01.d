import std.file;
import std.stdio;
import std.string;
import std.regex;
import std.conv;
import std.typecons;

const string INPUT_FILE = "input";

void main() {
    auto f = File(INPUT_FILE);

    string templ = f.readln().strip();

    string[string] rules;

    const reg = regex(r"(\w+) -> (\w+)");

    while (!f.eof()) {
        string ln = f.readln().strip();

        if (ln == "") continue;

        auto m = matchAll(ln, reg);

        rules[m.front[1]] = m.front[2];
    }

    writeln("template: ", templ);

    foreach (s; 0..10) {
        string newPoly = templ[0].to!string();

        for (int i = 0; i < templ.length - 1; i++) { // stfu
            string rule = templ[i..i+2];
            newPoly ~= rules[rule] ~ rule[$-1];
        }

        templ = newPoly;
    }

    auto minmax = stringMinMax(templ);
    auto res = minmax[1] - minmax[0];

    writeln(res);
}

Tuple!(int, int) stringMinMax(string s) {
    int[char] count;

    int max = int.min;
    int min = int.max;

    for (int i = 0; i < s.length; i++) {
        count[s[i]]++;

        if (count[s[i]] > max) {
            max = count[s[i]];
        }
    }

    for (int i = 0; i < s.length; i++) {
        if (count[s[i]] < min) {
            min = count[s[i]];
        }
    }

    return tuple(min, max);
}
