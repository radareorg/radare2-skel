import r2papi
import std/strformat
import std/json

echo("Hello From Nim");

var r = r2papi.R2Papi()
var o = r.cmdj("ij")
var fileName = o["core"]["file"].str
echo (fmt"filename is: {fileName}")
