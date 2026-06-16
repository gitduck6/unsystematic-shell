# Unsystematic (Unix) Shell
Minimal unix shell with intentions of having simple and readible code.
## Current feature list:
| Feature                    | State           |
| -------------------------- | --------------- |
| Tokenization               | Good but not perfect |
| I/O redirection           | only > and <            |
| Pipes                      | Not implemented |  
| Sequential execution       | Not implemented | 
| Daemonisation of a command | Not Implemented |
| Some internal commands | cd, exit, set, and help |
| Scriptablity | None|
| Proper signal handling | Somewhat (doesnt die upon ctrl+c)|
| enviroment variable support| reading via $, and writing via set |
| Autofill via tab           | Unplanned       |

---

## Installation and usage:

```
make
./ush
```
as simple as that! :)
```
 % ls   
include  LICENSE  Makefile  README.md  src  ush
 % echo "HELLO WORLD!!!!" > out.txt
 % cat out.txt
HELLO WORLD!!!!
```

## More things about it:
This shell currently has no dependencies as far as im aware, i dont think i used any GNU extentions either so it should work in most unix-like systems.


![BSD beastie cause unix](https://media1.giphy.com/media/v1.Y2lkPTc5MGI3NjExbnhlNjN0djd3YXB0b3h6NHFoZTZnbG00bjFjdmM2ZXJobHNheWJocSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/dDwicM3uFUqfC/giphy.gif)

### License: 
[Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0)

i would really appreciate any recognition, preferably positive tho :sweat_smile:
so please dont be shy to like, send issues, or pull requests
