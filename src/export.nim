echo "NOOP"

proc add3*(i: int): int {.exportc, dynlib.} =
  echo "Called"
  i + 3