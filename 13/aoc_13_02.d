import std.file;
import std.stdio;
import std.algorithm;
import std.array;
import std.conv;
import std.regex;
import core.stdc.stdio;
import std.string;

const string INPUT_PATH = "input";

void main() {
    bool[1500][1500] paper;

    auto f = File(INPUT_PATH);
    auto range = f.byLine()
                  .until("")
                  .map!(s => s.split(","));

    foreach (r; range) {
        auto x = r[0].to!int;
        auto y = r[1].to!int;

        paper[x][y] = true;
    }

    while (!f.eof) {
        string fl = f.readln["fold along ".length..$].strip();

        bool foldx = fl[0] == 'x';
        int foldline = fl[2..$].to!int;

        writeln((foldx ? "x" : "y") ~ ": " ~ foldline.to!string);

        for (int y = 0; y < 1500; y++) {
            for (int x = 0; x < 1500; x++) {
                if (!paper[x][y]) continue;

                if (foldx && x > foldline) {
                    paper[x][y] = false;
                    paper[(foldline * 2) - x][y] = true;
                } else if (!foldx && y > foldline) {
                    paper[x][y] = false;
                    paper[x][(foldline * 2) - y] = true;
                }
            }
        }
    }

    int maxX = int.min;
    int maxY = int.min;

    for (int y = 0; y < 1500; y++) {
        for (int x = 0; x < 1500; x++) {
            if (!paper[x][y]) continue;

            if (x > maxX) maxX = x;
            if (y > maxY) maxY = y;
        }
    }

    for (int y = 0; y < maxY + 1; y++) {
        for (int x = 0; x < maxX + 1; x++) {
            paper[x][y] ? write("#") : write(" ");
        }
        writeln();
    }
}

