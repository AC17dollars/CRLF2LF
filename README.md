# CRLF2LF
A command line tool to convert CRLF text files to LF text files or conversely. <br><br>
Usage: ./CRLF2LF &emsp; \[OPTION]....\[FILE]...<br><br>
Convert CRLF text files to LF text files.<br>Note: Specify file extension in filename<br><br>
Options:<br>
--help     &emsp; &emsp; &emsp;&emsp;     display this help and exit<br>
--version  &emsp;&emsp; &emsp;    output version information and exit<br>
--create-copy  &emsp; create a copy of the original file<br>
--crlf      &emsp;&emsp;&emsp;&emsp;&emsp;   convert LF to CRLF<br>
<br>
Eg: <br>
`./CRLF2LF foo.txt` &emsp; - Convert foo.txt into LF text file. <br>
`./CRLF2LF foo.c --crlf` &emsp; - Convert foo.c into CRLF C text file. <br>
`./CRLF2LF *.txt` &emsp; - Convert all text files in current directory to LF text file. <br>
<br>

## Installation
### Compilation
`gcc main.c -o CRLF2LF`

### Binaries
Check the release section for up to date binaries.

