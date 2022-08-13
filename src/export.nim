echo "NOOP"

proc add3*(i: int): int {.exportc, dynlib.} =
  echo "Nim: called"
  i + 3

proc strng*(i: cstring): cstring {.exportc, dynlib.} =
  echo i
  return "helloC"