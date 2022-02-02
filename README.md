# jsondiff
## Description

Compares 2 JSON files.

## Usage

jsondiff file1.json file2.json -v (diff values) -d (report only differences)

By default (no command options) this tool reports the structure of file1.json and the differences vs. the structure of file2.json.

Command option -v reports not just syntax differences, but also the values of the JSON elements.

Command option -d reports only the differences, not the matching syntax nor the matching values (in case -v is used).

jsondiff supports large JSON files.