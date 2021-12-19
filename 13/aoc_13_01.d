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

    int maxX = int.min;
    int maxY = int.min;

    foreach (r; range) {
        auto x = r[0].to!int;
        auto y = r[1].to!int;

        if (x > maxX) maxX = x;
        if (y > maxY) maxY = y;

        paper[x][y] = true;
    }

    writeln("x: " ~ maxX.to!string ~ " y: " ~ maxY.to!string);

    string fl = f.readln["fold along ".length..$].strip();

    bool foldx = fl[0] == 'x';
    int foldline = fl[2..$].to!int;

    writeln("x? " ~ foldx.to!string);

    writeln("foldline: " ~ foldline.to!string);

    int visible;

    for (int y = 0; y < maxY + 1; y++) {
        for (int x = 0; x < maxX + 1; x++) {
            if (!paper[x][y]) continue;

            if (foldx && x > foldline) {
                paper[x][y] = false;
                paper[maxX - x][y] = true;
            } else if (!foldx && y > foldline) {
                paper[x][y] = false;
                paper[x][maxY - y] = true;
            }
        }
    }

    for (int j = 0; j < maxY + 1; j++) {
        for (int i = 0; i < maxX + 1; i++) {
            if (paper[i][j]) visible++;
            // paper[i][j] ? write("# ") : write(". ");
        }
        // writeln();
    }

    writeln("visible dots: " ~ visible.to!string);
}