# diff-generator
Implementing file diff generation from scratch.

## Implementation

Uses a simple longest common subsequence tabulation algorithm to obtain an LCS matrix. From this the diff is generated through back-propagation.

## How to use

- The user is prompted (twice) for entering the paths to two files that need to be compared.
- The first file is treated as an "original", and the second file is treated as the "new"/"modified" version.
- A diff is printed after pressing the enter key, showing which lines in file 1 were deleted and which ones were inserted in file 2.

## Diff output format

The diff is printed out, line by line, giving information on the each singular change that occurred in order to transform file 1 to file 2.

For deletions, the format is to be interpreted as:

```
<LINE NUMBER IN FILE 1> (-) | <LINE CONTENT>
```

For insertions, the format is to be interpreted as:

```
<LINE NUMBER IN FILE 2> (+) | <LINE CONTENT>
```

The line content in each case is truncated after 50 characters for clear display.

## Example

![Screenshot 2025-04-05 030255](https://github.com/user-attachments/assets/26283115-00ab-49c4-b96f-d54878d83dca)
